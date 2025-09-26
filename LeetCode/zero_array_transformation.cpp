#include <iostream>
#include <vector>
#include <cmath>
/*
Вот самое быстрое решение, взятое с LeetCode, мое решение с деревом отрезков = 84 ms, это 1 ms, чувак нашел какую-то хитрую жадную закономерность
class Solution {
public:
    bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> storage(n, 0);
        for(int i=0; i<queries.size(); i++){
            int l = queries[i][0], r = queries[i][1] + 1;
            if(l>=0) storage[l] += -1;
            if(r<n) storage[r] += 1;
        }     

        for(int i=1; i<n; i++){
            storage[i] += storage[i-1];
        }

        for(int i=0; i<n; i++){
           if(nums[i]==0) storage[i] = 0;
           else storage[i] += nums[i]; 
        }

        for(auto i: storage){
            if(i>0) return 0;
        }

        return 1;
    }
*/
class Solution {
private:
    using arithmetic_t = int;
    //Дерево отрезков, где обход идет по вертикали
    class SegmentTree {
        private:
            std::vector<arithmetic_t> maxs;
            std::vector<arithmetic_t> cache;
            size_t a_end;
            void _build(int v, int L, int R, std::vector<arithmetic_t> &a) {
                if (L == R) {
                    maxs[v-1] = a[L];
                } else {
                    int C = (L + R) / 2;
                    const auto left_child = 2 * v, right_child = left_child + 1;
                    _build(left_child, L, C, a);
                    _build(right_child, C+1, R, a);
                    maxs[v-1] = std::max(maxs[left_child-1], maxs[right_child-1]);
                }
            }
            void _update(int v, int L, int R, const int q_left, const int q_right) {
                if (R < q_left || q_right < L) {
                    return;
                }
                if (q_left <= L && R <= q_right) {
                    ++cache[v-1];
                } else {
                    int C = (L + R) / 2;
                    const auto left_child = 2 * v, right_child = left_child + 1;
                    _update(left_child, L, C, q_left, q_right);
                    _update(right_child, C+1, R, q_left, q_right);
                }
            }
            bool _check(int v, int L, int R, int accum) {
                if (L == R) {
                    return accum + cache[v-1] >= maxs[v-1];
                } else {
                    int C = (L + R) / 2;
                    return _check(2 * v, L, C, accum+cache[v-1]) && _check(2*v+1, C+1, R, accum + cache[v-1]);
                }
            }
        public:
            SegmentTree(std::vector<arithmetic_t> &a) {
                /*
                [1 2 3 4 5 6] 1
                [1 2 3][4 5 6] 2
                [1 2][3][4 5][6] 4
                [1][2][][3][4][5][][6] 8
                1 + 2 + 4 + 8 = 15 , количество = 2^(up(log2(6))+1) - 1 = 2^4-1
                */
                size_t size = 0, current = a.size();
                a_end = a.size() - 1;
                while (current) {
                    size = (size << 1) | 1;
                    current >>= 1;
                }
                size = (size << 1) | 1;
                maxs.resize(size, 0);
                cache.resize(size, 0);
                _build(1, 0, a_end, a);
            }
            void update(const int q_left, const int q_right) {
                _update(1, 0, a_end, q_left, q_right);
            }
            bool check() {
                return _check(1, 0, a_end, 0);
            }
    };
    public:
        bool isZeroArray(std::vector<int>& nums, std::vector<std::vector<int>>& queries) {
            SegmentTree tree(nums);
            for (const auto &query : queries) {
                tree.update(query[0], query[1]);
            }
            return tree.check();
        }
    };

int main(void) {
    std::vector<int> nums1{1, 0, 1}, nums2 {4, 3, 2, 1};
    std::vector<std::vector<int>> queries1 {{0, 2}}, queries2{{1, 3}, {0, 2}};
    Solution sol;
    std::cout << sol.isZeroArray(nums1, queries1) << std::endl;
    std::cout << sol.isZeroArray(nums2, queries2) << std::endl;
    return 0;
}