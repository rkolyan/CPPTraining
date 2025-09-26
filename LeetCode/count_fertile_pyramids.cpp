#include <vector>
#include <list>
#include <iostream>

//SUCCESS
/*
Это первое решение которое пришло мне в голову, но оно сравнительно медленное, ввиду того, что под элементы списков постоянно выделяется память
и всё такое...
Как можно было решить эту задачу ещё раз потом подумаю
*/

class Solution {
    private:
        struct Interval {
            int left;
            int right;
            int count;
            Interval(int tleft, int tright, int tcount) : left{tleft},right{tright},count{tcount} {}
            Interval(const Interval &) = default;
            Interval(Interval &&) = default;
        };
        int fillInterceptions(const Interval &tmp_interval, const std::list<Interval> &lst_curr, std::list<Interval> &lst_next) {
            int count = 0;
            for (auto element : lst_curr) {
                /*
                Логика пересечения интервалов:
                В предыдущих 2х циклах мы специально расширили и сузили интервалы, так
                что при пересечении с новой строкой 
                */
                if (tmp_interval.left <= element.left) {
                    if (tmp_interval.right >= element.right) {
                        //Просто добавляем этот элемент в новый список
                        count += element.count;
                        lst_next.push_back(element);
                    } else {
                        //Ищем пересечение с
                        element.count -= element.right - tmp_interval.right;
                        element.right = tmp_interval.right;
                        if (element.count > 0) {
                            count += element.count;
                            lst_next.push_back(element);
                        }
                    }
                } else if (tmp_interval.left <= element.right) {
                    element.count -= tmp_interval.left - element.left;
                    element.left = tmp_interval.left;
                    if (tmp_interval.right < element.right) {
                        element.count -= element.right - tmp_interval.right;
                        element.right = tmp_interval.right;
                    }
                    if (element.count > 0) {
                        count += element.count;
                        lst_next.push_back(element);
                    }
                }
            }
            lst_next.push_back(tmp_interval);
            return count;
        }
    public:
        int countPyramids(std::vector<std::vector<int>>& grid) {
            /*
            Итак, у нас есть задача на пирамидки
            Чисто случайные мысли из наблюдения:
            1)Итак, задача явно на разделение областей на подобласти и поиск в этой самой подобласти пирамидки
            Таким образом можно свести задачу к следующему рекурентному поиску:
            f(A[m1, m2], [n1, n2]) {
                Берём окно размером 2x3
                Проходимся сверху вниз и просматриваем все области
                Если в окне встречается пирамидка, пытаемся достроить окно вниз до окна размером 3x5
                (Проверяем, заполнены ли они все единицами)
                Если заполнены единицами, то достраиваем ещё большую пирамиду (4x7,5x9 и тд) и проверяем каждую следующую строку на отсутствие нулей
                Аналогичный алгоритм и для инверсивной пирамидки
            }
            2)На основе предыдущего алгоритма можно сделать вывод, что по сути мы ищем пересечения строк, такие, что размер пересечнной строки должен быть меньше 
            старшей строки на 2k элементов и иметь смещение вправо на k элементов (В случае поиска вертикальных пирамид пересечение снизу вверх, в случае 
            перевернутых пирамидок снизу вверх)
            Тогда алгоритм следующий:
            f(A[n, m], оtr, level) {
                count = 0;
                Ищем все отрезки на последней строке
                Ищем пересечения с otr (размер должен быть меньше справа и слева минимум на 1 элемент)
                Если level > 0 {
                    Для каждого пересечения (sub) {
                        count += |sub|
                    }
                }
                Для каждого пересечения (sub) {
                    count += f(A[n-1,m], sub, level+1)
                }
                count += f(A[n-1, m], universum, 0)
                return count;
            }
            Для перевёрнутых пирамид аналогичный алгоритм только обход с первых строк

            3)Итак, простой алгоритм придумал, какие можно придумать оптимизации
            Сложный пример:
            0 0 0 1 1 0 0 0 0 0
            0 0 1 1 1 1 1 0 1 0
            0 1 1 1 1 1 1 1 1 1
            0 1 1 1 1 1 1 1 0 1
            0 0 0 1 1 1 0 0 0 0
            0 0 1 1 1 1 1 0 0 0
            0 1 1 1 1 1 1 1 0 0
            0 1 1 0 1 1 1 1 1 0
            1 1 1 1 1 1 1 0 0 0

            Итак, случайные идеи
            1)Матрицу единиц и нулей превращраем в матрицу отрезков
            2)Обход делаем сверху вниз и строим пересечения отрезков по следующему правилу:
            Для инвертированных пирамид нижний отрезок должен быть короче верхней, для обычной наоборот
            Посмотрим для верхнего примера
            Берём первую строку
            0 0 0 1 1 0 0 0 0 0
            Для для прямой пирамиды 2 элемента (3,4:0,2)
            для инвертированной 0
            count = 0
            следующая строка (увеличиваем уровень всех элементов)
            0 0 1 1 1 1 1 0 1 0
            Итак, для прямой пирамиды нашлись отрезки (2, 6:0,5) и (8,8:0,1) - Старые отрезки обновляем через пересечение с ними и эти же отрезки сохраняем для будущих пересечений
            count += 2
            Получилось множество (2,5:1,2),(2,6:0,5),(8,8:0,1)
            Эти же отрезки можно добавить в начало инвертированных пирамид
            Получилось множество (2,6:0,5)
            Увеличиваем все уровни на единицу
            Следующая строка
            0 1 1 1 1 1 1 1 1 1
            Итак нашелся отрезок (1, 9: 0,9)
            Пересекаем со старшими отрезками и добавляем как новый в вершину
            (1,6:2,2),(1,7:1,5),(7,9:1,1) + (1,9:0,9)
            count += 2 + 5 + 1
            (3,5:1,(5->3)) + (1,9:0,9)
            count += 3
            Следующая строка
            0 1 1 1 1 1 1 1 0 1
            Итак нашлись отрезки (1,7:0,7) и (9,9:0,1)
            Пересекаем со старшими отрезками и добавляем как новые в вершину
            (1,7:3,(2-1->1)), (1,7:2,(5-2)->3), (7,7:2,(1-2)->-1(удаляем)),(1,7:1,(9 - 4->5)) + (1,7:0,7),(9,9:0,1)

            //TODO: Можно удалить уровень, он роли не играет и количество (его можно вычесть исходя из левого и правого значения)
            //TODO: Посмотри, возмножно количество можно вычислить исходя из формулы, похожей на вычисление определителяa
            //TODO: Также задачу можно представить в виде пересекающихся диагоналей
            //TODO: Или поиска по симметрии (берём и в колонке просматриваем сверху вниз)

            1 0 0 0 1
            1 1 0 1 1
            1 1 1 1 1
            1 1 0 1 1
            1 0 0 0 1
            Строка:
            1 0 0 0 1
            Итак, мы нашли (0,0:1), (4,4:1)
            Множество прямое {(0,0:1),(4,4:1)}
            Множество обратное {(0,0:1),(4,4:1)}
            Следующая строка:
            1 1 0 1 1
            Обновляем прямое множество и обратное
            {(0,1:0->удаляем),(3,4:0->удаляем)}->{}
            {(1,-1:-1->удаляем)}
            */
            std::list<Interval> lst_curr, lst_curr_invert, lst_next, lst_next_invert, lst_tmp;
            int count = 0;
            bool flag = true;
            for (const auto &row : grid) {
                lst_tmp.clear();
                flag = true;
                for (int index = 0; index < row.size(); index++) {
                    if (row[index] && flag) {
                        lst_tmp.emplace_back(index, index, 1);
                        flag = false;
                    } else if (row[index]) {
                        lst_tmp.back().right++;
                        lst_tmp.back().count++;
                    } else {
                        flag = true;
                    }
                }
                for (auto iter = lst_curr.begin(), next_iter = std::next(iter); iter != lst_curr.end(); iter = next_iter, ++next_iter) {
                    (*iter).left--;
                    if ((*iter).left < 0) {
                        (*iter).left = 0;
                        (*iter).count--;
                    }
                    (*iter).right++;
                    if ((*iter).right >= row.size()) {
                        (*iter).right = row.size()-1;
                        (*iter).count--;
                    }
                    if ((*iter).count < 1) {
                        lst_curr.erase(iter);
                    }
                }
                for (auto iter = lst_curr_invert.begin(), next_iter = std::next(iter); iter != lst_curr_invert.end(); iter = next_iter, ++next_iter) {
                    (*iter).left++;
                    (*iter).right--;
                    (*iter).count-=2;
                    if ((*iter).count < 1) {
                        lst_curr_invert.erase(iter);
                    }
                }
                for (const auto &tmp_interval : lst_tmp) {
                    count += fillInterceptions(tmp_interval, lst_curr, lst_next);
                    count += fillInterceptions(tmp_interval, lst_curr_invert, lst_next_invert);
                }
                lst_curr = std::move(lst_next);
                lst_curr_invert = std::move(lst_next_invert);
                lst_next.clear();
                lst_next_invert.clear();
            }
            return count;
        }
};

int main(void) {
    std::vector<std::vector<int>> grid = {{1,1,1,1,0},{1,1,1,1,1},{1,1,1,1,1},{0,1,0,0,1}};
    std::cout << Solution().countPyramids(grid) << std::endl;
    return 0;
}