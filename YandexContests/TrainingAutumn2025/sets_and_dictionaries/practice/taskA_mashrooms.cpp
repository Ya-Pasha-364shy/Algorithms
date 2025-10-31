#include <iostream>
#include <set>

/**
 * @brief (Делёж грибов)
 * Вася и Маша ходили в лес и собрали n грибов,
 * для каждого гриба известен его вес a_i​.
 * Они выложили их в один ряд и решили делить следующим образом:
 * первый гриб берёт Вася, второй — Маша, третий — Вася, четвёртый — Маша и т.д.
 *
 * Вася очень любит грибы и не очень любит Машу. Количество радости Васи равно разности суммарного веса грибов,
 * доставшихся Васе, и суммарного веса грибов, доставшихся Маше. Т.е. радость вычисляется по формуле: ∑n_i= (−1)^(i−1)⋅ai = a1−a2+a3−…a_i 
 * Маша отвлеклась на минутку, и за это время Вася может выбрать любые два гриба и поменять их местами (а может и не менять).
 * Определите максимальную радость Васи, которую можно достичь не более чем одним обменом.
 * Формат ввода:
 * В первой строке содержится одно натуральное число n — количество грибов ( 2≤n≤10^5, 2≤n≤10^5).
 * Во второй строке содержится n чисел a_i​ — вес грибов ( 1≤a_i≤1000).
 * Формат вывода:
 * Выведите максимальную радость Васи.
 * Пример входных данных:
 * Ввод:
 * 11
 * 4 10 7 5 4 5 3 8 3 2 5
 * Вывод:
 * 10
 */

using namespace std;

int main(void) {
    int N = 0, mushroom_size = 0;
    cin >> N;

    multiset<int> vasyas_part;
    multiset<int> mashas_part;

    int vasyas_happiness = 0;

    for (int i = 0; i < N; i++) {
        cin >> mushroom_size;

        if (i % 2 == 0) {
            vasyas_part.insert(mushroom_size);
            vasyas_happiness += mushroom_size;
        } else {
            mashas_part.insert(mushroom_size);
            vasyas_happiness -= mushroom_size;
        }
    }
    int mashas_biggest_mushroom = *mashas_part.rbegin();
    int vasyas_smalles_mushroom = *vasyas_part.begin();
    int gap = 0;

    if (mashas_biggest_mushroom > vasyas_smalles_mushroom) {
        gap = 2 * (mashas_biggest_mushroom - vasyas_smalles_mushroom);
    }

    cout << vasyas_happiness+gap << endl;

    return 0;
}