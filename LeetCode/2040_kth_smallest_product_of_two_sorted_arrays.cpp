#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

//TODO: Доделать

class Solution {
    private:
        enum direction_t {
            HORIZONTAL,
            VERTICAL,
            DIAGONAL
        };
        enum move_t {
            FORWARD = 1,
            BACKWARD = -1,
        };
        enum number_type_t {
            NEGATIVE,
            NONNEGATIVE
        };
        using index_t = int;
        using jndex_t = int;
        using queue_element_t = std::tuple<long, direction_t, index_t, jndex_t>;
        using my_priority_queue_t = std::priority_queue<queue_element_t, std::vector<queue_element_t>, std::greater<queue_element_t>>;
        int find_first_positive_index(const std::vector<int> &nums) {
            int left = 0, right = nums.size()-1, center;
            if (nums[right] <= 0) {
                return nums.size();
            }
            while (nums[left] <= 0) {
                center = (right + left) / 2;
                if (nums[center] <= 0) {
                    left = center+1;
                } else {
                    right = center;
                }
            }
            return left;
        }
        long moveOneDirection(const std::vector<int> &nums1, move_t move1, index_t begin1, index_t end1,
            const std::vector<int> &nums2, move_t move2, jndex_t begin2, jndex_t end2,
            long long &k, my_priority_queue_t &queue) {
            if (begin1 == end1 || begin2 == end2) {
                return 0;
            }
            queue_element_t tmp;
            queue.emplace(static_cast<long>(nums1[begin1])*nums2[begin2], DIAGONAL, begin1, begin2);
            while (!queue.empty() && k) {
                tmp = queue.top();
                queue.pop();
                const auto &direction = std::get<1>(tmp);
                const auto &index = std::get<2>(tmp) + move1;
                const auto &jndex = std::get<3>(tmp) + move2;
                switch (direction) {
                case DIAGONAL:
                    if (index != end1 && jndex != end2) {
                        queue.emplace(static_cast<long>(nums1[index])*nums2[jndex], DIAGONAL, index, jndex);
                        queue.emplace(static_cast<long>(nums1[index])*nums2[jndex-move2], HORIZONTAL, index, jndex-move2);
                        queue.emplace(static_cast<long>(nums1[index-move1])*nums2[jndex], VERTICAL, index-move1, jndex);
                    } else if (index != end1) {
                        queue.emplace(static_cast<long>(nums1[index])*nums2[jndex-move2], HORIZONTAL, index, jndex-move2);
                    } else if (jndex != end2) {
                        queue.emplace(static_cast<long>(nums1[index-move1])*nums2[jndex], VERTICAL, index-move1, jndex);
                    }
                    break;
                case HORIZONTAL:
                    if (index != end1 ) {
                        queue.emplace(static_cast<long>(nums1[index])*nums2[jndex-move2], HORIZONTAL, index, jndex-move2);
                    }
                    break;
                case VERTICAL:
                    if (jndex != end2) {
                        queue.emplace(static_cast<long>(nums1[index-move1])*nums2[jndex], VERTICAL, index-move1, jndex);
                    }
                    break;
                }
                --k;
            }
            return std::get<0>(tmp);
        }
        long moveTwoDirection(number_type_t type, const std::vector<int> &nums1, int N1, int N, const std::vector<int> &nums2, int M1, int M, long long &k, my_priority_queue_t &queue) {
            queue_element_t tmp;
            if (type == NEGATIVE) {
                queue.emplace(static_cast<long>(nums1[0])*nums2[M-1], DIAGONAL, 0, M-1);
                queue.emplace(static_cast<long>(nums1[N-1])*nums2[0], DIAGONAL, N-1, 0);
            } else {
                queue.emplace(static_cast<long>(nums1[N1-1])*nums2[M1-1], DIAGONAL, N1-1, M1-1);
                queue.emplace(static_cast<long>(nums1[N1])*nums2[M1], DIAGONAL, N1, M1);
            }
            while (!queue.empty() && k) {
                tmp = queue.top();
                queue.pop();
                const auto &direction = std::get<1>(tmp);
                const auto &index = std::get<2>(tmp);
                const auto &jndex = std::get<3>(tmp);
                switch (type) {
                case NEGATIVE:
                    switch (direction) {
                    case DIAGONAL:
                        if (index < N1-1 && jndex > M1) {
                            queue.emplace(static_cast<long>(nums1[index+1])*nums2[jndex-1], DIAGONAL, index+1, jndex-1);
                            queue.emplace(static_cast<long>(nums1[index+1])*nums2[jndex], VERTICAL, index+1, jndex);
                            queue.emplace(static_cast<long>(nums1[index])*nums2[jndex-1], HORIZONTAL, index, jndex-1);
                        } else if (index < N1-1) {
                            queue.emplace(static_cast<long>(nums1[index+1])*nums2[jndex], VERTICAL, index+1, jndex);
                        } else if (jndex > M1) {
                            queue.emplace(static_cast<long>(nums1[index])*nums2[jndex-1], HORIZONTAL, index, jndex-1);
                        } else if (index > N1 && jndex < M1-1) {
                            queue.emplace(static_cast<long>(nums1[index-1])*nums2[jndex+1], DIAGONAL, index-1, jndex+1);
                            queue.emplace(static_cast<long>(nums1[index-1])*nums2[jndex], VERTICAL, index-1, jndex);
                            queue.emplace(static_cast<long>(nums1[index])*nums2[jndex+1], HORIZONTAL, index, jndex+1);
                        } else if (index > N1) {
                            queue.emplace(static_cast<long>(nums1[index-1])*nums2[jndex], VERTICAL, index-1, jndex);
                        } else if (jndex < M1-1) {
                            queue.emplace(static_cast<long>(nums1[index])*nums2[jndex+1], HORIZONTAL, index, jndex+1);
                        }
                        break;
                    case VERTICAL:
                        if (index < N1-1) {
                            queue.emplace(static_cast<long>(nums1[index+1])*nums2[jndex], VERTICAL, index+1, jndex);
                        } else if (index > N1) {
                            queue.emplace(static_cast<long>(nums1[index-1])*nums2[jndex], VERTICAL, index-1, jndex);
                        }
                        break;
                    case HORIZONTAL:
                        if (jndex < M1-1) {
                            queue.emplace(static_cast<long>(nums1[index])*nums2[jndex+1], HORIZONTAL, index, jndex+1);
                        } else if (jndex > M1) {
                            queue.emplace(static_cast<long>(nums1[index])*nums2[jndex-1], HORIZONTAL, index, jndex-1);
                        }
                    }
                    break;
                case NONNEGATIVE:
                    switch (direction) {
                    case DIAGONAL:
                        if (index >= N1 || jndex >= M1) {
                            if (index < N-1 && jndex < M-1) {
                                queue.emplace(static_cast<long>(nums1[index+1])*nums2[jndex+1], DIAGONAL, index+1, jndex+1);
                                queue.emplace(static_cast<long>(nums1[index+1])*nums2[jndex], VERTICAL, index+1, jndex);
                                queue.emplace(static_cast<long>(nums1[index])*nums2[jndex+1], HORIZONTAL, index, jndex+1);
                            } else if (index < N-1) {
                                queue.emplace(static_cast<long>(nums1[index+1])*nums2[jndex], VERTICAL, index+1, jndex);
                            } else if (jndex < M-1) {
                                queue.emplace(static_cast<long>(nums1[index])*nums2[jndex+1], HORIZONTAL, index, jndex+1);
                            }
                        } else if (index < N1 || jndex < M1) {
                            if (index > 0 && jndex > 0) {
                                queue.emplace(static_cast<long>(nums1[index-1])*nums2[jndex-1], DIAGONAL, index-1, jndex-1);
                                queue.emplace(static_cast<long>(nums1[index-1])*nums2[jndex], VERTICAL, index-1, jndex);
                                queue.emplace(static_cast<long>(nums1[index])*nums2[jndex-1], HORIZONTAL, index, jndex-1);
                            } else if (index > 0) {
                                queue.emplace(static_cast<long>(nums1[index-1])*nums2[jndex], VERTICAL, index-1, jndex);
                            } else if (jndex > 0) {
                                queue.emplace(static_cast<long>(nums1[index])*nums2[jndex-1], HORIZONTAL, index, jndex-1);
                            }
                        }
                        break;
                    case VERTICAL:
                        if (index >= N1 && index < N-1) {
                            queue.emplace(static_cast<long>(nums1[index+1])*nums2[jndex], VERTICAL, index+1, jndex);
                        } else if (index < N1 && index > 0) {
                            queue.emplace(static_cast<long>(nums1[index-1])*nums2[jndex], VERTICAL, index-1, jndex);
                        }
                        break;
                    case HORIZONTAL:
                        if (jndex >= M1 && jndex < M-1) {
                            queue.emplace(static_cast<long>(nums1[index])*nums2[jndex+1], HORIZONTAL, index, jndex+1);
                        } else if (jndex < M1 && jndex > 0) {
                            queue.emplace(static_cast<long>(nums1[index])*nums2[jndex-1], HORIZONTAL, index, jndex-1);
                        }
                    }
                }
                --k;
            }
            return std::get<0>(tmp);
        }
    public:
        long long kthSmallestProduct(std::vector<int> &nums1, std::vector<int> &nums2, long long k) {
            const auto N = nums1.size(), M = nums2.size();
            int N1 = 0, M1 = 0;
            long result = 0;
            N1 = find_first_positive_index(nums1);
            M1 = find_first_positive_index(nums2);
            std::vector<queue_element_t> buffer;
            buffer.reserve(N+M-1);
            my_priority_queue_t queue(std::greater<queue_element_t>{}, std::move(buffer));
            /*
            9 случев
            N1  M1  Обход
            =0  =0  Тогда
                    1)делаем прямой обход всего nums1 и прямой обход всего nums2
            =0  >0  Тогда 
                    1)делаем обратный обход всего nums1, и прямой обход nums2 до M1 (не включительно)
                    2)делаем прямой обход всего nums1 и прямой обход nums2 начиная с M1 (включительно)
            =0  =M  Тогда
                    1)делаем обратный обход всего nums1 и прямой обход всего nums2
            >0  =0  Тогда
                    1)делаем прямой обход nums1 до N1 (не включительно) и обратный обход всего nums2
                    2)делаем прямой обход nums1 с N1 (включительно) и прямой обход всего nums2
            >0  >0  Тогда
                    1.1)делаем прямой обход nums1 до N1 и обрантый ход nums2 с M до M1 (включительно)
                    1.2)делаем обратный обход nums1 с N до N1 (включительно) и прямой обход nums2 до M1 (не включительно)
                    2.1)делаем прямой обход nums1 с N1 и прямой обход nums2 с M1
                    2.2)делаем обратный обход nums1 с N1 и обратный обход nums2 с M1
            >0  =M  Тогда
                    1)делаем обратный обход nums1 с N до N1 и прямой обход всего nums2
                    2)делаем обратный обход nums1 c N1 до 0 и обратный обход всего nums2
            =N  =0  Тогда
                    1)Делаем прямой обход всего nums1 и обратный обход всего nums2
            =N  >0  Тогда
                    1)Делаем прямой обход всего nums1 и обратный обход nums2 с M до M1 (включительно)
                    2)Делаем обратный обход всего nums1 и обратный обход nums2 с M1-1 до 0
            =N  =M  Тогда
                    1)Делаем обратный обход всего nums1 и обратный обход всего nums2 
            */
            if (N1 == 0) {
                if (M1 == 0) {
                    result = moveOneDirection(nums1, FORWARD, 0, N, nums2, FORWARD, 0, M, k, queue);
                } else if (M1 < M) {
                    result = moveOneDirection(nums1, BACKWARD, N-1, -1, nums2, FORWARD, 0, M1, k, queue);
                    if (k) {
                        result = moveOneDirection(nums1, FORWARD, 0, N, nums2, FORWARD, M1, M, k, queue);
                    }
                } else {//M1 == M, то есть все числа отрицательны 
                    result = moveOneDirection(nums1, BACKWARD, N-1, -1, nums2, FORWARD, 0, M, k, queue);
                }
            } else if (N1 < N) {
                if (M1 == 0) {
                    result = moveOneDirection(nums1, FORWARD, 0, N1, nums2, BACKWARD, M-1, -1, k, queue);
                    if (k) {
                        result = moveOneDirection(nums1, FORWARD, N1, N, nums2, FORWARD, 0, M, k, queue);
                    }
                } else if (M1 < M) {
                    result = moveTwoDirection(NEGATIVE, nums1, N1, N, nums2, M1, M, k, queue);
                    if (k) {
                        result = moveTwoDirection(NONNEGATIVE, nums1, N1, N, nums2, M1, M, k, queue);
                    }
                } else {//M1 == M
                    result = moveOneDirection(nums1, BACKWARD, N-1, N1-1, nums2, FORWARD, 0, M, k, queue);
                    if (k) {
                        result = moveOneDirection(nums1, BACKWARD, N1-1, -1, nums2, BACKWARD, M-1, -1, k, queue);
                    }
                }
            } else {
                if (M1 == 0) {
                    result = moveOneDirection(nums1, FORWARD, 0, N, nums2, BACKWARD, M-1, -1, k, queue);
                } else if (M1 < M) {
                    result = moveOneDirection(nums1, FORWARD, 0, N, nums2, BACKWARD, M-1, M1-1, k, queue);
                    if (k) {
                        result = moveOneDirection(nums1, BACKWARD, N-1, -1, nums2, BACKWARD, M1-1, -1, k, queue);
                    }
                } else {//M1 == M
                    result = moveOneDirection(nums1, BACKWARD, N-1, -1, nums2, BACKWARD, M-1, -1, k, queue);
                }
            }
            return result;
        }
};

