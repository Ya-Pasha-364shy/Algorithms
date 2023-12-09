#include <gtest/gtest.h>
#include "PhonerLine.h"

namespace test {

class PhonerLineTest : public testing::Test
{
protected:
	PhonerLineTest()
	{
		ticks_on_state = TIMERTASK_TIMEOUT_3_SEC;
	}
	void setTicksByValue(int value)
	{
		ticks_on_state = value;
	}

	const std::string GetNameState()
	{
		return PhonerLineTest_.getContext().getState().getName();
	}
	const int GetStateID()
	{
		return PhonerLineTest_.getContext().getState().getId();
	}
	const std::string GetResponse()
	{
		return PhonerLineTest_.response();
	}

	// start state is always "Idle" state
	PhonerLine::PhonerLine PhonerLineTest_;
	int ticks_on_state;
};

// TEST_F(PhonerLineTest, FirstStateIsAlwaysIDLE)
// {
// 	ASSERT_EQ(GetStateID(), idle_state_ID) << "invalid state id for state \"" << GetNameState() << "\"" << std::endl;
// 	EXPECT_EQ(GetNameState(), "Idle");
// }

TEST_F(PhonerLineTest, testSequence1)
{
	// INPUT-OUTPUT TEST SEQUENCE: I/I I/I I/I validNumber/nul
	auto i = 0;
	ASSERT_EQ(GetStateID(), idle_state_ID) << "invalid state id for IDLE state" << std::endl;
	for (; i < ticks_on_state; i++)
	{
		// already in IDLE State always
		PhonerLineTest_.tick();
		ASSERT_EQ(GetResponse(), "I");
	}
	ASSERT_EQ(i, ticks_on_state);

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "nul");
}

TEST_F(PhonerLineTest, testSequence2)
{
	// INPUT-OUTPUT TEST SEQUENCE: I/I onHook/nul
	PhonerLineTest_.tick();
	ASSERT_EQ(GetResponse(), "I");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "nul");
}

TEST_F(PhonerLineTest, testSequence3)
{
	// INPUT-OUTPUT TEST SEQUENCE: invalidNumber/nul I/I I/I validNumber/nul
	PhonerLineTest_.invalidNumber();
	ASSERT_EQ(GetResponse(), "nul");

	setTicksByValue(2);

	for (int i = 0; i < ticks_on_state; i++)
	{
		PhonerLineTest_.tick();
		ASSERT_EQ(GetResponse(), "I");
	}

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "nul");
}

TEST_F(PhonerLineTest, testSequence4)
{
	// INPUT-OUTPUT TEST SEQUENCE: validNumber/nul I/I I/I validNumber/nul
	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "nul");

	setTicksByValue(2);

	for (int i = 0; i < ticks_on_state; i++)
	{
		PhonerLineTest_.tick();
		ASSERT_EQ(GetResponse(), "I");
	}

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "nul");
}

TEST_F(PhonerLineTest, testSequence5)
{
	// INPUT-OUTPUT TEST SEQUENCE: validNumber/nul onHook/nul
	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "nul");

	PhonerLineTest_.onHook();
	ASSERT_EQ(GetResponse(), "nul");
}

TEST_F(PhonerLineTest, testSequence6)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone I/I I/I I/I I/I validNumber/slowBusyTone
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	const bool & taskFinished = PhonerLineTest_.TaskState();
	while (not taskFinished); // I/I I/I I/I === "3I"
	ASSERT_EQ(GetResponse(), "3I");
	// we are in "Warning" state now (after timeout 3 sec)
	ASSERT_EQ(GetNameState(), "Warning");

	// input stimulus separate from the timer
	PhonerLineTest_.tick();
	ASSERT_EQ(GetResponse(), "I");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "slowBusyTone");

	// after loop we are back to this state too
	ASSERT_EQ(GetNameState(), "Warning");
}

TEST_F(PhonerLineTest, testSequence7)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone I/I I/I I/I validNumber/slowBusyTone
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	const bool & taskFinished = PhonerLineTest_.TaskState();
	while (not taskFinished); // I/I I/I I/I === "3I"
	ASSERT_EQ(GetResponse(), "3I");
	ASSERT_EQ(GetNameState(), "Warning");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "slowBusyTone");

	ASSERT_EQ(GetNameState(), "Warning");
}

