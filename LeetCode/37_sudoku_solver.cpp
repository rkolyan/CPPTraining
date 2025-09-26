#include <iostream>
#include <vector>
#include <tuple>
#include <stack>

//SUCCESS, ЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕ БЕЙБА, 6 ms, побеждает 98.33%, часть c бектрекингом была очень тяжелая, осилил без тестов, только отладкой, но потратил много времени
//ААААААААААААААААААААААААААА, Надо лучше структурировать, а то я в угоду производительности написал кошмар

/*
Вот самое быстрое решение (3ms) на сайте (Здесь чистый бектрекинг какой-то довольно быстрый):
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        // Masks for rows, cols, boxes: bit i means digit (i+1) is already used.
        array<int, 9> rows = {0}, cols = {0}, boxes = {0};
        vector<pair<int,int>> empties;

        // Initialize masks and list of empty cells.
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                if (board[r][c] == '.') {
                    empties.emplace_back(r, c);
                } else {
                    int d = board[r][c] - '1'; // 0..8
                    int mask = 1 << d;
                    rows[r] |= mask;
                    cols[c] |= mask;
                    boxes[boxIndex(r, c)] |= mask;
                }
            }
        }

        dfs(board, 0, empties, rows, cols, boxes);
    }

private:
    static int boxIndex(int r, int c) {
        return (r / 3) * 3 + (c / 3);
    }

    bool dfs(vector<vector<char>>& board, int filled, vector<pair<int,int>>& empties,
             array<int,9>& rows, array<int,9>& cols, array<int,9>& boxes) {
        if (filled == empties.size()) return true;

        // Choose the empty cell with the fewest possibilities (MRV heuristic)
        int bestIdx = -1;
        int minOptions = 10;
        for (int i = filled; i < empties.size(); ++i) {
            int r = empties[i].first;
            int c = empties[i].second;
            int used = rows[r] | cols[c] | boxes[boxIndex(r,c)];
            int options = 9 - __builtin_popcount(used);
            if (options < minOptions) {
                minOptions = options;
                bestIdx = i;
                if (options == 1) break;
            }
        }

        // Swap chosen into current position
        swap(empties[filled], empties[bestIdx]);
        int r = empties[filled].first;
        int c = empties[filled].second;
        int b = boxIndex(r,c);
        int used = rows[r] | cols[c] | boxes[b];
        int avail = (~used) & 0x1FF; // lower 9 bits

        // Try each candidate digit
        while (avail) {
            int pick = avail & -avail; // lowest set bit
            avail -= pick;
            int d = __builtin_ctz(pick); // digit index 0..8

            // Place digit
            board[r][c] = '1' + d;
            rows[r] |= pick;
            cols[c] |= pick;
            boxes[b] |= pick;

            if (dfs(board, filled + 1, empties, rows, cols, boxes)) return true;

            // Undo
            board[r][c] = '.';
            rows[r] &= ~pick;
            cols[c] &= ~pick;
            boxes[b] &= ~pick;
        }

        // backtrack: restore empties order
        swap(empties[filled], empties[bestIdx]);
        return false;
    }
};
*/


//Далее представлены мои черновичные выкладки и рассуждения

