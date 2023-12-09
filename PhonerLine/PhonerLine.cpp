#include "PhonerLine.h"

namespace PhonerLine {

/* methods-stimulus */
void PhonerLine::offHook()
{
	fsm_.offHook();
}
void PhonerLine::onHook()
{
	fsm_.onHook();
}
void PhonerLine::validNumber()
{
	fsm_.validNumber();
}
void PhonerLine::invalidNumber()
{
	fsm_.invalidNumber();
}
void PhonerLine::tick()
{
	fsm_.tick();
}

/* methods-reactions */
void PhonerLine::soundDialTone()
{
	response_ = "soundDialTone";
}
void PhonerLine::disconnectedLine()
{
	response_ = "disconnectedLine";
}
void PhonerLine::slowBusyTone()
{
	response_ = "slowBusyTone";
}
void PhonerLine::fastBusyTone()
{
	response_ = "fastBusyTone";
}
void PhonerLine::playMessage()
{
	response_ = "playMessage";
}
void PhonerLine::findConnection()
{
	response_ = "findConnection";
}
void PhonerLine::continues()
{
	response_ = "continues";
}
void PhonerLine::finish_tick(const unsigned int ticks_by_fact)
{
	response_ = std::to_string(ticks_by_fact) + "I";
}

void PhonerLine::startTimer(PhonerLineContext & context)
{
	timer_.startTimer(context);
}
int PhonerLine::stopTimer()
{
	int rc = timer_.stopTimer();
	if (rc == -1)
		std::cerr << "TimerTask already finished !" << std::endl;

	return rc;
}

}; // namespace PhonerLinew