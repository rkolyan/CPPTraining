#include <iostream>
#include <vector>

#define NUMS_SIZE 1000000

enum ANSWER {
    NO,
    YES
};

enum PLAY_STATE {
    LEFT_LOSE_RIGHT_WON,
    LEFT_WON_RIGHT_LOSE,
    LEFT_WON_RIGHT_WON,
    LEFT_LOSE_RIGHT_LOSE
};

ANSWER can_find_lier(const std::vector<unsigned int> &nums) {
    /*
    Итак, игроки играли с соседями, если левый проиграл - правый выиграл,
    короче, смотрим на края
    3 состояния - 
    левый игрок по любому проиграл либо выиграл
    если проиграл, значит правый точно выиграл
    LEFT_WON_RIGHT_LOSE
    Далее, если правый LEFT_WON_RIGHT_LOSE, и справа 0, то LEFT_LOSE_RIGHT_LOSE
    */
    
    if (nums.size() == 1) {
        if (nums[0]) {
            return YES;
        } else {
            return NO;
        }
    }
    PLAY_STATE state;
    bool only_won = false;
    if (nums.size() > 1) {
        if (!nums[0] && !nums[1]) {
            return YES;
        } else if (!nums[0] && nums[1]) {
            state = LEFT_LOSE_RIGHT_WON;
        } else if (nums[0] && !nums[1]) {
            state = LEFT_WON_RIGHT_LOSE;
        } else {
            state = LEFT_WON_RIGHT_WON;
            only_won = true;
        }
    }
    for (unsigned int i = 2; i < nums.size(); ++i) {
        if (nums[i]) {
            switch (state){
            case LEFT_LOSE_RIGHT_WON:
                state = LEFT_WON_RIGHT_WON;
                break;
            case LEFT_LOSE_RIGHT_LOSE:
            case LEFT_WON_RIGHT_LOSE:
                state = LEFT_LOSE_RIGHT_WON;
            }
        } else {
            switch (state){
            case LEFT_WON_RIGHT_WON:
                only_won = false;
            case LEFT_LOSE_RIGHT_WON:
                state = LEFT_WON_RIGHT_LOSE;
                break;
            case LEFT_WON_RIGHT_LOSE:
                return YES;
            }
        }
    }
    if (only_won) {
        return YES;
    }
    return NO;
}

enum STEP_STATE {
    FUAD_STEP,
    MUAF_STEP
};
unsigned int find_max_count(unsigned int n, unsigned int m, unsigned int a, unsigned int b) {
    /*
    Как определить оптимальность?
    Итак, Фуаду надо ставить монстра посередине, в ином случае, он потеряет большую часть клеток
    В то же время Муаф должен отрезать большую часть клеток, которая осталась
    Итак Фуаф должен ставить монстра в n/2 + n % 2,  m/2 + n% 2 позиции
    Далее, Муаф должен посчитать клетки слева ((fn - 0) * m), справа
    */
    unsigned f_i = a;
    unsigned f_j = b;
    unsigned int count = 1;
    unsigned int left_square = 0, up_square = 0;
    if (f_i > n / 2 + n % 2) {
        f_i = n - f_i + 1;
    }
    if (f_j > m / 2 + m % 2) {
        f_j = m - f_j + 1;
    }
    STEP_STATE state = MUAF_STEP;
    while (n != 1 || m != 1) {
        switch (state) {
        case FUAD_STEP:
            f_i = n / 2 + n % 2;
            f_j = m / 2 + m % 2;
            state = MUAF_STEP;
            ++count;
            break;
        default:
            left_square = (n - f_i) * m;
            up_square = (m - f_j) * n;
            if (left_square > up_square) {
                n = f_i;
            } else {
                m = f_j;
            }
            state = FUAD_STEP;
        }
    }
    return count;
}

std::vector<unsigned int> find_attainment(unsigned int n, const std::vector<unsigned int> &A, const std::vector<std::pair<unsigned int, unsigned int>> &edges) {
    std::vector<unsigned int> result(n, 0);
    for (unsigned int i = 1; i <= n; ++i) {
        /*
        Итак, мы можем взять значение из мультимножества, 
        Это что получается, мы должны иметь матрицу, которая сохраняет все вохможные расстояния, dp[n][g] - пути для вершины, сохраняем расстояния, 
        Получается модифицированный алгоритм Дейкстры, сохраняем все возможные расстояния
        */
    }
}

std::vector<unsigned int> find_operation_count(std::vector<unsigned int> bit_str, unsigned int k) {
    /*
    1)Нужно найти количество
    Итак, мы берём a1 a2 a3... ai-1 ai ai+1
    инвертируем
    b1 ... bi ai+1
    Далее, если мы ивертируем слева, то ничего не изменим
    только справа
    Мы можем выбирать только нули
    Итак, выбираем первый 0
    считаем количество 1-ц 
    */
} 

int main(void) {
    unsigned int t = 0, n = 0, m = 0, l = 0;
    std::vector<unsigned int> A;
    std::vector<std::pair<unsigned int, unsigned int>> edges;
    std::cin >> t;
    for (unsigned int ti = 0; ti < t; ++ti) {
        std::cin >> n >> m >> l;
        A.resize(l);
        for (auto &element : A) {
            std::cin >> element;
        }
        edges.resize(m);
        for (auto &element : edges) {
            std::cin >> element.first >> element.second;
        }
        
    }
    return 0;
}