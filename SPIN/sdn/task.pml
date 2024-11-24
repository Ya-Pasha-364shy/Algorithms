#define TRUE 1

mtype = {
    PF_App,
    DF_App,
    PF_Controller,
    DF_Controller,
    PF_Channel1,
    DF_Channel1,
    ACK_Channel2,
    LOSS, // LOSS_Channel1, LOSS_Channel2
    ACK_Switch
}

int flow_entry_cont = 0;
int flow_entry_switch = 0;

byte state_App = 0;
byte state_Switch = 0;
byte state_Channel1 = 0;
byte state_Channel2 = 0;
byte state_Controller = 0;

chan ch1 = [0] of { mtype }
chan ch2 = [0] of { mtype }
chan ch3 = [0] of { mtype }
chan ch4 = [0] of { mtype }
chan maybe_lost_ch5 = [0] of { mtype }

proctype App()
{
    do
    :: (state_App == 0) -> {
        flow_entry_cont = 1;
        state_App = 1;
        ch1 ! PF_App;
      }
    :: (state_App == 1) -> {
        if
        :: flow_entry_cont <= 10 -> {
                flow_entry_cont = flow_entry_cont + 1;
                ch1 ! PF_App;
            }
        :: flow_entry_cont > 1 -> {
                flow_entry_cont = flow_entry_cont - 1;
                ch1 ! DF_App;
            }
        :: flow_entry_cont == 1 -> {
                flow_entry_cont = 0;
                ch1 ! DF_App;

                state_App = 0;
            }
        fi
      }
    od
}

proctype Controller()
{
    byte msg;

    do
    // Receive
    :: (state_Controller == 0) -> {
        ch1 ? msg;
        if
        :: (msg == PF_App) -> {
                state_Controller = 1;
            }
        :: (msg == DF_App) -> {
                state_Controller = 3;
            }
        fi
      }
    // Send or resend PostFlow
    :: (state_Controller == 1) -> {
        ch2 ! PF_Controller;

        state_Controller = 2;
      }
    // Check PostFlow on Loses
    :: (state_Controller == 2) -> {
        byte switch_feedback;

        do
        :: maybe_lost_ch5 ? switch_feedback -> {
            if
            :: (switch_feedback == ACK_Channel2) -> state_Controller = 0;
            :: (switch_feedback == LOSS) -> state_Controller = 1;
            fi

            break
        }
        :: timeout -> state_Controller = 1; break
        :: else -> skip
        od
      }
    // Send or resend DeleteFlow
    :: (state_Controller == 3) -> {
        ch2 ! DF_Controller;

        state_Controller = 4;
      }
    // Check DeleteFlow on Loses
    :: (state_Controller == 4) -> {
        byte switch_feedback;

        do
        :: maybe_lost_ch5 ? switch_feedback -> {
            if
            :: (switch_feedback == ACK_Channel2) -> state_Controller = 0;
            :: (switch_feedback == LOSS) -> state_Controller = 3;
            fi

            break
        }
        :: timeout -> state_Controller = 3; break
        else -> skip
        od
      }
    od
}

proctype Channel1()
{
    do
    // Receive
    :: (state_Channel1 == 0) -> {
        byte msg;
        ch2 ? msg;
        if
        :: (msg == PF_Controller) -> {
                state_Channel1 = 1;
            }
        :: (msg == DF_Controller) -> {
                state_Channel1 = 2;
            }
        fi
      }
    // Send PostFlow for Switch or Get LOSS
    :: (state_Channel1 == 1) -> {
        if
        :: TRUE -> ch3 ! PF_Channel1;
        :: TRUE -> skip
        fi
        state_Channel1 = 0;
      }
    // Send DeleteFlow for Switch or Get LOSS
    :: (state_Channel1 == 2) -> {
        if
        :: TRUE -> ch3 ! DF_Channel1;
        :: TRUE -> skip
        fi
        state_Channel1 = 0;
      }
    od
}

proctype Switch()
{
    do
    // Receive
    :: (state_Switch == 0) -> {
        byte msg;
        ch3 ? msg;
        if
        :: (msg == PF_Channel1) -> {
                flow_entry_switch = flow_entry_switch + 1;
            }
        :: (msg == DF_Channel1) -> {
                flow_entry_switch = flow_entry_switch - 1;
            }
        fi
        state_Switch = 1;
      }
    // Send ACK to Controller by Channel2
    :: (state_Switch == 1) -> {
        state_Switch = 0;
        ch4 ! ACK_Switch;
      }
    od
}

proctype Channel2() {
    do
    // Receive
    :: (state_Channel2 == 0) -> {
        byte msg;
        ch4 ? msg;
        if
        :: (msg == ACK_Switch) -> {
                state_Channel2 = 1;
            }
        fi
      }
    // Send ACK or get LOSS (в жизни за место LOSS по-идее ничего не должно отсылаться)
    :: (state_Channel2 == 1) -> {
        if
        :: TRUE -> maybe_lost_ch5 ! ACK_Channel2;
        :: TRUE -> maybe_lost_ch5 ! LOSS;
        fi
        state_Channel2 = 0;
      }
    od
}

init
{
    atomic {
        run App();
        run Controller();
        run Channel1();
        run Switch();
        run Channel2();
    }
}

ltl no_negative_rules {
    [](flow_entry_cont >= 0 && flow_entry_switch >= 0)
}

ltl no_deadlock {
    []<>(1)
}