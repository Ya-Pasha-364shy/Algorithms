#ifndef _H_PHONERLINE
#define _H_PHONERLINE

#include "PhonerLine_sm.h"
#include "Timer.h"

#include <string>

inline bool streq(std::string compared, std::string src)
{
	return 0 == compared.compare(src) ? true : false;
}

namespace PhonerLine {

class PhonerLine
{
private:
	PhonerLineContext fsm_;
	Timer timer_;

	std::string response_;

public:
	PhonerLine() : fsm_(*this) {}

	PhonerLineContext& getContext()
	{
		return fsm_;
	}
	std::string & response()
	{
		return response_;
	}

	/* methods-triggers */
	void offHook();
	void onHook();
	void validNumber();
	void invalidNumber();
	void tick();
	/* and implicit timeout event */

	/* methods-reactions */
	void soundDialTone();
	void disconnectedLine();
	void slowBusyTone();
	void fastBusyTone();
	void playMessage();
	void findConnection();
	void continues();
	void finish_tick(const unsigned int ticks_by_fact);

	/* starts a timer with task. Timeout 3 seconds. If interrupted received - stops run task slowly */
	void startTimer(PhonerLineContext & context);
	/* stops a timer with task, cleans data about task running too */
	int stopTimer();

	/* helpers-methods, that gives timer or timerTask actual state */
	const bool getTimerTaskState()
	{
		return timer_.getTimerTaskState();
	}
	const unsigned int ticksByFact()
	{
		return timer_.ticksByFact();
	}
	const bool checkRunningStateTimer()
	{
		return timer_.checkRunningStateTimer();
	}
	bool & TaskState()
	{
		return timer_.TaskState();
	}
	bool & stopped()
	{
		return timer_.needStop();
	}

	void reloadTimerTask()
	{
		return timer_.reloadTimerTask();
	}
};

}; // namespace PhonerLine

#endif // _H_PHONERLINE