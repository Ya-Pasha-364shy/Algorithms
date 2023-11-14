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
#define TEST_END_SIGNATURE '%'
#define NEW_LINE_SIGNATURE "\n"

class dpll_sequence
{
private:
	bool dpll_contradiction_ = false;

	std::set<int> dpll_literals_all_saved_leaking_;
	std::set<int> dpll_literals_all_saved_;

	std::set<int> dpll_literals_proposed_leaking_;
	std::set<int> dpll_literals_proposed_;

	std::set<size_t> dpll_clause_idxs;

	std::vector<std::list<int>> dpll_clauses_; // S
public:
	bool occurs_literals_inited = false;
	std::map<int, std::list<size_t>> occurs_literals_;

	dpll_sequence() = delete;
	dpll_sequence(std::vector<std::string> & dpll_clauses);

	/* helpers */
	std::vector<std::list<int>> get_clauses()
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
	 * 
	 * DEPRECATED (в этом задании).
	*/
	// void dpll_monotone_variable_fixing();

	/*
	 * @brief
	 * Заполняет множество индексов клауз, подлежащих удалению относительно предложенных 
	 * единичных литералов.
	*/
	void dpll_clauses_of_proposed();

	void dpll_init_map_of_occurences();

	/*
	* @brief
	* Выбирает наиболее часто встерчающийся литерал в клаузах всей формулы.
	* возвращает 0, если формула пуста.
	*/
	int dpll_choice_literal();

	/* @brief
	 * Пока последовательность предложений содержит одиночную клаузу - предложение,
	 * имеющее один литерал - устанавливаем его значение = true. Удаляет все клаузы,
	 * которые содержат данный литерал, а также появление контрарного литерала.
	 * 
	 * Может найти противоречие. Если контрарный литерал был удалён из одиночной клаузы,
	 * значит, что возникло противоречие.
	 * 
	 * Используется правило распространения единицы !
	*/
	void dpll_unit_resolution(int literal);

	/* @brief
	 * Выбирает литерал, любой без отрицания, такой, что ещё не был выбран
	 * из всей формулы. Затем удаляет этот литерал, т.к. он уже был выбран для
	 * упрощения формулы.
	*/
	int dpll_get_and_erase_literal();

	/*
	 * @brief
	 * тоже самое но среди предложенных
	*/
	int dpll_get_and_erase_literal_from_proposed();

	void dpll_remove_inverse_occurences();

	void dpll_remove_inverse_occurences(int literal);

	/* @brief
	 * Обновляет "вёдра воды";
	*/
	friend void refresh_water_buckets(dpll_sequence * obj)
	{
		if (obj->dpll_literals_all_saved_leaking_.empty())
			obj->dpll_literals_all_saved_leaking_ = obj->dpll_literals_all_saved_;
		else if (obj->dpll_literals_proposed_leaking_.empty())
			obj->dpll_literals_proposed_leaking_ = obj->dpll_literals_proposed_;
	}

	/* @brief
	 * Возвращает любой литерал (без отрицания) из всей формулы.
	 * Нужно будет пройтись по всем клаузам и посмотреть, какой литерал встречается
	 * чаще всего и выбрать его. Также - с отрицательным
	*/
	int dpll_get_literal();

	/* @brief
	 * Задаёт шаг.Возвращает `true`, если формула выполнятся.
	 * Иначе - false.
	*/
	bool dpll_orchestrator();

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

	for (std::string line: dpll_clauses)
	{
		if (line.empty())
			continue;

		std::istringstream stream(line);
		while (stream >> number)
		{
			tmp_clause.emplace_back(number);
			if (number > 0)
				dpll_literals_all_saved_leaking_.insert(number);
			else
				dpll_literals_all_saved_leaking_.insert(abs(number));
		}

		dpll_clauses_.emplace_back(tmp_clause);
		tmp_clause.clear();
	}
	print_clauses(dpll_clauses_);
	dpll_literals_all_saved_ = dpll_literals_all_saved_leaking_;
}

