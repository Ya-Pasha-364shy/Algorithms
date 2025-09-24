#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

/**
 * @brief
 * Дан неориентированный граф. Найдите длину минимального пути между двумя вершинами.
 * В первой строке записано целое число N ( 1 ≤ N ≤ 100) – количество вершин в графе.
 * Далее записывается матрица смежности — N строк, в каждой из которых содержится N
 * чисел 0 или 1, разделённых пробелом. Число 0 означает отсутствие ребра, а 1 — наличие ребра.
 * 
 * В последней строке задаются номера двух вершин — начальной и конечной.
 * Вершины нумеруются с единицы.
 */

int bfs(const vector<vector<int>> &mtx, int N, int s_v, int f_v) {
    unordered_map<int, bool> visited_map;
    vector<int> distance(N, -1);
    queue<int> neighbors;
    
    neighbors.push(s_v);
    visited_map[s_v] = true;
    distance[s_v] = 0;

    while (!neighbors.empty()) {
        int v = neighbors.front();

        for (int i = 0; i < N; i++) {
            if (mtx[v][i] != 0 && v != i && visited_map[i] != true) {
                visited_map[i] = true;
                distance[i] = distance[v] + 1;

                if (i == f_v) {
                    return distance[i];
                }

                neighbors.push(i);
            }
        }
        neighbors.pop();
    }

    return distance[f_v];
}


int main(void) {
    int N, start_vertex, finish_vertex;
    cin >> N;

    vector<vector<int>> matrix(N, vector<int>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> matrix[i][j];
        }
    }

    cin >> start_vertex;
    cin >> finish_vertex;

    cout << bfs(matrix, N, start_vertex-1, finish_vertex-1) << endl;

    return 0;
}