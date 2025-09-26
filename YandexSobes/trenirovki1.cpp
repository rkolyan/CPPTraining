#include <cstring>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>

//Задача A
//SUCCESS
enum {
    SEQUENCE_0 = 0,
    SEQUENCE_1 = 1,
    SEQUENCE_11 = 2
};

unsigned int find_sequence_count(unsigned int N) {
    /*
    Итак, предположим у нас есть i-й элемент
    Если ai = 1 => a_{i+1} = 1 и a_{i+2} = 0 либо a_{i+1} = 0
    Если ai = 0 => a_{i+1} - любой
    Предположим в обратном порядке
    a_i = 1 -> a_{i-1} == 1 и a_{i-2} = 0, либо a_{i-1} = 0
    f(n, k) {
        Если k = 0
            Вернуть f(n-1, 1) + f(n-1, 0)
        Если k = 1
            Вернуть f(n-1, 2) + f(n-1, 1) + f(n-1, 0)
        Если k = 2
            вернуть f(n-1) 
        }
    f(0, k) {
        Вернуть 1
    }
    */
    unsigned int dp[2][3];
    dp[0][SEQUENCE_0] = 1;
    dp[0][SEQUENCE_1] = 1;
    dp[0][SEQUENCE_11] = 0;

    for (unsigned int i = 1; i < N; ++i) {
        dp[1][SEQUENCE_0] = dp[0][SEQUENCE_0] + dp[0][SEQUENCE_1] + dp[0][SEQUENCE_11];
        dp[1][SEQUENCE_1] = dp[0][SEQUENCE_0];
        dp[1][SEQUENCE_11] = dp[0][SEQUENCE_1];
        std::memcpy(dp[0], dp[1], sizeof(unsigned int[3]));
    }
    if (N > 1) {
        return dp[1][SEQUENCE_0] + dp[1][SEQUENCE_1] + dp[1][SEQUENCE_11];
    }
    return dp[0][SEQUENCE_0] + dp[0][SEQUENCE_1] + dp[0][SEQUENCE_11];
}



//Задача B
//SUCCESS
enum : unsigned int {
    BUY1 = 0,
    BUY2 = 1,
    BUY3 = 2
};

unsigned int find_min_buy_time(unsigned int N, const std::vector<std::array<unsigned int, 3>> &A) {
/*
    Опять жадный алгоритм
    Я пишу без оптимазиции потому что впадлу
*/
    std::array<std::array<unsigned int, 3>, 4> dp;
    unsigned int minimum = dp[0][BUY1] = A[0][BUY1];
    dp[0][BUY2] = A[0][BUY2];
    dp[0][BUY3] = A[0][BUY3];
    if (N > 1) {
        auto tmp = dp[0][BUY1];
        dp[1][BUY1] = A[1][BUY1] + tmp;
        dp[1][BUY2] = A[1][BUY2] + tmp;
        dp[1][BUY3] = A[1][BUY3] + tmp;
        minimum = std::min(dp[1][BUY1], dp[0][BUY2]);
        if (N > 2) {
            tmp = std::min(dp[1][BUY1], dp[0][BUY2]);
            dp[2][BUY1] = A[2][BUY1] + tmp;
            dp[2][BUY2] = A[2][BUY2] + tmp;
            dp[2][BUY3] = A[2][BUY3] + tmp;
            minimum = std::min(dp[0][BUY3], std::min(dp[1][BUY2], dp[2][BUY1]));
            if (N > 3) {
                for (auto iter = std::next(A.begin(), 3); iter != A.end(); ++iter) {
                    const auto &times = *iter;
                    tmp = std::min(dp[2][BUY1], std::min(dp[1][BUY2], dp[0][BUY3]));
                    dp[3][BUY1] = times[BUY1] + tmp;
                    dp[3][BUY2] = times[BUY2] + tmp;
                    dp[3][BUY3] = times[BUY3] + tmp;
                    std::copy(dp[1].cbegin(), dp[1].cend(), dp[0].begin());
                    std::copy(dp[2].cbegin(), dp[2].cend(), dp[1].begin());
                    std::copy(dp[3].cbegin(), dp[3].cend(), dp[2].begin());
                }
                minimum = std::min(dp[0][BUY3], std::min(dp[1][BUY2], dp[2][BUY1]));
            }
        }
    }
    return minimum;
}

