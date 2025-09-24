#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

/**
 * Дано натуральное число N. Необходимо представить его в виде суммы точных кубов, содержащей наименьшее число слагаемых.
 * Программа должна вывести это число слагаемых.
 * Формат ввода:
 * Программа получает на вход натуральное число N, не превосходящее 1 0 6 106
 * Формат вывода:
 * Программа должна вывести единственное натуральное число
 */

void dp(size_t N, vector<int> *arr) {
    vector<int> cubes;
    int inf = 0x7FFFFFFF;
    for (int i = 1; (int)pow(i, 3) <= N; i++) {
        cubes.push_back((int)pow(i, 3));
    }
    for (int i = 1; i < N+1; i++) {
        arr->at(i) = inf;
    }
    arr->at(0) = 0;

    for (const auto &cube : cubes) {
        for (int i = cube; i < N+1; i++) {
            arr->at(i) = min(arr->at(i), arr->at(i - cube) + 1);
        }
    }
}


int main() {
    int N;
    cin >> N;
    
    vector<int> arr(N+1);
    dp(N, &arr);
    cout << arr[N] << endl;

    return 0;
}