PhonerLine_StateMachine:
	c++ -c -std=c++20 PhonerLine_sm.cpp

PhonerLine_Automata: PhonerLine_StateMachine
	c++ -c -std=c++20 PhonerLine.cpp

PhonerLine_Sample: PhonerLine_Automata
	c++ -c -std=c++20 PhonerLineSample.cpp

Timers:
	c++ -c -std=c++20 Timer.cpp
	c++ -c -std=c++20 TimerTask.cpp

all: PhonerLine_Sample Timers
	c++ PhonerLineSample.o PhonerLine.o PhonerLine_sm.o Timer.o TimerTask.o -o PhonerLine_FSM_Sample
	rm *.o

test: PhonerLine_Automata Timers
	c++ -c -std=c++20 PhonerLine_gtest.cc
	c++ -lgtest -lgtest_main  PhonerLine_gtest.o PhonerLine.o PhonerLine_sm.o Timer.o TimerTask.o -o PhonerLine_FSM_test
	rm *.o

clean:
	rm -f *.o PhonerLine_FSM_Sample PhonerLine_FSM_test