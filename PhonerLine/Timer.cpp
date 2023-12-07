#include "Timer.h"
#include "PhonerLine.h"
#include <new>
#include <thread>

using namespace PhonerLine;

void Timer::startTimer(PhonerLineContext & context)
{	
	std::thread parent_background_load([&]
	{
		std::thread background_loader([&]
		{
			timerTask_->timerTaskRun();
		});
		background_loader.join();
		if (timerTask_->getTaskState())
		{
			/* if timer is fully completed, then change state to `Warning` */
			context.getOwner().finish_tick();
			context.setState(PhonerLineFSM::Warning);
		}
		taskFullyCompleted_ = true;
	});
	parent_background_load.detach();
}

int Timer::stopTimer()
{
	int rv = -1;
	
	if (timerTask_)
	{
		timerTask_->needStop() = true;
		rv = timerTask_->ticksByFact();

		delete timerTask_;
	}

	return rv;
}