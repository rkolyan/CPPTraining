#include <iostream>
#include <vector>
/*
int main(void) {
    unsigned int t = 0, n = 0;
    std::string str;
    std::cin >> t;
    for (unsigned int i = 0; i < t; i++) {
        std::cin >> n;
        std::getline(std::cin, str);
        std::getline(std::cin, str);
        std::vector<int> lefts(n), rights(n);
        for (unsigned int i = 1; i < n; ++i) {
            lefts[i] = lefts[i-1];
            if (str[i-1] == '1') {
                lefts[i]++;
            }
        }
        for (unsigned int i = n - 1; i > 0; --i) {
            rights[i-1] = rights[i];
            if (str[i] == '1') {
                rights[i-1]++;
            }
        }
        unsigned int count = 0;
        for (unsigned int i = 0; i < n; i++) {
            count += lefts[i] + rights[i];
            if (str[i] == '0') {
                ++count;
            }
        }
        std::cout << count << std::endl;
    }
}
*/

/*
TODO:Там по-видимому недосказанность условия
int main(void) {
    unsigned int t = 0, n = 0, x = 0;
    std::cin >> t;
    for (unsigned int i = 0; i < t; i++) {
        std::cin >> n;
        std::cin >> x;
        for (unsigned int num = 0; num < x; num++) {
            std::cout << num << ' ';
        }
        for (unsigned int num = x+1; num < n; num++) {
            std::cout << num << ' ';
        }
        std::cout << x << std::endl;
    }
}
*/

/*
int main(void) {
    unsigned int t = 0, n = 0, k = 0;
    int x = 0;
    unsigned int count = 0;
    bool flag = false;
    bool found = false;
    std::cin >> t;
    for (unsigned int i = 0; i < t; i++) {
        std::cin >> n;
        std::cin >> k;
        std::vector<int> a(n), b(n);
        for (auto &ai : a) {
            std::cin >> ai;
        }
        flag = false;
        for (auto &bi : b) {
            std::cin >> bi;
            if (bi != -1)
                flag = true;
        }
        count = 0;
        if (flag) {
            count = 1;
            found = false;
            for (unsigned int i = 0; i < n; i++) {
                if (b[i] != -1) {
                    if (!found) {
                        found = true;
                        x = a[i] + b[i];
                    } else {
                        if (x != a[i] + b[i]) {
                            count = 0;
                            break;
                        }
                    }
                }
            }
            if (count) {
                //TODO: Нужно проверить на то, что есть число большее чем x в ai
                for (const auto &ai : a) {
                    if (ai > x || x - ai > k) {
                        count = 0;
                        break;
                    }
                }
            }
        } else {
            int minimum = a[0], maximum = minimum;
            for (const auto &ai : a) {
                maximum = std::max(ai, maximum);
                minimum = std::min(ai, minimum);
            }
            count = minimum + k - maximum + 1;
        }
        std::cout << count << std::endl;
    }
}
*/

/*
        Далее, используя жадный алгоритм смотрим слева направо b
        f(b, a, s, jndex, index, max_index, flag, k = 0) {
            Сначала проверяем можно ли найти без этого элемента
            Если s[jndex] < 0:
                Тогда ищем первое i < max_index, для которого b[jndex] <= a[i]:
                    Если i найдено:
                        f(b, a, s, jndex+1, i, max_index, flag, k);
                    Иначе, если flag:
                        f(b, a, s, jndex+1, index, max_index, false, b[jndex]);
                    Иначе:
                        Вернуть -1
            Иначе Если s[jndex] >= index:
                Вернуть k
            Иначе
                Вернуть -1

        }
*/

