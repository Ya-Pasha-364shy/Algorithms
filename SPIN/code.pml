#define soldiers_count 3
#define children_count 2

#define soldiers (soldiers_count - 1)

// Мой вариант - №3
// Условие задачи по варианту:
// Решите с помощью SPIN следующую головоломку («Мальчики и солдаты»). Два мальчика с
// лодкой согласились помочь трем (в общем случае N) солдатам переплыть реку. Лодка такова,
// что может выдержать либо одного солдата, либо двух мальчиков. И мальчики, и солдаты могут
// управлять лодкой. Как спланировать переправу?

int i = 0;
bool need_to_across_back = false;

byte PREV_CHOICE = 0;
byte CHOICE = 0;
chan SOLDIERS = [ soldiers_count ] of { bool };
int counter;

bool childrens_labels[children_count];

#define CHILDREN_SWIM_ACROSS_RIVER() \
	childrens_labels[0] = true; childrens_labels[1] = true

#define CHILD_MAKE_CHOICE_AND_ACROSS_BACK() atomic { \
	CHOICE = 1 - CHOICE; \
	assert (true == childrens_labels[CHOICE]); \
	childrens_labels[CHOICE] = false \
}

#define SOLDIER_SWIM_ACROSS_RIVER() \
	if \
	:: nempty(SOLDIERS) -> SOLDIERS?_; counter = counter + 1 \
	:: empty(SOLDIERS) -> need_to_across_back = true \
 	fi

#define RETURN_BOAT_FOR_SOILDERS_BY_BOY(inverse_boy_idx) \
	assert false == childrens_labels[1-inverse_boy_idx]; \
	childrens_labels[inverse_boy_idx] = false; \
	PREV_CHOICE = CHOICE

#define RESULT_STATE_REACHED() (((counter >= (soldiers)) && (childrens_labels[0] && childrens_labels[1])) && empty(SOLDIERS))

proctype moving()
{
	int inverse_boy_idx;
	do
	:: CHILDREN_SWIM_ACROSS_RIVER() ->
	   CHILD_MAKE_CHOICE_AND_ACROSS_BACK() ->
	   SOLDIER_SWIM_ACROSS_RIVER() ->
	   inverse_boy_idx = 1 - CHOICE
	:: if
	   :: nempty(SOLDIERS) && (CHOICE != PREV_CHOICE)    -> IF_TRANSITION: RETURN_BOAT_FOR_SOILDERS_BY_BOY(inverse_boy_idx)
	   :: empty(SOLDIERS) || need_to_across_back == true -> RETURN_BOAT_FOR_SOILDERS_BY_BOY(inverse_boy_idx); \
	                                                        RS_STATE_REACHED: CHILDREN_SWIM_ACROSS_RIVER() -> RESULT_STATE_REACHED() -> break
	   else -> skip
	   fi
	od
}

ltl ResultStateNotWillBeReachedInFUTURE {
	[](moving@IF_TRANSITION -> !<>(moving@RS_STATE_REACHED));
}

init
{
	childrens_labels[0] = false; childrens_labels[1] = false;
	for (i : 0..(soldiers)) {
		SOLDIERS!true;
	}
	counter = 0;

	run moving();
}
