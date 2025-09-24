#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

/**
 * @brief
 * В неориентированном графе требуется найти минимальный путь между двумя вершинами.
 * 
 * Первым на вход поступает число N – количество вершин в графе (1≤N≤100).
 * Затем записана матрица смежности (0 обозначает отсутствие ребра, 1 – наличие ребра).
 * Далее задаются номера двух вершин – начальной и конечной ( 1 ≤ s , e ≤ N )
 * 
 * Выведите сначала L – длину кратчайшего пути (количество ребер, которые нужно пройти), а потом сам путь.
 * Если путь имеет длину 0, то его выводить не нужно, достаточно вывести длину.
 * Необходимо вывести путь (номера всех вершин в правильном порядке). Если пути нет, нужно вывести -1.
 */

int bfs(const vector<vector<int>> &mtx, int N, int s_v, int f_v, vector<int> *path) {
    if (s_v == f_v) {
        return 0;
    }
    vector<bool> visited(N, false);
    vector<int> parent(N, -1);
    queue<int> neighbors;
    
    neighbors.push(s_v);
    visited[s_v] = true;

    while (!neighbors.empty()) {
        int v = neighbors.front();

        for (int i = 0; i < N; i++) {
            if (mtx[v][i] != 0 && visited[i] != true) {
                visited[i] = true;
                parent[i] = v;

                if (i == f_v) {
                    int _v = f_v;
                    while (_v != -1) {
                        path->push_back(_v+1);
                        _v = parent[_v];
                    }
                    return path->size() - 1;
                }
                neighbors.push(i);
            }
        }
        neighbors.pop();
    }
    return -1;
}

int main(void) {
    vector<int> path;
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

    int res = bfs(matrix, N, start_vertex-1, finish_vertex-1, &path);
    cout << res << endl;

    if (res > 0) {
        for (int i = path.size() - 1; i > 0; i--) {
            cout << path[i] << " ";
        }
        cout << path[0] << endl;
    }

    return 0;
}