//Задача C
//SUCCESS
enum {
    NAIL_DISCONNECTED = 0,
    NAIL_CONNECTED = 1
};

unsigned int find_shortest_sum_of_ropes(std::vector<unsigned int> &coords) {
    /*
    логично предположить, что ниточкой надо соединять соседние гвоздики
    поэтому сортируем
    */
    const unsigned int &N = coords.size();
    if (N > 1) {
        std::sort(coords.begin(), coords.end());
        std::array<std::array<unsigned int, 2>, 2> dp;
        dp[0][NAIL_CONNECTED] = coords[1] - coords[0];
        if (N > 2) {
            /*
                Я просто использую немного памяти, поэтому написал проще
                dp[2][NAIL_DISCONNECTED] = dp[1][NAIL_CONNECTED]
                dp[2][NAIL_CONNECTED] = dp[1][NAIL_CONNECTED] + coords[2] - coords[1];
            */
            dp[0][NAIL_DISCONNECTED] = dp[0][NAIL_CONNECTED];
            dp[0][NAIL_CONNECTED] = dp[0][NAIL_CONNECTED] + coords[2] - coords[1];
            for (unsigned int i = 3; i < N; ++i) {
                dp[1][NAIL_DISCONNECTED] = dp[0][NAIL_CONNECTED];
                dp[1][NAIL_CONNECTED] = std::min(dp[0][NAIL_DISCONNECTED],dp[0][NAIL_CONNECTED]) + coords[i] - coords[i-1];
                std::copy(dp[1].cbegin(), dp[1].cend(), dp[0].begin());
            }
            return dp[0][NAIL_CONNECTED];
        } else {
            return dp[0][NAIL_CONNECTED];
        }
    }
    return 0;
}

//Задача D
//SUCCESS
enum MOVE_DIRECTION {
    MOVE_RIGHT = 0,
    MOVE_DOWN = 1
};

unsigned int find_longest_path(const std::vector<std::vector<unsigned int>> &matr, std::vector<MOVE_DIRECTION> &path) {
    const auto &N = matr.size(), &M = matr[0].size();
    /*
    Да вашу мать, надо сохранять путь
    Алгоритм требует сохранять путь
    Хорошо, будем использовать 2 матрицы, 
    В первую будем записывать текущую максимальную длину до клетки
    Во вторую будем записывать действия, которое мы сделали относительно предыдущей клетки 
    */
    MOVE_DIRECTION moves[N][M];
    unsigned int prefixes[N][M];
    unsigned int left, up;
    prefixes[0][0] = matr[0][0];
    for (unsigned int j = 1; j < M; ++j) {
        prefixes[0][j] = prefixes[0][j-1] + matr[0][j];
        moves[0][j] = MOVE_RIGHT;
    }
    for (unsigned int i = 1; i < N; ++i) {
        prefixes[i][0] = prefixes[i-1][0] + matr[i][0];
        moves[i][0] = MOVE_DOWN;
        for (unsigned int j = 1; j < M; ++j) {
            left = prefixes[i][j-1];
            up = prefixes[i-1][j];
            if (left > up) {
                moves[i][j] = MOVE_RIGHT;
                prefixes[i][j] = left + matr[i][j];
            } else {
                moves[i][j] = MOVE_DOWN;
                prefixes[i][j] = up + matr[i][j];
            }
        }
    }
    path.resize(N + M - 2);
    for (unsigned int i = N-1, j = M-1, k = path.size() - 1; i != 0 || j != 0; --k) {
        if (moves[i][j] == MOVE_DOWN) {
            path[k] = MOVE_DOWN;
            --i;
        } else {
            path[k] = MOVE_RIGHT;
            --j;
        }
    }
    return prefixes[N-1][M-1];
}

