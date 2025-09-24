#include <iostream>
#include <vector>

/**
 * Дана последовательность,
 * Требуется найти её наибольшую возрастающую подпоследовательность.
 * Напомним:
 * Последовательность x называется подпоследовательностью последовательности y,
 * если x получается из y удалением нескольких (возможно, нуля или всех) элементов.
 * Наибольшая возрастающая подпоследовательность - строго возрастающая
 * подпоследовательность наибольшей длины.
 * 
 * Формат ввода:
 * В первой строке входных данных задано число
 * N — длина последовательности (1 ≤ N ≤ 1000).
 * Во второй строке задается сама последовательность (разделитель — пробел).
 * Элементы последовательности — целые числа, не превосходящие 10000 по модулю.
 * Формат вывода:
 * Требуется вывести наибольшую возрастающую подпоследовательность
 * данной последовательности.
 * Если таких подпоследовательностей несколько,
 * необходимо вывести одну (любую) из них.
 * 
 * Пример:
 * Ввод:)
 * 6
 * 3 29 5 5 28 6
 * Вывод:
 * 3 5 28
 */

using namespace std;

void dp(vector<int> &input_a, vector<int> *output_a, size_t N) {
    vector<int> nvp_lens(N);
    nvp_lens.assign(N, 1);

    vector<int> parent(N);
    parent.assign(N, -1);

    int best_len = 0;
    int best_idx = 0;
    int i = 0;

    for (i = 1; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (input_a[j] < input_a[i] && nvp_lens[j] + 1 > nvp_lens[i]) {
                nvp_lens[i] = nvp_lens[j] + 1;
                parent[i] = j;
            }
        }
    }

    for (i = 1; i < N; i++) {
        if (nvp_lens[i] > best_len) {
            best_len = nvp_lens[i];
            best_idx = i;
        }
    }

    i = best_idx;
    while (i != -1) {
        output_a->push_back(input_a[i]);
        i = parent[i];
    }
}

int main(void) {
    int N = 0;
    cin >> N;
    cin.peek();

    vector<int> a(N), b;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        cin.peek();
    }

    dp(a, &b, N);
    for (int i = b.size()-1; i > 0; i--) {
        cout << b[i] << " ";
    }
    cout << b[0] << endl;

    return 0;
}