/*
    Нужно найти k-ю по счету (начиная счет с 1) наименьшее произведение между элементом nums1[i] и nums2[j]
    nums1 и nums2 отсортированы по возрастанию
    Итак предположим для простоты, что все числа положительные
    a1, a2, ..., an
    b1, b2, ..., bm
    Итак, может быть такое, что a_i * b_{j+1} > a_{i+1} * b_j
    при этом в любом случае a_i * b_{j+1} <= a_{i+1} * b_{j+1}
    Итак, допустим
    (x + dx) * y > x * y
    x * (y + dy) > x * y
    однако, как (x + dx)*y ? x*(y + dy)
    допустим x < y
    предположим что dx < dy
    x * (y+dy) ? (x+dx) * y
    xy + xdy ? xy + ydx
    x*dy ? y * dx
    
    тогда x * (y + dy) < (x + dx) * y
    Если x < y и dy < dx
    Если xdy < ydx, то есть dy < (y*dx)/x

    Посмотрим частный пример
    1 6 8 9 11
    10 20 21 22
    10 20 21 22 60 120 126 132 80 160 168 176 90 180 189 198 110 220 231 242
    10   20   21   22   60   80   90   110   120  126  132  160  168  176  180  189  198  220   231   242
    1*10 1*20 1*21 1*22 6*10 8*10 9*10 11*10 6*20 6*21 6*22 8*20 8*21 8*22 9*20 9*21 9*22 11*20 11*21 11*22
    0,0  0,1  0,2  0,3  1,0  2,0  3,0  4,0   1,

        1   6   8   9   11  12
    10  10  60  80  90  110 120
    20  20  120 160 180 220 240
    21  21  126 168 189 231 252
    22  22  132 176 198 242 264
    25  25  150 200 225 275 300

    Итак, задача явно на использование стека
    Ну, самая быстрая релизация через очередь приоритетов
    Берём первое число и кладём в очередь приоритетов (вместе с индексом предыдушего и следующего)
    Причем обход делаем следующим образом, чтобы не было повторений - если элемент помечен как горизонтальный, то добавляем nums1[i+1] вместо nums1[i], если вертикальный, то nums2[j+1] вместо nums2[j], если диагональный 

    Проблема - есть отрицательные числа, которые при умножении дают положительные числа

    Итак, алгоритм с очередью приоритетов не прошёл по времени выполнения
    Второй вариант банальный - просто создать массив вмещающий 10^10 чисел, записать всевозожмные числа и сортировать, но походу и этот вариант не пройдет
    3-й вариант - использовать таблицу с индексом по значению (по сути массив с размером = обхват всего диапазона), но ограничения не позволят
    Что можно использовать
    Двоичный поиск?
    Итак, допустим у нас простая версия, мы умножаем массив (все числа неотрицательные) a1, a2, ..., an на b1, ..., bm
    Известно, что a1 * b1 = min num, an * bm = max num
    f(A, B, k) {
        if (k == 1) {
            return A[1] * B[1];
        } else {
            Итак, минимальный элемент min = A[1] * B[1]
            k--
            Пусть A_1 = A[2:], B_1 = B[2:]
            Тогда нужно рассмотреть подзадачи перемножения 
            f(A[0], B_1, k)
            f(A_1, B[0], k)
            f(A_1, B_1, k)
            При этом мы имеем следующие свойства:
            A[i] <= A[i+1]
            B[j] <= B[j+1]
            A[i] * B[j] <= A[i]*B[j+1]
            A[i] * B[j] <= A[i+1] *B[j+1]
            Однако, не факт, что A[i] * B[j+1] <= A[i+1] * B[j]
            Это верно, только если A[i] <= (A[i+1] * B[j])/B[j+1]
            A[i+1] = A[i] + dA
            B[j+1] = B[j] + dB
            A[i] <= (A[i] + dA) * B[j] / (B[j] + dB)
            1 <= (1 + dA/A[i]) / (1 + dB/B[j])
            1 + dB/B[j] <= 1 + dA/A[i]
            dB/B[j] <= dA/A[i]
            A[i]dB <= B[j]dA
            
            Итак возьмем произведение A[i]*B[j]
            (индексирование начинаем с 1)
            Итак, мы однозначно знаем, что слева от него находится минимум i*j-1 элементов
            Справа минимум (n-i)*(m-j)+(n-i)+(m-j) элементов
            Если 
            Итак, нашли первый элемент, A[i]*B[j] который минимум точно больше или равен k (TODO: Или найдем)
            1.1)Далее ищем первый i1 < i слева, для которого A[i1]*B[j+1] >= A[i]*B[j], и находим последний j1 > j, для которого A[i1]*B[j1] >= A[i]*B[j]
            Тогда справа точно будет ещё (i-i1)*(j1-j) элементов
            Получается справа будет (n-i)*(m-j)+(n-i)+(m-j) + (i-i1)*(j1-j)
            1.2)Одновременно с этим ищем первый j2 < j слева, для которого A[i+1]*B[j2] >= A[i]*B[j], и находим последний i2 > i, для которого A[i2]*B[j2] >= A[i]*B[j]
            Тогда справа точно будет ещё (i2-i)*(j-j2) элементов
            Получается справа будет как минимум (n-i)*(m-j)+(n-i)+(m-j) + (i-i1)*(j1-j) + (i2-i)*(j-j2)
            
            Проблема может быть так, что A[1] * B[m] >= A[i]*B[j], хотя A[1] * B[j+1] < A[i]*B[j]
            Меняем алгоритм
            Изем первый i1_1 < i слева, такой, что A[i1_1]*B[m] >= A[i]*B[j]
            Далее, ищем первый j1_1 > j, такой, что A[i1_1]*B[j1_1] <= A[i]*B[j]
            i1_1-1 потому что в любом случае для t < i1 при любом произведении A[t]*B[m] <= A[i]*B[j]
            А для s:j < s < j1 получаем ещё, что A[t]*B[s] <= A[i]*B[j] гарантировано
            Тогда слева от C[i,j] будет минимум (i*j-1)+(j1_1-j)*(i1_1-1)
            Справа от C[i,j] будет минимум (n-i)*(m-j)+(n-i)+(m-j)+(i-i1_1)*(m-j1_1)
            L(i,j) = (i*j-1)+(j1_1-j)*(i1_1-1)
            R(i,j) = (n-i)*(m-j)+(n-i)+(m-j)+(i-i1_1)*(m-j1_1)
            Далее, ищем первый j1_2 < j слева, такой, что A[n]*B[j1_2] >= A[i]*B[j]
            Далее, ищем последний i1_2 > i, такой, что A[i1_2]*B[j1_2] <= A[i]*B[j]
            Тогда слева от C[i,j] будет минимум (i*j-1)+(j1_1-j)*(i1_1-1)+(i1_2-i)*(j1_2-1)
            Справа от C[i,j] будет минимум (n-i)*(m-j)+(n-i)+(m-j)+(i-i1_1)*(m-j1_1)+(j-j1_2)*(n-i1_2)
            L(i,j) = (i*j-1) + (j1_1-j)*(i1_1-1) + (i1_2-i)*(j1_2-1) + ... + (jr_1-j)*(ir_1-1) + (ir_2-i)*(jr_2-1)
            R(i,j) = (n-i)*(m-j)+(n-i)+(m-j) + (i-i1_1)*(m-j1_1) + (j-j1_2)*(n-i1_2) + ... + (i-ir_1)*(m-jr_1) + (j-jr_2)*(n-ir_2)
            Можно ли осуществлять сдвиг функций L и R по i и по j?
            1)можно ли заменить L(i,j) на L(i+1,j)?
            Пусть L(i,j) = (i*j-1) + (j1_1-j)*(i1_1-1) + (j2_1-j)*(i2_1-1) + ... + (jr_1-j)*(ir_1-i)
            меняем (i*j-1) на ((i+1)*j-1) - верно
            Итак, i1_1 - это первый элемент слева, для которого A[i1_1]*B[m] >= A[i]*B[j]
            Но, не факт, что A[i1_1]*B[m] >= A[i+1]*B[j]
            Ответ, нет, нельзя
            2)можно ли заменить L(i,j) на L(i-1,j)?
            (i-1)*j-1 - верно, минимум слева столько, да
            Касательно i1_1  A[i1_1]*B[m] >= A[i]*B[j] ---> A[i1_1]*B[m] >= A[i-1]*B[j] - верное
            Но не факт, что i1_1 является минимальной левым значением, таким, что A[i1_1]*B[m] >= A[i-1]*B[j]
            Касательно j1_2  A[n]*B[j1_2] >= A[i]*B[j] ---> A[n]*B[j1_2] >= A[i-1]*B[j] - верно
            Тогда L(i-1,j)=((i-1)*j-1) + (j1_1-j)*(i1_1-1)
            Таким образом в любом случае, придётся вычислять несколько разных L
            Нам по сути нужно найти такое i,j, что полное значение L(i,j) = k-1
            Полное значение L - это точное значение сколько в массиве элементов точно меньше или равно A[i]*B[j]
            Итак, допустим мы вычисляем несколько значений L сразу, типа
            матрица ML
            L(i-di,j-dj)  L(i-di, j)  L(i-di, j+dj)
            L(i, j-dj)    L(i,j)      L(i, j+dj)
            L(i+di,j-dj)  L(i+di, j)  L(i+di, j+dj),
            Изместно что ML[x+1][y] > ML[x][y], ML[x][y+1] > ML[x][y],
            Проблема, мы точно не можем установить границы, где находится k
            Например мы не знаем как сравнивать элементы в матрице L побочной диагонали
            Но мы можем предположить, в какой четверти он приблизительно находится 
            Типа вычисляем точно 9 точек, для каждой точки используя ранее используемый метод двоичного поиска для уточнения L
            Далее, определяем в каком квадрате находится k, для этого сравниваем ML[x+1][y+1] >= k >= ML[x][y]
            Далее берём этот квадрат и строим новую матрицу, где выбраные i+-di = i, j+-di = j, di = di/2, dj = dj/2 и продолжаем процесс до тех пор, пока какой-нибудь ML[x][y] не будет равен k
            В начале матрица имеет вид
            L(1,1)      L(1,m/2)      L(1,m)
            L(n/2,1)    L(n/2,m/2)    L(n/2,m)
            L(n,1)      L(n,m/2)      L(n,m)
            Где, L(1,1) = 0, L(n,m) = n*m (не факт, в случае с отрицательными числами может быть сюрприз)
            Остальные вычисляются, 

            Я совершил ошибку при вычислении L(i, j)
            Начальное значение L(i,j) = i*j-1
            Ищем i1 - первый индекс слева (i1 < i), такой, что A[i1]*B[m] >= A[i]*B[j]
            Далее ищем j2 - первый индекс слева (j2 > j), такой, что A[i1]*B[j1] >= A[i]*B[j]
            Тогда гарантировано (в первой итерации) обновляем L(i,j) на значение (i1-1)*(M-j-1)
            Далее ищем следующий i1_1 > i1, такой, что его граница j2_1 < j2, j2_1 <= M
            Тогда гарантированно имеем ещё (i1_1 - i1) * (j2 - j2_1) элементов слева от A[i]*B[j]
            Далее так делаем, пока i1_r < i, j2_r > j
            Аналогично и для j1 и i2 делаем, решения не пересекаются
            Таким образом полная формула L выглядит следующим образом
            1 2 3 4 5 i 7
            L(i,j) = i*j-1 + (i1_1-1)*(M-j) + (j1_1-1)*(N-i) + (i1_2-i1_1)*(j2_2-j) + (j1_2-j1_1)*(i2_2-i) + ... + (i1_r - i1_{r-1}) * (j2_r - j) + (j1_t - j1_{t-1}) * (i2_t - i)
            Первая итерация и последующие немного отличаются
            //TODO: Проверь на бумаге истиность количества элементов слева и справа
            //TODO: Для оптимизации не обязательно считать все 9 точек, можно проверять, если в только что вычисленном квадрате находится k, то остальные точки вычислять не надо
            Таким образом алгоритм следующий
            find_binary_search_i1(A, prev_i1, i, Bvalue, lower) {
                //TODO:Попроси DeepSeek
                //TODO
            }
            find_binary_search_j2(B, prev_j2, j, Avalue, lower) {
                //TODO
            }
            find_L_base(i, j) {
                return (i+1)*(j+1)-1;
            }
            find_L_adv(A, B, i, j, prev_i1, prev_j2) {
                int result = 0;
                int j1 = prev_i1;
                int mult = A[i]*B[j];
                while (true) {
                    i1 = find_binary_search_i1(A, prev_i1, i, B[prev_j2], mult);
                    if (i1 < i && prev_j2 > j) {
                        result += (i1 - prev_i1)*(prev_j2-j-1);
                        prev_j2 = find_binary_search_j2(B, prev_j2, j, A[i1], mult);     
                        prev_i1 = i1;
                    } else {
                        break;
                    }
                }
                return result;
            }
            find_L(A, B, i, j, i_begin, j_begin, N, M) {
                return find_L_base(i, j) + find_L_adv(A, B, i, j, i_begin, M-1) + find_L_adv(B, A, j, i, j_begin, N-1);
            }
            fill_index_array_init(index_array, index_begin, index_end) {
                index_array[0] = index_begin;
                index_array[1] = (index_begin + index_end) / 2;
                index_array[2] = index_end
            }
            //TODO: По идее нам можно обойтись и без вычисления точек [0][2] и [2][0]
            fill_ML_init(ML, A, B, N, M, i_array, j_array, i_begin, j_begin) {
                for (int x = 0; x < 3; ++x) {
                    for (int y = 0; y < 3; ++y) {
                        ML[x][y] = find_L(A, B, i_array[x], j_array[y], i_begin, j_begin, N, M);
                    }
                }
            }
            fill_ML_update(ML, A, B, N, M, int x1, int y1, i_array, j_array, i_begin, j_begin) {
                ML[0][0] = ML[x1][y1];
                ML[0][2] = ML[x1][y1+1];
                ML[2][0] = ML[x1+1][y1];
                ML[2][2] = ML[x1+1][y1+1];
                for (int x = 0; x < 3; ++x) {
                    ML[x][1] = find_L(A, B, i_array[x], j_array[1], i_begin, j_begin, N, M);
                }
                for (int y = 0; y < 3; y += 2) {
                    ML[1][y] = find_L(A, B, i_array[1], j_array[y], i_begin, j_begin, N, M);
                }
            }
            
            f_positive(A,B,N,M,k, i_begin, j_begin) {
                Создать массивы i_array и j_array размера 3, и матрицу ML размера 3x3, 
                fill_index_array_init(i_array, i_begin, N-1);
                fill_index_array_init(j_array, j_begin, M-1);
                fill_ML_init(ML, A, B, N, M, i_array, j_array, i_begin, j_begin);
                //TODO: Вроде проверять на выход за пределы допустимых k не нужно
                while(not_calculated(ML, k-1)) {
                    //TODO: find_x_y(ML, x, y);
                    fill_index_array_init(i_array, i_array[x], i_array[x+1]);
                    fill_index_array_init(j_array, j_array[y], j_array[y+1]);
                    fill_ML_update(ML, A, B, N, M, x, y, i_array, j_array, i_begin, j_begin)
                }
            }
            f_negative_one(A,B,N,M,k,j_end) {
                //TODO: По сути делаем то же самое, только порядок обхода А этой функции от большего к меньшему, потом запускаем f_positive
            }
            
            Итак, у нас есть 2 соответствующих одновременных прохода влево и вправо
            Итак, мы одновременно идём влево и вправо
            Допустим мы выбрали A[i]*B[j], как в этом случае узнать L(i,j)

            !!!Подзадача первая!!!
            Допустим и A[i], и B[j] отрицательные числа
            Пусть i0 и j0 - это индексы, когда начинаются неотрицательные числа
            Тогда 1)ищем i1_l < i0, i1_l > i, j2_l < j, j2_l < j0, такие, что A[i1_l]*B[j1_l] >= A[i]*B[j] (по той же самой логике, что искали в f_positive, только обход справа налево)
            2)Ищем такую первую i1_r > i0, A[i1_r] <= A[i], такую что A[i1_r]*B[m] >= A[i]*B[j], далее ищем первый слева такой j2_r > j0, что A[i1_r]*B[j2_r] >= A[i]*B[j]
            A: 10 9 8 7 6 i 4 3 i1_l 1 i0 1 2 3 i1_r 4 5 6 7 8 9 10 N
            B: 10 9 j2_l 7 6 j 4 3 2 1 j0 1 2 3 j2_r 4 5 6 7 8 9 10 M
            В начале L(i,j) = (i0-i-1)*(j0-j-1)
            Затем добавляем с каждой стороны уточнения
            L_adv(i,j) = (i1_r - i0)*(M-j0)* + (i0-1 - i1_l)*(j0-1) + симметричный аналог относительно B
            //TODO: Может ли быть такое, что в случае с симметрией тут может быть повторение?
            Далее обновляем значения
            i1_l: i1_l_old > i1_l > i
            j2_l: j > j2_l > j2_l_old
            i2_r: i0 <= i2_r_old < i2_r < N, A[i2_r] <= A[i]; 
            j2_r: j0 <= j2_r < j2_r_old < M, A[i1_l]*B[j2_l] >= A[i]*B[j], A[i1_r] * B[j2_r] >= A[i]*B[j]
            //TODO: Не забудь, чтоб в варианте с положительными числами должно быть > вместо >=
            L_adv(i,j) = L_adv(i,j) + (i1_r - i1_r_old)*(j1_r_old - j0) + (i1_l_old - i1_l)*(j-j2_l_old-1) + симметрия относительно B
            Пока изменяется хотя бы одна из двух пар (i1_l, j2_l) и (i1_r, j2_r) обновляем L_adv
            Затем L(i,j) = L(i,j) + L_adv(i,j)
            //TODO: Рассмотреть проблемы с симметрией

            !!!Подзадача вторая!!!
            Допустим одно из чисел A[i] и B[j] - отрицательное, другое неотрицательное (A[i] - отрицательно)
            10 9 8 7 6 i 4 3 2 1 i0 1 2 3 4 5 6 7 8 9 10
            10 9 8 7 6 5 4 3 2 1 j0 1 2 3 4 5 6 j 8 9 10
            Итак, A[i]*B[j] <= 0, значит, нужно брать наименьшие значения слева и наибольшие значения справа, например, при t,s >=0 гарантированно, что A[i-t]*B[j+t] <= A[i]*B[j]
            Таким образом в начале L(i,j) = (i-1)*(M-j)
            1)Находим слева первый такой i1: i1 < i, A[i1]*B[j0] >= A[i]*B[j]
            Также ищем последний такой j2: j0 <= j2 < j, A[i1]*B[j2] >= A[i]*B[j]
            10 9 8 i1 6 i 4 3 2 1 i0 1 2 3 4 5 6 7 8 9 10
            10 9 8 7 6 5 4 3 2 1 j0 1 2 3 j2 5 6 j 8 9 10
            L_adv(i,j) = (i1-1)*(j-j0);
            Далее обновляем i1_old < i1 < i, j2_old < j2 < j
            L_adv(i,j) = L_adv(i,j) + (i1-i1_old)*(j-j2_old)
            2)Находим справа первый такой j1: j1 > j, A[i0-1]*B[j1] >= A[i]*B[j]
            Также ищем первый слева такой i2: i < i2 < i0, что A[i2]*B[j1] >= A[i]*B[j]
            10 9 8 7 6 i 4 i2 2 1 i0 1 2 3 4 5 6 7 8 9 10
            10 9 8 7 6 5 4 3 2 1 j0 1 2 3 4 5 6 j 8 j1 10
            L_adv(i,j) = L_adv(i,j) + (i2-(i+1))*(M-j1)
            Далее обновляем j < j1 < j1_old, i < i2 < i2_old
            L_adv(i,j) = L_adv(i,j) + (i2-(i+1))*(j1_old-j1)
            3)Однако, также ищем первый слева j3 < j0 такой, что A[i0]*B[j3] >= A[i]*B[j]
            Далее, ищем последний такой i3 слева, i0 <= i3 < N, что A[i3]*B[j3] >= A[i]*B[j]
            L_adv(i,j) = L_adv(i,j) + (j3-1)*(N-i0)
            Далее обновляем следующий j3_old < j3 < j0, i3_old < i3, что A[i3]*B[j3] >= A[i]*B[j]
            L_adv(i,j) = L_adv(i,j) + (j3-j3_old)*(N-i3_old)//TODO: N-i3_old надо проверить

            //TODO: Проверить все эти интервалы
            //TODO: Я походу пропускаю элементы типа A[i+t]*B[j], так что может быть ошибка

            Итак, как осуществлять двоичный поиск между L(i1,j1) и L(i2,j2), Тут похоже 2 сетки
            !!!Первая подзадача!!!
            Результат умножения должен быть неотрицательный, то есть
            Итак, пусть i0 и j0 - индексы, с которых начинаются не отрицательные числа
            Тогда считаем L(1,1), L(i0-1,j0-1) - границы левой сетки, причем L(i0-1,j0-1) < L(1,1)
                          L(i0,j0), L(N,M) - границы правой сетки
            Решаем задачу так же как в случае с положительными числами, только мы проверяем квадраты сразу в 2-х сетках, и на основе этих квадратов строим новые сетки, пока в одной из сеток не будет найдено значение = k-1

            !!!Вторая подзадача!!!
            Результат умножения должен быть неположительный, то есть
            Итак, пусть i0 и j0 - индексы, с которых начинаются не отрицательные числа
            Тогда считаем L(1,M), L(i0-1,j0) - границы левой сетки, L(1,M) < L(i0-1,j0)
                          L(N,1), L(i0,j0-1) - границы правой сетки L(N,1) < L(i0,j0-1)
            
            //TODO: Может можно как-то привести эту задачу, к виду, где есть только неотрицательные числа
        }
    }
*/