//Задача E
//Где-то ошибся
unsigned int find_min_sum(const std::vector<unsigned int> &prices, unsigned int &K1, unsigned int &K2, std::vector<unsigned int> &coupon_days) {
    const unsigned int &N = prices.size();
    /*
    Итак, нужно определить минимальную сумму
    Итак, Петя всегда покупает ровно 1 обед, поэтому он платит только ту сумму, которая ему предоставлена на сегодняшний день
    Допустим, он получил купон на i-м, тогда логично было бы его потратить на самый дорогой обед из N - i оставшихся обедов, тогда сумма оставшихся
    обедов будет меньше наименьшая
    Если так, то помечаем тот обед как день на который потратим купон
    Далее проходимся дальше и ищем очередной день > 100 рублей ценой, который не отмечен
    Получаем купон - опять расстрачиваем его на максимальный день среди следующих не отмеченных

    Итак, алгоритм следующий:
    f(a, marks, n, i_begin, K1, K2, coupons_indexes) {
        Ищем первый индекс i >= i_begin, для которого a_i > 100 и marks[i] != 1:
        Далее ищем индекс j_max > i
        coupon_indexes.append(j_max)
        marks[j_max] = 1;
    }
    Как ускорить поиск следующих максимумов после удаленного
    Ладно, обойдёмся без этого, там максимум всего 100 элементов, задача для маленьких
    */
    bool marks[N] = {false};
    unsigned int maximum = 0;
    unsigned int sum = std::accumulate(prices.cbegin(), prices.cend(), 0);
    K1 = K2 = 0;
    coupon_days.clear();
    for (unsigned int i_begin = 0, i, j, j_max; i_begin < N; ) {
        for (i = i_begin; i < N && (prices[i] <= 100 || marks[i]); ++i);
        if (i != N) {
            K1++;
        } else {
            break;
        }
        for (j_max = i+1; j_max < N && marks[i]; ++j_max);
        if (j_max != N) {
            maximum = prices[j_max];
            for (j = j_max + 1; j < N; ++j) {
                if (!marks[j] && maximum < prices[j]) {
                    j_max = j;
                    maximum = prices[j];
                }
            }
            K1--;
            K2++;
            sum -= maximum;
            marks[j_max] = true;
            coupon_days.push_back(j_max + 1);
        } else {
            break;
        }
        i_begin = i + 1;
    }
    return sum;
}

//Задача F
enum HEAP_OPERATION {
    HEAP_INSERT,
    HEAP_EXTRACT
};

struct Heap {
public:
    Heap(size_t reserve_size) {
        reserve_table = new HeapNode[reserve_size];
        root.parent = nullptr;
        root.previos_max = &root;
        root.next_max = &root;
        root.left = nullptr;
        root.right = nullptr;
        root.color = NODE_BLACK;
        root.value = 0;
        current_free_node_index = 0;
    }
    void insert(unsigned int num) {
        auto &node = _allocateNode(num);
        if (_IS_TREE_EMPTY()) {
            _insertRoot(node);
        } else {
            _insertNode(node);
            _fixInsertNode(node);
        }
    }
    unsigned int extract() {
        if (_IS_TREE_EMPTY()) {
            return 0;
        } else {
            auto &node = _getMaximumNode();
            _deleteNode(node);
            return node.value;
            //
        }
        return 0;
        //TODO: TreeDelete, TreeDeleteFixup
    }
private:
    enum HeapNodeColor {
        NODE_BLACK,
        NODE_RED
    };
    struct HeapNode {
        HeapNode *previos_max;
        HeapNode *next_max;
        HeapNode *parent;
        HeapNode *left;
        HeapNode *right;
        HeapNodeColor color;
        unsigned int value;
    };
    HeapNode *reserve_table;
    HeapNode root;
    unsigned int current_free_node_index;