TEST_F(PhonerLineTest, testSequence8)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone I/I I/I invalidNumber/playMessage I/I I/I validNumber/slowBusyTone
	setTicksByValue(2);
	
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	const bool & taskFinished = PhonerLineTest_.TaskState();
	while (not taskFinished)
	{
		if (PhonerLineTest_.ticksByFact() != ticks_on_state) // I/I I/I === "2I"
		{
			PhonerLineTest_.tick();
			ASSERT_EQ(GetResponse(), "I");
		}
		else
		{
			PhonerLineTest_.invalidNumber();
		}
	}
	ASSERT_EQ(GetResponse(), "playMessage");
	ASSERT_EQ(GetNameState(), "Warning");

	for (auto i = 0; i < ticks_on_state; i++)
	{
		PhonerLineTest_.tick();
		ASSERT_EQ(GetResponse(), "I");
	}
	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "slowBusyTone");
}

TEST_F(PhonerLineTest, testSequence9)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone I/I I/I invalidNumber/playMessage validNumber/slowBusyTone
	setTicksByValue(2);
	
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	const bool & taskFinished = PhonerLineTest_.TaskState();
	while (not taskFinished)
	{
		if (PhonerLineTest_.ticksByFact() != ticks_on_state) // I/I I/I === "2I"
		{
			PhonerLineTest_.tick();
			ASSERT_EQ(GetResponse(), "I");
		}
		else
		{
			PhonerLineTest_.invalidNumber();
		}
	}
	ASSERT_EQ(GetResponse(), "playMessage");
	
	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "slowBusyTone");

	ASSERT_EQ(GetNameState(), "Warning");
}

TEST_F(PhonerLineTest, testSequence10)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone I/I I/I invalidNumber/playMessage onHook/disconnectedLine
	setTicksByValue(2);
	
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	const bool & taskFinished = PhonerLineTest_.TaskState();
	while (not taskFinished)
	{
		if (PhonerLineTest_.ticksByFact() != ticks_on_state) // I/I I/I === "2I"
		{
			PhonerLineTest_.tick();
		}
		else
		{
			PhonerLineTest_.invalidNumber();
		}
	}
	ASSERT_EQ(GetResponse(), "playMessage");
	ASSERT_EQ(GetNameState(), "Warning");

	PhonerLineTest_.onHook();
	ASSERT_EQ(GetResponse(), "disconnectedLine");
	ASSERT_EQ(GetNameState(), "Idle");
}

TEST_F(PhonerLineTest, testSequence11)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone I/I I/I invalidNumber/playMessage onHook/disconnectedLine
	setTicksByValue(2);
	
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	const bool & taskFinished = PhonerLineTest_.TaskState();
	while (not taskFinished)
	{
		if (PhonerLineTest_.ticksByFact() != ticks_on_state) // I/I I/I === "2I"
		{
			PhonerLineTest_.tick();
			ASSERT_EQ(GetResponse(), "I");
		}
		else
		{
			PhonerLineTest_.invalidNumber();
		}
	}
	ASSERT_EQ(GetResponse(), "playMessage");

	ASSERT_EQ(GetNameState(), "Warning");

	PhonerLineTest_.onHook();
	ASSERT_EQ(GetResponse(), "disconnectedLine");
	ASSERT_EQ(GetNameState(), "Idle");
}


TEST_F(PhonerLineTest, testSequence12)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone I/I I/I validNumber/findConnection I/I validNumber/continues
	setTicksByValue(2);
	
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	const bool & taskFinished = PhonerLineTest_.TaskState();
	while (not taskFinished)
	{
		if (PhonerLineTest_.ticksByFact() != ticks_on_state) // I/I I/I === "2I"
		{
			PhonerLineTest_.tick();
			ASSERT_EQ(GetResponse(), "I");
		}
		else
		{
			PhonerLineTest_.validNumber();
		}
	}
	ASSERT_EQ(GetResponse(), "findConnection");
	ASSERT_EQ(GetNameState(), "Conversation");

	PhonerLineTest_.tick();
	ASSERT_EQ(GetResponse(), "I");

	PhonerLineTest_.validNumber();
	// a loop to itself
	ASSERT_EQ(GetResponse(), "continues");
	ASSERT_EQ(GetNameState(), "Conversation");
}

