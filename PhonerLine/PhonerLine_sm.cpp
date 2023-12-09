#include "PhonerLine_sm.h"
#include "PhonerLine.h"

#include <unistd.h>

#define TICK_STIMULUS "I"
#define ON_HOOK_STIMULUS "onHook"
#define OFF_HOOK_STIMULUS "offHook"
#define VALID_NUMBER_STIMULUS "validNumber"
#define INVALID_NUMBER_STIMULUS "invalidNumber"

pid_t timerTask_pid;

using namespace PhonerLine;

// Static class declarations.
PhonerLineFSM_Conversation PhonerLineFSM::Conversation("Conversation", convesation_state_ID);
PhonerLineFSM_Warning PhonerLineFSM::Warning("Warning", warning_state_ID);
PhonerLineFSM_Ready PhonerLineFSM::Ready("Ready", ready_state_ID);
PhonerLineFSM_Idle PhonerLineFSM::Idle("Idle", idle_state_ID);

void PhonerLineState::Default(PhonerLineContext& context)
{
	throw (
	    TransitionUndefinedException(
	        context.getState().getName(),
	        context.getTransition()));

	return;
}

void PhonerLineFSM_Idle::ReceiveStimulusAndDoTransition(PhonerLineContext& context)
{
	const std::string input_stimulus = context.stimulus();
	if (input_stimulus.empty())
		return;

	PhonerLine & ctx = context.getOwner();

	if (streq(input_stimulus, OFF_HOOK_STIMULUS))
	{
		ctx.soundDialTone();
		context.setState(PhonerLineFSM::Ready);
		PhonerLineFSM::Ready.Entry(context);
	}
	else if (streq(input_stimulus, TICK_STIMULUS))
	{
		// a loop into itself
		ctx.response() = "I";
	}
	else
	{
		/* nothing */
		ctx.response() = "nul";
	}
	return;
}

void PhonerLineFSM_Ready::Entry(PhonerLineContext& context)
{
	PhonerLine & ctx = context.getOwner();
	if (ctx.checkRunningStateTimer() == false)
	{
		ctx.reloadTimerTask();
		ctx.startTimer(context);
	}
	else
	{
		std::cerr << "Unable to reload timer with timertask, because its already running !" << std::endl;
	}
	return;
}

int PhonerLineFSM_Ready::Exit(PhonerLineContext& context)
{
	PhonerLine & ctx = context.getOwner();
	int ticksByFact = ctx.stopTimer();
	
	if (ticksByFact == TIMERTASK_TIMEOUT_3_SEC)
	{
		context.setState(PhonerLineFSM::Warning);
	}
	return ticksByFact;
}

inline void redirectInputStimulusToWarningState(PhonerLineContext& context)
{
	context.setState(PhonerLineFSM::Warning);
	PhonerLineFSM::Warning.ReceiveStimulusAndDoTransition(context);
	return;
}

void PhonerLineFSM_Ready::ReceiveStimulusAndDoTransition(PhonerLineContext& context)
{
	const std::string input_stimulus = context.stimulus();
	if (input_stimulus.empty())
		return;

	PhonerLine & ctx = context.getOwner();

	if (streq(input_stimulus, ON_HOOK_STIMULUS))
	{
		if (PhonerLineFSM::Ready.Exit(context) != TIMERTASK_TIMEOUT_3_SEC)
		{
			ctx.disconnectedLine();
			context.setState(PhonerLineFSM::Idle);
		}
		else
		{
			return redirectInputStimulusToWarningState(context);
		}
	}
	else if (streq(input_stimulus, VALID_NUMBER_STIMULUS))
	{
		if (PhonerLineFSM::Ready.Exit(context) != TIMERTASK_TIMEOUT_3_SEC)
		{
			ctx.findConnection();
			context.setState(PhonerLineFSM::Conversation);
		}
		else
		{
			return redirectInputStimulusToWarningState(context);
		}
	}
	else if (streq(input_stimulus, INVALID_NUMBER_STIMULUS))
	{
		if (PhonerLineFSM::Ready.Exit(context) != TIMERTASK_TIMEOUT_3_SEC)
		{
			ctx.playMessage();
			context.setState(PhonerLineFSM::Warning);
		}
		else
		{
			return redirectInputStimulusToWarningState(context);
		}
	}
	else if (streq(input_stimulus, TICK_STIMULUS))
	{
		/* Only for this state a transition to another state is provided by timeout.
		   Until the timeout occurs, we are in the same state with the "I" output */
		ctx.response() = "I";
	}
	else
	{
		ctx.response() = "nul";
	}
}

void PhonerLineFSM_Warning::ReceiveStimulusAndDoTransition(PhonerLineContext& context)
{
	const std::string input_stimulus = context.stimulus();
	if (input_stimulus.empty())
		return;

	PhonerLine & ctx = context.getOwner();

	if (streq(input_stimulus, VALID_NUMBER_STIMULUS) or streq(input_stimulus, INVALID_NUMBER_STIMULUS))
	{
		// a loop into itself
		ctx.slowBusyTone();
	}
	else if (streq(input_stimulus, ON_HOOK_STIMULUS))
	{
		ctx.disconnectedLine();
		context.setState(PhonerLineFSM::Idle);
	}
	else if (streq(input_stimulus, TICK_STIMULUS))
	{
		// a loop into itself
		ctx.response() = "I";
	}
	else
	{
		/* nothing */
		ctx.response() = "nul";
	}
}

void PhonerLineFSM_Conversation::ReceiveStimulusAndDoTransition(PhonerLineContext& context)
{
	const std::string input_stimulus = context.stimulus();
	if (input_stimulus.empty())
		return;

	PhonerLine & ctx = context.getOwner();

	if (streq(input_stimulus, VALID_NUMBER_STIMULUS) or streq(input_stimulus, INVALID_NUMBER_STIMULUS))
	{
		// a loop into itself
		ctx.continues();
	}
	else if (streq(input_stimulus, ON_HOOK_STIMULUS))
	{
		ctx.disconnectedLine();
		context.setState(PhonerLineFSM::Idle);
	}
	else if (streq(input_stimulus, TICK_STIMULUS))
	{
		// a loop into itself
		ctx.response() = "I";
	}
	else
	{
		/* nothing */
		ctx.response() = "nul";
	}
}