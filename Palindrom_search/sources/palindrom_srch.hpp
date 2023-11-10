#ifndef PALINRDROM_SRCH_H_
#define PALINRDROM_SRCH_H_

#include <string>
#include <set>
#include <vector>

namespace fsm {

#define MAX_TEXT_LEN __INT32_MAX__
#define MAX_STR_LEN  (MAX_TEXT_LEN / 2)

typedef enum
{
	CURRENT_STROKE_SYMBOL,
	ANY_NON_SPACE_SYMBOL,
	ANY_SPACE_SYMBOL,
} fsm_symbol_t;

typedef enum
{
	NODE_STATUS_FAILED,
	NODE_STATUS_COMPLETED,

	/* Это не выходной символ, нужный для обособления случая, когда длина строки = 1 */
	NODE_STATUS_INVALID = -1,
} fsm_output_symbol_t;

class fsm_palindrom_srch
{
private:
	fsm_symbol_t        state_input_symbol_;
	fsm_output_symbol_t state_output_symbol_;
	u_int32_t           state_current_idx_;
	u_int32_t           state_current_reverse_idx_;

	u_int32_t           palindrom_counter_ = 0;

	/* @brief
	 * Этот множество хранит в себе уникальные палиндромы текста.
	*/
	std::set<std::string> set_of_palindroms_;

	/* @brief
	 * Этот список выходных символов нужен для тестов.
	*/
	std::vector<fsm_output_symbol_t> fsm_sequence_symbols_;

public:
	fsm_palindrom_srch() : state_current_idx_(0),
	    state_current_reverse_idx_(MAX_STR_LEN) {}

	/*
	 * @brief
	 * Метод возврата последовательности выходных символов - реакций.
	*/
	std::vector<fsm_output_symbol_t> fsm_get_output_sequence() const
	{
		return fsm_sequence_symbols_;
	}

	/*
	 * @brief
	 * Метод инициального состояния FSM - S0. Находимся в данном состоянии до
	 * тех пор, пока в поданном тексте не обнаружится любой непробельный символ.
	 * @param
	 * `character` - подаваемый символ текста.
	*/
	fsm_output_symbol_t fsm_init_state(const char character);

	/*
	 * @brief
	 * Метод состояния S1. После получения любого символа, если следующий
	 * элемент пробельный или отличный от обратного текущего, то
	 * осуществляется возврат в предыдующее состояние.
	 * Иначе, если текущий элемент равен соответствующему
	 * обратному - переход в S2.
	 * @param
	 * `current_string` - указатель на текущую строку.
	*/
	fsm_output_symbol_t fsm_check_state(const std::string current_string);

	/*
	 * @brief
	 * Метод состояния перехода S2. Если следующий элемент есть в строке
	 * (с начала, но не считая текущий), проверяется обратный ему через
	 * возврат в состояние S1.
	 * Если все символы строки были обойдены, то переходим в следующее состояние.
	*/
	fsm_output_symbol_t fsm_step_state();

	/*
	 * @brief
	 * Метод состояния - счётчика.
	 * Увеличивает своё значение, когда осуществляется переход в него.
	 * Если переход был, значит рассматриваемая строка - палиндром.
	*/
	fsm_output_symbol_t fsm_counter_state();

	/*
	 * @brief
	 * Метод управления состояниями.
	 * @param
	 * `text` - подаваемый пользователем текст.
	*/
	void fsm_orchestrator_states(const std::string & text);

	/*
	 * @brief
	 * Метод, преобразующий любой символ текста в соответсвующий
	 * символ состояний автомата.
	 * @param
	 * `character` - любой символ строки.
	*/
	static fsm_symbol_t fsm_display_character_on_fsm_symbol(const char character);

	void fsm_print_palindroms_of_text(void)
	{
		std::cout << "\nNumber of palindroms in the inputted text: " << palindrom_counter_ << std::endl;
		std::cout << "{ ";
		for (auto it = set_of_palindroms_.cbegin(); it != set_of_palindroms_.cend(); it++)
		{
			std::cout << *it << ", ";
		}
		std::cout << "};" << std::endl;
	}

	friend inline void add_palindrom_into_set(std::string * item, fsm_palindrom_srch * obj)
	{
		obj->set_of_palindroms_.insert(*item);
	}

	friend inline bool palindrom_set_is_empty(fsm_palindrom_srch * obj)
	{
		bool rc;
		obj->set_of_palindroms_.empty() ? rc = true : rc = false;
		return rc;
	}

	~fsm_palindrom_srch() = default;
};

} // namespace fsm

#endif // PALINRDROM_SRCH_H_