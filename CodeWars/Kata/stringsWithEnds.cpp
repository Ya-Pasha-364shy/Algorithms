#include <iostream>
#include <string>
#include <string.h>

#include "testlib.h"
/*
 * Description:
 *
 * Complete the solution so that it returns true
 * if the first argument(string) passed in ends
 * with the 2nd argument (also a string).
*/

bool solution(std::string const &str, std::string const &ending)
{
	if (ending.empty())
		return true;


	size_t position = str.rfind(ending);
	if (position == std::string::npos)
		return false;

	std::string to_end = str.substr(position);
	if (0 == to_end.compare(ending))
		return true;
	else
		return false;
}

int main()
{
	IS_EQUALS(solution("abc", "bc"), true);
	IS_EQUALS(solution("abcde", "cde"), true);
	IS_EQUALS(solution("abcde", "abc"), false);
	IS_EQUALS(solution("abc", "d"), false);
	IS_EQUALS(solution("qwerty", "qwerty"), true);
	IS_EQUALS(solution("abc", ""), true);
	IS_EQUALS(solution("abcabc", "bc"), true);

	return 0;
}