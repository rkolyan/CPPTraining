//
// Created by rkolyan on 29.05.2024.
//

#include <list>
#include <iostream>

using segment_list_element = std::pair<int, int>;
using segment_list = std::list<segment_list_element>;

bool compare(const segment_list_element &element1, const segment_list_element &element2) {
    if (element1.first <= element2.first && element1.second >= element2.second ||
    element1.first >= element2.first && element1.second <= element2.second)
        return true;
    return false;
}

int find_interception_count(segment_list &segments) {
    int count = 0;
    bool flag = false;
    for (auto begin_iter = segments.begin(); begin_iter != segments.end(); begin_iter++) {
        flag = false;
        for (auto iter = std::next(begin_iter); iter != segments.end();) {
            if (compare(*begin_iter, *iter)) {
                flag = true;
                iter = segments.erase(iter);
            } else {
                iter++;
            }
        }
        if (!flag) {
            count++;
        }
    }
    return count;
}

int main12431234(void) {
    segment_list segments;
    int N = 0, tmp = 0;
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        std::cin >> tmp;
        segments.emplace_back(tmp, 0);
    }
    for (auto &segment : segments) {
        std::cin >> segment.second;
    }
    std::cout << find_interception_count(segments);
    return 0;
}