//max_index должна быть по умолчанию a.size();
int find_recursive_greedy_forward(const std::vector<int> &a, const std::vector<int> &b, const std::vector<int> &s, int index, int jndex, int max_index, bool set_flag = true, int k = 0) {
    //TODO граничные случаи и переполнение индексов например при a = 1, b = 2, k = 2,
    if (jndex == b.size()) {
        return k;
    }
    if (s[jndex] < 0) {
        bool found_flag = false;
        int i = index;
        for (; i < max_index; ++i) {
            if (a[i] >= b[jndex]) {
                found_flag = true;
                break;
            }
        }
        if (found_flag) {
            return find_recursive_greedy_forward(a, b, s, i + 1, jndex + 1, max_index, set_flag, k);
        } else if (set_flag) {
            return find_recursive_greedy_forward(a, b, s, index, jndex + 1, max_index, false, b[jndex]);
        } else {
            return -1;
        }
    } else if (s[jndex] >= index) {
        return k;
    }
    return -1;
}

std::vector<int> create_suffixes(const std::vector<int> &a, const std::vector<int> &b, int &max_index) {
    std::vector<int> suffixes(b.size(), -1);
    int j = b.size() - 1, i = a.size() - 1;
    for (; j >= 0; --j) {
        for (; i >= 0; --i) {
            if (a[i] >= b[j]) {
                suffixes[j] = i;
                max_index = i;
                --i;
                break;
            }
        }
    }
    return suffixes;
}

int find_recursive_greedy_backward(const std::vector<int> &a, const std::vector<int> &b, const std::vector<int> &s, int index, int jndex, int min_index, bool set_flag = true, int k = 0) {
    //TODO граничные случаи и переполнение индексов например при a = 1, b = 2, k = 2,
    if (jndex < 0) {
        return k;
    }
    if (s[jndex] < 0) {
        bool found_flag = false;
        int i = index;
        for (; i > min_index; --i) {
            if (a[i] >= b[jndex]) {
                found_flag = true;
                break;
            }
        }
        if (found_flag) {
            return find_recursive_greedy_backward(a, b, s, i - 1, jndex - 1, min_index, set_flag, k);
        } else if (set_flag) {
            return find_recursive_greedy_backward(a, b, s, index, jndex - 1, min_index, false, b[jndex]);
        } else {
            return -1;
        }
    } else if (s[jndex] <= index) {
        return k;
    }
    return -1;
}

std::vector<int> create_prefixes(const std::vector<int> &a, const std::vector<int> &b, int &min_index) {
    std::vector<int> prefixes(b.size(), -1);
    int j = 0, i = 0;
    for (; j < b.size(); ++j) {
        for (; i < a.size(); ++i) {
            if (a[i] >= b[j]) {
                prefixes[j] = i;
                min_index = i;
                ++i;
                break;
            }
        }
    }
    return prefixes;
}

/*
    i = 0 1 2 3 4 5 6 7 8
    a = 3 5 2 3 3 5 8 1 2
    b = 4 6 2 4 6
    s =-1-1 4 5 6
    p = 1 6 8-1-1
    6

    i = 0 1 2 3 4 5
    a = 1 2 6 8 2 1
    b = 5 4 3
    s =-1 2 3
    p = 2 3-1
    3

    i = 0 1 2 3 4
    a = 4 3 5 4 3
    b = 7 4 5
    s =-1 0 2
    p =-1-1-1
    7

    i = 0 1 2 3 4
    a = 1 2 3 4 5
    b = 5 4 3 2 1
    s = 4-1-1-1-1
    p = 1 2 3-1-1
    -1

    i = 0 1 2 3 4 5
    a = 8 4 2 1 2 5
    b = 6 1 4
    s = 0 4 5
    p = 0 1 5
    0
*/

