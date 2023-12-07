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
		ctx.response() = "I";
	}
	else
	{
		ctx.response() = "nul";
	}
	return;
}

void PhonerLineFSM_Ready::Entry(PhonerLineContext& context)
{
	PhonerLine & ctx = context.getOwner();
	ctx.startTimer(context);
	return;
}

bool PhonerLineFSM_Ready::Exit(PhonerLineContext& context)
{
	PhonerLine & ctx = context.getOwner();
	unsigned ticksByFact = ctx.stopTimer();
	
	if (ticksByFact == TIMERTASK_TIMEOUT_3_SEC)
	{
		context.setState(PhonerLineFSM::Warning);
		return false;
	}
	else
	{
		return true;
	}
}

inline void redirectInputStimulusToWarning(PhonerLineContext& context)
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
		if (PhonerLineFSM::Ready.Exit(context))
		{
			ctx.disconnectedLine();
			context.setState(PhonerLineFSM::Idle);
		}
		else
		{
			return redirectInputStimulusToWarning(context);
		}
	}
	else if (streq(input_stimulus, VALID_NUMBER_STIMULUS))
	{
		if (PhonerLineFSM::Ready.Exit(context))
		{
			ctx.findConnection();
			context.setState(PhonerLineFSM::Conversation);
		}
		else
		{
			return redirectInputStimulusToWarning(context);
		}
	}
	else if (streq(input_stimulus, INVALID_NUMBER_STIMULUS))
	{
		if (PhonerLineFSM::Ready.Exit(context))
		{
			ctx.playMessage();
			context.setState(PhonerLineFSM::Warning);
		}
		else
		{
			return redirectInputStimulusToWarning(context);
		}
	}
	else if (streq(input_stimulus, TICK_STIMULUS))
	{
		/* Only for this state a transition to another state is provided by timeout.
		   Until the timeout occurs, we are in the same state with the "I" output */
		ctx.response() = "I";
		// ADD CHECK, THAT TASK IS STILL RUNNING
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
		// a loop
		ctx.slowBusyTone();
	}
	else if (streq(input_stimulus, ON_HOOK_STIMULUS))
	{
		ctx.disconnectedLine();
		context.setState(PhonerLineFSM::Idle);
	}
	else if (streq(input_stimulus, TICK_STIMULUS))
	{
		ctx.response() = "I";
	}
	else
	{
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
		// a loop
		ctx.continues();
	}
	else if (streq(input_stimulus, ON_HOOK_STIMULUS))
	{
		ctx.disconnectedLine();
		context.setState(PhonerLineFSM::Idle);
	}
	else if (streq(input_stimulus, TICK_STIMULUS))
	{
		ctx.response() = "I";
	}
	else
	{
		ctx.response() = "nul";
	}
}