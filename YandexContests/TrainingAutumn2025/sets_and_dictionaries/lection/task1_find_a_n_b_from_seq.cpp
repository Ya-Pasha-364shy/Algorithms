#include <iostream>
#include <set>

/**
 * @brief
 * Дана последовательность положительных чисел длиной N и число X 
 * Нужно найти из последовательности два различных числа A,B таких,
 * что A+B = X или вернуть пару (0,0), если такой пары нет.
 * 
 * Пример:
 * Ввод:
 * 10 6
 * 0 1 2 3 4 5 6 7 8 9
 * Вывод:
 * 4 2
 */

using namespace std;

int main() {
    int N, x, a, b, i;
    cin >> N >> x;

    multiset<int> seq; 

    for (i = 0; i < N; i++) {
        cin >> a;
        b = x-a;
        if (seq.find(b) != seq.end()) {
            cout << a << " " << b << endl; 
            return 0;
        }
        seq.insert(a);
    }
    cout << "0 0" << endl;

    return 0;
}