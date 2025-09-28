#include <iostream>
#include <vector>

/**
 * @brief
 * На вход подаётся две строки, необходимо найти
 * самую длиную общую подпоследовательность букв,
 * вывести её и её длину.
 * 
 * Пример:
 * Вход:
 * FISH
 * FOSH
 * Вывод:
 * 3
 * FSH
 */

using namespace std;

string dp2(const string &s1, const string &s2) {
    string subseq;
    int n = s1.size() + 1, i = 0;
    int m = s2.size() + 1, j = 0;
    char s1_tmp, s2_tmp;

    vector<vector<int>> dp(n, vector<int>(m, 0));

    for (i = 1; i < n; i++) {
        s1_tmp = s1[i-1];
        for (j = 1; j < m; j++) {
            s2_tmp = s2[j-1];
            if (s1_tmp == s2_tmp) {
                dp[i][j] = dp[i-1][j-1] + 1;
                if (i == j) {
                    subseq += s1_tmp;
                }    
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return subseq;
}

int main(void) {
    string s1, s2, max_subsequence;
    cin >> s1 >> s2;

    max_subsequence = dp2(s1, s2);

    cout << max_subsequence.size() << endl << max_subsequence << endl;

    return 0;
}