TEST_F(PhonerLineTest, testSequence13)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone I/I I/I validNumber/findConnection onHook/disconnectedLine
	setTicksByValue(2);
	
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	const bool & taskFinished = PhonerLineTest_.TaskState();
	while (not taskFinished)
	{
		if (PhonerLineTest_.ticksByFact() != ticks_on_state) // I/I I/I === "2I"
		{
			PhonerLineTest_.tick();
			ASSERT_EQ(GetResponse(), "I");
		}
		else
		{
			PhonerLineTest_.validNumber();
		}
	}
	ASSERT_EQ(GetResponse(), "findConnection");

	PhonerLineTest_.onHook();
	ASSERT_EQ(GetResponse(), "disconnectedLine");
	ASSERT_EQ(GetNameState(), "Idle");
}

TEST_F(PhonerLineTest, testSequence14)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone I/I I/I offHook/nul I/I validNumber/slowBusyTone
	setTicksByValue(2);
	
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	const bool & taskFinished = PhonerLineTest_.TaskState();
	while (not taskFinished)
	{
		if (PhonerLineTest_.ticksByFact() == ticks_on_state) // I/I I/I === "2I"
		{
			// does not affect the progress of the timer.
			PhonerLineTest_.offHook();
			ASSERT_EQ(GetResponse(), "nul");
		}
	}
	ASSERT_EQ(GetResponse(), "3I");
	ASSERT_EQ(GetNameState(), "Warning");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "slowBusyTone");
	// a loop to itself
	ASSERT_EQ(GetNameState(), "Warning");
}

TEST_F(PhonerLineTest, testSequence15)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone I/I I/I offHook/nul onHook/disconnectedLine
	setTicksByValue(2);
	
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	const bool & taskFinished = PhonerLineTest_.TaskState();
	while (not taskFinished)
	{
		if (PhonerLineTest_.ticksByFact() != ticks_on_state) // I/I I/I === "2I"
		{
			// does not affect the progress of the timer.
			PhonerLineTest_.tick();
			ASSERT_EQ(GetResponse(), "I");
		}
		else
		{
			// does not affect the progress of the timer.
			PhonerLineTest_.offHook();
			ASSERT_EQ(GetResponse(), "nul");
			// make affect the progress of the timer.
			PhonerLineTest_.onHook();
		}
	}
	ASSERT_EQ(GetResponse(), "disconnectedLine");
	ASSERT_EQ(GetNameState(), "Idle");
}

TEST_F(PhonerLineTest, testSequence16)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone I/I I/I onHook/disconnectedLine I/I validNumber/nul
	setTicksByValue(2);
	
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	const bool & taskFinished = PhonerLineTest_.TaskState();
	while (not taskFinished)
	{
		if (PhonerLineTest_.ticksByFact() != ticks_on_state) // I/I I/I === "2I"
		{
			// does not affect the progress of the timer.
			PhonerLineTest_.tick();
			ASSERT_EQ(GetResponse(), "I");
		}
		else
		{
			PhonerLineTest_.onHook();
		}
	}
	ASSERT_EQ(GetResponse(), "disconnectedLine");
	PhonerLineTest_.tick();
	ASSERT_EQ(GetResponse(), "I");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "nul");

	ASSERT_EQ(GetNameState(), "Idle");
}