//TODO: Я где-то облажался в рассуждениях
/*

Пусть a - последовательность (a1, a2, ..., an), b - последовательность (b1, b2, ..., bm)
Отношение b <in> a будем называть, если для каждого bj найдётся такой ai : ai >= bj, j1 > j2 : i_{j1} > i_{j2}
Если b = (), то выражение истинно для любого a
Итак, берём из b первый элемент b1, тогда проверяем:
1)b <in> a
Если выражение истинно, то вставлять элементы не имеет смысла, выходим
Иначе, для того, выражение стало истиным нужно вставить какой-то элемент
Допустим, этим элементом является b1
Тогда должно быть истинно b/{b1} <in> a
Но не факт, что оно может быть единственно истиным решением
Допустим это не единственный вариант, тогда
Ищем первый подходящий под b1, ai
Если ai найден:
    рассматриваем аналогичную задачу для b/{b1}, a/(a1,a2,...,ai)
Если ai не найден:
    Тогда решением по-любому должно являться b1
    Но это только в случае, если b/{b1} <in> a

Алгоритм следующий (без сохранения промежуточный результатов с использованием срезов)
f(a, b, k) {
    Если b <in> a:
        Вернуть k
    Иначе:
        Если b/(b1) <in> a: //Значит b является решением, но не факт, что единственным
            Если k = 0, то k = b1,
            Иначе k = min(k, b1)
            Ищем первый подходящий ai
            Если ai найден:
                Возвращаем f(a/(a1,...,ai), b/(b1), k) //Ищем возможное другое решение
            Иначе:
                Вернуть k  //Потому что решений больше не может быть
        Иначе:
            Ищем первый подходящий ai
            Если ai найден:
                Возвращаем f(a/(a1,...,ai), b/(b1), k) //Это означает, что проблема не в b1
            Иначе:
                Вернуть -1 //Потому что даже без b1 нельзя получить полное выражение
}
Добавим следующие свойства:
Если b <in> v, и v <in> a, тогда b <in> a
Попробуем использовать это для мемоизации задачи
Пусть v = a/(a1,...,ai)
Тогда если b <in> a/(a1,...,ai) значит b <in> a
Можно сохранять индексы в s = (s1,...,sm) (равна по длине b) по следующей процедуре:

CREATE_SUFFIXES(s,a) {
для sm ищем самое "правое" (наибольшее по индексу i) допустимое ai
Если оно есть,
    sm = i
    CREATE_SUFFIXES(s/(sm), a/(ai,...,an))
Иначе
    Заполняем s значением -1
}

Если s1 != -1 и s1 >= i: 
    истинно b <in> a/(a1,...,a(i-1))
Иначе:
    ложно b <in> a/(a1,...,ai)

Итоговый рекурсивный вариант решения задачи поиска минимального вставляемого элемента (с суффиксами, индексами и без срезов):
update(k, bj) {
    Если k == 0:
        Вернуть bj
    Иначе:
        Вернуть min(k, bj)
}

find_index(a, i, n, bj) {
    i1 = i
    Увеличиваем i1, пока i1 < n и a[i1] < bj
    Возвращаем i1 
}

f(a, b, s, i, j, n, m, k) {//Индекс начинаем с 0
    Если j == m или s[j] >= i:
        Вернуть k
    Иначе:
        Если j == m - 1:
            k = update(k, b[j])
            вернуть k
        Иначе если s[j+1] >= i:  
            k = update(k, b[j])
            i1 = find_index(a, i, n, b[j])
            Если индекс i1 < n:
                Вернуть f(a,b,s,i1+1,j+1,n,m,k)
            Иначе:
                Вернуть k
        Иначе:
            i1 = find_index(a, i, n, b[j])
            Если индекс i1 < n:
                Вернуть f(a,b,s,i1+1,j+1,n,m,k)
            Иначе:
                Вернуть -1
}
*/

int update_k(int k, int bj) {
    if (k) {
        return std::min(k, bj);
    }
    return bj;
}

int find_index(const std::vector<int> &a, int index, int n, int bj) {
    for (int i = index; i < n; i++) {
        if (a[i] >= bj) {
            return i;
        }
    }
    return n;
}

