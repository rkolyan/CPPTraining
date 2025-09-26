//
// Created by rkolyan on 04.06.2024.
//

#include <iostream>
#include <climits>
#include <map>
#include <list>

/*
Алгоритм следующий
В случае если длина и ширина где-то посередине (не минимум и не максимум)
	Просматриваем все, отсортированные по длине листы, которые меньше-равно по длине, если ширина больше - ставим флаг invisible
В случае, если у листа наибольшая длина - просматриваем, чтобы ширина была наименьшей
Аналогично в случае ширины
*/

using width_t = unsigned int;
using height_t = unsigned int;

int main() {
	unsigned int N = 0, width = 0, height = 0;
	bool flag = false;
	std::map<width_t, std::list<height_t>> blanks;
	unsigned int min_width = UINT_MAX, max_width = 0, min_height = UINT_MAX, max_height = 0;

	std::cin >> N;

	std::cin >> width >> height;
	blanks[width].push_front(height);
	min_height = height;
	min_width = width;
	max_height = height;
	max_width = width;
	for (unsigned int i = 1; i < N; i++) {
		std::cin >> width >> height;
		if (!flag) {
			if (width < min_width) {
				min_width = width;
				if (height < min_height) {
					min_height = height;
				} else if (height > max_height) {
					max_height = height;
				}
			} else if (height < min_height) {
				min_height = height;
				if (width > max_width) {
					max_width = width;
				}
			} else {
				if (width >= max_width || height >= max_height) {
					flag = true;
				} else {
					for (const auto &blanks_sub : blanks) {
						if (blanks_sub.first <= width) {
							for (const auto &blank_height : blanks_sub.second) {
								if (blank_height <= height) {
									flag = true;
									goto finish;
								}
							}
						} else {
							goto finish;
						}
					}
				}
			}
		}
		finish:
			blanks[width].push_back(height);
	}
	if (flag)
		std::cout << "Invisible paper detected";
	else
		std::cout << "Well done";
	return 0;
}