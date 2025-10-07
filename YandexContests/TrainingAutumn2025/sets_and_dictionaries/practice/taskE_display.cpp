#include <iostream>
#include <stdint.h>
#include <map>
#include <vector>
#include <math.h>

/**
 * @brief
 * На табло написано n чисел. Каждую секунду
 * к последнему числу прибавляется последняя цифра этого числа.
 * Определите, какое число будет отображаться через k секунд.
 * 
 * На вход подаётся два числа n, k (0 <= n,k <= 10^9)
 * Ввод:
 * 1 10
 * Вывод:
 * 44
 * 
 * Ограничение времени - 1 секунда.
 * Ограничение памяти - 256 Мб.
 * 
 */

using namespace std;

#if 0
int main() {

    uint64_t n, k, old_n;
    int o = 0, T = 0, diff_T = 0, i;
    cin >> n;
    old_n = n;

    vector<map<int, int>> v(5);
    for (i = 0; i < 5; i++) {
        o = n % 10;
        n += o;

        v[i][o] = n;
        if (i > 0) {
            diff_T += o;
        }
    }
    // 4*T < k, T - неизвестный период
    // T < k/4, T∊Z, 4 - потому что ровно 4 числа повторяются в периоде

    cin >> k;
    if (k == 0) {
        cout << old_n << endl;
        return 0;
    }

    T = k/4;
    if (k % 4 == 0) {
        T -= 1;
    }
    k -= 1;

    // получаем первое число того периода, в котором лежит это число, которое принадлежит
    // v[1], так как в v[0] лежит число, которое повторяется один раз.
    uint64_t a_ti = (uint64_t)T*diff_T + v[1].begin()->second;
    int a_t1_idx = i = 4*T + 1, j = 2;

    for (; i < k && j < 5; i++, j++) {
        a_ti += v[j].begin()->first;
    }

    cout << a_ti << endl;

    return 0;
}
#endif

int main() {
    uint64_t n, k;
    cin >> n >> k;

    // если шагов нет — сразу выводим n
    if (k == 0) {
        cout << n << endl;
        return 0;
    }

    // выполняем первый шаг
    n += n % 10;
    k--;

    // если k==0 — готово
    if (k == 0) {
        cout << n << endl;
        return 0;
    }

    // если теперь последняя цифра 0 — больше ничего не изменится
    if (n % 10 == 0) {
        cout << n << endl;
        return 0;
    }

    // цикл из 4 шагов всегда добавляет +20
    uint64_t full_cycles = k / 4;
    n += full_cycles * 20ULL;

    // оставшиеся шаги
    uint64_t rem = k % 4;
    for (uint64_t i = 0; i < rem; ++i) {
        n += n % 10;
        if (n % 10 == 0) break; // на случай, если вошли в стационарность
    }

    cout << n << endl;
    return 0;
}