TEST_F(PhonerLineTest, testSequence17)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone I/I I/I onHook/disconnectedLine onHook/nul
	setTicksByValue(2);
	
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	const bool & taskFinished = PhonerLineTest_.TaskState();
	while (not taskFinished)
	{
		if (PhonerLineTest_.ticksByFact() != ticks_on_state) // I/I I/I === "2I"
		{
			// does not affect the progress of the timer.
			PhonerLineTest_.tick();
			ASSERT_EQ(GetResponse(), "I");
		}
		else
		{
			PhonerLineTest_.onHook();
		}
	}
	ASSERT_EQ(GetResponse(), "disconnectedLine");
	ASSERT_EQ(GetNameState(), "Idle");

	PhonerLineTest_.onHook();
	ASSERT_EQ(GetResponse(), "nul");

	ASSERT_EQ(GetNameState(), "Idle");
}

TEST_F(PhonerLineTest, testSequence18)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone I/I invalidNumber/playMessage I/I validNumber/slowBusyTone
	setTicksByValue(2);
	
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	const bool & taskFinished = PhonerLineTest_.TaskState();
	while (not taskFinished)
	{
		if (PhonerLineTest_.ticksByFact() != ticks_on_state) // I/I I/I === "2I"
		{
			// does not affect the progress of the timer.
			PhonerLineTest_.tick();
			ASSERT_EQ(GetResponse(), "I");
		}
		else
		{
			PhonerLineTest_.onHook();
		}
	}
	ASSERT_EQ(GetResponse(), "disconnectedLine");
	ASSERT_EQ(GetNameState(), "Idle");

	PhonerLineTest_.onHook();
	ASSERT_EQ(GetResponse(), "nul");

	ASSERT_EQ(GetNameState(), "Idle");
}

TEST_F(PhonerLineTest, testSequence19)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone I/I validNumber/findConnection I/I validNumber/continues
	setTicksByValue(1);
	
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	const bool & taskFinished = PhonerLineTest_.TaskState();
	while (not taskFinished)
	{
		if (PhonerLineTest_.ticksByFact() != ticks_on_state) // I/I
		{
			// does not affect the progress of the timer.
			PhonerLineTest_.tick();
			ASSERT_EQ(GetResponse(), "I");
		}
		else
		{
			PhonerLineTest_.validNumber();
		}
	}
	ASSERT_EQ(GetResponse(), "findConnection");
	ASSERT_EQ(GetNameState(), "Conversation");

	PhonerLineTest_.tick();
	ASSERT_EQ(GetResponse(), "I");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "continues");

	ASSERT_EQ(GetNameState(), "Conversation");
}

TEST_F(PhonerLineTest, testSequence20)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone I/I offHook/nul I/I validNumber/findConnection
	setTicksByValue(2);
	
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	const bool & taskFinished = PhonerLineTest_.TaskState();
	while (not taskFinished)
	{
		if (PhonerLineTest_.ticksByFact() == 1)
		{
			// does not affect the progress of the timer.
			PhonerLineTest_.tick();
			ASSERT_EQ(GetResponse(), "I");
			PhonerLineTest_.offHook();
			ASSERT_EQ(GetResponse(), "nul");
		}
		if (PhonerLineTest_.ticksByFact() == ticks_on_state) // I/I
		{
			PhonerLineTest_.tick();
			ASSERT_EQ(GetResponse(), "I");
			PhonerLineTest_.validNumber();
		}
	}
	ASSERT_EQ(GetResponse(), "findConnection");
	ASSERT_EQ(GetNameState(), "Conversation");
}

TEST_F(PhonerLineTest, testSequence21)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone I/I onHook/disconnectedLine I/I validNumber/nul
	setTicksByValue(1);
	
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	const bool & taskFinished = PhonerLineTest_.TaskState();
	while (not taskFinished)
	{
		if (PhonerLineTest_.ticksByFact() != ticks_on_state) // I/I
		{
			PhonerLineTest_.tick();
			ASSERT_EQ(GetResponse(), "I");
		}
		else
		{
			PhonerLineTest_.onHook();
		}
	}
	ASSERT_EQ(GetResponse(), "disconnectedLine");
	ASSERT_EQ(GetNameState(), "Idle");

	PhonerLineTest_.tick();
	ASSERT_EQ(GetResponse(), "I");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "nul");

	ASSERT_EQ(GetNameState(), "Idle");
}

