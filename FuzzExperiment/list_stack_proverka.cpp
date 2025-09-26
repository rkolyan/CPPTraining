//
// Created by rkolyan on 04.06.2024.
//

/*
Wrong

Идея раннего алгоритма хороша, но правильность его не доказана
*/

/*
Итак, как вариант, можно построить из углов прямоугольника функцию, похожую на гиперболу,
(Мы берём и увеличиваем в 2 раза длину и ширину листов и изучаем 1 четверть этого листа где ширина и длина = изначальным значениям)
Итак, составляем множество прямоугольников, которые сортируются по длине
Когда вставляем новый элемент, проверяем:
1)Если ширина предыдущего элемента <= вставляемого --> invisible
2)Если ширина предыдущего элемента > вставляемого и нижняя граница для этого элемента <= вставляемого --> invisible
3)Если ширина следующего элемента > вставляемого, то обновляем нижнюю границу (можно просто удалить элементы с большей высотой), до последнего неподходящего элемента
*/

#include <iostream>
#include <set>
#include <list>

#include "list_stack_proverka.h"

bool is_fully_intersected(const std::list<Node> &list) {
	bool flag = false;
	std::set<Node> nodes;
	for (const auto &element : list) {
		if (!flag) {
			auto iter = nodes.emplace(element).first;
			auto prev_iter = std::prev(iter), next = std::next(iter);
			if (iter != nodes.cbegin()) {
				if ((*prev_iter).height_less_eq(*iter)) {
					flag = true;
					continue;
					//return true;
				}
			} else {
				while (next != nodes.cend() && (*iter).height_less_eq(*next)) {
					(*next).update_min_height((*iter).height);
					next++;
				}
			}
		}
	}
	return flag;
}

bool is_fully_intersected_right(const std::list<Node> &list) {
	for (auto iter_i = list.cbegin(); iter_i != list.cend(); iter_i++) {
        for (auto iter_j = std::next(iter_i); iter_j != list.cend(); iter_j++) {
			if ((*iter_i).width <= (*iter_j).width && (*iter_i).height <= (*iter_j).height) {
                return true;
            }
        }
    }
	return false;
}