/*
Короче, у нас 2 есть подзадачи, В обих случаях мы вычисляем 2 сетки - сетку обходов с разных сторон

Но что делать с равными произведениями
..., a_i1, ..., a_i2, ...
..., b_j1, ..., b_j2, ...
a_i1*b_j2 = a_i2*b_j1

//TODO: Не знаю что делать с равными элементами, вернусь позже
//TODO: Может паралельно с функцией L, считать функцию E(i, j), которая считает количество равных c A[i]*B[j] произведений 
Тогда, если значение L(i,j) =< k-1 <= L(i,j) + E(i,j), то C[k] = A[i]*B[j]
Тогда вычисление значений усложняется
Вместе с сетками со значениями L строим сетки со значениями E,
для удобства можно заранее сделать префиксный и суффиксный массив с индексами первых и последних элементов

Ну допустим 
*/
//i < i0, j >= j0
long long find_E1_base(const std::vector<int> &A, const std::vector<int> &B, int i, int j, int N, int M) {
    long long equal = 0;
    int left = 0, right = 0;
    for (int i1 = i; i1 >= 0 && A[i1] == A[i]; --i, ++left);
    for (int j1 = j; j1 < M && A[j1] == A[j]; ++j, ++right);
    return left*right;
}

//Значение вычисляется так, что A[i] < 0, B[j] >= 0
long long find_L1_base(int i, int j, int i0, int j0, int N, int M) {
    return (i+1)*(M-j);
}

