#include <iostream>
#include <vector>
#include <queue>
#include <sstream>

/**
 * @brief
 * Метрополитен состоит из нескольких линий метро.
 * Все станции метро в городе пронумерованы натуральными числами
 * от 1 до N. На каждой линии расположено несколько станций.
 * Если одна и та же станция расположена сразу на нескольких линиях,
 * то она является станцией пересадки и на этой станции можно пересесть
 * с любой линии, которая через нее проходит, на любую другую
 * (опять же проходящую через нее).
 * Напишите программу, которая по данному вам описанию метрополитена определит, с каким минимальным числом пересадок можно добраться со станции A на станцию B. Если данный метрополитен не соединяет все линии в одну систему, то может так получиться, что со станции A на станцию B добраться невозможно,
 * в этом случае ваша программа должна это определить.
 * Формат ввода:
 * Сначала вводится число N — количество станций метро в городе (2 ≤ N ≤ 100).
 * Далее следует число M — количество линий метро (1 ≤ M ≤ 20).
 * Далее идет описание M линий. Описание каждой линии состоит из числа
 * Pi​ — количество станций на этой линии (2 ≤ Pi​ ≤ 50) и Pi​ чисел,
 * задающих номера станций, через которые проходит линия (ни через какую станцию линия не проходит дважды).
 * Затем вводятся два различных числа:
 * A — номер начальной станции, и B — номер станции, на которую нам нужно попасть.
 * При этом если через станцию A проходит несколько линий, то мы можем спуститься на любую из них.
 * Так же если через станцию B проходит несколько линий, то нам не важно, по какой линии мы приедем.
 * Формат вывода:
 * Выведите минимальное количество пересадок, которое нам понадобится. Если добраться со станции A на станцию B невозможно,
 * программа должна вывести одно число -1.
 */

using namespace std;

int analyze(const vector<vector<int>> &a, int from, int to, int N, int M) {
    vector<vector<int>> metro_map(a.size(), vector<int>(N, 0));

    for (int i = 0; i < a.size(); i++) {
        for (int j = 1; j < a[i].size(); j++) {
            metro_map[i][a[i][j]] = 1;
        }
    }

    queue<pair<int, vector<int>>> q;
    vector<bool> visited(N, false);
    vector<int> parent(M, -1);
    int transimitions = -1;

    for (int i = 0; i < metro_map.size(); i++) {
        if (metro_map[i][from] == 1) {
            q.push({i, metro_map[i]});
            visited[i] = true;
        }
    }

    while (!q.empty()) {
        const auto &metro_info = q.front().first; 
        const auto &metro_line = q.front().second;

        for (int i = 1; i < N; i++) {
            if (i == to && metro_line[i] == 1) {
                transimitions = 0;
                int cur_metro_line = metro_info;
                while (parent[cur_metro_line] != -1) {
                    cur_metro_line = parent[cur_metro_line];
                    transimitions++;
                }
                return transimitions;
            }
            for (int j = 0; j < metro_map.size(); j++) {
                if (j == metro_info) {
                    continue;
                }
                if (metro_map[j][i] == 1 && metro_line[i] == 1) {
                    if (visited[j] != true) {
                        parent[j] = metro_info;
                        q.push({j, metro_map[j]});
                        visited[j] = true;
                    }
                }
            }

        }

        q.pop();
    }

    return transimitions;
}


int main(void) {
    int N = 0, M = 0, tmp_num = 0, A = 0, B = 0;
    if (scanf("%d\n", &N) != 1) {
        return 1;
    }
    if (scanf("%d\n", &M) != 1) {
        return 1;
    }
    vector<vector<int>> a(M);
    for (int i = 0; i < M; i++) {
        string tmp;
        getline(cin, tmp);

        stringstream ss(tmp);
        while (ss >> tmp_num) {
            a[i].push_back(tmp_num);
        }
    }
    if (scanf("%d %d", &A, &B) != 2) {
        return 1;
    }

    cout << analyze(a, A, B, N+1, M) << endl;

    return 0;
}