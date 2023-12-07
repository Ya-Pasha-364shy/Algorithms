#include "PhonerLine.h"


int main(int argc, char * argv[])
{
	PhonerLine::PhonerLine obj;

	std::cout << "Start state: " << obj.getContext().getState().getName() << std::endl;

	obj.offHook(); std::cout << "offHook/" << obj.response() << std::endl;
	// WE ARE IN `READY` STATE ALREADY.
	obj.offHook(); std::cout << "offHook/" << obj.response() << std::endl;
	// WE ARE IN `READY` STATE ALREADY
	// obj.stopped() = true;
	// obj.validNumber(); std::cout << "validNumber/" << obj.response() << std::endl;

	sleep(1);
	const bool & waitingTaskFinished = obj.checkTaskState();
	while (not waitingTaskFinished and not obj.stopped())
	{
		std::cout << "Task for ticking is running, waiting..." << std::endl;
		// obj.stopped() = true;
	}

	// If timer isn't running, then it was very strange value...
	unsigned int rv = obj.ticksByFact();
	std::cout << "ticksByFact = " << rv << std::endl;

	std::cout << "Current state: " << obj.getContext().getState().getName() << std::endl;
		
	return EXIT_SUCCESS;
}
