#include <vector>
#include <queue>
#include <algorithm>

//SUCCESS, мое решение 67 ms, побеждает 83.5%
/*
Быстрое решение какого-то рандома из leetcode, лол, почти 1 в 1 моё решение, но с этими отключениями операций ввода/вывода

const auto _ = std::cin.tie(nullptr)->sync_with_stdio(false);
#define LC_HACK
#ifdef LC_HACK
const auto __ = []() {
    struct ___ {
        static void _() { std::ofstream("display_runtime.txt") << 0 << '\n'; }
    };
    std::atexit(&___::_);
    return 0;
}();
#endif

class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        vector<int> rooms(n,0);
        sort(meetings.begin(),meetings.end());
        priority_queue<int,vector<int>,greater<int>> availablerooms;
        priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> occupytime;
        int a;
        for(int i=0;i<n;i++){
            availablerooms.push(i);
        }
        for(int i=0;i<meetings.size();i++){
            while(!occupytime.empty() && occupytime.top().first <= meetings[i][0]){
                availablerooms.push(occupytime.top().second);
                occupytime.pop();
            }
            if(!availablerooms.empty()){
                a=availablerooms.top();
                availablerooms.pop();
                rooms[a]++;
                occupytime.push({meetings[i][1],a});
            }
            else{
                pair<long long,int> b=occupytime.top();
                occupytime.pop();
                rooms[b.second]++;
                occupytime.push({b.first+meetings[i][1]-meetings[i][0],b.second});
            }
        }
        int max_bookings = -1;
        int most_booked_room_idx = -1;
        for (int i = 0; i < n; ++i) {
            if (rooms[i] > max_bookings) {
                max_bookings = rooms[i];
                most_booked_room_idx = i;
            }
        }
        return most_booked_room_idx;
    }
};
*/

class Solution {
public:
    int mostBooked(int n, std::vector<std::vector<int>>& meetings) {
        /*
        Дано n комнат, и массив встреч (meetings), где каждая встреча проходит длительностью в meetings[1]-meetings[0], meetings[0] - расписание начала встречи
        При встрече занимается комната с наименьшим номером, если все комнаты заняты, то люди ждут первой попавшейся комнаты, причем в порядке очередь - кто первый, того и тапки
        Нужно узнать номер комнаты, в которой происходило большинство встреч
        
        Первые мысли - использование очереди приоритетов, (meetings не отсортирова), или кучи
        Итак, мы храним очередь приоритетов по endtime и номеру комнаты (приоритет по меньшинству endtime, потом по меньшинству номера комнаты)
        Можно воспользоваться тем трюком с лямбда функцией
        Алгоритм следующий
        1)в 1-ю очередь приоритетов складываем комнаты, упорядочивая по номеру комнаты (приоритет у наименьшей), 
        во 2-ю очередь приоритетов складываем занимаемые комнаты с приоритетом по времени освбождения (приоритет у наименьшей по времени)
        То есть для каждой
        */
        std::vector<int> _tmp_buffer;
        _tmp_buffer.reserve(n);
        std::vector<int> _tmp_buffer2;
        _tmp_buffer2.reserve(n);
        for (std::size_t i = 0; i < n; ++i) {
            _tmp_buffer2.push_back(i);
        }

        std::sort(meetings.begin(), meetings.end());

        std::vector<std::size_t> counts(n, 0);
        std::vector<long> endtime(n, 0);
        auto myless_endtime = [&](int a, int b){return endtime[a] > endtime[b] || endtime[a] == endtime[b] && a > b;};
        std::priority_queue<int, std::vector<int>, decltype(myless_endtime)> endtime_queue(myless_endtime, std::move(_tmp_buffer));
        std::priority_queue<int, std::vector<int>, std::greater<int>> free_rooms_queue(std::greater<int>{}, std::move(_tmp_buffer2));
        int tmp_index = 0;

        for (const auto &meeting : meetings) {
            while (!endtime_queue.empty() && endtime[endtime_queue.top()] <= meeting[0]) {
                free_rooms_queue.push(endtime_queue.top());
                endtime_queue.pop();
            }
            if (!free_rooms_queue.empty()) {
                tmp_index = free_rooms_queue.top();
                free_rooms_queue.pop();
                endtime[tmp_index] = meeting[1];
            } else {
                tmp_index = endtime_queue.top();
                endtime_queue.pop();
                endtime[tmp_index] = meeting[1] + (endtime[tmp_index] - meeting[0]);
            }
            ++counts[tmp_index];
            endtime_queue.push(tmp_index);
        }

        int max_index = 0;
        std::size_t maximum = 0;
        for (int i = 0; i < counts.size(); ++i) {
            if (maximum < counts[i]) {
                maximum = counts[i];
                max_index = i;
            }
        }
        return max_index;
    }
};

#include <iostream>

int main(void) {
    Solution sol;
    std::vector<std::vector<int>> meetings1 = {{0,10},{1,5},{2,7},{3,4}}, meetings2 = {{1,20},{2,10},{3,5},{4,9},{6,8}}, meetings3 = {{1,10},{2,10},{3,10},{4,10},{5,10},{6,10},{7,10}};
    std::cout << sol.mostBooked(2, meetings1) << std::endl;
    std::cout << sol.mostBooked(3, meetings2) << std::endl;
    std::cout << sol.mostBooked(2, meetings3) << std::endl;

    return 0;
}