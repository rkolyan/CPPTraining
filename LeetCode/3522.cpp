#include <vector>
#include <string>

//SUCCESS, но что забавно, моё решение 4 ms, в то время как такое же решение, но через while, а не for, занимает 0 ms

class Solution {
    public:
        long long calculateScore(std::vector<std::string>& instructions, std::vector<int>& values) {
           /*
           Итак, есть 2 массива - instructions и values
           Есть score = 0
           в instructions есть 2 типа операций - add и jump
           если instructions[i] == "add":
               score += values[i]
               i++
           Иначе (instructions[i] == "jump"):
               i = i + values[i]

            Судя по комментариям это легкая задача, мда
           */
            const auto N = values.size();
            std::vector<bool> visited(N, false);
            const std::string add_instr{"add"};
            long long score = 0;
            for (int i = 0; i >= 0 && i < N && !visited[i];) {
                if (instructions[i] == add_instr) {
                    score += values[i];
                    visited[i] = true;
                    ++i;
                } else {
                    visited[i] = true;
                    i = i + values[i];
                }
            }
            return score;
        }
    };

#include <iostream>

int main(void) {
    Solution sol;
    std::vector<std::string> instructions {"jump","add","add","jump","add","jump"};
    std::vector<int> values {2,1,3,1,-2,-3};

    std::cout << sol.calculateScore(instructions, values) << std::endl;
    return 0;
}