int find_i1_1(const std::vector<int> &nums, int begin, int end, int Bj, long long mult) {
    for (int i = begin; i < end; ++i) {
        if (static_cast<long long>(nums[i])*Bj >= mult) {
            return i;
        }
    }
    return end;
}

int find_j2_1(const std::vector<int> &nums, int begin, int end, int Ai, long long mult) {
    for (int j = begin; j < end; ++j) {
        if (static_cast<long long>(nums[j])*Ai == mult) {
            return j;
        }
    }
    return end;
}

int find_equal_index_last(const std::vector<int> &nums, int begin, int end, int num) {
    int index = begin;
    for (int i = begin + 1; i < end && nums[i] == num; ++i, ++index);
    return index;
}

long long find_E1_adv1(const std::vector<int> &A, const std::vector<int> &B, int i, int j, int i0, int j0, int N, int M) {
    long long result = 0, mult = A[i]*B[j];
    int i1_1 = 0, i1_2 = -1, j2_1 = 0, j2_2 = j0-1;
    /*
    1)Ищем первый слева 0 <= i1_1 < i, такой, что A[i1_1]*B[j0] >= A[i]*B[j]
    2)Ищем первый слева j0 <= j2_1 < j, такой, что A[i1_1]*B[j2_1] == A[i]*B[j]
    3)Ищем последний слева i1_1 <= i1_2 < i, такой, что A[i1_2] == A[i1_1]
    4)Ищем последний слева j2_1 <= j2_2 < j, такой, что B[j2_2] == B[j2_1]
    */
    ++i;
    ++j;
    while(true) {
        ++j2_2;
        if (j2_2 < j) {
            //TODO: Для оптимизации надо 0 заменить на i1_* какое-то, чтобы не проверять ранние значения
            i1_1 = find_i1_1(A, 0, i, B[j2_2], mult);
            //j2_2 - увеличивается, значит произведение уменьшается
            if (i1_1 == i) {
                break;
            }
            j2_1 = find_j2_1(B, j2_2, j, A[i1_1], mult);
            if (j2_1 < j) {
                //Чтобы не было пересечений с find_E1_base
                if (i1_1 == i-1 && j2_1 == j-1) {
                    --result;
                }
                i1_2 = find_equal_index_last(A, i1_1, i, A[i1_1]);
                j2_2 = find_equal_index_last(B, j2_1, j, B[j2_1]);
                result += (i1_2 - i1_1 + 1) * (j2_2 - j2_1 + 1);
            }
        }
    }
    return result;
}