//TODO: Здесь есть какой-то нерассмотреный случай, при котором выдается неправильный ответ, но в итеративной версии я его решил
int find_recursive_greedy(const std::vector<int> &a, const std::vector<int> &b, const std::vector<int> &s, int index, int jndex, int n, int m, int k = 0) {
    if (jndex == m || s[jndex] >= index) {
        return k;
    } else if (jndex == m - 1) {
        return update_k(k, b[jndex]);
    } else if (s[jndex + 1] >= index) {
        k = update_k(k, b[jndex]);
        index = find_index(a, index, n, b[jndex]);
        if (index < n) {
            return find_recursive_greedy(a, b, s, index + 1, jndex + 1, n, m, k);
        } else {
            return k;
        }
    } else {
        index = find_index(a, index, n, b[jndex]);
        if (index < n) {
            return find_recursive_greedy(a, b, s, index + 1, jndex + 1, n, m, k);
        } else {
            if (k)
                return k;
            else
                return -1;
        }
    }
    return -2;//Невозможный конец
}

int find_iterative_greedy(const std::vector<int> &a, const std::vector<int> &b, const std::vector<int> &s, int n, int m) {
    int k = 0;
    int i = 0;
    for (int j = 0; j < m - 1; j++) {
        if (s[j] >= i) {
            return k;
        } else if (s[j+1] >= i) {
            k = update_k(k, b[j]);
            i = find_index(a, i, n, b[j]);
            if (i < n) {
                i++;
            } else {
                return k;
            }
        } else {
            i = find_index(a, i, n, b[j]);
            if (i < n) {
                i++;
            } else {
                if (k) {
                    return k;
                } else {
                    return -1;
                }
            }
        }
    }
    if (s[m-1] >= i)
        return k;
    return update_k(k, b[m-1]);
}

/*
//Задача на цветочного мальчика решена за 2 прохода, получилось O(n)
int main(void) {
    unsigned int t = 0, n = 0, m = 0;
    std::cin >> t;
    for (unsigned int ti = 0; ti < t; ti++) {
        std::cin >> n;
        std::cin >> m;
        std::vector<int> a(n), b(m);
        for (auto &ai : a) {
            std::cin >> ai;
        }
        for (auto &bi : b) {
            std::cin >> bi;
        }
        int max_index = a.size(), min_index = -1;
        std::vector<int> suffixes(create_suffixes(a, b, max_index));
        //std::cout << find_recursive_greedy(a, b, suffixes, 0, 0, n, m) << std::endl;
        std::cout << find_iterative_greedy(a, b, suffixes, n, m) << std::endl;
    }
    return 0;
}
*/

/*
Задается двоичная строка s = (s1, ..., sn)
Создается матрица g путём копирования s i-ю строку и замены s[i] на ~s[i]
g
~s[0] s[1] ... s[n-1]
s[0] ~s[1] ... s[n-1]
....
s[0]  s[1] ...~s[n-1]

Короче взяли и сделали A (матрица, полученная просто путем копирования) xor E (единичная матрица)
Если s[0] == 0, то n-1 строк будет = 0
Если матрицу перевернуть получится исходная
Итак, рассмотрим 4 варианта соседних элементов
Если g_{ii} и g_{(i+1)(i+1)} элементы являются 0, то сверху и снизу и сверху множество хороших клеток
Если g_{ii} = 0, а g_{(i+1)(i+1)} = 1, то возникает стена с 1 просветом снизу
Например
0 1
0 1
1 1
0 0
0 1
0 1
Если g_{ii} = 1, a g_{(i+1)(i+1)} = 0, то, если предыдущая пара была с просветом снизу, то предыдущее нижнее множество присоединяется к верхнему
пример:
1 0
1 0
0 0
1 1
1 0
Если g_{ii} = 1, a g_{(i+1)(i+1)} = 1, то возникает 2 стены, идет сброс предыдущих множеств, нижнее множество устанавливаем в 1
1 1
1 1
0 1
1 0
1 1 1

Итак, в первом случае мы просто обновляем нижнее и верхнее множество соседями справа
Во 2 случае - верхнее множество заканчивается, нижнее либо заканчивается, либо переходит в верхнее множество
В 3 случае - наоборот нижнее может перейти в верхнее
В 4 случае - оба множества сбрасываются, верхнее = 1
Таким образом алгоритм можно составить следующим образом:
f(s, n) {
    Крайний случай:
    Если n == 1:
        Если s[0] == 1:
            вернуть 1
        Иначе
            вернуть 0
    Иначе:
        //TODO: Не факт, что первый 0
        Вернуть f2(s, n, 0, n-1, 0, 1, n-1)
}
f2(s, n, up_sum, down_sum, i1, i2, k) {
    Если i2 == n:
        Вернуть k
    Если s[i1] == 0 и s[i2] == 0:
        up_sum += i2
        down_sum += n - i2 - 1
    Иначе если s[i1] == 0 и s[i2] == 1:
        up_sum = down_sum + 1
        down_sum = 0
    Иначе если s[i1] == 1 и s[i2] == 0:
        up_sum += i2
        down_sum = n - i2 - 1
    Иначе если s[i1] == 1 и s[i2] == 1:
        up_sum = 1
        down_sum = 0
    k = max(k, up_sum, down_sum)
    Вернуть f2(s, n, up_sum, down_sum, i2, i2+1, k)
}
*/

