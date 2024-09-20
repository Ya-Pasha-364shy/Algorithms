package main

import (
	"fmt"
)

/*
Description:

"Split Strings"

Complete the solution so that it splits the string into pairs of two characters.
If the string contains an odd number of characters then it should replace
the missing second character of the final pair with an underscore ('_').
*/

func solution(str string) []string {
	var i int
	var string_length int = len(str)
	var pairs []string 

	for i = 0; i < string_length; i += 2 {
		if i + 2 > string_length {
			var tmp string = str[i:] + "_"
			pairs = append(pairs, tmp)	
		} else {
			pairs = append(pairs, str[i:i+2])
		}
	}
	return pairs;
}

func main() {
	/* there are tests located */
	test1 := "abcdefgh" // 8 symbols
	fmt.Printf("%q\n", solution(test1))	
	test2 := "biba&boba" // 9 symbols
	fmt.Printf("%q\n", solution(test2))	
}