#include <vector>
#include <queue>
#include <iostream>

//SUCCESS

class Solution {
    public:
        int maxCandies(std::vector<int>& status, std::vector<int>& candies, std::vector<std::vector<int>>& keys, std::vector<std::vector<int>>& containedBoxes, std::vector<int>& initialBoxes) {
            //status - массив из 1 и 0, коробка открыта или нет
            //candies - количества конфет в коробках
            //keys - хранит списки ключей коробок, которые можно открыть после i-й коробки
            //containedBoxes - список коробок, которые находятся внутри коробки i
            //initialBoxes - коробки, которые мы уже имеем на руках
            /*
            Итак, мы берём коробку из initialBoxes,
            На всякий случай создаем массив boxUsesd, чтобы писать, что коробка уже использована

            Алгоритм дебила
            Засовываем в очередь коробок коробки из initialBoxes
            Маркер сбрасывается
            Пока очередь не пуста {
                Берём коробку из очереди
                Если маркер не сброшен и равен этой коробке:
                    Выходим из цикла
                Если коробка уже открыта, то 
                    добавляем число конфет в общее число конфет
                    изменяем статус на 1 у тех коробок, ключи к которой лежат в этой
                    Добавляем в очередь коробки, которые лежат внутри этой коробки
                Иначе:
                    Кладём эту коробку опять в очередь
                    Если маркер сброшен, устанавливаем маркер = номеру этой коробки
            }
            */
            int marker = 0, current_box = 0;
            int candies_count = 0;
            bool marker_set = false;
            std::queue<int> box_queue;
            for (const auto &box : initialBoxes) {
                box_queue.push(box);
            }
            while (!box_queue.empty()) {
                current_box = box_queue.front();
                box_queue.pop();
                if (marker_set && marker == current_box) {
                    break;
                }
                if (status[current_box]) {
                    candies_count += candies[current_box];
                    for (const auto &key : keys[current_box]) {
                        status[key] = 1;
                    }
                    for (const auto &box : containedBoxes[current_box]) {
                        box_queue.push(box);
                    }
                    marker_set = false;
                } else {
                    if (!marker_set) {
                        marker = current_box;
                        marker_set = true;
                    }
                    box_queue.push(current_box);
                }
            }
            return candies_count;
        }
    };

int main(void) {
    Solution sol;
    std::vector<int> status1 = {1,0,1,0}, status2 = {1,0,0,0,0,0};
    std::vector<int> candies1 = {7,5,4,100}, candies2 = {1,1,1,1,1,1};
    std::vector<std::vector<int>> keys1 = {{},{},{1},{}}, keys2 = {{1,2,3,4,5},{},{},{},{},{}};
    std::vector<std::vector<int>> containedBoxes1 = {{1,2},{3},{},{}}, containedBoxes2 = {{1,2,3,4,5},{},{},{},{},{}};
    std::vector<int> initialBoxes1 = {0}, initialBoxes2 = {0};

    std::cout << sol.maxCandies(status1, candies1, keys1, containedBoxes1, initialBoxes1) << std::endl;
    std::cout << sol.maxCandies(status2, candies2, keys2, containedBoxes2, initialBoxes2) << std::endl;
    return 0;
}