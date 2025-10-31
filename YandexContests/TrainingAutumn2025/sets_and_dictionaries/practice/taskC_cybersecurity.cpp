#include <iostream>
#include <string>
#include <map>
#include <set>
#include <stdint.h>

/**
 * @brief
 * На работе у Васи требуют менять пароль каждую неделю,
 * причём новый пароль не должен совпадать ни с одним из предыдущих.
 * Любимый Васин пароль — это строка s, состоящая из строчных английских букв.
 * Этот пароль он использует первую неделю. Придумывать и запоминать новые пароли Васе лень.
 * Поэтому он решил менять местами пару букв в исходном пароле s и получать новый пароль.
 * Определите, сколько недель Вася сможет генерировать новые пароли с учетом пароля s на первой неделе.
 * 
 * Не проходит 9 тест.
 */

using namespace std;

#if 0
uint64_t factorial(int v) {
    if (v == 0) {
        return 1;
    }
    return v * factorial(v-1);
}

int main() {
    string s;
    cin >> s;
    int n_s = s.size();
    int k = 2;

    map<char, int> words_cnt;
    for (const char &c : s) {
        words_cnt[c]++;
    }

    uint64_t all_possible_changes = factorial(n_s) / (factorial(n_s - k) * factorial(k));
    for (const auto &pair : words_cnt) {
        if (pair.second > 1) {
            n_s = pair.second;
            uint64_t meaningless_changes_cnt = factorial(n_s) / (factorial(n_s - k) * factorial(k));
            all_possible_changes -= meaningless_changes_cnt;
        }
    }
    cout << all_possible_changes + 1 << endl;

    return 0;
}
#endif

int main() {
    string s;
    cin >> s;
    int n_s = s.size(), tmp = 0;

    map<char, int> words_cnt;
    for (const char &c : s) {
        words_cnt[c]++;
    }

    uint64_t all_possible_changes = n_s * (n_s-1)/2;
    for (const auto &pair : words_cnt) {
        tmp = pair.second;
        all_possible_changes -= tmp * (tmp-1)/2;
    }

    cout << all_possible_changes+1 << endl;

    return 0;
}