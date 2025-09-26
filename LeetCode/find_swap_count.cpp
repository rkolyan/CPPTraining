#include <vector>
#include <iostream>
class Solution {
    private:
        inline bool less(int left_num, int right_num, int left_dsum, int right_dsum) {
            return left_dsum < right_dsum || left_dsum == right_dsum && left_num < right_num;
        }
        inline int leftChild(int i) {
            // Если индекс начинается с 1, то 2i, а если с 0 то 2 * (i + 1) - 1 = 2i + 1
            return (i << 1) | 1;
        }

        inline int rightChild(int i) {
            return (i << 1) + 2;
        }

        void maxHeapify(std::vector<int> &nums, std::vector<int> &dsums, std::vector<int> &poses, int i, int heapSize) {
            int l = 0, r = 0, prev_largest = i, new_largest = i;
            do {
                std::swap(nums[prev_largest], nums[new_largest]);
                std::swap(dsums[prev_largest], dsums[new_largest]);
                std::swap(poses[prev_largest], poses[new_largest]);
                prev_largest = new_largest;
                l = leftChild(prev_largest);
                r = rightChild(prev_largest);
                if (l < heapSize && less(nums[prev_largest], nums[l], dsums[prev_largest], dsums[l])) {
                    new_largest = l;
                }
                if (r < heapSize && less(nums[new_largest], nums[r], dsums[new_largest], dsums[r])) {
                    new_largest = r;
                }
            } while(new_largest != prev_largest);
        }

        void buildMaxHeap(std::vector<int> &nums, std::vector<int> &dsums, std::vector<int> &poses) {
            for (int i = nums.size()/2; i >= 0; --i) {
                maxHeapify(nums, dsums, poses, i, nums.size());
            }
        }

        void heapSort(std::vector<int> &nums, std::vector<int> &dsums, std::vector<int> &poses) {
            int heapSize = nums.size();
            buildMaxHeap(nums, dsums, poses);
            for (int i = nums.size()-1; i > 0; --i) {
                std::swap(nums[i], nums.front());
                std::swap(dsums[i], dsums.front());
                std::swap(poses[i], poses.front());
                //TODO: Там обновляется размер кучи,
                --heapSize;
                maxHeapify(nums, dsums, poses, 0, heapSize);
            }
        }
    public:

        int minSwaps(std::vector<int>& nums) {
            /*
            Итак, у нас есть вектор чисел с суммами цифр, числами и перестановками (начальными)
            Итак 
            s0 s1 ... sn
            n0 n1 ... nn
            p0 p1 ... pn
            (Начальная перестановка = I = (0 1 2 3 ... n))
            Допустим мы делаем замену элементов pi и pj
            Получаем перестановку (p0 p1 ... pi-1 pj pi+1 ... pj-1 pi pj+1 ... pn)
            Допустим мы в конце концов имеем
            (5 2 3 0 1 4)
            
            Итак, в конце получили эту перестановку (постоянно меняя значения массивов)
            Чтобы получить изначальную позицию, умножаем на саму себя
            (5 2 3 0 1 4)
            (5 2 3 0 1 4)
            0(5)->5 
            1(2)->2
            2(3)->3
            3(0)->0
            4(1)->1
            5(4)->4

            Тут просто сдвиг вправо
            Итак, и того для сдвига достаточно сделать n-1 свопов от перестановки
            (5 2 3 0 1 4)
            (5-4) 0->5
            (4 2 3 0 1 5)
            (4-0) 3->0
            (0 2 3 4 1 5)
            (3-4) 2->3
            (0 2 4 3 1 5)
            (2-4) 1->2
            (0 4 2 3 1 5)
            (4-1) 4->1
            (0 1 2 3 4 5)

            Итак, ищем аналог ((ai1)(ai2 ai3 ai4)
            Таким образом алгоритм следующий
            Пока сортируем, одновременно с этим делаем перестановки
            Далее,
            (0  1  ... n)
            (p0 p1 ... pn) - конечные позиции
            0->p0, p0->pi1..., pit->0
            
            Алгоритм следующий:
            Для каждого j = 0...n:
                Если mark[j] == false:
                    curr = p[j]
                    while (current != j) {
                        current = p[current]
                        ++count;
                    }
            */
            std::vector<int> dsums(nums.size(), 0), poses(nums.size());
            std::vector<bool> marks(nums.size(), false);
            int tmp = 0, result = 0, current = 0, swap_count = 0;
            for (unsigned int i = 0; i < nums.size(); ++i) {
                poses[i] = i;
                tmp = nums[i];
                result = 0;
                while (tmp) {
                    result += tmp % 10;
                    tmp /= 10;
                }
                dsums[i] = result;
            }
            heapSort(nums, dsums, poses);
            for (unsigned int i = 0; i < nums.size(); ++i) {
                if (!marks[i]) {
                    current = poses[i];
                    while (current != i) {
                        marks[current] = true;
                        current = poses[current];
                        ++swap_count;
                    }
                }
            }
            return swap_count;
        }
};

int main(void) {
    std::vector<int> arr1 = {37, 100}, arr2 = {22, 14, 33, 7}, arr3 = {18,43,34,16};
    Solution sol;
    std::cout << sol.minSwaps(arr1) << std::endl;
    std::cout << sol.minSwaps(arr2) << std::endl;
    std::cout << sol.minSwaps(arr3) << std::endl;
    return 0;
}