int find_j1_1(const std::vector<int> &nums, int begin, int end, int Ai, long long mult) {
    for (int j = begin; j > end; --j) {
        if (static_cast<long long>(nums[j])*Ai >= mult) {
            return j;
        }
    }
    return end;
}

int find_i2_1(const std::vector<int> &nums, int begin, int end, int Bj, long long mult) {
    for (int i = begin; i > end; --i) {
        if (static_cast<long long>(nums[i])*Bj == mult) {
            return i;
        }
    }
    return end;
}

int find_equal_index_first(const std::vector<int> &nums, int begin, int end, int num) {
    int index = begin;
    for (int i = begin - 1; i > end && nums[i] == num; --i, --index);
    return index;
}

long long find_E1_adv2(const std::vector<int> &A, const std::vector<int> &B, int i, int j, int i0, int j0, int N, int M) {
    long long result = 0, mult = A[i]*B[j];
    //TODO:старые значения надо быть осторожнее
    int j1_1 = j, j1_2 = M, i2_1 = 0, i2_2 = i0;
    --j;
    --i;
    while (true) {
        --i2_2;
        if (i2_2 > i) {
            //TODO:M-1 надо на что-то заменить
            j1_1 = find_j1_1(B, M-1, j, A[i2_2], mult);
            if (j1_1 == j) {
                break;
            }
            i2_1 = find_i2_1(A, i2_2, i, B[j1_1], mult);
            if (i2_1 > i) {
                if (i2_1 == i+1 && j1_1 == j+1) {
                    --result;
                }
                j1_2 = find_equal_index_first(B, j1_1, j, B[j1_1]);
                i2_2 = find_equal_index_first(A, i2_1, i, A[i2_1]);
                result += (j1_1 - j1_2 + 1) * (i2_1 - i2_2 + 1);
            }
        }
    }
    return result;
    /*
        2)Находим справа первый такой j1: j1 > j, A[i0-1]*B[j1] >= A[i]*B[j]
        Также ищем первый слева такой i2: i < i2 < i0, что A[i2]*B[j1] >= A[i]*B[j]
        10 9 8 7 6 i 4 i2 2 1 i0 1 2 3 4 5 6 7 8 9 10
        10 9 8 7 6 5 4 3 2 1 j0 1 2 3 4 5 6 j 8 j1 10
        L_adv(i,j) = L_adv(i,j) + (i2-(i+1))*(M-j1)
        Далее обновляем j < j1 < j1_old, i < i2 < i2_old
        L_adv(i,j) = L_adv(i,j) + (i2-(i+1))*(j1_old-j1)
    */
}

