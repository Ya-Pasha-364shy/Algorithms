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
	};

	const bool getTimerTaskState()
	{
		return timerTask_->getTaskState();
	}

	const bool & checkTaskState()
	{
		return taskFullyCompleted_;
	}

	bool & needStop()
	{
		return timerTask_->needStop();
	}

	const unsigned int ticksByFact()
	{
		return timerTask_->ticksByFact();
	}

	void startTimer(PhonerLineContext & context);
	/* останавливает таймер, возвращая количество тиков по факту */
	int stopTimer();

	~Timer() {}
};

} // namespace PhonerLine

#endif // TIMER_H
