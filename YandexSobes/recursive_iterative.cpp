/*
    Предоположим, что мы хотим реализовать следующий алгоритм сортировки
    f(a_1, ..., a_i, ..., a_n) = a_if(a2, ..., a_{i-1}, a_{1}, a_{i+1})
*/

#include <vector>
#include <stack>
#include <functional>
#include <iostream>
//Вот его рекурсивная реализация

void mysort(std::vector<int>::iterator begin, std::vector<int>::iterator end, const std::function<int(int, int)> &func) {
    if (begin == end)
        return;
    auto iter_max = begin;
    for (auto iter = begin; iter != end; iter++) {
        if (func(*iter, *iter_max) > 0) {
            iter_max = iter;       
        }
    }
    std::swap(*begin, *iter_max);
    mysort(std::next(begin), end, func);
}

//Вот его итеративная реализация с использованием стека
//Так как end и func не меняются, их мы в стек не сохраняем (begin вообще по идее тоже можно отбросить)
void mysort_primitive_iterative(std::vector<int>::iterator begin, std::vector<int>::iterator end, const std::function<int(int, int)> &func) {
    std::stack<std::vector<int>::iterator> stack;
    //Первое вхождение в стек (когда мы её только вызвали)
    stack.push(begin);
    bool on_enter = true;
    while (!stack.empty()) {
        if (on_enter) {
            begin = stack.top();
            if (begin != end) {
                auto iter_max = begin;
                for (auto iter = begin; iter != end; iter++) {
                    if (func(*iter, *iter_max) > 0) {
                        iter_max = iter;       
                    }
                }
                std::swap(*begin, *iter_max);
                stack.push(std::next(begin));
            } else {
                on_enter = false;
            }
        } else {
            stack.pop();
        }
    }
}

//Вот его итеративная оптимизированная версия
void mysort_iterative(std::vector<int>::iterator begin, std::vector<int>::iterator end, const std::function<int(int, int)> &func) {
    for (auto iter_begin = begin; iter_begin != end; ++iter_begin) {
        auto iter_max = iter_begin, iter = iter_begin;
        for (; iter != end; iter++) {
            if (func(*iter, *iter_max) > 0) {
                iter_max = iter;
            }
        }
        std::swap(*iter_begin, *iter_max);
    }
}

//Превратить в итеративную версию просто, если функция рекурсивно только 1 раз вызывается в теле функции
/*
Итак, для задач, у которых множество рекурсивных вызовов советы следующие:
1)Помимо входа в функцию и выхода есть ещё процесс изменения данных 
(то есть между вызовами функций есть какая-то функция, которая меняет значения входных аргументов)
*/

//Пример с решением рекурсивной задачи со скобочками
/*
    Если (n1 == 0)
        f(0, n2) = n2x')'
        выход
    иначе Если (n1 < n2)
        f(n1, n2) = '('f(n1-1, n2) || ')'f(n1, n2 - 1)
    Иначе Если (n1 == n2)
        f(n1, n2) = '('f(n1-1, n2)
    f(0, n) = ')'f(0, n-1)
    || - ветвление (то есть добавляет новое значение)
    Вызов f подразумевает - обновление позиции вправо и сохранение в стеке (n1, n2) (сохраняем в стек LEFT или RIGHT)
    Выход из f подразумевает - обновление позиции влево и возвращение из стека (n1, n2) (выбрасываем из стека последний элемент, )
*/


//Рекурсивная версия
void _fill_parenthesis_recursive(std::string &str, std::string::iterator iter, std::size_t n1, std::size_t n2) {
    if (n1 == 0) {
        std::fill(iter, str.end(), ')');
        std::cout << str << std::endl;
    } else if (n1 < n2) {
        *iter = '(';
        _fill_parenthesis_recursive(str, std::next(iter), n1 - 1, n2);
        *iter = ')';
        _fill_parenthesis_recursive(str, std::next(iter), n1, n2 - 1);
    } else {
        *iter = '(';
        _fill_parenthesis_recursive(str, std::next(iter), n1 - 1, n2);
    }
}
void fill_parenthesis_recursive(std::size_t n) {
    std::size_t n1 = n, n2 = n;
    std::string str;
    str.resize(2 * n);
    _fill_parenthesis_recursive(str, str.begin(), n1, n2);
}

enum VARIANT {
    LEFT,
    RIGHT,
    ONLY_LEFT
};

//Итеративная версия (неоптимизированная)
void fill_parenthesis_iterative(std::size_t n) {
    std::size_t n1 = n, n2 = n;
    std::string str;
    std::stack<VARIANT> stack;
    VARIANT cur_op = LEFT;
    bool on_enter = true;

    str.resize(2 * n);
    auto iter = std::next(str.begin());
    stack.push(ONLY_LEFT);
    str[0] = '(';
    n1--;

    while (!stack.empty()) {
        if (on_enter) {
            if (!n1) {
                std::fill(iter, str.end(), ')');
                std::cout << str << std::endl;
                on_enter = false;
                iter--;
            } else if (n1 < n2) {
                *iter = '(';
                iter++;
                n1--;
                stack.push(LEFT);
            } else {
                *iter = '(';
                iter++;
                n1--;
                stack.push(ONLY_LEFT);
            }
        } else {
            switch (stack.top())
            {
            case LEFT:
                stack.top() = RIGHT;
                *iter = ')';
                n1++;
                n2--;
                iter++;
                on_enter = true;
                break;
            case RIGHT:
                n2++;
                iter--;
                stack.pop();
                break;
            default:
                n1++;
                iter--;
                stack.pop();
            }
        }
    }
}