/* @brief
 * infinite water backet
*/
int dpll_sequence::dpll_get_literal()
{
	static std::set<int>::iterator lit = dpll_literals_all_saved_.begin();
	int returned_value;

	if (lit != dpll_literals_all_saved_.end())
	{
		returned_value = *lit;
		++lit;
		return returned_value;
	}
	else
	{
		lit = dpll_literals_all_saved_.begin();
		returned_value = *lit;
		return returned_value;
	}
}

int dpll_sequence::dpll_get_and_erase_literal()
{
	int returned_value = *dpll_literals_all_saved_leaking_.begin();
	dpll_literals_all_saved_leaking_.erase(returned_value);
	return returned_value;
}

int dpll_sequence::dpll_get_and_erase_literal_from_proposed()
{
	int returned_value = *(dpll_literals_proposed_leaking_.begin());
	dpll_literals_proposed_leaking_.erase(returned_value);
	return returned_value;
}

void dpll_sequence::dpll_init_map_of_occurences()
{
	if (occurs_literals_inited)
		return;
	else
	{
		bool found;
		int literal;
		size_t number_of_clauses = dpll_clauses_.size();

		while (0 != (literal = dpll_get_and_erase_literal()))
		{
			unsigned occurences_of_literal = 0;
			std::list<size_t> tmp_occurences_of_literal;

			for (size_t i = 0; i < number_of_clauses; i++)
			{
				auto fixed = dpll_clauses_[i];
				found = (std::find(fixed.begin(), fixed.end(), literal) != fixed.end());
				if (found)
					tmp_occurences_of_literal.emplace_back(i);
			}
			occurs_literals_[literal] = std::move(tmp_occurences_of_literal);
		}
		refresh_water_buckets(this);
	}

}

int dpll_sequence::dpll_choice_literal()
{
	if (dpll_clauses_.empty())
		return 0;

	dpll_init_map_of_occurences();

	auto max_pair = std::max_element(occurs_literals_.begin(), occurs_literals_.end(),
	                    [] (const std::pair<int, std::list<size_t>> & less, const std::pair<int, std::list<size_t>> & greater)
	                    {
	                        return less.second.size() < greater.second.size();
	                    });
	return max_pair->first;
}

void dpll_sequence::dpll_clauses_of_proposed()
{
	bool found;
	int literal;
	size_t number_of_clauses = dpll_clauses_.size();

	while (0 != (literal = dpll_get_and_erase_literal_from_proposed()))
	{
		for (size_t i = 0; i < number_of_clauses; i++)
		{
			auto fixed = dpll_clauses_[i];
			found = (std::find(fixed.begin(), fixed.end(), literal) != fixed.end());
			if (found)
				dpll_clause_idxs.insert(i);
		}
	}
	refresh_water_buckets(this);
}

inline int inverse(int positive)
{
	return positive * (-1);
}

void dpll_sequence::dpll_remove_inverse_occurences()
{
	int literal;
	size_t number_of_clauses = dpll_clauses_.size();

	while (0 != (literal = dpll_get_and_erase_literal_from_proposed()))
	{
		for (size_t i = 0; i < number_of_clauses; i++)
		{
			auto & fixed = dpll_clauses_[i];
			auto to_remove = std::find(fixed.begin(), fixed.end(), inverse(literal));
			if (to_remove != fixed.end())
			{
				if (fixed.size() == 1)
				{
					dpll_contradiction_ = true;
					dpll_clauses_.erase(dpll_clauses_.begin() + i);
					return;
				}
				fixed.erase(to_remove);
			}
		}
	}
}

void dpll_sequence::dpll_remove_inverse_occurences(int literal)
{
	size_t number_of_clauses = dpll_clauses_.size();

	for (size_t i = 0; i < number_of_clauses; i++)
	{
		auto & fixed = dpll_clauses_[i];
		auto to_remove = std::find(fixed.begin(), fixed.end(), inverse(literal));
		if (to_remove != fixed.end())
		{
			if (fixed.size() == 1)
			{
				dpll_contradiction_ = true;
				dpll_clauses_.erase(dpll_clauses_.begin() + i);
				return;
			}
			fixed.erase(to_remove);
		}
	}
}

