#define n               3
#define childrens_count 2

// Мой вариант -- №3
// Условие задачи по варианту:
// Решите с помощью SPIN следующую головоломку («Мальчики и солдаты»). Два мальчика с
// лодкой согласились помочь трем (в общем случае N) солдатам переплыть реку. Лодка такова,
// что может выдержать либо одного солдата, либо двух мальчиков. И мальчики, и солдаты могут
// управлять лодкой. Как спланировать переправу?

byte CHOICE = 0;

byte SOLDIERS[n];
bool childrens_labels[childrens_count];

#define MAKE_CHOICE_AND_ACROSS_BACK() atomic { \
	CHOICE = 1 - CHOICE; \
	assert true == childrens_labels[CHOICE]; \
	childrens_labels[CHOICE] = false \
}

#define SWIM_ACROSS_RIVER() \
	childrens_labels[0] = true; childrens_labels[1] = true

// TODO: fifo -> array
#define SOLDIER_ACROSS_RIVER() \
	SOLDIERS?false;

#define RETURN_BOAT_FOR_SOILDERS_BY_BOY(inverse_idx) \
	childrens_labels[inverse_idx] = false

#define RESULT_STATE_REACHED() ((empty(SOLDIERS) && (true == (childrens_labels[0] && childrens_labels[1]))))

proctype moving()
{
	do
	:: SWIM_ACROSS_RIVER()
	:: MAKE_CHOICE_AND_ACROSS_BACK()
	:: SOLDIER_ACROSS_RIVER()
	:: if
	   :: empty(SOLDIERS) -> IF_EMPTY: childrens_labels[CHOICE] = true
	   else -> int inverse_boy = 1 - CHOICE; RETURN_BOAT_FOR_SOILDERS_BY_BOY(inverse_boy)
	   fi
	:: if
	   :: RESULT_STATE_REACHED() -> THEN_WILL: break
	   else -> skip
	   fi
	else -> skip
	od
}

ltl ResultStateWillBeReached {
	<>(moving@IF_EMPTY -> moving@THEN_WILL);
}

byte i;

init
{
	childrens_labels[0] = false; childrens_labels[1] = false;
	for (i : 0..(N-1)) {
		SOLDIERS[i] = true;
	}

	run moving();
}