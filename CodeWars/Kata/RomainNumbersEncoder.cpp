#include <iostream>
#include <string>

/*
 * Description:
 *
 * Create a function taking a positive integer between 1 and 3999 (both included)
 * as its parameter and returning a string containing the Roman Numeral
 * representation of that integer.
 * Modern Roman numerals are written by expressing each digit separately starting
 * with the left most digit and skipping any digit with a value of zero. I
 * Roman numerals 1990 is rendered: 1000=M, 900=CM, 90=XC; resulting in MCMXC.
 * 2008 is written as 2000=MM, 8=VIII; or MMVIII.
 * 1666 uses each Roman symbol in descending order: MDCLXVI.
*/

void convert_thousands(int counter, int digit, std::string & rs)
{
	if (counter != 0)
		return;

	if (digit == 3)
		rs.append("MMM");
	else if (digit == 2)
		rs.append("MM");
	else if (digit == 1)
		rs.append("M");
}

void convert_to_Romain_numbers(int digit, std::string & rs, const std::string * romain_numbers)
{
	if (digit == 5)
	{
		rs.insert(rs.length(), romain_numbers[4]);
		return;
	}

	for (int i = 4, counter = 1; i < 9; counter++)
	{
		std::string init_hundred;

		if ((counter-1) % 2 == 0)
		{
			i -= counter;
			init_hundred = romain_numbers[i];
		}
		else
		{
			i += counter;
			init_hundred = romain_numbers[i];
		}
		if (digit == i+1)
		{
			rs.insert(rs.length(), init_hundred);
			return;
		}
	}
}

void convert_hundreds(int counter, int digit, std::string & rs)
{
	if (counter != 1)
		return;

	std::string romain_hundreds[] = {"C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
	convert_to_Romain_numbers(digit, rs, romain_hundreds);
}

void convert_tens(int counter, int digit, std::string & rs)
{
	if (counter != 2)
		return;

	std::string romain_tens[] = {"X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
	convert_to_Romain_numbers(digit, rs, romain_tens);
}

void convert_units(int counter, int digit, std::string & rs)
{
	if (counter != 3)
		return;

	std::string romain_units[] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
	convert_to_Romain_numbers(digit, rs, romain_units);
}

std::string dec_digit_to_romain_encoder(int number)
{
	int tmp_digit;
	std::string romain_number_encoded;

	for (int i = 1000, counter = 0; i >= 1 && number; i /= 10, counter++)
	{
		tmp_digit = (number - (number % i)) / i;
		if (tmp_digit == 0)
		{
			continue;
		}
		else if (tmp_digit != number or i == 1)
		{
			number -= (i * tmp_digit);

			convert_thousands(counter, tmp_digit, romain_number_encoded);
			convert_hundreds(counter, tmp_digit, romain_number_encoded);
			convert_tens(counter, tmp_digit, romain_number_encoded);
			convert_units(counter, tmp_digit, romain_number_encoded);
		}
		else
			continue;
	}
	return romain_number_encoded;
}

int main()
{
	// MMCDXXI
	std::string result = dec_digit_to_romain_encoder(2421);
	std::cout << "[1] Result = " << result << std::endl;

	// CLXXXII
	result = dec_digit_to_romain_encoder(4182);
	std::cout << "[2] Result = " << result << std::endl;

	result = dec_digit_to_romain_encoder(1);
	std::cout << "[3] Result = " << result << std::endl;

	return 0;
}