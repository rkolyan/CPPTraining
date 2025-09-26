#include <vector>

//SUCCESS, моё решение 6 ms, побило 89,24 %
/*
Чъе-то решение на 4 ms, использует ranges, диапазоны
#include <ranges>

class Solution {
public:
  int maxFreeTime(int eventTime, vector<int>& startTime, vector<int>& endTime) {
    int n = size(startTime);
    auto max_gap_before = 0;
    auto last_end = 0;
    auto max_free_time = 0;
    for (auto i : views::iota(0, n)) {
      auto meeting_time = endTime[i] - startTime[i];
      auto next_start = i == n - 1 ? eventTime : startTime[i + 1];
      auto free_time = next_start - last_end;
      if (meeting_time > max_gap_before) free_time -= meeting_time; 
      if (free_time > max_free_time) max_free_time = free_time;
      if (auto gap_before = startTime[i] - last_end;
          gap_before > max_gap_before) {
        max_gap_before = gap_before;
      }
      last_end = endTime[i];
    }

    auto max_gap_after = 0;
    auto last_start = eventTime;
    for (auto i : views::iota(0, n) | views::reverse) {
      auto meeting_time = endTime[i] - startTime[i];
      auto next_end = i == 0 ? 0 : endTime[i - 1];
      auto free_time = last_start - next_end;
      if (meeting_time <= max_gap_after) {
        if (free_time > max_free_time) max_free_time = free_time;
      }
      if (auto gap_after = last_start - endTime[i];
          gap_after > max_gap_after) {
        max_gap_after = gap_after;
      }
      last_start = startTime[i];
    }
    return max_free_time;
  }

*/

class Solution {
public:
    int maxFreeTime(int eventTime, std::vector<int>& startTime, std::vector<int>& endTime) {
        /*
        1)Ищем максимальный размер слева (prefix), и справа (suffix), не граничещего с текущим элементом свободным блоком
        2)Далее проходимся по каждому элементу и смотрим сумму  размеров свободных позиций + если длительность встречи меньше suffix[i] или prefix[i], то ещё добавляем длительность этого периода
        */
        if (startTime.size() == 1) {
            return startTime[0] + (eventTime - endTime[0]);
        }
        std::vector<int> prefixes(startTime.size()), suffixes(endTime.size());
        prefixes[0] = 0;
        prefixes[1] = startTime[0];
        for (std::size_t i = 2; i < prefixes.size(); ++i) {
            prefixes[i] = std::max(prefixes[i-1], startTime[i-1] - endTime[i-2]);
        }
        suffixes[suffixes.size()-1] = 0;
        suffixes[suffixes.size()-2] = eventTime - endTime[endTime.size()-1];
        for (int i = suffixes.size()-3; i >= 0; --i) {
            suffixes[i] = std::max(suffixes[i+1], startTime[i+2] - endTime[i+1]);
        }
        
        int free_time = startTime[0] + (startTime[1]-endTime[0]), max_free_time = 0;
        int duration = endTime[0]-startTime[0];
        if (duration > suffixes[0]) {
            duration = 0;
        }
        max_free_time = free_time + duration;
        free_time -= startTime[0];
        for (std::size_t i = 1, i_end = startTime.size()-1; i < i_end; ++i) {
            free_time += startTime[i+1] - endTime[i];
            duration = endTime[i] - startTime[i];
            if (duration > std::max(prefixes[i], suffixes[i])) {
                duration = 0;
            }
            max_free_time = std::max(max_free_time, free_time + duration);
            free_time -= startTime[i] - endTime[i-1];
        }
        free_time += eventTime - endTime[endTime.size()-1];
        duration = endTime[endTime.size()-1] - startTime[startTime.size()-1];
        if (duration > prefixes[prefixes.size()-1]) {
            duration = 0;
        }
        max_free_time = std::max(max_free_time, free_time + duration);
        return max_free_time;
    }
};

#include <iostream>

int main(void) {
    Solution sol;
    std::vector<int> startTime1{1,3}, endTime1{2,5}, startTime2{0,7,9}, endTime2{1,8,10}, startTime3{0,3,7,9}, endTime3{1,4,8,10}, startTime4{0,1,2,3,4}, endTime4{1,2,3,4,5};

    std::cout << sol.maxFreeTime(5, startTime1, endTime1) << std::endl;
    std::cout << sol.maxFreeTime(10, startTime2, endTime2) << std::endl;
    std::cout << sol.maxFreeTime(10, startTime3, endTime3) << std::endl;
    std::cout << sol.maxFreeTime(5, startTime4, endTime4) << std::endl;

    return 0;
}