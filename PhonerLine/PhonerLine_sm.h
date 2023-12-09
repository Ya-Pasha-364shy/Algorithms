#ifndef _H_PHONERLINE_SM
#define _H_PHONERLINE_SM

#define SMC_USES_IOSTREAMS

#include "statemap.h"

namespace PhonerLine {

#define convesation_state_ID 0
#define warning_state_ID     1
#define ready_state_ID       2
#define idle_state_ID        3

class PhonerLineFSM;
class PhonerLineFSM_Conversation;
class PhonerLineFSM_Warning;
class PhonerLineFSM_Ready;
class PhonerLineFSM_Idle;
class PhonerLineFSM_Default;
class PhonerLineState;
class PhonerLineContext;
class PhonerLine;

class PhonerLineFSM
{
public:
	static PhonerLineFSM_Conversation Conversation;
	static PhonerLineFSM_Warning Warning;
	static PhonerLineFSM_Ready Ready;
	static PhonerLineFSM_Idle Idle;
};

class PhonerLineState : public State
{
public:
	PhonerLineState(const char * name, int stateId)
	: State(name, stateId) {};

	virtual void Entry(PhonerLineContext &) {};
	virtual int Exit(PhonerLineContext  &) { return true; };

	virtual void ReceiveStimulusAndDoTransition(PhonerLineContext &) {};

protected:
	virtual void Default(PhonerLineContext & context);
};

class PhonerLineFSM_Default : public PhonerLineState
{
public:
	PhonerLineFSM_Default(const char * name, int stateId)
	: PhonerLineState(name, stateId) {};
};

class PhonerLineFSM_Conversation final : public PhonerLineFSM_Default
{
public:
	PhonerLineFSM_Conversation(const char * name, int stateId)
	: PhonerLineFSM_Default(name, stateId) {};

	void ReceiveStimulusAndDoTransition(PhonerLineContext &) override;
};

class PhonerLineFSM_Warning final : public PhonerLineFSM_Default
{
public:
	PhonerLineFSM_Warning(const char * name, int stateId)
	: PhonerLineFSM_Default(name, stateId) {};

	void ReceiveStimulusAndDoTransition(PhonerLineContext &) override;

};

class PhonerLineFSM_Ready final : public PhonerLineFSM_Default
{
public:
	PhonerLineFSM_Ready(const char * name, int stateId)
	: PhonerLineFSM_Default(name, stateId) {};

	void Entry(PhonerLineContext &) override;
	int Exit(PhonerLineContext  &) override;

	void ReceiveStimulusAndDoTransition(PhonerLineContext &) override;
};

class PhonerLineFSM_Idle final : public PhonerLineFSM_Default
{
public:
	PhonerLineFSM_Idle(const char * name, int stateId)
	: PhonerLineFSM_Default(name, stateId) {};

	void ReceiveStimulusAndDoTransition(PhonerLineContext &) override;
};

class PhonerLineContext final : public FSMContext
{
public:
	PhonerLineContext(PhonerLine& owner)
	: _owner(owner), _stimulus("")
	{
		setState(PhonerLineFSM::Idle);
		PhonerLineFSM::Idle.ReceiveStimulusAndDoTransition(*this);
	};

	PhonerLine& getOwner() const
	{
		return _owner;
	};

	PhonerLineState& getState() const
	{
		if (_state == NULL)
		{
			throw StateUndefinedException();
		}
		return (dynamic_cast<PhonerLineState&>(*_state));
	};

	void makeTransitionByStimulus()
	{
		getState().ReceiveStimulusAndDoTransition(*this);
	}

	/* методы-стимулы */
	void offHook()
	{
		_stimulus = "offHook";
		makeTransitionByStimulus();
	}
	void onHook()
	{
		_stimulus = "onHook";
		makeTransitionByStimulus();
	}
	void validNumber()
	{
		_stimulus = "validNumber";
		makeTransitionByStimulus();
	}
	void invalidNumber()
	{
		_stimulus = "invalidNumber";
		makeTransitionByStimulus();
	}
	void tick()
	{
		_stimulus = "I";
		makeTransitionByStimulus();
	}

	const std::string stimulus() const
	{
		return _stimulus;
	}

private:
	std::string _stimulus;
	PhonerLine & _owner;
};

}; // namespace PhonerLine

#endif // _H_PHONERLINE_SM
