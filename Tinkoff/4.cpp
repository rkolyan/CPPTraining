//
// Created by rkolyan on 27.01.2025.
//

#include <cmath>
#include <iostream>
#include <vector>
#include <stack>
#include <list>

//SUCCESS
/*
 * Ксюша решила попробовать себя в дизайне, поэтому теперь она разрабатывает флаг Тинькофф. Ксюша любит современное
 * искусство, поэтому новый флаг Тинькофф будет не прямоугольником, а самым настоящим правильным -угольником с длиной
 * стороны 1. Помимо -угольников Ксюше нравятся треугольники, которыми она хочет заполнить флаг. Эти треугольники при
 * этом должны иметь вершины, совпадающие с вершинами -угольника, а также не иметь общих между собой точек, в том числе вершин.
Ксюша хочет покрыть треугольниками как можно большую часть нового флага, чтобы он не выглядел слишком пустым. Пожалуйста,
 посчитайте, какую максимальную площадь -угольника она сможет заполнить.

Формат входных данных
В единственной строке вводится целое число   — число вершин -угольника.

Формат выходных данных
Выведите одно вещественное число — максимальную суммарную площадь, которую можно покрыть треугольниками. Ответ будет
 считаться верным, если его абсолютная или относительная погрешность не более .
 */

//TODO: Можно решить проще, отсекая множества и вычисляя в них отдельно максимальную площадь

int main(void) {
    unsigned int N = 0;
    double S = 0, angle = 2 * M_PI / static_cast<double>(N);
    std::vector<unsigned int> indexes;
    std::cin >> N;
    indexes.resize(N);
    std::fill(indexes.begin(), indexes.end(), 0);

    S = 0;
    unsigned int tri_num = 1, cur_pos = 0, vert_count = 0;
    unsigned int i1_pos, i2_pos, i3_pos, begin_pos = 0;
    double sqr = 0, max_sqr = 0, R = sqrt(1.0 / (2 * (1 - cos(M_PI / N )))), alpha = 0;
    double a = 0, b = 0, c = 0;
    std::list<unsigned int> positions;
    std::stack<double> sqrs;
    do {
        while (!positions.empty()) {
            cur_pos = positions.front();
            positions.pop_front();
            if (cur_pos != N) {
                indexes[cur_pos] = 0;
            }
            cur_pos++;
            if (vert_count == 0) {
                tri_num--;
                vert_count = 2;
                sqr = sqrs.top();
                sqrs.pop();
                S -= sqr;
            } else {
                vert_count--;
            }
            if (cur_pos != N && indexes[cur_pos] == 0)
                break;
        }
        if (positions.empty())
            begin_pos = cur_pos;
        while (cur_pos != N && indexes[cur_pos] == 0) {
            indexes[cur_pos] = tri_num;
            vert_count++;
            positions.push_front(cur_pos);
            if (vert_count == 3) {
                for (const auto &elem : indexes) {
                    std::cout << elem << ' ';
                }
                i1_pos = positions.front();
                i2_pos = *(std::next(positions.begin()));
                i3_pos = *(std::next(positions.begin(), 2));
                auto minim = std::min(i1_pos, i2_pos);
                auto maxim = std::max(i1_pos, i2_pos);
                alpha = M_PI / N * std::min(maxim - minim, minim + N - maxim);
                a = R * sqrt(2 * (1 - cos(alpha)));
                minim = std::min(i3_pos, i2_pos);
                maxim = std::max(i3_pos, i2_pos);
                alpha = M_PI / N * std::min(maxim - minim, minim + N - maxim);
                b = R * sqrt(2 * (1 - cos(alpha)));
                minim = std::min(i3_pos, i1_pos);
                maxim = std::max(i3_pos, i1_pos);
                alpha = M_PI / N * std::min(maxim - minim, minim + N - maxim);
                c = R * sqrt(2 * (1 - cos(alpha)));
                auto p = (a + b + c) / 2;
                sqr = sqrt(p * (p - a) * (p - b) * (p - c));
                vert_count = 0;
                tri_num++;
                S += sqr;
                std::cout << S << std::endl;
                sqrs.push(sqr);
                for (unsigned int i = begin_pos + 1; i < N - 1; i++) {
                    if (!indexes[i - 1] && !indexes[i] && !indexes[i + 1]) {
                        cur_pos = i - 2;
                        break;
                    }
                }
            }
            cur_pos++;
        }
        if (max_sqr < S)
            max_sqr = S;
    } while (!positions.empty());
    std::cout << max_sqr;
    return 0;
}