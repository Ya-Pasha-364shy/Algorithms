#include <iostream>
#include <cstring>
#include <string>

#include "palindrom_srch.hpp"

bool inline is_odd(size_t size)
{
	return size % 2 ? true : false;
}

bool middle_equals_every_element(const std::string & str, size_t size)
{
	if (is_odd(size))
	{
		char mid = str[(size / 2) + 1];
		for (auto it = str.begin(); it != str.end(); it++)
		{
			if (mid != *it)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

using namespace fsm;

fsm_symbol_t fsm_palindrom_srch::fsm_display_character_on_fsm_symbol(const char character)
{
	if (isalnum(character))
		return ANY_NON_SPACE_SYMBOL;
	else
		return ANY_SPACE_SYMBOL;
}

fsm_output_symbol_t fsm_palindrom_srch::fsm_init_state(const char character)
{
	fsm_output_symbol_t return_symbol;

	if (ANY_SPACE_SYMBOL == fsm_palindrom_srch::fsm_display_character_on_fsm_symbol(character))
		return_symbol = NODE_STATUS_FAILED;
	else
		return_symbol = NODE_STATUS_COMPLETED;

	fsm_sequence_symbols_.push_back(return_symbol);
	return return_symbol;
}

fsm_output_symbol_t fsm_palindrom_srch::fsm_check_state(const std::string current_string)
{
	fsm_output_symbol_t return_symbol;

	if (current_string.length() == 1)
	{
		return_symbol = NODE_STATUS_FAILED;
	}
	else
	{
		if (state_current_reverse_idx_ == MAX_STR_LEN)
		{
			state_current_reverse_idx_ = current_string.length() - 1;
		}
		if (tolower(current_string[state_current_idx_]) ==
		    tolower(current_string[state_current_reverse_idx_]))
		{
			return_symbol = NODE_STATUS_COMPLETED;
		}
		else
		{
			return_symbol = NODE_STATUS_FAILED;
		}
	}

	fsm_sequence_symbols_.push_back(return_symbol);
	return return_symbol;
}

fsm_output_symbol_t fsm_palindrom_srch::fsm_step_state()
{
	fsm_output_symbol_t return_symbol;

	++state_current_idx_;
	--state_current_reverse_idx_;

	if (state_current_idx_ < state_current_reverse_idx_)
	{
		return_symbol = NODE_STATUS_COMPLETED;
	}
	else
	{
		return_symbol = NODE_STATUS_FAILED;
	}

	fsm_sequence_symbols_.push_back(return_symbol);
	return return_symbol;
}

fsm_output_symbol_t fsm_palindrom_srch::fsm_counter_state()
{
	fsm_output_symbol_t return_symbol = NODE_STATUS_COMPLETED;
	palindrom_counter_++;

	fsm_sequence_symbols_.push_back(return_symbol);
	return return_symbol;
}

std::string get_full_str(std::string::const_iterator iterator_, unsigned * next_space_pos)
{
	std::string substring;
	std::string::const_iterator it;

	for (auto it = iterator_; *it; it++)
	{
		if (ANY_NON_SPACE_SYMBOL == fsm_palindrom_srch::fsm_display_character_on_fsm_symbol(*it))
		{
			substring += *it;
			(*next_space_pos)++;
		}
		else
		{
			break;
		}
	}
	return substring;
}

// в самом худшем случае сложность: O(n^2) + O(n/2)
void fsm_palindrom_srch::fsm_orchestrator_states(const std::string & text)
{
	for (auto it = text.begin(); it < text.end(); it++)
	{
		// если найден символ, выходим из состояния s0 -> s1 или из s3 -> s0.
		if (NODE_STATUS_COMPLETED == fsm_init_state(*it))
		{
			unsigned next_space_pos = 0;
			// получаем текущее слово в тексте.
			std::string tmp_substring = get_full_str(it, &next_space_pos);

			fsm_output_symbol_t out_symbol_s1;
			while (NODE_STATUS_FAILED != (out_symbol_s1 = fsm_check_state(tmp_substring)))
			{
				if (NODE_STATUS_FAILED == fsm_step_state())
				{
					if (middle_equals_every_element(tmp_substring, tmp_substring.size()))
					{
						/* Проверка того, что всё слово состоит из последовательности,
						   пара символов из которой - всегда равны. Такое слово не является палиндромом */
						fsm_sequence_symbols_.back() = NODE_STATUS_COMPLETED;
					}
					break; // всё слово `tmp_string` было обойдено => это палиндром.
				}
			}
			if (NODE_STATUS_COMPLETED == out_symbol_s1 && NODE_STATUS_COMPLETED != fsm_sequence_symbols_.back())
			{
				fsm_counter_state();
				add_palindrom_into_set(&tmp_substring, this);
				/* перевод коретки на новое слово. */
				it += next_space_pos;
			}
			else if (tmp_substring.length() == 1)
			{
				it += next_space_pos;
			}
			else
			{
				it += next_space_pos - 1;
			}
		}
		else
		{
			continue;
		}
		// обновляем счётчики индексов строки.
		state_current_idx_ = 0, state_current_reverse_idx_ = MAX_STR_LEN;
	}
}

int main(int argc, char * argv[])
{
	std::string user_input;
	while (true)
	{
		std::cout << "=== Palindrom search by FSM ===" << std::endl;
		std::cout << "Enter your text: ";

		getline(std::cin, user_input);
		if (not std::cin.good())
		{
			std::cin.clear();
			std::cin.ignore(MAX_TEXT_LEN, '\n');
		}
		else if (user_input.empty())
		{
			std::cout << "Please enter valid text !" << std::endl;
			std::cout << std::endl;
		}
		else
		{
			break;
		}
	}

	fsm_palindrom_srch fsm;
	fsm.fsm_orchestrator_states(user_input);

	/* печатаем палиндромы после выполнения алгоритма поиска,
	 * если есть, что печатать. */
	if (not palindrom_set_is_empty(&fsm))
	{
		fsm.fsm_print_palindroms_of_text();
	}

	return EXIT_SUCCESS;
}