#include <vector>
#include <string>
#include <queue>

typedef int len_t;
typedef int row_t;
typedef int column_t;
using coords_t = std::pair<row_t, column_t>;
using path_coords_t = std::pair<len_t, coords_t>;

inline column_t get_length(const path_coords_t &path_coords) {
    return path_coords.first;
}
inline column_t get_column(const path_coords_t &path_coords) {
    return path_coords.second.second;
}
inline row_t get_row(const path_coords_t &path_coords) {
    return path_coords.second.first;
}

class Solution {
    public:
        int minMoves(std::vector<std::string>& matrix) {
            /*
            Задача, нужно узнать короткий путь
            Очередной вариант алгоритма Дейкстры?
            Итак, есть очередь приоритетов
            Итак, как там было в ории
            */
            //1)Создать массив размером 'A'-'Z' + 1 и в нём хранить координаты
            constexpr unsigned int ALPHABET_SIZE = 'Z' - 'A' + 1;
            const auto &N = matrix.size(), &M = matrix.front().size();
            path_coords_t current;
            std::vector<std::vector<coords_t>> portals(ALPHABET_SIZE);
            std::vector<std::vector<len_t>> d(N, std::vector<len_t>(M, -1));
            for (row_t i = 0; i < N; ++i) {
                for (column_t j = 0; j < M; ++j) {
                    const auto &sym = matrix[i][j];
                    if (sym >= 'A' && sym <= 'Z') {
                        portals[sym - 'A'].emplace_back(i, j);
                    }
                }
            }
            std::priority_queue<path_coords_t, std::vector<path_coords_t>, std::greater<path_coords_t>> Q(std::greater<path_coords_t>{});
            Q.emplace(len_t{0}, coords_t{0, 0});
            while (!Q.empty()) {
                current = Q.top();
                const auto len = get_length(current);
                const auto row = get_row(current);
                const auto column = get_column(current);
                //TODO: Проблема, как блокировать проход для телепорта, неужели придется ещё и маску с буквами сохранять в каждое состояние?

                if (len >= d[row][column]) {
                    continue;
                }
                if (row > 0 && )
                /*
                Итак, 
                */
            }
        }
    };