#include <iostream>
#include <vector>

class Solution {
    public:
        int search(std::vector<int>& nums, int target) {
            /*
                Берём первый элемент и конечный
                Берём индекс i = середина массива
                Пусть есть массив (a1, ..., an)
                Выбираем середину ai
                Итак Если ai == target, значит возвращаем i
                Если ai > target:
                    если правая граница < ai:
                        если правая граница < target:
                            Ищем в левом диапазоне
                        иначе:
                            Ищем в правом диапазоне
                    иначе:
                        Ищем в левом диапазоне
                Иначе (ai < target):
                    если левая граница > ai:
                        если левая граница > target:
                            Ищем в правом диапазоне
                        иначе:
                            Ищем в левом диапазоне
                    иначе:
                        Ищем в правом диапазоне
            */
            int left_index = 0, right_index = nums.size() - 1, center_index;
            do {
                if (nums[left_index] == target)
                    return left_index;
                if (nums[right_index] == target)
                    return right_index;
                center_index = (right_index + left_index) / 2;
                if (nums[center_index] > target) {
                    if (nums[right_index] < nums[center_index] &&
                        nums[right_index] > target) {
                        left_index = center_index;
                    } else {
                        right_index = center_index;
                    }
                } else {
                    if (nums[left_index] > nums[center_index] &&
                        nums[left_index] < target) {
                        right_index = center_index;
                    } else {
                        left_index = center_index;
                    }
                }
            } while (right_index - left_index > 1);
            return -1;
        }
    };

int main(void) {
    std::vector<int> nums = {1, 3};
    std::cout << Solution().search(nums, 2) << std::endl;
    return 0;
}