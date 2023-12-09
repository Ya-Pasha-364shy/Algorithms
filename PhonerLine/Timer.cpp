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

		if (timerTask_->getTaskState() == true) // If task is ready
		{
			/* if timer is fully completed, then change state to `Warning` */
			context.setState(PhonerLineFSM::Warning);
		}
		context.getOwner().finish_tick(ticksByFact());
		taskFullyCompleted_ = true;

	});
	parent_background_load.detach();
}

int Timer::stopTimer()
{
	int rv = -1;
	
	if (timerTask_ != nullptr)
	{
		timerTask_->needStop() = true;
		rv = timerTask_->ticksByFact();

		/* sync with thread, that runs or stops a task */
		while (not taskFullyCompleted_);

		delete timerTask_;
		timerTask_ = nullptr;
	}

	return rv;
}