TEST_F(PhonerLineTest, testSequence22)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone invalidNumber/playMessage I/I validNumber/slowBusyTone
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	PhonerLineTest_.invalidNumber();
	ASSERT_EQ(GetResponse(), "playMessage");
	ASSERT_EQ(GetNameState(), "Warning");

	PhonerLineTest_.tick();
	ASSERT_EQ(GetResponse(), "I");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "slowBusyTone");

	ASSERT_EQ(GetNameState(), "Warning");
}

TEST_F(PhonerLineTest, testSequence23)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone invalidNumber/playMessage invalidNumber/slowBusyTone I/I validNumber/slowBusyTone
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	PhonerLineTest_.invalidNumber();
	ASSERT_EQ(GetResponse(), "playMessage");
	ASSERT_EQ(GetNameState(), "Warning");

	PhonerLineTest_.invalidNumber();
	ASSERT_EQ(GetResponse(), "slowBusyTone");

	PhonerLineTest_.tick();
	ASSERT_EQ(GetResponse(), "I");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "slowBusyTone");

	ASSERT_EQ(GetNameState(), "Warning");
}

TEST_F(PhonerLineTest, testSequence24)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone invalidNumber/playMessage validNumber/slowBusyTone validNumber/slowBusyTone
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	PhonerLineTest_.invalidNumber();
	ASSERT_EQ(GetResponse(), "playMessage");
	ASSERT_EQ(GetNameState(), "Warning");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "slowBusyTone");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "slowBusyTone");

	ASSERT_EQ(GetNameState(), "Warning");
}

TEST_F(PhonerLineTest, testSequence25)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone invalidNumber/playMessage offHook/nul validNumber/slowBusyTone
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	PhonerLineTest_.invalidNumber();
	ASSERT_EQ(GetResponse(), "playMessage");
	ASSERT_EQ(GetNameState(), "Warning");

	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "nul");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "slowBusyTone");

	ASSERT_EQ(GetNameState(), "Warning");
}

TEST_F(PhonerLineTest, testSequence26)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone invalidNumber/playMessage onHook/disconnectedLine validNumber/nul
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	PhonerLineTest_.invalidNumber();
	ASSERT_EQ(GetResponse(), "playMessage");
	ASSERT_EQ(GetNameState(), "Warning");

	PhonerLineTest_.onHook();
	ASSERT_EQ(GetResponse(), "disconnectedLine");

	ASSERT_EQ(GetNameState(), "Idle");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "nul");
	ASSERT_EQ(GetNameState(), "Idle");
}

TEST_F(PhonerLineTest, testSequence27)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone validNumber/findConnection I/I validNumber/continues
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "findConnection");
	ASSERT_EQ(GetNameState(), "Conversation");

	PhonerLineTest_.tick();
	ASSERT_EQ(GetResponse(), "I");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "continues");
	ASSERT_EQ(GetNameState(), "Conversation");
}

TEST_F(PhonerLineTest, testSequence28)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone validNumber/findConnection invalidNumber/continues validNumber/continues
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "findConnection");
	ASSERT_EQ(GetNameState(), "Conversation");

	PhonerLineTest_.invalidNumber();
	ASSERT_EQ(GetResponse(), "continues");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "continues");
	ASSERT_EQ(GetNameState(), "Conversation");
}

TEST_F(PhonerLineTest, testSequence29)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone validNumber/findConnection invalidNumber/continues onHook/disconnectedLine
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "findConnection");
	ASSERT_EQ(GetNameState(), "Conversation");

	PhonerLineTest_.onHook();
	ASSERT_EQ(GetResponse(), "disconnectedLine");
	ASSERT_EQ(GetNameState(), "Idle");
}

TEST_F(PhonerLineTest, testSequence30)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone validNumber/findConnection validNumber/continues validNumber/continues
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "findConnection");
	ASSERT_EQ(GetNameState(), "Conversation");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "continues");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "continues");

	ASSERT_EQ(GetNameState(), "Conversation");
}

TEST_F(PhonerLineTest, testSequence31)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone validNumber/findConnection offHook/nul validNumber/continues
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "findConnection");
	ASSERT_EQ(GetNameState(), "Conversation");

	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "nul");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "continues");

	ASSERT_EQ(GetNameState(), "Conversation");
}

