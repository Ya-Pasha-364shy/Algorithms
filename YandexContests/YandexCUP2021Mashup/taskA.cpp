#include <iostream>
#include <string>
#include <math.h>

/**
 * Сравните два числа в двоичной системе счисления.
 * Числа представлены последовательностью слов без пробелов
 * обозначающих цифры (0 — zero, 1 — one).
*/

#define ONE  "one"
#define ZERO "zero"

using namespace std;

void convertFromWordsToDecimals(string src, long unsigned int & dst) {
  bool need_to_track_ones_after = false;
  unsigned count_of_ones = 0, order = 0;
  string tmp = "";
  string tmp_result = "";

  for (auto i = 0; i < src.size(); i++) {
    tmp += src[i];
    if (tmp.size() == 3 and 0 == tmp.compare(ONE)) {
      if (not need_to_track_ones_after) {
        dst += pow(10, count_of_ones++);
      } else {
        ++order;
      }
      tmp.erase();
    } else if (tmp.size() == 4 and 0 == tmp.compare(ZERO)) {
      if (order) {
        dst *= pow(10, order);
        for (int i = 0; i < order; i++) {
          dst += pow(10, i);
        }
      }
      dst *= 10;
      need_to_track_ones_after = true;
      tmp.erase();
      order = 0;
    }
  }
  if (order) {
    dst *= pow(10, order);
    for (int i = 0; i < order; i++) {
      dst += pow(10, i);
    }
  }
}

int main(void) {
  string num1, num2;
  cin >> num1;
  cin >> num2;

  long unsigned int dec_num1 = 0, dec_num2 = 0;
  convertFromWordsToDecimals(num1, dec_num1);
  convertFromWordsToDecimals(num2, dec_num2);

  cout << endl;
  cout << dec_num1 << endl;
  cout << dec_num2 << endl;
  cout << endl;

  if (dec_num1 > dec_num2)
    cout << ">" << endl;
  else if (dec_num1 < dec_num2)
    cout << "<" << endl;
  else
    cout << "=" << endl;

  return 0;
}