    bool _IS_TREE_EMPTY() {
        return root.left == nullptr;
    }
    bool _IS_NODE_LIST(const HeapNode &node) {
        return node.left == nullptr && node.right == nullptr;
    }
    HeapNode &_allocateNode(unsigned int num) {
        HeapNode &node = reserve_table[current_free_node_index];
        node.value = num;
        node.color = NODE_RED;
        node.left = nullptr;
        node.right = nullptr;
        node.next_max = nullptr;
        node.previos_max = nullptr;
        node.parent = nullptr;
        ++current_free_node_index;
    }
    HeapNode &_getMaximumNode() {
        return *root.previos_max;
    };
    HeapNode *__findMinimum(HeapNode *node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }
    HeapNode *__treeSuccessor(HeapNode &node) {
        if (node.right) {
            return __findMinimum(node.right);
        }
        HeapNode *parent = node.parent, *current = &node;
        while (parent && current == parent->right) {
            current = parent;
            parent = parent->parent;
        }
        return parent;
    }
    void _deleteNode(HeapNode &node) {
        //TODO: Удаляем 
        /*
        Нужно добавить TreeSuccessor

        */
    }
    void _leftRotate(HeapNode *node) {
        HeapNode *right = node->right;
        node->right = right->left;
        if (right->left) {
            right->left->parent = node;
        }
        if (node->parent) {
            if (node->parent->left == node) {
                node->parent->left = right;
            } else {
                node->parent->right = right;
            }
            right->parent = node->parent;
        }
        right->left = node;
        node->parent = right;
    }
    void _rightRotate(HeapNode *node) {
        HeapNode *left = node->left;
        node->right = left->right;
        if (left->right) {
            left->right->parent = node;
        }
        if (node->parent) {
            if (node->parent->left == node) {
                node->parent->left = left;
            } else {
                node->parent->right = left;
            }
            left->parent = node->parent;
        }
        left->right = node;
        node->parent = left;
    }
    void _insertRoot(HeapNode &node) {
        root.left = root.previos_max = root.next_max = &node;
        node.parent = &root;
        node.color = NODE_BLACK;
    }
    void _insertNode(HeapNode &node) {
        HeapNode *previous = nullptr;
        int direction = 0;
        for (HeapNode *current = root.left; current != nullptr; ) {
            previous = current;
            if (node.value < current->value) {
                direction = 0;
                current = current->left;
            } else {
                direction = 1;
                current = current->right;
            }
        }
        if (direction) {
            previous->right = &node;
            node.next_max = previous->next_max;
            node.previos_max = previous;
            previous->next_max->previos_max = &node;
            previous->next_max = &node;
        } else {
            previous->left = &node;
            node.previos_max = previous->previos_max;
            node.next_max = previous;
            previous->previos_max->next_max = &node;
            previous->previos_max = &node;
        }
    }
    void _fixInsertNode(HeapNode &node) {
        HeapNode *current = &node, *tmp = nullptr, *parent = current->parent, *grand_parent = parent->parent;
        while (parent != &root && parent->color == NODE_RED) {
            if (parent == grand_parent->left) {
                tmp = grand_parent->right;
                //Так как в оригинальном алгоритме nil - это пустой чёрный list
                if (tmp && tmp->color == NODE_RED) {
                    parent->color = NODE_BLACK;
                    tmp->color = NODE_BLACK;
                    grand_parent->color = NODE_RED;
                    current = grand_parent;
                    parent = current->parent;
                    grand_parent = parent->parent;
                } else {
                    if (current == parent->right) {
                        current = parent;
                        _leftRotate(current);
                    }
                    parent->color = NODE_BLACK;
                    grand_parent->color = NODE_RED;
                    _rightRotate(grand_parent);
                }
            } else {
                tmp = grand_parent->left;
                //Так как в оригинальном алгоритме nil - это пустой чёрный list
                if (tmp && tmp->color == NODE_RED) {
                    parent->color = NODE_BLACK;
                    tmp->color = NODE_BLACK;
                    grand_parent->color = NODE_RED;
                    current = grand_parent;
                    parent = current->parent;
                    grand_parent = parent->parent;
                } else {
                    if (current == parent->left) {
                        current = parent;
                        _rightRotate(current);
                    }
                    parent->color = NODE_BLACK;
                    grand_parent->color = NODE_RED;
                    _leftRotate(grand_parent);
                }
            }
        }
        root.left->color = NODE_BLACK;
    }
    
    //TODO: Какую структуру будем использовать для решения задачи?
    /*
    Итак, у нас всего 2 операции, в которых мы будем использовать только 
    1)insert - вставка элемента
    2)extract - вернуть и удалить из кучи наибольшее значение
    И вставка и удаление должны быть как можно быстрее
    Что можно использовать:
    Сбалансированное дерево
    Возможно хэш-таблицу с сохранением обратного чередования по максимуму
    Тогда Heap хранит в себе массив Node, который осуществляет поис
    Но есть проблемы с быстрым добавлением по максимальному элементу
    */
};

int main(void) {
    unsigned int N = 0;
    unsigned int K1 = 0, K2 = 0;
    std::cin >> N;
    std::vector<unsigned int> prices(N), coupon_days;
    coupon_days.reserve(N);
    for (auto &price : prices) {
        std::cin >> price;
    }
    std::cout << find_min_sum(prices, K1, K2, coupon_days) << std::endl << K1 << ' ' << K2 << std::endl;
    std::sort(coupon_days.begin(), coupon_days.end());
    for (const auto &day : coupon_days) {
        std::cout << day << std::endl;
    }
    return 0;
}