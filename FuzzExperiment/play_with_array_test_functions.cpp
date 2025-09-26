//
// Created by rkolyan on 04.06.2024.
//

#include <vector>
#include <cstdlib>

unsigned int play_with_array_right(const std::vector<long int> &array) {
    unsigned int N = array.size(), diff = 0, tmp_diff = 0;
    long int sign = 1;

    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < N - i; j++) {
            tmp_diff = 0;
            sign = 1;
            for (unsigned int k = 0; k <= i; k++) {
                tmp_diff += sign * array[j + k];
                sign = -sign;
            }
            if (abs(tmp_diff) > diff)
                diff = abs(tmp_diff);
        }
    }

    return diff;
}

unsigned int play_with_array_my(const std::vector<long int> &array) {
    unsigned int N = array.size(), diff = 0, tmp_diff = 0;
    long int sign = 1;
    std::vector<long int> tmp;
    tmp.resize(N);
    sign = 1;
    diff = 0;

    //1)Итак, есть три операции для значения разности (1 - сдвиг влево на 1, 2 - свдиг вправо на 1, 3 - увеличение отрезка вправо на 1, 4 - увеличение отрезка влево на )
    //Итак весь отрезок можно разделить на сумму 2-х подотрезков (в случае если четно, то разделяем отрезки на кратные 2)
    //Пример
    //размер 10
    //0 и 10 (тут всегда будет 10)
    //1 и 10 (10 вариантов, размером будет максимальное по модулю число)
    //2 и 9 (9 - вариантов, размером будет максимальная разница по модулю между 2мя соседними числами)
    //3 и 8 (8 - вариантов, разница по сути является сумма пары из (2 и 9) и числа (1 и 10))
    //4 и 7 (7 - вариантов, разница является разностью (3 и 8) и (1 и 10))
    //Далее будет сумма (4 и 7) и (1 и 10)

    //Алгоритм следующий: Если отрезок = 0, то 0
    //Далее, для 
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < N - i; j++) {
            tmp[j] += sign * array[j + i];
            if (abs(tmp[j]) > diff) {
                diff = abs(tmp[j]);
            }
        }
        sign = -sign;
    }

    return diff;
}