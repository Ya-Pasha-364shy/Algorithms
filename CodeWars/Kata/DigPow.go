package main
import (
	"math"
	"strconv"
)

/**
 * Description:

 * Given two positive integers n and p
 * we want to find a positive integer k,
 * if it exists, such that the sum of the digits
 * of n raised to consecutive powers starting
 * from p is equal to k * n:
 *
 * (a^p+b^(p+1)+c^(p+2)+d^(p+3)+...)=n∗k
 * Note: a,b,c,d,... - digits of n.
 *
 * return p, if it in this case, otherwise -1
*/

func DigPow(n, p int) int {
	var actual int
	var str_repr string = strconv.Itoa(n)

	for power, i := p, 0; power < p + len(str_repr) && i < len(str_repr); power, i = power+1, i+1 {
		digit, _ := strconv.Atoi(string(str_repr[i]))
		actual += int(math.Pow(float64(digit), float64(power)))
	}

	if (actual % n) {
		return actual / n
	} else {
		return -1
	}
}

func main() {

}