/*
Задача явно на CSP
1)Переменные:
X = {x_00, x_01, ..., x_ij, ..., x_88}, где x_ij - значение в клетке на i-й строке и j-м столбце, i,j in A = {0, 1, 2, 3, 4, 5, 6, 7, 8}
2)Домены:
D_ij = D = {1, 2, 3, 4, 5, 6, 7, 8, 9}
3)Ограничения
Ограничения типа C1: для некоторых упорядоченных пар (i,j) известно, что x_ij = value.(По сути присвоение домена D_ij = {value}), также необходимо ставит
C2(alldifferent по строке): для любых j1,j2 in A, j1 != j2: x_i{j1} != x_i{j2}.
C3(alldifferent по столбцу): для любых i1,i2 in A, i1 != i2: x_{i1}j  != x_{i2}j.
C4(alldiffenent по квадрату): для любых i, j in A,для любого di_1,dj_1,di_2,d_j2 in {0, 1, 2}, (di_1, dj_1) != (di_2, dj_2) должно выполняться следующее:
x_{r+di_1}{c+dj_1} != x_{r+di_2}{c+dj_2}, где r = i - i % 3, c = j - j % 3
Дополнительные ограничения:
C5(горизонталь в квадранте)): Если какие-то значения есть в доменах только для фиксированного i, (в каком-то квадранте), то удаляем эти значения из доменов D_ik в других квадрантах
С6(вертикаль в квадранет):Тоже самое, только для столбца.
//TODO: Необходимо описать более формально С5 и C6

Обозначим наличие значений в домене x_ij битовой последовательностью b_{ij} = (a_0,a_1,a_2,a_3,a_4,a_5,a_6,a_7,a_8), где a_r in {0, 1}, 
0 - значение r+1 присутствует в домене D_ij, 
1 - r+1 отсутствует в D_ij.
b{ij} == 0, если все биты принимают значение 0.
Тогда ограничения имеют следующий вид:
C1)x_ij = value => b_{ij} = 1 << (value-1)
C2(ослабленное))AND(b_i0, b_i1, ... b_i8) == 0
//TODO: C2(усиленное)
C3(ослабленное))AND(b_1j, b_2j, ... b_8j) == 0
//TODO: С3(усиленное)
C4(ослабленное))r = i - i % 3, c = j - j % 3 : AND(b_rc, b_r{c+1}, b_r{c+2}, b_{r+1}c, b_{r+1}{c+1}, b_{r+1}{c+2}, b_{r+2}c, b_{r+2}{c+1}, b_{r+2}{c+2}) == 0
//TODO: C4(усиленное)
Я хз зачем я ослабил эти ограничения, но да ладно, идентичные ограничения подразумевает попарный AND между каждым элементом множества

Методы сужения доменов
1)если в x_ij всего 1 бит, то для каждого элемента квадрата, строки и столбца делаем b_{i1}{j1} &= ~b_ij, если b_{i1}{j1} изменилось, значит бит сбросился, ячейка изменилась
2)для каждой строки в квадранте делаем OR(b_ic, b_i{c+1}, b_i{c+2}), чтобы определить какие значения в доменах точно есть в этой строке
Как при помощи битовых операций определить что только в этой строке в доменах есть это значение?
Таблица:
i1  i2  result
0   0   0
1   0   1
0   1   0
1   1   0
Это вроде как НЕ импликация A->B = ~A|B
~(A->B) = ~(~A|B) = A&(~B)
A   B   A&(~B)
0   0   0
0   1   0
1   0   1
1   1   0
Тогда для каждой строки в квадранте сначала вычисляем b_is = OR(b_ic, b_i{c+1}, b_i{c+2}), затем делаем относительно делаем b_is = AND(b_is, NOT(b_io))
Аналогично для каждого столбца в квадранте.
3)Я думаю проверять количество значений в доменах уже после того, когда алгоритм сужения перестанет работать.

Итак, тут явно в начале нужно сузить домены, 
Алгоритм следующий:
1)Сужение доменов, используя какой-нибудь AC-3 (AC-3 выполняем до тех пор, пока после i-й итерации домены не перестанут сужаться)
2)Перебор значений (предварительно отмечаем карту неизменяемых значений (тех, в которых клетки изменять нельзя))

///////////////////////////////////////////Сужение доменов/////////////////////////////////////////////////////
Матрица D[3][3][3][3]; - матрица битовых флагов? где первые [3][3] - это координаты квадранта, [3][3] - координаты точки внутри квадранта
rows[3][3][3] - матрица битов строк в каждом квадранте
cols[3][3][3] - матрица битов столбцов в каждом квадранте
changed[3][3][3][3] - матрица измененных значений
Делать обновления по строке или столбцу будем уже после операции над всем квадрантом 

Может вообще обозначать состояния игры какой-нибудь хеш-функцией, как в случае с шахматами, а переходы xor-ами

*/

