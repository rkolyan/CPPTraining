#include <vector>

//SUCCESS, 0 ms, 100 %, самая легкая и быстро решенная задача уровня hard на leetcode

class Solution {
public:
    char kthCharacter(long long k, std::vector<int>& operations) {
        /*
        1)Ищем первую степень двойки m: 2^m >= k
        2)t = 2*m 
        каждый раз делим t на 2, если k > t, то добавляем c++
        */
        long long t = 1;
        int m = 0;
        char delta = 0;
        while (t < k) {
            t <<= 1;
            ++m;
        }
        while (t > 1) {
            t >>= 1;
            if (k > t) {
                if (operations[m]) {
                    delta++;
                }
                k -= t;
            }
            --m;
        }
        return 'a'+ delta % ('z'-'a'+1);
    }
};

int main(void) {
    return 0;
}