TEST_F(PhonerLineTest, testSequence32)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone validNumber/findConnection onHook/disconnectedLine validNumber/nul
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "findConnection");
	ASSERT_EQ(GetNameState(), "Conversation");

	PhonerLineTest_.onHook();
	ASSERT_EQ(GetResponse(), "disconnectedLine");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "nul");

	ASSERT_EQ(GetNameState(), "Idle");
}

TEST_F(PhonerLineTest, testSequence33)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone offHook/nul validNumber/findConnection
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "nul");

	PhonerLineTest_.validNumber();
	const bool & taskFinished = PhonerLineTest_.TaskState();
	while (not taskFinished);
	ASSERT_EQ(GetResponse(), "findConnection");

	ASSERT_EQ(GetNameState(), "Conversation");
}

TEST_F(PhonerLineTest, testSequence34)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone onHook/disconnectedLine validNumber/nul
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");

	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	PhonerLineTest_.onHook();
	const bool & taskFinished = PhonerLineTest_.TaskState();
	while (not taskFinished);
	ASSERT_EQ(GetResponse(), "disconnectedLine");

	ASSERT_EQ(GetNameState(), "Idle");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "nul");

	ASSERT_EQ(GetNameState(), "Idle");
}

TEST_F(PhonerLineTest, testSequence35)
{
	// INPUT-OUTPUT TEST SEQUENCE: onHook/nul I/I I/I validNumber/nul
	PhonerLineTest_.onHook();
	ASSERT_EQ(GetResponse(), "nul");

	// now we are in "Idle" state
	ASSERT_EQ(GetNameState(), "Idle");

	PhonerLineTest_.tick(); ASSERT_EQ(GetResponse(), "I");
	PhonerLineTest_.tick(); ASSERT_EQ(GetResponse(), "I");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "nul");

	ASSERT_EQ(GetNameState(), "Idle");
}

TEST_F(PhonerLineTest, testSequence36)
{
	// INPUT-OUTPUT TEST SEQUENCE: onHook/nul validNumber/nul
	PhonerLineTest_.onHook();
	ASSERT_EQ(GetResponse(), "nul");

	PhonerLineTest_.validNumber();
	ASSERT_EQ(GetResponse(), "nul");

	ASSERT_EQ(GetNameState(), "Idle");
}

TEST_F(PhonerLineTest, testSequence37)
{
	// INPUT-OUTPUT TEST SEQUENCE: onHook/nul onHook/nul
	PhonerLineTest_.onHook();
	ASSERT_EQ(GetResponse(), "nul");

	PhonerLineTest_.onHook();
	ASSERT_EQ(GetResponse(), "nul");

	ASSERT_EQ(GetNameState(), "Idle");
}

TEST_F(PhonerLineTest, testSequence38)
{
	// INPUT-OUTPUT TEST SEQUENCE: offHook/soundDialTone I/I offHook/nul I/I I/I validNumber/slowBusyTone
	setTicksByValue(3);
	
	PhonerLineTest_.offHook();
	ASSERT_EQ(GetResponse(), "soundDialTone");
	// now we are in "READY" state
	ASSERT_EQ(GetNameState(), "Ready");

	const bool & taskFinished = PhonerLineTest_.TaskState();
	while (not taskFinished)
	{
		if (PhonerLineTest_.ticksByFact() == 1)
		{
			// does not affect the progress of the timer.
			PhonerLineTest_.tick();
			ASSERT_EQ(GetResponse(), "I");
			PhonerLineTest_.offHook();
			ASSERT_EQ(GetResponse(), "nul");
		}
		else if (PhonerLineTest_.ticksByFact() != ticks_on_state) // I/I I/I
		{
			PhonerLineTest_.tick();
			ASSERT_EQ(GetResponse(), "I");
		}
		else
		{
			PhonerLineTest_.validNumber();
		}
	}
	ASSERT_EQ(GetResponse(), "slowBusyToneосмотрим, ");

	ASSERT_EQ(GetNameState(), "Warning");
}

} // namespace test

int main(int argc, char * argv[])
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}