/* DEPRECATED
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
	refresh_water_bucket(this);

	for (auto & literal_occurs: monotonic_occurs_literals)
	{
		auto occurences = literal_occurs.second;
		for (auto it = occurences.begin(); occurences.size() > 1 && it != occurences.end(); it++)
		{
			unique_occur_positions.insert(*it);
		}
	}

	auto beg_it = dpll_clauses_.begin();
	for (size_t occurence : unique_occur_positions)
	{
		dpll_clauses_.erase(beg_it + occurence);
	}
}
*/

void dpll_sequence::dpll_unit_resolution(int literal)
{
	size_t number_of_clauses = dpll_clauses_.size();
	if (not literal)
	{
		for (size_t i = 0; i < number_of_clauses; i++)
		{
			if (dpll_clauses_[i].size() == 1)
			{
				// сохраняем литералы всех единичных клауз
				dpll_literals_proposed_leaking_.insert(*dpll_clauses_[i].begin());
			}
		}
		if (not dpll_literals_proposed_leaking_.empty())
		{
			dpll_literals_proposed_ = dpll_literals_proposed_leaking_;

			dpll_clauses_of_proposed();
			if (not dpll_clause_idxs.empty())
			{
				// удаляем из формулы все клаузы, содержащие единицы
				auto begin_clauses_it = dpll_clauses_.begin();
				for (size_t idx: dpll_clause_idxs)
				{
					// нужно ли удалять единичные клаузы, литералы которых были выбраны для выполнения правила ?
					dpll_clauses_.erase(begin_clauses_it + idx);
				}
			}
			// удаляем из формулы все появления обратных единиц
			dpll_remove_inverse_occurences();
			if (dpll_contradiction_)
			{
				// конфликт
				return;
			}
		}
		else
		{
			// единичных клауз нет
			return;
		}
	}
	else if (literal != 0)
	{
		if (not occurs_literals_[literal].empty() and not dpll_clauses_.empty())
		{
			auto begin_clauses_it = dpll_clauses_.begin();
			for (size_t idx: occurs_literals_[literal])
			{
				// нужно ли удалять единичную клаузу, литерал которой был выбран для выполнения правила ?
				dpll_clauses_.erase(begin_clauses_it + idx);
			}
			// удаляем появления обратных единиц
			dpll_remove_inverse_occurences(literal);
			if (dpll_contradiction_)
			{
				return;
			}
		}
	}
	return;
}

bool dpll_sequence::dpll_orchestrator()
{
	int tmp_literal_first = 0;
	int tmp_literal_second = 0;
	std::list<int> tmp;

	while (true)
	{
		if (not tmp_literal_first and not tmp_literal_second)
		{
			dpll_unit_resolution(0);
		}
		else
		{
			if (tmp_literal_first)
			{
				dpll_unit_resolution(tmp_literal_first);
			}
			if (tmp_literal_second && not dpll_clauses_.empty())
			{
				tmp.push_back(tmp_literal_second);
				dpll_clauses_.emplace_back(std::move(tmp));
				if (occurs_literals_.find(tmp_literal_second) != occurs_literals_.end())
				{
					std::list<size_t> tmp_occurence; tmp_occurence.push_back(dpll_clauses_.size() - 1);
					occurs_literals_[tmp_literal_second] = std::move(tmp_occurence);
				}
				else
				{
					occurs_literals_[tmp_literal_second].emplace_back(dpll_clauses_.size() - 1);
				}
				dpll_unit_resolution(tmp_literal_second);
			}
		}

		if (dpll_contradiction_)
		{
			return false;
		}
		if (dpll_clauses_.empty())
		{
			return true;
		}

		// избавляемся от прошлых литералов, чтобы взять новые
		if (tmp_literal_first)
		{
			occurs_literals_.erase(tmp_literal_first);
		}
		if (tmp_literal_second)
		{
			occurs_literals_.erase(tmp_literal_second);
		}

		tmp_literal_first = dpll_choice_literal();
		if (not tmp_literal_first)
			return true;

		tmp_literal_second = inverse(tmp_literal_first);

		tmp.push_back(tmp_literal_first);
		dpll_clauses_.emplace_back(std::move(tmp));
		occurs_literals_[tmp_literal_first].emplace_back(dpll_clauses_.size() - 1);
	}

	return false;
}

#endif // DPLL_ALGORITHM_H_