/*
Решил задачу эффективно на питоне, здесь проблемы
с переполнением численного типа
int main(void) {
    unsigned int t = 0, n = 0;
    std::cin >> t;
    for (unsigned int ti = 0; ti < t; ++ti) {
        std::cin >> n;
        std::string str;
        std::getline(std::cin, str);
        std::getline(std::cin, str);
        int up_sum = 0, down_sum = 0, k = 0;
        if (n > 1) {
            if (str[0] == '1') {
                up_sum = 1;
                down_sum = 0;
                k = 1;
            } else {
                up_sum = 0;
                down_sum = n - 1;
            }
            for (int i = 1; i < n; i++) {
                if (str[i-1] == '0') {
                    if (str[i] == '0') {
                        up_sum += i;
                        down_sum += n - i - 1;
                    } else {
                        up_sum = down_sum + 1;
                        down_sum = 0;
                    }
                } else {
                    if (str[i] == '0') {
                        up_sum += i;
                        down_sum = n - i - 1;
                    } else {
                        up_sum = 1;
                        down_sum = 0;
                    }
                }
                k = std::max(k, std::max(up_sum, down_sum));
            }
        } else {
            if (str[0] == '1') {
                k = 1;
            } else {
                k = 0;
            }
        }
        std::cout << k << std::endl;
    }
    return 0;
}
*/

int main(void){
    unsigned int t = 0, n = 0, q = 0, l = 0, r = 0, k = 0;
    std::cin >> t;
    for (unsigned int ti = 0; ti < t; ++ti) {
        std::cin >> n >> q;
        std::vector<int> nums(n);
        for (auto &num : nums) {
            std::cin >> num;
        }
        for (int i = 0; i < q; i++) {
            std::cin >> l >> r >> k;
        }
        /*
        Итак f(l, r, k), m = (l + r)/2
        если nums[m] == k - успех
        если nums[m] > k, то делаем f(l, m-1, k)
        если nums[m] < k, то делаем f(m+1,r, k)
        Итак, мы должны найти такое d
        Допустим мы вибираем отрезок [l,r]
        m = (l+r)/2
        Для того, чтобы поиск был успешен, то справа от k должны быть значения большие k (не все), а слева k меньшие
        Итак, если k сразу же попадает как nums[m], то d = 0
        Мы при поиске ищем меняющуюся левую и правую границу отрезка
        Надо просто представить, что если у нас значения отсортированы
        И вместо поиска k мы осуществляем поиск соответствующего элемента, который стоит на его месте

        Таким образом алгоритм следующий:
        1)Ищем позицию k
        2)Копируем массив и сортируем его
        3)Находим в новом массиве k1
        4)Используя f проходимся в отсортированном массиве
        5)
        *
    }
    return 0;
}