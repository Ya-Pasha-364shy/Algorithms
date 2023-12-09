#ifndef TIMER_H
#define TIMER_H

#include "TimerTask.h"
#include "PhonerLine_sm.h"

namespace PhonerLine {

class PhonerLine;

class Timer
{
private:
	TimerTask * timerTask_;
	bool taskFullyCompleted_;

public:
	Timer() : taskFullyCompleted_(false)
	{
		timerTask_ = new TimerTask(TIMERTASK_TIMEOUT_3_SEC);
	}

	const bool getTimerTaskState()
	{
		return timerTask_->getTaskState();
	}

	bool & TaskState()
	{
		return taskFullyCompleted_;
	}

	const bool checkRunningStateTimer()
	{
		return timerTask_->timerTaskState();
	}

	bool & needStop()
	{
		return timerTask_->needStop();
	}

	const unsigned int ticksByFact()
	{
		return timerTask_->ticksByFact();
	}

	/* must be called if task isn't running rigth now */
	void reloadTimerTask()
	{
		delete timerTask_;
		timerTask_ = new TimerTask(TIMERTASK_TIMEOUT_3_SEC);
	}

	void startTimer(PhonerLineContext & context);

	/* stops the timer, returns number of "ticks" by fact */
	int stopTimer();

	~Timer()
	{
		if (timerTask_ != nullptr)
			delete timerTask_;
	}
};

} // namespace PhonerLine

#endif // TIMER_H
