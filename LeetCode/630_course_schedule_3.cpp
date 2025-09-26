#include <vector>
#include <algorithm>
        /*
        Итак у нас дана длительность курса, а также последний день
        Мы можем брать только 1 курс в одно время
        Допустим попробуем решить жадно
        Хотя, тут явно прослеживается алгоритм дейкстры,
        Допустим, мы будем хранить дерево где по ключу будем искать конец курса - длительность
        И сохранять все значения до следующего
        Таким образом алгоритм следующий
        Или может сразу упорядочить и в начале брать самые короткие курсы с наименьшей duration и наименьшим end?
        */

//Первое решение используещее жадный подход (Но он не дает точный ответ, а только приблизительный)
class Solution1 {
public:
    int scheduleCourse(std::vector<std::vector<int>>& courses) {
        std::sort(courses.begin(), courses.end(), [](const std::vector<int> &a, const std::vector<int> &b){
            if (a[1] < b[1]) {
                return true;
            } else if (a[1] == b[1]) {
                return a[0] < b[0];
            }
            return false;
        });
        int count = 0, current_day = 0;
        for (const auto &course : courses) {
            if (current_day + course[0] <= course[1]) {
                ++count;
                current_day += course[0];
            }
        }
        return count;
    }
};

#include <queue>

//SUCCESS
/*
На самом деле идея спизжена, но суть простая - мы сначала сортируем массив по возрастанию "последнего дня" (courses[i][1]),
Потом проходимся в массиве по порядку и кладем текущий элемент в очередь. Также смотрим текущий день. Если он превышает дедлайн для текущего элемента
то из списка используемых длительностей удаляем самую большую
Количество используемых длинтельностей - это есть количество курсов

*/

class Solution {
public:
    int scheduleCourse(std::vector<std::vector<int>>& courses) {
        std::priority_queue<int> durations;
        std::sort(courses.begin(), courses.end(), [](const std::vector<int> &a, const std::vector<int> &b){
            return a[1] < b[1];
        });
        int days_used = 0;
        for (const auto &course : courses) {
            days_used += course[0];
            durations.emplace(course[0]);
            if (days_used > course[1]) {
                days_used -= durations.top();
                durations.pop();
            }
        }
        return durations.size();
    }
};