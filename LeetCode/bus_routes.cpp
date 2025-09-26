#include <iostream>
#include <vector>
#include <queue>

#define ROUTES_MAX_COUNT 1000000
#define STOPS_MAX_COUNT 1000000



class Solution {
public:
    int numBusesToDestination(std::vector<std::vector<int>>& routes, int source, int target) {
        /*
        Итак, тут сразу напрашивается использования поиска в ширину
        Итак, у нас есть 2 типа точек
        промежуточные точки и точки автобусы
        таким образом у нас получается двудольный граф с обходом в ширину
        Тогда алгоритм приблизительный выглядит следующим образом
        bfs_bus()
        bfs_stop()
        Чередующаяся рекурсия
        f() {
            Создаём массивы
            marked_buses
            marked_stops
            Итак, имеем 2 очереди
            Создаем матрицы для номеров автобусов (рейсов) для каждой остановки
            Одну для номеров автобусов (bus)
            Другую для номеров остановок (stop)
            1)Кладём номер остановки в очередь
            Пока хотя бы одна очередь не пуста
                Пока не пуста очередь остановок
                    Берём остановку
                    Просматриваем каждый рейс:
                        Если рейс не отмечен:
                            Отмечаем рейс
                            Кладем номер рейса в очередь рейсов
                Пока не пуста очередь рейсов
                    Берём рейс
                    Просматриваем каждую остановку, через которую он проходит
                        Если остановка не отмечена:
                            Отмечаем остановку
                            Кладём остановку в очередь остановок
        }
        */
        if (source == target)
            return 0;
        bool stop_marks[STOPS_MAX_COUNT];
        bool routes_marks[ROUTES_MAX_COUNT];
        std::vector<std::vector<int>> stops(STOPS_MAX_COUNT);
        for (size_t i = 0; i < routes.size(); ++i) {
            for (const auto &stop : routes[i]) {
                stops[stop].push_back(i);
            }
        }
        std::queue<int> route_queue, stop_queue;
        int current = 0, count = 0;
        bool found = false;
        stop_queue.push(source);
        stop_marks[source] = true;
        while (!stop_queue.empty()) {
            while (!stop_queue.empty()) {
                current = stop_queue.back();
                if (current == target) {
                    found = true;
                    goto finally;
                }
                for (const auto &route : stops[current]) {
                    if (!routes_marks[route]) {
                        routes_marks[route] = true;
                        route_queue.push(route);
                    }
                }
                stop_queue.pop();
            }
            ++count;
            while (!route_queue.empty()) {
                current = route_queue.back();
                for (const auto &stop : routes[current]) {
                    if (!stop_marks[stop]) {
                        stop_marks[stop] = true;
                        stop_queue.push(stop);
                    }
                }
                route_queue.pop();
            }
        }
        finally:
        if (found)
            return count;
        return -1;
    }
};

int main(void) {
    std::vector<std::vector<int>> matrix = {{2}, {8,2}};
    std::cout << Solution().numBusesToDestination(matrix, 8, 2) << std::endl;
    return 0;
}