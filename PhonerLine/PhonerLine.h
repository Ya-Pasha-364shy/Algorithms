#ifndef _H_PHONERLINE
#define _H_PHONERLINE

#include "PhonerLine_sm.h"
#include "Timer.h"

#include <string>

inline bool streq(std::string compared, std::string src)
{
	return 0 == compared.compare(src) ? true : false;
}

namespace PhonerLine {

class PhonerLine
{
private:
	/* чтобы понимать в каком состоянии мы находимся сейчас */
	PhonerLineContext fsm_;
	Timer timer_;

	std::string response_;

public:
	PhonerLine() : fsm_(*this) {}

	PhonerLineContext& getContext()
	{
		return fsm_;
	}
	std::string & response()
	{
		return response_;
	}

	/* methods-triggers */
	void offHook();
	void onHook();
	void validNumber();
	void invalidNumber();
	/* and implicit timeout event */

	/* methods-reactions */
	void soundDialTone();
	void disconnectedLine();
	void slowBusyTone();
	void fastBusyTone();
	void playMessage();
	void findConnection();
	void continues();
	void finish_tick();

	/* запускает таймер с задачей - прождать 3 секунды, может прерваться внешним событием */
	void startTimer(PhonerLineContext & context);
	/* останавливает таймер и очищает задание, возвращая при этом количество тиков по факту */
	int stopTimer();

	/* методы-помощник, отдающий состояние таймера */
	const bool getTimerTaskState()
	{
		return timer_.getTimerTaskState();
	}

	const unsigned int ticksByFact()
	{
		return timer_.ticksByFact();
	}

	bool & stopped()
	{
		return timer_.needStop();
	}

	const bool & checkTaskState()
	{
		return timer_.checkTaskState();
	}
};

}; // namespace PhonerLine

#endif // _H_PHONERLINE