#ifndef TIMERTASK_H
#define TIMERTASK_H

#include <unistd.h>
#include <iostream>

#define TIMERTASK_TIMEOUT_3_SEC 3

namespace PhonerLine {

class TimerTask
{
private:
	bool taskIsReady_;
	bool needToStop_;
	bool taskIsRunning_;

	int secondsForTask_;
	unsigned int timerSecond_;

public:
	TimerTask()
	{
		taskIsReady_    = false;
		needToStop_     = false;
		taskIsRunning_  = false;
		timerSecond_    = 0;
		secondsForTask_ = 0;
	}

	TimerTask(int * seconds)
	{
		taskIsReady_    = false;
		needToStop_     = false;
		taskIsRunning_  = false;
		timerSecond_    = 0;
		secondsForTask_ = *seconds;
	}
	TimerTask(int seconds)
	{
		taskIsReady_    = false;
		needToStop_     = false;
		taskIsRunning_  = false;
		timerSecond_    = 0;
		secondsForTask_ = seconds;
	}

	const bool getTaskState()
	{
		return taskIsReady_;
	}

	const unsigned int ticksByFact()
	{
		return timerSecond_;
	}

	bool & checkTaskState()
	{
		return taskIsRunning_;
	}

	bool & needStop()
	{
		return needToStop_;
	}

	void timerTaskClean();
	void timerTaskRun();

	~TimerTask() = default;
};

} // namespace PhonerLine

#endif // TIMERTASK_H
