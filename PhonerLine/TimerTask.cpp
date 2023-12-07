#include "TimerTask.h"

using namespace PhonerLine;

void TimerTask::timerTaskRun()
{
	while (timerSecond_ < secondsForTask_)
	{
		taskIsRunning_ = true;
		if (needToStop_) break;

		sleep(1);
		timerSecond_++;
	}
	if (needToStop_ != true and timerSecond_ == secondsForTask_)
	{
		taskIsReady_ = true;
		taskIsRunning_ = false;
	}
	else
	{
		std::cout << "CLEAN..." << std::endl;
		timerTaskClean();
	}
}

void TimerTask::timerTaskClean()
{
	taskIsRunning_ = false;
	taskIsReady_   = false;
}