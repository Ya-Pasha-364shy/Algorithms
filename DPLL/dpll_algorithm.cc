#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "dpll_algorithm.hpp"

using namespace std;
/*
 * @brief
 * Здесь представлен алгоритм DPLL,
 * предназначенный для того, чтобы делать
 * вердикт о конъюнктивной нормальной форме о
 * том, является ли она выполнимой или нет.
 * 
 * Если формула выполнима, то программа возвращает - SAT,
 *                                           иначе - UNSAT.
 * 
 * Требования к реализации:
 * - нет рекурсий и утечек памяти, а также ошибок доступа к памяти
 * - вход - файл в формате DIMACS
 * - производительность не более 30 секунд на тесте hanoi4.
 * - потребление памяти не более 8 Мб (8 * 1024 * 1024 байт)
*/

template <typename T>
static void print_clauses(const vector<T> vector)
{
	cout << "[ " << endl;
	for (auto item: vector)
	{
		cout << item << endl;
	}
	cout << "]" << endl;
}

int main(int argc, char * argv[])
{
	ifstream cnf;
	string path_to_cnf;
	vector<string> clause_sequences;

	if (argc >= 2)
	{
		path_to_cnf = argv[1];
		cnf.open(path_to_cnf);
	}
	else
		return EXIT_FAILURE;
	
	if (cnf.is_open())
	{
		bool remember_clause = false;
		size_t idx;
		while (cnf.good())
		{
			std::string tmp_line;
			getline(cnf, tmp_line);

			if (tmp_line.find(COMMENT_SIGNATURE)   == 0 or
			    tmp_line.find(PREAMBULE_SIGNATURE) == 0)
				continue;

			if (string::npos != (idx = tmp_line.find('0')))
			{
				if (idx == (tmp_line.size() - 1))
				{
					tmp_line.pop_back();
				}
				else
				{
					string substr = tmp_line.substr(0, idx);
					clause_sequences.emplace_back(substr);

					// смещение до числа
					substr = tmp_line.substr(idx + 2, tmp_line.size() - 1);
					clause_sequences.emplace_back(substr);
					remember_clause = true;
					continue;
				}
			}
			else if (not remember_clause)
			{
				clause_sequences.emplace_back(tmp_line);
				remember_clause = true;
				continue;
			}
			if (remember_clause)
			{
				/* поддержка случая, когда каждая строка не заканчивается нулём */
				clause_sequences.back() += " " + tmp_line;
				continue;
			}
			clause_sequences.emplace_back(tmp_line);
			remember_clause = false;
		}
	}
	else
	{
		cerr << "Unable to open .cnf file" << endl;
		return EXIT_FAILURE;
	}

	dpll_sequence dpll(clause_sequences);

	print_clauses(dpll.get_clauses());
	std::cout << "ORCHESTRATOR START !" << std::endl;

	dpll.dpll_orchestrator();


	return EXIT_SUCCESS;
}
