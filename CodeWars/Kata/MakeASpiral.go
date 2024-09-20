package main

import (
	"fmt"
)

/*

s=1; draw = 10; k = 0
s=2; draw = 9 ; k = 1
s=3; draw = 9 ; k = 1
s=4; draw = 7 ; k = 3

s=5; draw = 7 ; k = 3
s=6; draw = 5 ; k = 5
s=7; draw = 5 ; k = 5
s=8; draw = 3 ; k = 7

s=9; draw = 3 ; k = 7
s=10;draw = 1 ; k = 9

* * * * * * * * * *
!                 *
* * * * * * * * ! *
*   !         *   *
*   * * * *   *   *
*   *     *   *   *
*   *     !   *   *
*   * * * * * * ! *
*                 *
* * * * * * * * * *

--------->X
|
|
|
Y
*/

func Spiralize(size int) [][]int {
	snake := make([][]int, size)
	for i := range snake {
		snake[i] = make([]int, size)
	}

	var step, k, action int
	var x, y int;

	k  = 0
	action = 0
	step = 0

	for {
		if action == 0 {
			/* keep value of "k" */
			for ; x < (size - k); x++ {
				snake[y][x] = 1;
			}
			action = 1

		} else if action == 1 {
			k += 1

			for y = k; y < size; y++ {
				snake[y][x-1] = 1;
			}
			action = 2

		} else if action == 2 {
			/* keep value of "k" */
			x -= k
			for ; x >= 0; x-- {
				snake[y-1][x] = 1;
			}
			action = 3
			x = 0

		} else if action == 3 {
			k += 2
			y -= 1

			for ; y > (size - k); y-- {
				snake[y][x] = 1;
			}
			action = 0
		}
		step++

		if step >= size {
			break
		}
	}
	return snake
}

func main() {
	result := Spiralize(5)
	for i := 0; i < 5; i++ {
		fmt.Println(result[i])
	}
}