//Моё решение
class Solution {
    private:
        using domain_t = unsigned int;
        void _initDomains(domain_t D[3][3][3][3], const std::vector<std::vector<char>> &board) {
            for (unsigned int row = 0; row < 3; ++row) {
                for (unsigned int col = 0; col < 3; ++col) {
                    auto &cur_quad = D[row][col];
                    for (unsigned int i = 0; i < 3; ++i) {
                        for (unsigned int j = 0; j < 3; ++j) {
                            if (board[row*3 + i][col*3 + j] != '.') {
                                cur_quad[i][j] = 1 << (board[row*3 + i][col*3 + j] - '1');
                            } else {
                                cur_quad[i][j] = 0x01ff;
                            }
                        }
                    }
                }
            }
        }
        int count(domain_t value) {
            int count = 0;
            for (domain_t i = 1; i < 0x01ff; i <<= 1) {
                if (value & i) {
                    ++count;
                }
            }
            return count;
        }
        void _updateDomain(domain_t &domain, domain_t del_domain, bool &addiction1, bool &addiction2) {
            domain_t old_domain = domain;
            domain &= ~del_domain;
            if (old_domain != domain) {
                addiction1 |= true;
                addiction2 |= true;
            }
        }
        void _fillELine(domain_t l[3], domain_t el[3]) {
            el[0] = l[0] & (~l[1]) & (~l[2]);
            el[1] = l[1] & (~l[0]) & (~l[2]);
            el[2] = l[2] & (~l[0]) & (~l[1]);
        }
        void _doConsistency(domain_t D[3][3][3][3]) {
            bool changed[3][3][3][3];
            bool something_changed = false;
            bool quad_changed = false;
            domain_t l[3], el[3];
            for (unsigned int row = 0; row < 3; ++row) {
                for (unsigned int col = 0; col < 3; ++col) {
                    auto &cur_changed = changed[row][col];
                    for (unsigned int i = 0; i < 3; ++i) {
                        for (unsigned int j = 0; j < 3; ++j) {
                            cur_changed[i][j] = true;
                        }
                    }
                }
            }
            do {
                something_changed = false;
                for (unsigned int row = 0; row < 3; ++row) {
                    for (unsigned int col = 0; col < 3; ++col) {
                        auto &cur_changed = changed[row][col];
                        auto &cur_quad = D[row][col];
                        quad_changed = false;
                        for (unsigned int i = 0; i < 3; ++i) {
                            for (unsigned int j = 0; j < 3; ++j) {
                                if (cur_changed[i][j]) {
                                    if (count(cur_quad[i][j]) == 1) {
                                        for (unsigned int i1 = 0; i1 < i; ++i1) {
                                            for (unsigned int j1 = 0; j1 < 3; ++j1) {
                                                _updateDomain(cur_quad[i1][j1], cur_quad[i][j], cur_changed[i1][j1], something_changed);
                                            }
                                        }
                                        for (unsigned int j1 = 0; j1 < 3; ++j1) {
                                            if (j1 != j) {
                                                _updateDomain(cur_quad[i][j1], cur_quad[i][j],cur_changed[i][j1], something_changed);
                                            }
                                        }
                                        for (unsigned int i1 = i+1; i1 < 3; ++i1) {
                                            for (unsigned int j1 = 0; j1 < 3; ++j1) {
                                                _updateDomain(cur_quad[i1][j1], cur_quad[i][j],cur_changed[i1][j1], something_changed);
                                            }
                                        }
                                    }
                                    cur_changed[i][j] = false;
                                    quad_changed = true;
                                }
                            }
                        }
                        if (quad_changed) {
                            l[0] = cur_quad[0][0] | cur_quad[0][1] | cur_quad[0][2];
                            l[1] = cur_quad[1][0] | cur_quad[1][1] | cur_quad[1][2];
                            l[2] = cur_quad[2][0] | cur_quad[2][1] | cur_quad[2][2];
                            _fillELine(l, el);
                            for (unsigned int c = 0; c < 3; ++c) {
                                if (c != col) {
                                    for (unsigned int i = 0; i < 3; ++i) {
                                        auto &drow = D[row][c][i];
                                        for (unsigned int j = 0; j < 3; ++j) {
                                            _updateDomain(drow[j], el[i],changed[row][c][i][j], something_changed);
                                        }
                                    }
                                }
                            }
                            l[0] = cur_quad[0][0] | cur_quad[1][0] | cur_quad[2][0];
                            l[1] = cur_quad[0][1] | cur_quad[1][1] | cur_quad[2][1];
                            l[2] = cur_quad[0][2] | cur_quad[1][2] | cur_quad[2][2];
                            _fillELine(l, el);
                            for (unsigned int r = 0; r < 3; ++r) {
                                if (r != row) {
                                    auto &tmp_quad = D[r][col];
                                    for (unsigned int j = 0; j < 3; ++j) {
                                        for (unsigned int i = 0; i < 3; ++i) {
                                            _updateDomain(tmp_quad[i][j], el[j],changed[r][col][i][j], something_changed);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } while(something_changed);
        }
        
        typedef union {
            unsigned int _all;
            struct {
                unsigned int row:2;
                unsigned int col:2;
                unsigned int i:2;
                unsigned int j:2;
                unsigned int bitnum:4;//Текущее выбранное значение
                //domain_t cur_value:10;
                domain_t old_value:10;
            };
        } x_t;
        bool _updateDomainAndSave(domain_t &domain, domain_t del_domain,
        std::vector<x_t> &changes, unsigned int row, unsigned int col, unsigned int i, unsigned int j) {
            domain_t old_value = domain;
            domain &= ~del_domain;
            if (old_value != domain) {
                changes.push_back({.row=row,.col=col,.i=i,.j=j,.bitnum=0,.old_value=old_value});
                if (domain == 0) {
                    return false;
                }
            }
            return true;
        }
        void _doBacktracking(domain_t D[3][3][3][3]) {
            /*
            Создаём вектор, в которую записываем текущее значение координат (можно записывать координаты в 2 байта, по 4 бит на строку, номер ), 
            Или может просто вектор координат,
            Проходимся по каждой координате, увеличиваем текущий битнам (он в начале 0) до тех пор, пока (1 << bitnum-1) & domain = 0;
            если bitnum == 9, то решения нет
            */
            std::vector<x_t> xvalues;
            std::vector<std::vector<x_t>> xchanges;
            xvalues.reserve(81);
            for (unsigned int row = 0; row < 3; ++row) {
                for (unsigned int col = 0; col < 3; ++col) {
                    for (unsigned int i = 0; i < 3; ++i) {
                        for (unsigned int j = 0; j < 3; ++j) {
                            if (count(D[row][col][i][j]) != 1) {
                                xvalues.push_back(x_t{.row=row,.col=col,.i=i,.j=j,.bitnum = 0,.old_value=D[row][col][i][j]});
                            }
                        }
                    }
                }
            }
            xchanges.resize(xvalues.size());
            //8 + 6 + 6 = 20
            for (auto &xchanges_sub : xchanges) {
                xchanges_sub.reserve(20);
            }
            domain_t bitnum = 0;
            unsigned int row = 0, col = 0, i = 0, j = 0;
            //ВНИМАНИЕ, ОЧЕНЬ КОСТЫЛЬНЫЙ ЦИКЛ
            for (int k = 0; k < static_cast<int>(xvalues.size());) {
                //1)Мы зачищаем 
                auto &xcurrent = xvalues[k];
                auto &xchange = xchanges[k];
                row = xcurrent.row, col = xcurrent.col, i = xcurrent.i, j = xcurrent.j;
                for (auto &x : xchange) {
                    D[x.row][x.col][x.i][x.j] = x.old_value;
                }
                xchange.clear();

                bitnum = xcurrent.bitnum;
                if (bitnum > 0) {
                    D[row][col][i][j] = xcurrent.old_value;
                } else {
                    xcurrent.old_value = D[row][col][i][j];
                }
                auto &D_current = D[row][col][i][j];

                while (bitnum < 9 && !((1 << bitnum) & D_current)) {
                    ++bitnum;
                }
                if (bitnum == 9) {
                    D_current = xcurrent.old_value;
                    xcurrent.bitnum = 0;
                    --k;
                } else {
                    bool flag = true;
                    domain_t new_value = 0;
                    //Проверяем, подходит ли
                    new_value = 1 << bitnum;
                    for (unsigned int i1 = 0; i1 < i; ++i1) {
                        for (unsigned int j1 = 0; j1 < 3; ++j1) {
                            flag = _updateDomainAndSave(D[row][col][i1][j1], new_value, xchange, row, col, i1, j1);
                            if (!flag) {
                                goto FUNC_END;
                            }
                        }
                    }
                    for (unsigned int j1 = 0; j1 < 3; ++j1) {
                        if (j1 != j) {
                            flag = _updateDomainAndSave(D[row][col][i][j1], new_value, xchange, row, col, i, j1);
                            if (!flag) {
                                goto FUNC_END;
                            }
                        }
                    }
                    for (unsigned int i1 = i+1; i1 < 3; ++i1) {
                        for (unsigned int j1 = 0; j1 < 3; ++j1) {
                            flag = _updateDomainAndSave(D[row][col][i1][j1], new_value, xchange, row, col, i1, j1);
                            if (!flag) {
                                goto FUNC_END;
                            }
                        }
                    }
                    for (unsigned int r = 0; r < 3; ++r) {
                        if (r != row) {
                            for (unsigned int i1 = 0; i1 < 3; ++i1) {
                                flag = _updateDomainAndSave(D[r][col][i1][j], new_value, xchange, r, col, i1, j);
                                if (!flag) {
                                    goto FUNC_END;
                                }
                            }
                        }
                    }
                    for (unsigned int c = 0; c < 3; ++c) {
                        if (c != col) {
                            for (unsigned int j1 = 0; j1 < 3; ++j1) {
                                flag = _updateDomainAndSave(D[row][c][i][j1], new_value, xchange, row, c, i, j1);
                                if (!flag) {
                                    goto FUNC_END;
                                }
                            }
                        }
                    }
                FUNC_END:
                    xcurrent.bitnum = bitnum+1;
                    if (flag) {
                        xcurrent.old_value = D_current;
                        D_current = new_value;
                        ++k;
                    }
                }
            }
            
        }
        char _findValue(domain_t bitValue) {
            char value = 0;
            for (int bit = 1; value < 9 && !(bit & bitValue); ++value, bit <<= 1);
            return value + '1';
        }
        void _fillBoard(domain_t D[3][3][3][3], std::vector<std::vector<char>>& board) {
            for (unsigned int row = 0; row < 3; ++row) {
                for (unsigned int col = 0; col < 3; ++col) {
                    for (unsigned int i = 0; i < 3; ++i) {
                        for (unsigned int j = 0; j < 3; ++j) {
                            board[row * 3 + i][col * 3 + j] = _findValue(D[row][col][i][j]);
                        }
                    }
                }
            }
        }
    public:
        void solveSudoku(std::vector<std::vector<char>>& board) {
            domain_t D[3][3][3][3];
            //int counts[3][3][3][3];
            //1)Инициализация
            _initDomains(D, board);
            //2)Сам алгоритм сужения доменов
            _doConsistency(D);
            //3)Инициализация бектрекинга
            //_initBacktracking(D, counts);
            //TODO:4)Backtracking
            _doBacktracking(D);
            //5)Заполнение значений
            _fillBoard(D, board);
        }
};

#include <iostream>

void printBoard(const std::vector<std::vector<char>> &board) {
    for (unsigned int i = 0; i < 9; ++i) {
        for (unsigned int j = 0; j < 9; ++j) {
            std::cout << board[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

int main(void) {
    std::vector<std::vector<char>> board = {
        {'.','.','9','7','4','8','.','.','.'},
        {'7','.','.','.','.','.','.','.','.'},
        {'.','2','.','1','.','9','.','.','.'},
        {'.','.','7','.','.','.','2','4','.'},
        {'.','6','4','.','1','.','5','9','.'},
        {'.','9','8','.','.','.','3','.','.'},
        {'.','.','.','8','.','3','.','2','.'},
        {'.','.','.','.','.','.','.','.','6'},
        {'.','.','.','2','7','5','9','.','.'}
    };
    /*
    std::vector<std::vector<char>> board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    */
    Solution sol;
    sol.solveSudoku(board);
    printBoard(board);
}