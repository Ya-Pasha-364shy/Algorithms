#include <iostream>
#include <string>

#include "testlib.h"
/*
 * Description:
 *
 * Write a function that takes a string of braces,
 * and determines if the order of the braces is valid.
 * It should return true if the string is valid, and
 * false if it's invalid.
*/

#define OPEN_PARENTHESIS  '('
#define CLOSE_PARENTHESIS ')'

#define SQUARE_OPEN_BRACKET  '['
#define SQUARE_CLOSE_BRACKET ']'

#define CURLY_OPEN_BRACE  '{'
#define CURLY_CLOSE_BRACE '}'

/*
 * NOTE: да, выглядит это не очень привлекательно, но это хорошо работает !
*/

bool is_opening_bracket(char chr)
{
	if (chr == OPEN_PARENTHESIS    or
	    chr == SQUARE_OPEN_BRACKET or
	    chr == CURLY_OPEN_BRACE)
		return true;
	return false;
}

bool is_closing_bracket(char chr)
{
	if (chr == CLOSE_PARENTHESIS    or
	    chr == SQUARE_CLOSE_BRACKET or
	    chr == CURLY_CLOSE_BRACE)
		return true;
	return false;
}

bool pair_is_parenthesis_brackets(const std::string & s, size_t idx1, size_t idx2)
{
	if (s[idx1] == OPEN_PARENTHESIS and s[idx2] == CLOSE_PARENTHESIS)
		return true;
	return false;
}

bool pair_is_square_brackets(const std::string & s, size_t idx1, size_t idx2)
{
	if (s[idx1] == SQUARE_OPEN_BRACKET and s[idx2] == SQUARE_CLOSE_BRACKET)
		return true;
	return false;
}

bool pair_is_curly_brackets(const std::string & s, size_t idx1, size_t idx2)
{
	if (s[idx1] == CURLY_OPEN_BRACE and s[idx2] == CURLY_CLOSE_BRACE)
		return true;
	return false;
}

bool pair_is_one_of_brackets(const std::string & s, size_t idx1, size_t idx2)
{
	if (pair_is_parenthesis_brackets(s, idx1, idx2) or
	    pair_is_square_brackets(s, idx1, idx2) or
	    pair_is_curly_brackets(s, idx1, idx2))
		return true;
	return false;
}

inline bool boundaries_not_violated(size_t idx1, size_t idx2, size_t len)
{
	return idx1 >= 0 and idx2 < len ? true : false;
}

int check_brackets(const std::string & s, size_t idx1, size_t idx2)
{
	if (pair_is_one_of_brackets(s, idx1, idx2))
	{
		size_t idx1_, idx2_;
		if (boundaries_not_violated(idx1 - 1, idx2 + 1, s.length()))
		{
			idx1_ = idx1 - 1, idx2_ = idx2 + 1;
			if (check_brackets(s, idx1_, idx2_)) // finish when boundaries are violated
			{
				return 1;
			}
			else return 0;
		}
		else return -1;
	}
	else if (is_closing_bracket(s[idx1]) and is_opening_bracket(s[idx2])) // ]( -- in this case, for example
	{
		// -1 and +1 might be some offsets
		size_t idx1_ = idx1 - 1, idx1_hatch_ = idx2, idx2_ = idx1, idx2_hatch_ = idx2 + 1;
		if (boundaries_not_violated(idx1_, idx2_, s.length()) and boundaries_not_violated(idx1_hatch_, idx2_hatch_, s.length())) // check that "[]()" is exists
		{
			if (pair_is_one_of_brackets(s, idx1_, idx2_) and pair_is_one_of_brackets(s, idx1_hatch_, idx2_hatch_))
			{
				size_t idx1__ = idx1_ - 1, idx2__ = idx2_hatch_ + 1; // check external braces
				if (boundaries_not_violated(idx1__, idx2__, s.length()))
				{
					if (check_brackets(s, idx1__, idx2__))
					{
						return 1;
					}
					else return 0;
				}
				else return -1;
			}
			else return 0;
		}
		else return 0;
	}
	else if (is_opening_bracket(s[idx1]) and is_opening_bracket(s[idx2]))
	{
		size_t idx1_ = idx1, idx2_ = idx2;
		do
		{
			--idx1_; --idx2_;
			if (not boundaries_not_violated(idx1_, idx2_, s.length()))
			{
				return 0;
			}
			else if (is_closing_bracket(s[idx1_]) and is_opening_bracket(s[idx2_]))
			{
				break;
			}
		} while (true);
		// разделяем и властвуем
		std::string left_substring = s.substr(0, idx1_ + 1), right_string = s.substr(idx2_);
		
		size_t left_stroke_length = left_substring.length();
		size_t l_idx1_ = left_stroke_length/2 - 1, l_idx2_ = left_stroke_length/2;

		size_t right_stroke_length = right_string.length();
		size_t r_idx1_ = right_stroke_length/2 - 1, r_idx2_ = right_stroke_length/2;

		if (check_brackets(left_substring, l_idx1_, l_idx2_) and check_brackets(right_string, r_idx1_, r_idx2_))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (is_closing_bracket(s[idx1]) and is_closing_bracket(s[idx2]))
	{
		size_t idx1_ = idx1, idx2_ = idx2;
		do
		{
			++idx1_; ++idx2_;
			if (not boundaries_not_violated(idx1_, idx2_, s.length()))
			{
				return 0;
			}
			if (is_closing_bracket(s[idx1_]) and is_opening_bracket(s[idx2_]))
			{
				break;
			}
		} while (true);
		// разделяем и властвуем v2
		std::string left_substring = s.substr(0, idx1_+1), right_string = s.substr(idx2_);
		
		size_t left_stroke_length = left_substring.length();
		size_t l_idx1_ = left_stroke_length/2 - 1, l_idx2_ = left_stroke_length/2;

		size_t right_stroke_length = right_string.length();
		size_t r_idx1_ = right_stroke_length/2 - 1, r_idx2_ = right_stroke_length/2;

		if (check_brackets(left_substring, l_idx1_, l_idx2_) and check_brackets(right_string, r_idx1_, r_idx2_))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else return 0;
}

bool valid_braces(std::string braces)
{
	if (braces.length() % 2)
		return false;

	size_t stroke_length = braces.length();
	size_t idx1 = (stroke_length / 2) - 1, idx2 = stroke_length / 2;

	int rc = check_brackets(braces, idx1, idx2);
	if (rc)
		return true;
	else
		return false;
}

int main()
{
	IS_EQUALS(valid_braces("([{}])"), true);
	IS_EQUALS(valid_braces("{[]()}"), true);
	IS_EQUALS(valid_braces("[](){}"), true);
	IS_EQUALS(valid_braces("[]{[]()}()"), true);

	IS_EQUALS(valid_braces("({})[({})]"), true); // The principle of divide and conquer applies
	IS_EQUALS(valid_braces("[({})]{()}"), true);
	return 0;
}