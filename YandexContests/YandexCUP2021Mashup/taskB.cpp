#include <iostream>
#include <string>
#include <sstream>
#include <vector>

/**
 * Разработчики любят проводить свободное время за настольными играми.
 * Иногда это шахматы, иногда — UNO, а иногда — шашки.
 * Однако, когда неопытные игроки садятся за шашки,
 * они периодически допускают ошибки (прямо как в программировании!)
 * и не рубят шашку соперника, когда такая возможность есть.
 *
 * Чтобы избежать ошибок, разработчики решили написать программу,
 * которая будет по текущей позиции определять, можно ли сходить так,
 * чтобы срубить шашку противника. Но прямо сейчас у них много других
 * важных проектов, поэтому запрограммировать анализатор позиции попросили вас.
 *
 * Для тех, кто давненько не брал в руки шашек, напомним правила:
 *  + все шашки стоят на полях одного цвета;
 *  + одна шашка может срубить другую, если та стоит на соседней
 *    клетке по диагонали и при этом в следующей диагональной клетке
 *    в направлении соперника нет никакой другой шашки.
 *
 * В единственной строке выведите "Yes", если автор хода может срубить шашку
 * соперника, и "No" в противоположном случае.
*/

using namespace std;

#define WHITE_WORD "white"
#define BLACK_WORD "black"

int main() {
  bool w_step = true;
  int n, m = { 0 };
  string str = " ";
  istringstream stream;
  vector<pair<int, int>> positions_w_checkers,
                         positions_b_checkers; 

  getline(cin, str);
  stream.str(str);
  stream >> n; stream >> m;

  // парсинг координат шашек
  unsigned c = 0, count = 0;
  while (cin.good()) {
    getline(cin, str);
    if (str.empty()) {
      break;
    } else if (str.compare(WHITE_WORD) == 0) { 
      break;
    } else if (str.compare(BLACK_WORD) == 0) {
      w_step = false;
      break;
    }

    count = stoul(str);
    int left, right = { 0 };
    auto * pointer = ((c == 0) ? &positions_w_checkers :
                                 &positions_b_checkers);
    for (auto i = 0; i < count; i++) {
      getline(cin, str);
      stream.clear();
      stream.str(str);

      stream >> left; stream >> right;
      pointer->emplace_back(make_pair(left, right));
    }
    c++;
  }
  size_t positions_w = positions_w_checkers.size();
  size_t positions_b = positions_b_checkers.size();

  // ход белых
  if (w_step) {
    bool blocked_black_checkers[positions_b] = { false };
    for (size_t i = 0; i < positions_b; i++) {
      if (blocked_black_checkers[i]) continue;

      auto fixed_pair = positions_b_checkers[i];
      if ((fixed_pair.first == n and fixed_pair.second == 1) or
          (fixed_pair.first == 1 and fixed_pair.second == n) or
          (fixed_pair.first == n and fixed_pair.second == n) or
          (fixed_pair.first == 1 and fixed_pair.second == 1)) {
        blocked_black_checkers[i] = true;
        continue;
      }

      for (size_t j = 0; j < positions_b; j++) {
        if (j == i) continue;
        auto j_pair = positions_b_checkers[j];
        if (blocked_black_checkers[j] == true)
          continue;

        if (abs(j_pair.first  - fixed_pair.first)  == 1 and
            abs(j_pair.second - fixed_pair.second) == 1) {
          blocked_black_checkers[i] = true;
          blocked_black_checkers[j] = true;
        }
      }
    }

    for (size_t i = 0; i < positions_w; i++) {
      auto w_cur_pair = positions_w_checkers[i];
      for (size_t j = 0; j < positions_b; j++) {
        if (blocked_black_checkers[j])
          continue;
        auto b_cur_pair = positions_b_checkers[j];

        if (abs(w_cur_pair.first  - b_cur_pair.first)  == 1 and
            abs(w_cur_pair.second - b_cur_pair.second) == 1) {
          cout << "Yes" << endl;
          return 0;
        }
      }
    }
    cout << "No" << endl;
  } else { // ход чёрных
    bool blocked_white_checkers[positions_w] = { false };
    for (size_t i = 0; i < positions_w; i++) {
      if (blocked_white_checkers[i]) continue;

      auto fixed_pair = positions_w_checkers[i];
      if ((fixed_pair.first == n and fixed_pair.second == 1) or
          (fixed_pair.first == 1 and fixed_pair.second == n) or
          (fixed_pair.first == n and fixed_pair.second == n) or
          (fixed_pair.first == 1 and fixed_pair.second == 1)) {
        blocked_white_checkers[i] = true;
        continue;
      }

      for (size_t j = 0; j < positions_w; j++) {
        if (j == i) continue;
        auto j_pair = positions_w_checkers[j];
        if (blocked_white_checkers[j] == true)
          continue;

        if (abs(j_pair.first  - fixed_pair.first)  == 1 and
            abs(j_pair.second - fixed_pair.second) == 1) {
          blocked_white_checkers[i] = true;
          blocked_white_checkers[j] = true;
        }
      }
    }

    for (size_t i = 0; i < positions_b; i++) {
      auto b_cur_pair = positions_b_checkers[i];
      for (size_t j = 0; j < positions_w; j++) {
        if (blocked_white_checkers[j])
          continue;

        auto w_cur_pair = positions_w_checkers[i];
        if (abs(w_cur_pair.first  - b_cur_pair.first)  == 1 and
            abs(w_cur_pair.second - b_cur_pair.second) == 1) {
          cout << "Yes" << endl;
          return 0;
        }
      }
    }
    cout << "No" << endl;
  }
  return 0;
}