#define soldiers_count 3
#define children_count 2

// Мой вариант - №3
// Условие задачи по варианту:
// Решите с помощью SPIN следующую головоломку («Мальчики и солдаты»). Два мальчика с
// лодкой согласились помочь трем (в общем случае N) солдатам переплыть реку. Лодка такова,
// что может выдержать либо одного солдата, либо двух мальчиков. И мальчики, и солдаты могут
// управлять лодкой. Как спланировать переправу?

bool childrens_labels[children_count];
bool soldiers_labels[soldiers_count];
bool all_soldiers_on_rigth_waterfront = false;
bool boat_location = false;

/* независимые элементарные шаги:
 * all_childrens_across_river_on_another_waterfront_IF_can - оба мальчика пересекают реку на лодке и прибывают на противоположный берег с лодкой,
      если у них есть.
 * one_child_across_river_IF_can - один мальчик пересекает реку на лодке и прибывает на противоположный берег с лодкой, если она у него имеется.
 * soldier_across_river_on_another_waterfront - один солдат пересекает реку на лодке и пребывает на противоположный берег с ней.
 *
 * NOTE:
 * Для всех inline функций/макросов, в которых упоминаются солдаты - используется цикл, так как по условию задачи их может быть N штук.
*/

inline all_childrens_across_river_on_another_waterfront_IF_can()
{
	if
	:: (boat_location == childrens_labels[0]) && (boat_location == childrens_labels[1]) -> childrens_move: \
	     childrens_labels[0] = !childrens_labels[0]; \
	     childrens_labels[1] = !childrens_labels[1]; \
	     boat_location       = !boat_location; \
	     printf("childrens are across river and NOW on the \"%d\" waterfront WITH boat\n", boat_location ) \
	fi
}

inline one_child_across_river_IF_can()
{
	if
	:: (childrens_labels[0] == boat_location) -> zero_child_move:
	      childrens_labels[0] = !childrens_labels[0]; boat_location = !boat_location;
	      printf("child #0 across the river on the \"%d\" waterfront WITH boat\n", boat_location)
	:: (childrens_labels[1] == boat_location) -> one_child_move:
	      childrens_labels[1] = !childrens_labels[1]; boat_location = !boat_location;
	      printf("child #1 across the river on the \"%d\" waterfront WITH boat\n", boat_location)
	fi
}

inline soldier_across_river_on_another_waterfront()
{
	int i = 0;
	do 
	:: (i < soldiers_count) ->
	   if
	   :: (boat_location == soldiers_labels[i]) -> soldier_move:
	          soldiers_labels[i] = !soldiers_labels[i];
	          boat_location      = !boat_location;
	          printf("Soldier with number %d is across river on \"%d\" waterfront WITH boat\n", i, boat_location);
	          break
	   :: else -> i++;
	   fi
	:: (i >= soldiers_count) -> break
	od
}

inline check_all_soldiers_on_the_rigth_waterfront()
{
	int i = 0;
	do
	:: (i < soldiers_count) ->
	   if
	   :: soldiers_labels[i] == false -> all_soldiers_on_rigth_waterfront = false; break
	   :: soldiers_labels[i] == true  -> all_soldiers_on_rigth_waterfront = true;  i++
	   fi
	:: (i >= soldiers_count) -> break
	od
}

/*
 * Данный процесс запускается посредством вызова из процесса "init".
 * и перебирает все комбинации до тех пор, пока не встретит решения.
 *
 * Решение в данной задаче - это наступления такого события, что все мальчики и все солдаты оказались на правом берегу (вместе с лодкой).
*/

#define RESULT_STATE_REACHED() ((childrens_labels[0] == true) && (childrens_labels[1] == true) && (boat_location == true) && (all_soldiers_on_rigth_waterfront == true))

proctype moving()
{
	do
	:: all_childrens_across_river_on_another_waterfront_IF_can()
	:: one_child_across_river_IF_can()
	:: soldier_across_river_on_another_waterfront(); check_all_soldiers_on_the_rigth_waterfront()
	od
}

init
{
	int i = 0;
	/*
	 * Изначально все "солдаты" и "мальчики" находятся на левом берегу
	 * (метки, говорящие о том, что они находятся на левом берегу имеют значение false, а на правом - true).
	*/
	childrens_labels[0] = false; childrens_labels[1] = false;
	for (i : 0..(soldiers_count-1)) {
		soldiers_labels[i] = false;
	}

	run moving()
}

ltl goal { !<>(RESULT_STATE_REACHED()) }