//TODO: Доделать
long long find_E1_adv3(const std::vector<int> &A, const std::vector<int> &B, int i, int j, int i0, int j0, int N, int M) {
    /*
        3)Однако, также ищем первый слева j3 < j0 такой, что A[i0]*B[j3] >= A[i]*B[j]
        Далее, ищем последний такой i3 слева, i0 <= i3 < N, что A[i3]*B[j3] >= A[i]*B[j]
        L_adv(i,j) = L_adv(i,j) + (j3-1)*(N-i0)
        Далее обновляем следующий j3_old < j3 < j0, i3_old < i3, что A[i3]*B[j3] >= A[i]*B[j]
        L_adv(i,j) = L_adv(i,j) + (j3-j3_old)*(N-i3_old)//TODO: N-i3_old надо проверить
    */
    long long result = 0, mult = A[i]*B[j];
    int j3_1 = 0, j3_2 = -1, i3_2 = i0-1, i3_1 = i0;

    while (true) {
        ++j3_2;
        ++i3_2;
        //TODO: Можно ли как-то не пересчитывать начиная с i0
        if (j3_2 < j0) {
            j3_1 = find_i1_1(B, j3_2, j0, A[i0], mult);
            if (j3_1 == j0) {
                break;
            }
            i3_1 = find_j2_1(A, i0, N, B[j3_1], mult);
            if (i3_1 < N) {
                j3_2 = find_equal_index_last(B, j3_1, j0, B[j3_1]);
                i3_2 = find_equal_index_last(A, i3_1, N, A[i3_1]);
                result += (j3_2 - j3_1 + 1) * (i3_2 - i3_1 + 1);
            }
        }
    }
    return result;
}

long long find_E1(const std::vector<int> &A, const std::vector<int> &B, int i, int j, int i0, int j0, int N, int M) {
    return find_E1_base(A, B,)//TODO:
}

