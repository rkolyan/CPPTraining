#include <vector>
#include <iostream>

inline int leftChild(int i) {
    // Если индекс начинается с 1, то 2i, а если с 0 то 2 * (i + 1) - 1 = 2i + 1
    return (i << 1) | 1;
}

inline int rightChild(int i) {
    return (i << 1) + 2;
}

void maxHeapify(std::vector<int> &nums, int i, int heapSize) {
    int l = 0, r = 0, prev_largest = i, new_largest = i;
    do {
        std::swap(nums[prev_largest], nums[new_largest]);
        prev_largest = new_largest;
        l = leftChild(prev_largest);
        r = rightChild(prev_largest);
        if (l < heapSize && nums[l] > nums[prev_largest]) {
            new_largest = l;
        }
        if (r < heapSize && nums[r] > nums[new_largest]) {
            new_largest = r;
        }
    } while(new_largest != prev_largest);
}

void buildMaxHeap(std::vector<int> &nums) {
    for (int i = nums.size()/2; i >= 0; --i) {
        maxHeapify(nums, i, nums.size());
    }
}

void heapSort(std::vector<int> &nums) {
    int heapSize = nums.size();
    buildMaxHeap(nums);
    for (int i = nums.size()-1; i > 0; --i) {
        std::swap(nums[i], nums.front());
        //TODO: Там обновляется размер кучи,
        --heapSize;
        maxHeapify(nums, 0, heapSize);
    }
}

int main(void) {
    std::vector<int> arr = {5, 2, 3, 4, 0, 10, 2};
    heapSort(arr);
    for (const auto &element : arr) {
        std::cout << element << ' ' << std::endl;
    }
    return 0;
}