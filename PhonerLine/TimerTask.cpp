#include "TimerTask.h"

using namespace PhonerLine;

void TimerTask::timerTaskRun()
{
	taskIsRunning_ = true;
	while (timerSecond_ < secondsForTask_ and not needToStop_)
	{
		timerSecond_++;
		sleep(1); // wait a second

		if (needToStop_)
		{
			taskIsRunning_ = false;
			break;
		}
	}
	if (needToStop_ != true and timerSecond_ == secondsForTask_)
	{
		taskIsReady_ = true;
	}
	else
	{
		needToStop_ = false;
	}
	taskIsRunning_ = false;
}

void TimerTask::timerTaskClean()
{
	taskIsRunning_ = false;
	taskIsReady_   = false;
}