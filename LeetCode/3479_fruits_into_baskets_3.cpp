#include <vector>

//SUCCESS, 55 ms, побеждает 91.85%
/*
Вот решение за 5 ms, тут помимо дерево префиксов автор решения умудрился как-то использовать двоичный поиск...
// O(n*logn*logn)
// max segment tree + binary search
auto init=atexit([](){ofstream("display_runtime.txt")<<"0";});
class Segment_Tree {
    vector<int> seg;
public:
    Segment_Tree(int n){
        seg.resize(4*n+1);
    }

    void build(int idx,int low,int high,vector<int>& v) {
        if(low==high) {
            seg[idx] = v[low];
            return;
        }
        int mid = (low+high)/2;
        build(2*idx+1,low,mid,v);
        build(2*idx+2,mid+1,high,v);
        seg[idx] = max(seg[2*idx+1],seg[2*idx+2]);
    }

    void update(int idx,int low,int high,int i,int val) {
        if(low==high) {
            seg[idx] = val;
            return;
        }
        int mid = (low+high)/2;
        if(i<=mid)
            update(2*idx+1,low,mid,i,val);
        else
            update(2*idx+2,mid+1,high,i,val);
        seg[idx] = max(seg[2*idx+1],seg[2*idx+2]);
    }

    int query(int idx,int low,int high,int l,int r) {
        // complete overlap
        if(low>=l && high<=r)   return seg[idx];
        // no overlap
        if(high<l || low>r)     return INT_MIN;
        // partial overlap
        int mid = (low+high)/2;
        int left = query(2*idx+1,low,mid,l,r);
        int right = query(2*idx+2,mid+1,high,l,r);
        return max(left,right);
    }
};

class Solution {
public:
    int numOfUnplacedFruits(vector<int>& f, vector<int>& b) {
        int n = b.size();
        Segment_Tree st(n);
        st.build(0,0,n-1,b);

        int ans = n;
        for(int a:f) {
            // binary searching on segment tree to find the leftmost available basket
            int sub = -1;
            int l=0,r=n-1;
            while(l<=r) {
                int mid = (l+r)/2;
                int cap = st.query(0,0,n-1,0,mid);
                if(cap >= a) {
                    sub = mid;
                    r = mid-1;
                }
                else {
                    l = mid+1;
                }
            }

            if(sub != -1) {
                --ans;
                st.update(0,0,n-1,sub,0);
            }
        }

        return ans;
    }
};
*/


//Моё решение
class Solution {
private:
    using arithmetic_t = int;
    class SegmentTree {
        private:
            std::vector<arithmetic_t> maxs;
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
            bool _check(int v, int L, int R, int value) {
                if (L == R) {
                    //Этот случай возможен только если размер массива 1
                    if (maxs[v] >= value) {
                        maxs[v] = 0;
                        return true;
                    }
                } else if (maxs[v] >= value) {
                    int C = (L + R) / 2;
                    int new_v = 2*v + 1;
                    if (maxs[new_v] >= value) {
                        if (L == C) {
                            maxs[new_v] = 0;
                        } else {
                            _check(new_v, L, C, value);
                        }
                        maxs[v] = std::max(maxs[new_v], maxs[new_v+1]);
                        return true;
                    }
                    ++new_v;
                    if (maxs[new_v] >= value) {
                        if (C == R) {
                            maxs[new_v] = 0;
                        } else {
                            _check(new_v, C+1, R, value);
                        }
                        maxs[v] = std::max(maxs[new_v-1], maxs[new_v]);
                        return true;
                    }
                }
                return false;
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
                _build(0, 0, a.size() - 1, a);
            }
            bool check(int value) { return _check(0, 0, a_size - 1, value); }
    };
public:
    int numOfUnplacedFruits(std::vector<int>& fruits, std::vector<int>& baskets) {
        /*
        Ну тут явно сложность должна быть <= n*log(n)
        В подсказках указано дерево отрезков
        Можно чуть-чуть модифицировать дерево
        Поиск осуществляем несколько иным способом - находим отрезок с максимальным элементов 
        Смотрим подотрезки слева направо, если элемент на отрезке >= fruit то спускаемся в этот подотрезок
        Когда спустились до листа, сбрасвыаем значение на 0 и возвращаясь вверх обновляем новые значения на 0
        */
        int remained = static_cast<int>(fruits.size());
        SegmentTree st(baskets);
        for (const auto &fruit : fruits) {
            if (st.check(fruit)) {
                --remained;
            }
        }
        return remained;
    }
};

#include <iostream>

int main(void) {
    std::vector<int> fruits = {4, 2, 5}, baskets = {3,5,4};
    Solution sol;
    std::cout << sol.numOfUnplacedFruits(fruits, baskets) << std::endl;
    return 0;
}