//TODO: Как определять порядок равных по произведению элементов? (наверное по старшинству индексов), типа сначала сравниваем индексы по i, потом по j
//TODO: Тогда придётся менять базовые функции
//Значение вычисляется так, что A[i] < 0, B[j] >= 0
long long find_L1_adv1(const std::vector<int> &A, const std::vector<int> &B, int i, int j, int i0, int j0) {
    long long result = 0;
    int i1 = 0, i1_old = 0, j2 = 0, j2_old = j0;
    //TODO: Надо ещё с равными значениями посчитать
    //TODO:Ищем первый слева 0 =< i1 < i, такой, что A[i1]*B[j0] > A[i]B[j]
    //TODO:Ищем первый справа j0 <= j2 < j, такой, что A[i1]*B[j2] > A[i]*B[j]
    long long mult = A[i]*B[j];
    while (true) {
        result += static_cast<long long>(i1-i1_old)*(j - j2_old);
        i1_old = i1;
        j2_old = j2;
        //TODO:Ищем первый слева i1_old < i1 < i, такой, что A[i1]*B[j2_old-1] > A[i]*B[j]
        //TODO:Ищем первый справа j0 <= j2 < j2_old, такой, что A[i1]*B[j2] > A[i]*B[j]
    }
    return result;
}

long long find_L1_adv2(const std::vector<int> &A, const std::vector<int> &B, int i, int j, int i0, int j0) {
    long long result = 0;
    int j1 = 0, j1_old = B.size()-1, i2 = 0;
    //TODO: Находим справа первый такой j1: M-1 > j1 > j, A[i0-1]*B[j1] > A[i]*B[j]
    //TODO: Находим первый слева такой i2: i < i2 < i0, A[i2]B[j1] > A[i]*B[j]
    //TODO: Надо ещё с равными значениями посчитать
    long long mult = A[i]*B[j];
}

//A[i] - отрицательно, B[j] - неотрицательно
long long find_L1(const std::vector<int> &A, const std::vector<int> &B, int i, int j, int i0, int j0) {
    return find_L1_base(i, j, i0, j0, A.size(), B.size());
}
class Solution2 {
    private:
        using index_t = int;
        using jndex_t = int;
        ///////////////////////////////////////Простые фукции для двоичного поиска///////////////////////
        int find_first_nonnegative_index(const std::vector<int> &nums) {
            int left = 0, right = nums.size()-1, center;
            if (nums[right] < 0) {
                return nums.size();
            }
            while (nums[left] < 0) {
                center = (right + left) / 2;
                if (nums[center] < 0) {
                    left = center+1;
                } else {
                    right = center;
                }
            }
            return left;
        }
        //TODO: Поиски find_binary_search_i1, find_binary_search_j2
        /////////////////////////////////////версия только для неотрицательных чисел///////////////
        void fill_index_array_init(int index_array[3], int index_begin, int index_end) {
                index_array[0] = index_begin;
                index_array[1] = (index_begin + index_end) / 2;
                index_array[2] = index_end;
        }
        /////////////////////////////////////Функции для поиска L на неотрицательных массивах////////////////////
        long find_L_base1(int i, int j) {
            return static_cast<long>(i+1)*(j+1)-1;
        }
        long find_L_adv1(const std::vector<int> &A, const std::vector<int> &B, int i, int j, int prev_i1, int prev_j2) {
            int result = 0;
            int i1;
            int mult = A[i]*B[j];
            while (true) {
                i1 = find_binary_search_i1(A, prev_i1, i, B[prev_j2], mult);
                if (i1 < i && prev_j2 > j) {
                    result += (i1 - prev_i1)*(prev_j2-j-1);
                    prev_j2 = find_binary_search_j2(B, prev_j2, j, A[i1], mult);     
                    prev_i1 = i1;
                } else {
                    break;
                }
            }
            return result;
        }
        long find_L1(const std::vector<int> &A, const std::vector<int> &B, const int i, const int j, const int i_begin, const int j_begin, const int N, const int M) {
            return find_L_base1(i - i_begin, j-j_begin) + find_L_adv1(A, B, i, j, i_begin, M-1) + find_L_adv1(B, A, j, i, j_begin, N-1);
        }
        ////////////////////////////////////Функции для поиска L на общем отрезке, в случае если оба числа отрицательны, в этом случае
        /*
        Итак, мы походу не можем 
        */
        enum ML_result_t {
            FOUND,
            IN,
            OUT
        };
        ML_result_t fill_ML_init(long ML[3][3], 
            const std::vector<int> &A, const std::vector<int> &B, 
            int i_array[3], int j_array[3], 
            const int i_begin, const int j_begin, 
            const int N, const int M,
            const int k,
            int &x1, int &y1) {
            for (int x = 0; x < 2; ++x) {
                for (int y = 0; y < 2; ++y) {
                    ML[x][y] = find_L(A, B, i_array[x], j_array[y], i_begin, j_begin, N, M);
                    if (ML[x][y] == k) {
                        x1 = x;
                        y1 = y;
                        return FOUND;
                    }
                }
            }
            if (ML[0][0] < k && k < ML[1][1]) {
                x1 = 0;
                y1 = 0;
                return IN;
            }
            for (int x = 0; x < 2; ++x) {
                ML[x][2] = find_L(A, B, i_array[x], j_array[2], i_begin, j_begin, N, M);
                if (ML[x][2] == k) {
                    x1 = x;
                    y1 = 2;
                    return FOUND;
                }
            }
            if (ML[0][1] < k && k < ML[1][2]) {
                x1 = 0;
                y1 = 1;
                return IN;
            }
            for (int y = 0; y < 2; ++y) {
                ML[2][y] = find_L(A, B, i_array[2], j_array[y], i_begin, j_begin, N, M);
                if (ML[2][y] == k) {
                    x1 = 2;
                    y1 = y;
                    return FOUND;
                }
            }
            if (ML[1][0] < k && k < ML[2][1]) {
                x1 = 1;
                y1 = 0;
                return IN;
            }
            ML[2][2] = find_L(A, B, i_array[2], j_array[2], i_begin, j_begin, N, M);
            if (ML[2][2] == k) {
                x1 = 2;
                y1 = 2;
                return FOUND;
            }
            if (ML[1][1] < k && k < ML[2][2]) {
                x1 = 1;
                y1 = 1;
                return IN;
            }
            return OUT;
        }
        ML_result_t fill_ML_update(long ML[3][3], 
            const std::vector<int> &A, const std::vector<int> &B, 
            int i_array[3], int j_array[3], 
            const int i_begin, const int j_begin, 
            const int N, const int M,
            const int k,
            int &x1, int &y1) {
            ML[0][0] = ML[x1][y1];
            ML[0][2] = ML[x1][y1+1];
            ML[2][0] = ML[x1+1][y1];
            ML[2][2] = ML[x1+1][y1+1];

            for (int x = 0; x < 2; ++x) {
                for (int y = x ^ 1; y < 2; ++y) {
                    ML[x][y] = find_L(A, B, i_array[x], j_array[y], i_begin, j_begin, N, M);
                    if (ML[x][y] == k) {
                        x1 = x;
                        y1 = y;
                        return FOUND;
                    }
                }
            }
            if (ML[0][0] < k && k < ML[1][1]) {
                x1 = 0;
                y1 = 0;
                return IN;
            }
            ML[1][2] = find_L(A, B, i_array[1], j_array[2], i_begin, j_begin, N, M);
            if (ML[1][2] == k) {
                x1 = 1;
                y1 = 2;
                return FOUND;
            }
            if (ML[0][1] < k && k < ML[1][2]) {
                x1 = 0;
                y1 = 1;
                return IN;
            }
            ML[2][1] = find_L(A, B, i_array[2], j_array[1], i_begin, j_begin, N, M);
            if (ML[2][1] == k) {
                x1 = 2;
                y1 = 1;
                return FOUND;
            }
            if (ML[1][0] < k && k < ML[2][1]) {
                x1 = 1;
                y1 = 0;
                return IN;
            }
            if (ML[1][1] < k && k < ML[2][2]) {
                x1 = 1;
                y1 = 1;
                return IN;
            }
            return OUT;
        }

