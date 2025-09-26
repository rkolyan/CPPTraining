#include <vector>

//SUCCESS, 100 %, вроде O(log2n)

class Solution {
    private:
        int findRightEnd(const std::vector<int>&nums, int left, int right, int target) {
            int mid;
            if (nums[right] == target) {
                return right;
            }
            while (right - left > 1) {
                mid = (left + right) / 2;
                if (nums[mid] > target) {
                    right = mid;
                } else {
                    left = mid;
                }
            }
            return left;
        }
        int findLeftEnd(const std::vector<int>&nums, int left, int right, int target) {
            int mid;
            if (nums[left] == target) {
                return left;
            }
            while (right - left > 1) {
                mid = (left + right) / 2;
                if (nums[mid] < target) {
                    left = mid;
                } else {
                    right = mid;
                }
            }
            return right;
        }
    public:
        std::vector<int> searchRange(std::vector<int>& nums, int target) {
            /*
            Итак, у нас массив в неубывающем порядке, нам необходимо найти первую и конечную позицию подмассива где элементы = target
            1)Мы ищем бинарным поиском до тех пор, пока середина не будет равна target
            2)Если нашли, то при помощи специльной подфункции ищем левую часть, при помощи другой ищем последний правый
            */
           std::vector<int> result {-1,-1};
           if (!nums.size()) {
               return result;
           }
            int left = 0, right = nums.size()-1;
            if (nums[left] == target) {
                result[0] = left;
                result[1] = findRightEnd(nums, left, right, target);
            } else if (nums[right] == target) {
                result[0] = findLeftEnd(nums, left, right, target);
                result[1] = right;
            } else {
                int mid;
                while (right - left > 1) {
                    mid = (right + left) / 2;
                    if (nums[mid] == target) {
                        result[0] = findLeftEnd(nums, left, mid, target);
                        result[1] = findRightEnd(nums, mid, right, target);
                        break;
                    } else if (target > nums[mid]) {
                        left = mid;
                    } else {
                        right = mid;
                    }
                }
            }
            return result;
        }
    };

#include <iostream>

int main(void) {
    std::vector<int> nums1 {5,7,7,8,8,10}, nums2, nums3{1}, nums4{1,1}, nums5{1,2}, nums6{2,1};
    Solution sol;
    auto result = sol.searchRange(nums1, 8);
    std::cout << '[' << result[0] << ',' << result[1] << ']' << std::endl;
    result = sol.searchRange(nums1, 6);
    std::cout << '[' << result[0] << ',' << result[1] << ']' << std::endl;
    result = sol.searchRange(nums2, 0);
    std::cout << '[' << result[0] << ',' << result[1] << ']' << std::endl;
    result = sol.searchRange(nums3, 0);
    std::cout << '[' << result[0] << ',' << result[1] << ']' << std::endl;
    result = sol.searchRange(nums3, 1);
    std::cout << '[' << result[0] << ',' << result[1] << ']' << std::endl;
    result = sol.searchRange(nums4, 1);
    std::cout << '[' << result[0] << ',' << result[1] << ']' << std::endl;
    result = sol.searchRange(nums5, 1);
    std::cout << '[' << result[0] << ',' << result[1] << ']' << std::endl;
    result = sol.searchRange(nums6, 1);
    std::cout << '[' << result[0] << ',' << result[1] << ']' << std::endl;
    return 0;
}