/*
N перекрестков (вершин), M дорог, Нужно найти кратчайшую дорогу с наибольшим количеством вершин

На ум приходит поиск в глубину с отсечением, в случае превышен текущий максимальный путь

Возможный алгоритм
f(matr, i, path, count, path_len, max_path_len, max_path):
    path.push(i);
    для каждой доступной вершины в i кроме последней:
        Если вершина непомечена:
            Пометить matr[i][j]
            f(matr, j, path, count + 1, path_len + matr[i][j], max_count, min_path_len)
            Сбросить метку matr[i][j]
    Если последняя вершина доступна:
        path_len += matr[i][last];
        count++
        Если (path_len < min_path_len)
            min_path = path;
        Иначе если (path_len == min_path_len && count > max_count)
            max_count = count;
    path.pop()      
*/
using vertice_t = unsigned int;
using Matrix = std::vector<std::vector<int>>;
enum Mark {
    MARKED,
    UNMARKED
};
using Marks = std::vector<Mark>;
void _find_longest_shortest_recursive(const Matrix &matr, Marks &marks, vertice_t curr, vertice_t last, std::size_t count, std::size_t path_len, std::size_t &max_count, std::size_t &min_path_len) {
    count++;
    marks[curr] = MARKED;
    for (vertice_t vertice = 0; vertice < last; vertice++) {
        if (matr[curr][vertice] != -1 && marks[vertice] == UNMARKED) {
            _find_longest_shortest_recursive(matr, marks, vertice, last, count, path_len + matr[curr][vertice], max_count, min_path_len);
        }
    }
    if (matr[curr][last] != -1) {
        path_len += matr[curr][last];
        count++;
        if (path_len < min_path_len)
            min_path_len = path_len;
        else if (path_len == min_path_len && count > max_count)
            max_count = count;
        count--;
        path_len -= matr[curr][last];
    }
    marks[curr] = UNMARKED;
    count--;
}

void find_longes_shortest_recursive(const Matrix &matr, std::size_t &count, std::size_t &path_len) {
    path_len = ~static_cast<std::size_t>(0);
    count = static_cast<std::size_t>(0);
    Marks marks;
    marks.resize(matr.size());
    std::fill(marks.begin(), marks.end(), UNMARKED);   
    _find_longest_shortest_recursive(matr, marks, 0, matr.size() - 1, 0, 0, count, path_len);
}

void find_longes_shortest_iterative(const Matrix &matr, std::size_t &max_count, std::size_t &min_path_len) {
    min_path_len = ~static_cast<std::size_t>(0);
    max_count = static_cast<std::size_t>(0);
    Marks marks;
    std::stack<vertice_t> stack;
    bool on_enter = true, flag = false;
    std::size_t count = 0, path_len = 0;
    marks.resize(matr.size());
    vertice_t next = 0, last = marks.size() - 1;
    std::fill(marks.begin(), marks.end(), UNMARKED);
    //_find_longest_shortest_recursive(matr, marks, 0, matr.size() - 1, 0, 0, count, path_len);
    stack.push(0);
    while (!stack.empty()) {
        if (on_enter) {
            marks[stack.top()] = MARKED;
            flag = true;
            for (++next; next < last; ++next) {
                if (matr[stack.top()][next] != -1 && matr[stack.top()][next] == UNMARKED) {
                    path_len += matr[stack.top()][next];
                    count++;
                    stack.push(next);
                    next = 0;
                    flag = false;
                    break;
                }
            }
            if (flag) {
                if (matr[stack.top()][last] != -1) {
                    path_len += matr[stack.top()][last];
                    count++;
                    if (path_len < min_path_len) {
                        min_path_len = path_len;
                        max_count = count;
                    } else if (path_len == min_path_len && count > max_count) {
                        max_count = count;
                    }
                    count--;
                    path_len -= matr[stack.top()][last];
                }
                on_enter = false;
            }
        } else {
            marks[stack.top()] = UNMARKED;
            next = stack.top();
            stack.pop();
            if (!stack.empty()) {
                path_len -= matr[stack.top()][next];
                count--;
            }
            on_enter = true;
        }
    }
}

Matrix input_matrix() {
    Matrix matr;
    std::size_t N, M;
    
    std::cin >> N >> M;
    matr.resize(N);
    for (auto &vec : matr) {
        vec.resize(N);
        std::fill(vec.begin(), vec.end(), -1);
    }

    unsigned int a, b;
    int c;
    for (std::size_t i = 0; i < M; ++i) {
        std::cin >> a >> b >> c;
        matr[a-1][b-1] = c;
    }
    return matr;
}

int main(void) {
    //std::vector<int> v{5, 2, 3, 7, 1};
    //mysort(v.begin(), v.end(), [=](int a, int b){return b - a;});
    //mysort_iterative(v.begin(), v.end(), [=](int a, int b){return b - a;});
    //mysort_primitive_iterative(v.begin(), v.end(), [=](int a, int b){return b - a;});
    //for (const auto &elem : v) {
    //    std::cout << elem;
    //}

    //std::size_t N = 4;
    //fill_parenthesis_recursive(N);
    //fill_parenthesis_iterative(N);
    auto matr = input_matrix();
    std::size_t count{}, pathlen{};
    find_longes_shortest_iterative(matr, count, pathlen);
    std::cout << pathlen << ' ' << count;
    return 0;
}