        //TODO: Сделать функцию, которая проверяет точки на равен
        long long find_positive_positive(const std::vector<int> &A, const std::vector<int> &B,
        const int N, const int M, 
        const int i0, const int j0, 
        long long &k) {
            long ML[3][3];
            int i_array[3], j_array[3];
            int x1, y1;
            ML_result_t code;
            fill_index_array_init(i_array, i0, N-1);
            fill_index_array_init(j_array, j0, M-1);
            code = fill_ML_init(ML, A, B, i_array, j_array, i0, j0, N, M, k, x1, y1);
            if (code == OUT) {
                //TODO: Как выйти с ошибкой
            }
            while (code == IN) {
                fill_index_array_init(i_array, i_array[x1], i_array[x1+1]);
                fill_index_array_init(j_array, j_array[y1], j_array[y1+1]);
                code = fill_ML_update(ML, A, B, i_array, j_array, i0, j0, N, M, k, x1, y1);
            }
            return static_cast<long long>(A[i_array[x1]])*B[j_array[y1]];
            /*
            Первая функция - вычисляет первые 4 точки (квадрате), затем следующие 2 точки справа, затем первые 2 точки снизу, затем последнюю точку
            Вторая функция - вычисляет первые 3 точки (1 точка уже вычислена), затем следующая 1 точка (1 точка уже вычислена), затем нижнюю точку последнюю точку (для 3-го квадрата), для последней точки уже вычислены
            */
        }
        //TODO: А как в функциях поиска осуществляется
        long long find_negative_negative(const std::vector<int> &A, const std::vector<int> &B,
        const int N, const int M, 
        const int i0, const int j0, 
        long long &k) {
            return find_positive_positive(A, B, 0, 0, i0-1, j0-1, k);
        }
        long long find_positive_negative(const std::vector<int> &A, const std::vector<int> &B,
        const int N, const int M, 
        const int i0, const int j0, 
        long long &k) {
        }
        //TODO: Нужно создать общую функцию поиска, которая ищет либо слева либо справа с началом и концом (наверное не включая конец)
    public:
        long long kthSmallestProduct(std::vector<int> &nums1, std::vector<int> &nums2, long long k) {
            const auto N = nums1.size(), M = nums2.size();
            int i0 = 0, j0 = 0;
            long result = 0;
            i0 = find_first_nonnegative_index(nums1);
            j0 = find_first_nonnegative_index(nums2);
            //TODO: создать 5 функций - позитив и позитив, позитив и негатив, позитив и позитив/негатив, негатив и позитив/негатив, позитив/негатив и позитив/негатив
            if (i0 == 0) {
                if (j0 == 0) {
                    //TODO: позитив и позитив
                    //result = moveOneDirection(nums1, FORWARD, 0, N, nums2, FORWARD, 0, M, k, queue);
                } else if (j0 < M) {
                    //TODO: позитив и позитив/негатив
                    /*
                    result = moveOneDirection(nums1, BACKWARD, N-1, -1, nums2, FORWARD, 0, M1, k, queue);
                    if (k) {
                        result = moveOneDirection(nums1, FORWARD, 0, N, nums2, FORWARD, M1, M, k, queue);
                    }
                    */
                } else {//M1 == M, то есть все числа отрицательны 
                    //TODO: позитив и негатив
                    //result = moveOneDirection(nums1, BACKWARD, N-1, -1, nums2, FORWARD, 0, M, k, queue);
                }
            } else if (i0 < N) {
                if (j0 == 0) {
                    //TODO: позитив и позитив/негатив
                    /*
                    result = moveOneDirection(nums1, FORWARD, 0, N1, nums2, BACKWARD, M-1, -1, k, queue);
                    if (k) {
                        result = moveOneDirection(nums1, FORWARD, N1, N, nums2, FORWARD, 0, M, k, queue);
                    }
                    */
                } else if (j0 < M) {
                    //TODO: Позитив/негатив и позитив/негатив
                    /*
                    result = moveTwoDirection(NEGATIVE, nums1, N1, N, nums2, M1, M, k, queue);
                    if (k) {
                        result = moveTwoDirection(NONNEGATIVE, nums1, N1, N, nums2, M1, M, k, queue);
                    }
                    */
                } else {//M1 == M
                    //TODO: Позитив/негатив и негатив
                    /*
                    result = moveOneDirection(nums1, BACKWARD, N-1, N1-1, nums2, FORWARD, 0, M, k, queue);
                    if (k) {
                        result = moveOneDirection(nums1, BACKWARD, N1-1, -1, nums2, BACKWARD, M-1, -1, k, queue);
                    }
                    */
                }
            } else {
                if (j0 == 0) {
                    //TODO: Негатив и позитив
                    //result = moveOneDirection(nums1, FORWARD, 0, N, nums2, BACKWARD, M-1, -1, k, queue);
                } else if (j0 < M) {
                    //TODO: Негатив и позитив/негатив
                    /*
                    result = moveOneDirection(nums1, FORWARD, 0, N, nums2, BACKWARD, M-1, M1-1, k, queue);
                    if (k) {
                        result = moveOneDirection(nums1, BACKWARD, N-1, -1, nums2, BACKWARD, M1-1, -1, k, queue);
                    }
                    */
                } else {//M1 == M
                    //TODO: Негатив и негатив
                    //result = moveOneDirection(nums1, BACKWARD, N-1, -1, nums2, BACKWARD, M-1, -1, k, queue);
                }
            }
            return result;
        }
};
void printVector(const std::vector<int> &nums) {
    for (int i = 1; i <= nums.size(); ++i) {
        std::cout << '\t' << i;
    }
    std::cout << std::endl;
    for (const auto &num : nums) {
        std::cout << '\t' << num;
    }
    std::cout << std::endl;
}

int main(void) {
    Solution sol;
    std::vector<int> nums1_1{2,5}, nums2_1{3,4};
    std::vector<int> nums1_2{-4,-2,0,3}, nums2_2{2,4};
    std::vector<int> nums1_3{-2,-1,0,1,2}, nums2_3{-3,-1,2,4,5};
    std::vector<int> nums1_4{-100000, 0, 100000}, nums2_4{-100000, 0, 100000};
    std::vector<int> tmp_nums(25);
    for (int k = 0, i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            tmp_nums[k] = nums1_3[i]*nums2_3[j];
            ++k;
        }
    }
    std::sort(tmp_nums.begin(), tmp_nums.end());
    std::cout << sol.kthSmallestProduct(nums1_1, nums2_1, 2) << std::endl;
    std::cout << sol.kthSmallestProduct(nums1_2, nums2_2, 6) << std::endl;
    printVector(tmp_nums);
    std::cout << sol.kthSmallestProduct(nums1_3, nums2_3, 24) << std::endl;
    std::cout << sol.kthSmallestProduct(nums1_4, nums2_4, 3) << std::endl;
    return 0;
}