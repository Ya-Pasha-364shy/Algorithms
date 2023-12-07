#include "PhonerLine.h"

namespace PhonerLine {

/* методы-стимулы */
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

/* методы-реакции */
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

void PhonerLine::finish_tick()
{
	response_ = "3I";
}

void PhonerLine::startTimer(PhonerLineContext & context)
{
	timer_.startTimer(context);
}

int PhonerLine::stopTimer()
{
	return timer_.stopTimer();
}

}; // namespace PhonerLinew