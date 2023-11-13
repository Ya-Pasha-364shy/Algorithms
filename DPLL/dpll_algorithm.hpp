#ifndef DPLL_ALGORITHM_H_
#define DPLL_ALGORITHM_H_

#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

#define MAX_MEMORY_SIZE 8388608 // 8 * 1024 * 1024

#define COMMENT_SIGNATURE 'c'
#define PREAMBULE_SIGNATURE 'p'

class dpll_sequence
{
private:
	bool dpll_contradiction_ = false;

	std::set<int> dpll_literals_;
	std::set<int> dpll_literals_saved_;

	std::vector<std::list<int>> dpll_clauses_; // S
public:
	dpll_sequence() = delete;
	dpll_sequence(std::vector<std::string> & dpll_clauses);

	/* helpers */
	std::vector<std::list<int>> & get_clauses()
	{
		return dpll_clauses_;
	}

	template <typename T>
	friend void print_clauses(std::vector<std::list<T>>);

	/* main methods */

	/* @brief
	 * Согласно алгоритму DPLL, данная функция должна
	 * выбирать монотонный литерал, такой, который повторяется хотя бы
	 * один раз в более, чем одной клаузе без отрицания (это будет уже другой лит.).
	 * И задаёт значение этому литералу = true, контрарному литералу же = false.
	 * 
	 * Полезная нагрузка относительно последовательности предложений:
	 * Удаляет клаузы, которые несут в себе литерал L (так как они уже правда).
	*/
	void dpll_monotone_variable_fixing();

	/* @brief
	 * Пока последовательность предложений содержит одиночную клаузу - предложение,
	 * имеющее один литерал - устанавливаем его значение = true. Удаляет все клаузы,
	 * которые содержат данный литерал, а также появление всех контрарных литералов.
	 * 
	 * Может найти противоречие. Если контрарный литерал был удалён из одиночной клаузы,
	 * значит, что возникло противоречие.
	*/
	void dpll_unit_resolution();

	/* @brief
	 * Выбирает литерал, любой без отрицания, такой, что ещё не был выбран
	 * из всей формулы. Затем удаляет этот литерал, т.к. он уже был выбран для
	 * упрощения формулы
	*/
	int dpll_get_and_erase_literal();

	/* @brief
	 * Обновляет "ведро воды" dpll_literals_;
	*/
	friend void refresh_water_bucket(dpll_sequence * obj)
	{
		obj->dpll_literals_ = obj->dpll_literals_saved_;
	}

	/* @brief
	 * Выбирает литерал, любой без отрицания, из всей формулы.
	*/
	int dpll_get_literal();

	/* @brief
	 * Задаёт шаг. Выполняет первые два метода, если S (`clauses_`) пустое, то
	 * говорим, что формула выполнима (SAT), иначе - невыполнима (UNSAT).
	*/
	void dpll_orchestrator();

	/* destructor */
	virtual ~dpll_sequence() = default;
};

template <typename T>
void print_clauses(std::vector<std::list<T>> clauses)
{
	std::cout << "{";
	for (const auto clause: clauses)
	{
		std::cout << "\t[ ";
		for (const auto item: clause)
		{
			std::cout << item << " ";
		}
		std::cout << "]," << std::endl;
	}
	std::cout << "};" << std::endl;
}

dpll_sequence::dpll_sequence(std::vector<std::string> & dpll_clauses)
{
	int number;
	std::list<int> tmp_clause;

	for (auto line: dpll_clauses)
	{
		std::istringstream stream(line);
		while (stream >> number)
		{
			tmp_clause.emplace_back(number);
			dpll_literals_.insert(abs(number));
		}

		dpll_clauses_.emplace_back(tmp_clause);
		tmp_clause.clear();
	}
	dpll_literals_saved_ = dpll_literals_;

	std::cout << "dpll_literals_ = [ ";
	for (auto it = dpll_literals_.begin(); it != dpll_literals_.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << "];" << std::endl;
}

/*
 * @brief
 * возвращает 0, если все элементы закончились,
 * иначе возвращает литерал
*/
int dpll_sequence::dpll_get_and_erase_literal()
{
	int returned_value = *dpll_literals_.end();
	dpll_literals_.erase(returned_value);
	return returned_value;
}

int dpll_sequence::dpll_get_literal()
{
	static std::set<int>::iterator lit = dpll_literals_saved_.begin();
	int returned_value;

	if (lit != dpll_literals_saved_.end())
	{
		returned_value = *lit;
		++lit;
		return returned_value;
	}
	else
	{
		lit = dpll_literals_saved_.begin();
		returned_value = *lit;
		return returned_value;
	}
}

void dpll_sequence::dpll_monotone_variable_fixing()
{
	bool found;
	int literal;
	size_t number_of_clauses;
	std::set<size_t> unique_occur_positions;
	std::map<int, std::list<size_t>> monotonic_occurs_literals;

	while (0 != (literal = dpll_get_and_erase_literal()))
	{
		number_of_clauses = dpll_clauses_.size();
		std::list<size_t> tmp_list_positions;

		for (size_t i = 0; i < number_of_clauses; i++)
		{
			auto fixed = dpll_clauses_[i];
			found = (std::find(fixed.begin(), fixed.end(), literal) != fixed.end());
			if (found)
				tmp_list_positions.emplace_back(i);
		}
		monotonic_occurs_literals[literal] = std::move(tmp_list_positions);
	}

	for (auto & literal_occurs: monotonic_occurs_literals)
	{
		auto occurences = literal_occurs.second;
		for (auto it = occurences.begin();  occurences.size() > 1 && it != occurences.end(); it++)
		{
			unique_occur_positions.insert(*it);
		}
	}

	auto beg_it = dpll_clauses_.begin();
	for (size_t occurence : unique_occur_positions)
	{
		dpll_clauses_.erase(beg_it + occurence);
	}

	// std::cout << "SUCCESS" << std::endl;
	// print_clauses(dpll_clauses_);

	refresh_water_bucket(this);
}

void dpll_sequence::dpll_unit_resolution()
{

}

void dpll_sequence::dpll_orchestrator()
{
	while (true)
	{
		dpll_monotone_variable_fixing();
		dpll_unit_resolution();

		if (dpll_contradiction_)
		{
			std::cout << "UNSAT" << std::endl;
			return;
		}
		if (dpll_clauses_.empty())
		{
			std::cout << "SAT" << std::endl;
			return;
		}
		// int literal = dpll_get_and_erase_literal();

		// if (literal)
		// 	std::cout << literal << std::endl;
		// else
		// 	break;
		break;

		// while (true)
		// {

		// }
	}
}

#endif // DPLL_ALGORITHM_H_