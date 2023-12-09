#include "PhonerLine.h"

int main()
{
	PhonerLine::PhonerLine phonerLine_;

	std::cout << "Start state: " << phonerLine_.getContext().getState().getName() << std::endl;

	phonerLine_.offHook(); std::cout << "offHook/" << phonerLine_.response() << std::endl;
	// WE ARE IN `READY` STATE ALREADY.
	phonerLine_.offHook(); std::cout << "offHook/" << phonerLine_.response() << std::endl;
	// WE ARE IN `READY` STATE ALREADY

	const bool & waitingTaskFinished = phonerLine_.TaskState();
	while (not waitingTaskFinished)
	{
		if (phonerLine_.ticksByFact() == 2)
		{
			phonerLine_.validNumber();
		}
		else
		{
			phonerLine_.tick();
			// std::cout << "Responce for tick: " << phonerLine_.response() << std::endl;
		}
	}
	std::cout << "Responce after timeout: " << phonerLine_.response() << std::endl;

	std::cout << "Current state 1: " << phonerLine_.getContext().getState().getName() << std::endl;
	phonerLine_.validNumber(); std::cout << "validNumber/" << phonerLine_.response() << std::endl;

	std::cout << "Current state 2: " << phonerLine_.getContext().getState().getName() << std::endl;
	phonerLine_.onHook(); std::cout << "onHook/" << phonerLine_.response() << std::endl;

	std::cout << "Current state 3: " << phonerLine_.getContext().getState().getName() << std::endl;
	
	return EXIT_SUCCESS;
}
