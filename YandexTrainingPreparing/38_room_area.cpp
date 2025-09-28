#include <iostream>
#include <vector>
#include <stack>

/**
 * @brief
 * Требуется вычислить площадь комнаты в квадратном лабиринте.
 *
 * Формат ввода:
 * В первой строке вводится число N – размер лабиринта (3≤N≤10).
 * В следующих N строках задан лабиринт (‘.’ – пустая клетка, ‘*’ – стенка).
 * И наконец, последняя строка содержит два числа – номер строки и столбца клетки,
 * находящейся в комнате, площадь которой необходимо вычислить.
 * Гарантируется, что эта клетка пустая и что лабиринт окружен стенками со всех сторон.
 * Переходить из клетки в клетку можно, если они имеют общую грань !!!
 *
 * Формат вывода:
 * Требуется вывести единственное число – количество пустых клеток в данной комнате.
 */

using namespace std;

typedef vector<vector<int>> room_int_t;

struct coord_t {
    int y, x;
};

int dfs(const room_int_t &room, int s_i, int s_j, int N) {
    room_int_t distances(N, vector<int>(N, -1));
    stack<coord_t> s;
    coord_t tmp;
    int dy[4] =  {-1, 1, 0, 0};
    int dx[4] =  {0, 0, -1, 1};

#if 0
    // если бы было можно перемещаться по диагонали
    int dy[3] = {0, 1, -1};
    int dx[3] = {-1, 1, 0};
    // тогда в теле while один цикл надо было заменить на два
    for (int i = 0; i < sizeof(dy)/sizeof(dy[0]); i++)
        for (int j = 0; j < sizeof(dx)/sizeof(dx[0]); j++) {
            int res_x = tmp.x + dx[j];
            int res_y = tmp.y + dy[i];
            if (res_x >= 0 && res_x < N && res_y >= 0 && res_y < N &&
                distances[res_y][res_x] < 0 && room[res_x][res_y] == 1)
            {
                distances[res_y][res_x] = 1;
                s.push({res_x, res_y});
            }
        }
#endif

    int result_square = 0;

    s.push({s_i, s_j});
    distances[s_i][s_j] = 1;
    
    while (!s.empty()) {
        tmp = s.top(); s.pop();
        result_square++;

        for (int i = 0; i < 4; i++) {
            int res_x = tmp.x + dx[i];
            int res_y = tmp.y + dy[i];

            if ((res_x >= 0 && res_x < N) &&
                (res_y >= 0 && res_y < N) &&
                (room[res_y][res_x] == 1) &&
                (distances[res_y][res_x] < 0))
            {
                distances[res_y][res_x] = 1;
                s.push({res_y, res_x});
            }
        }
    }
    return result_square;
}


int main(void) {
    int N, start_i = 0, start_j = 0;
    cin >> N;

    room_int_t room(N, vector<int>(N, 0));
    string line;

    for (int i = 0; i < N; i++) {
        cin >> line;
        for (int j = 0; j < line.size(); j++) {
            char c = line[j];
            if (c == '.') {
                room[i][j] = 1;
            }
        }
    }

    cin >> start_i >> start_j;

    cout << dfs(room, start_i-1, start_j-1, N) << endl;

    return 0;
}