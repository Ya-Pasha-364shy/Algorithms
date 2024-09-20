package main

import (
	"fmt"
)

/*
Description:

"Two Sum"

Write a function that takes an array of numbers (integers for the tests) and a target number.
It should find two different items in the array that, when added together, give the target value.
The indices of these items should then be returned in a
tuple / list (depending on your language) like so: (index1, index2).
*/

func solution(numbers []int, target int) [2]int {
	/* let's use simple bruteforce */
	var index1, index2 int
	var total_numbers = len(numbers)
	var result [2]int

	for index1 = 0; index1 < total_numbers; index1++ {
		for index2 = 0; index2 < total_numbers; index2++ {
			if index1 == index2 {
				continue
			}
			if numbers[index1] + numbers[index2] == target {
				result = [2]int{index1, index2}
				return result
			}
		}
	}
	return result
}

func main() {
	fmt.Println(solution([]int{1, 2, 3}, 4))  // 0, 2
	fmt.Println(solution([]int{1234, 5678, 9012}, 14690)) // 1, 2
	fmt.Println(solution([]int{2, 2, 3}, 4)) // 0, 1
}