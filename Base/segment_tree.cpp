#include <vector>
/*
Дерево отрезков представляется как пирамида, здесь по аналогии можно построить
такую структуру, основанную на векторе
*/

using arithmetic_t = int;

class SegmentTree {
    private:
        std::vector<arithmetic_t> maxs;
        std::vector<arithmetic_t> cache;
        size_t a_size;
        void _build(int v, int L, int R, std::vector<arithmetic_t>& a) {
            if (L == R) {
                maxs[v] = a[L];
            } else {
                int C = (L + R) / 2;
                const auto left_child = 2 * v + 1, right_child = left_child + 1;
                _build(left_child, L, C, a);
                _build(right_child, C + 1, R, a);
                maxs[v] = std::max(maxs[left_child], maxs[right_child]);
            }
        }
        void _update(int v, int L, int R, const int q_left, const int q_right) {
            if (R < q_left || q_right < L) {
                return;
            }
            if (q_left <= L && R <= q_right) {
                ++cache[v];
            } else {
                int C = (L + R) / 2;
                const auto left_child = 2 * v + 1, right_child = left_child + 1;
                _update(left_child, L, C, q_left, q_right);
                _update(right_child, C + 1, R, q_left, q_right);
            }
        }
        bool _check(int v, int L, int R, int accum) {
            if (L == R) {
                return accum + cache[v] >= maxs[v];
            } else {
                int C = (L + R) / 2;
                return _check(2 * v + 1, L, C, accum + cache[v]) &&
                       _check(2 * v + 2, C + 1, R, accum + cache[v]);
            }
        }

    public:
        SegmentTree(std::vector<arithmetic_t>& a) {
            /*
            [1 2 3 4 5 6] 1
            [1 2 3][4 5 6] 2
            [1 2][3][4 5][6] 4
            [1][2][][3][4][5][][6] 8
            1 + 2 + 4 + 8 = 15 , количество = 2^(up(log2(6))+1) - 1 = 2^4-1
            */
            size_t size = 0, current = a.size();
            a_size = a.size();
            while (current) {
                size = (size << 1) | 1;
                current >>= 1;
            }
            size = (size << 1) | 1;
            maxs.resize(size, 0);
            cache.resize(size, 0);
            _build(0, 0, a.size() - 1, a);
        }
        void update(const int q_left, const int q_right) {
            _update(0, 0, a_size - 1, q_left, q_right);
        }
        bool check() { return _check(0, 0, a_size - 1, 0); }
    };