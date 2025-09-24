#include <iostream>
#include <vector>
#include <queue>

/**
 * @brief
 * Пещера представлена кубом, разбитым на N частей по каждому измерению
 * (то есть на N^3 кубических клеток). Каждая клетка может быть или пустой,
 * или полностью заполненной камнем.
 * Исходя из положения спелеолога в пещере, требуется найти,
 * какое минимальное количество перемещений по клеткам ему требуется,
 * чтобы выбраться на поверхность.
 * Переходить из клетки в клетку можно, только если они обе свободны и имеют общую грань.
 * Формат ввода:
 * В первой строке содержится число N (1≤N≤30).
 * Далее следует N блоков.
 * Блок состоит из пустой строки и N строк по N символов:
 * # - обозначает клетку, заполненную камнями, точка - свободную клетку.
 * Начальное положение спелеолога обозначено заглавной буквой S.
 * Первый блок представляет верхний уровень пещеры,
 * достижение любой свободной его клетки означает выход на поверхность.
 * Выход на поверхность всегда возможен.
 * Формат вывода:
 * Вывести одно число - длину пути до поверхности.
 */

using namespace std;

struct Coord {
    int z, x, y;
    bool operator==(const Coord &o) const {
        return z == o.z && x == o.x && y == o.y;
    }
};

struct hash_coord {
    size_t operator()(const Coord &c) const {
        return ((c.z * 31 + c.x) * 31 + c.y);
    }
};

typedef vector<vector<vector<int>>> cave_t;

int bfs(const cave_t &cave, Coord start, int N) {
    queue<Coord> q;
    cave_t dist(N, vector<vector<int>>(N, vector<int>(N, -1)));

    q.push(start);
    dist[start.z][start.x][start.y] = 0;

    int dz[6] = {1, -1, 0, 0, 0, 0};
    int dx[6] = {0, 0, 1, -1, 0, 0};
    int dy[6] = {0, 0, 0, 0, 1, -1};

    while (!q.empty()) {
        Coord v = q.front();
        q.pop();

        if (v.z == 0) {
            return dist[v.z][v.x][v.y];
        }

        for (int dir = 0; dir < 6; dir++) {
            int shift_z = v.z + dz[dir];
            int shift_x = v.x + dx[dir];
            int shift_y = v.y + dy[dir];

            if (shift_z >= 0 && shift_z < N &&
                shift_x >= 0 && shift_x < N &&
                shift_y >= 0 && shift_y < N &&
                cave[shift_z][shift_x][shift_y] == 1 && // переход существует
                dist[shift_z][shift_x][shift_y] == -1)  // и вершина ещё не была посещена
            {
                dist[shift_z][shift_x][shift_y] = dist[v.z][v.x][v.y] + 1;
                q.push({shift_z, shift_x, shift_y});
            }
        }
    }

    return -1;
}

int main() {
    int N;
    cin >> N;

    cave_t cave(N, vector<vector<int>>(N, vector<int>(N)));
    Coord start{0, 0, 0};

    for (int z = 0; z < N; z++) {
        string line;
        for (int x = 0; x < N; x++) {
            cin >> line;
            for (int y = 0; y < N; y++) {
                char c = line[y];
                if (c == '#') {
                    cave[z][x][y] = 0;
                } else if (c == '.') {
                    cave[z][x][y] = 1;
                } else if (c == 'S') {
                    cave[z][x][y] = 1;
                    start = {z, x, y};
                }
            }
        }
    }

    cout << bfs(cave, start, N) << endl;
    return 0;
}
