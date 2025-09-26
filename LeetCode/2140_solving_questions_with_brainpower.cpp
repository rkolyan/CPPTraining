#include <vector>

//SUCCESS, 8ms, побеждает  45,42%
/*
Вот решение за 0 ms, хз, тут суть та же что и у меня, только обход в обратном порядке
class Solution {
public:
    long long mostPoints(vector<vector<int>>& questions) {
        int n = questions.size();
        vector<long long> dp (n+1, 0);

        for(int i = n-1 ; i>=0;i--){
            int points = questions[i][0];
            int brainPower = questions[i][1];
            int nextIndex = brainPower + i + 1;
            long long nextPoints = nextIndex < n ? dp[nextIndex] : 0; 
            dp[i] = max( points + nextPoints, dp[i+1]);
        }

        return dp[0];
    }
};
*/

class Solution {
public:
    long long mostPoints(std::vector<std::vector<int>>& questions) {
        /*
        Итак, у нас следующая задача, имеем несколько вопросов, за решение i-го вопроса мы получаем определенное количество очков questions[i][0], но при этом мы не можем решить следующие questions[i][1] задач
        Нужно определить максимальное количество очков, которые мы можем заработать на экзамене.
        Задача явно на DP
        */
        std::vector<long long> dp(questions.size(), 0);
        int next_index;
        long long maxPoints = 0, points;
        points = questions[0][0];
        maxPoints = points;
        next_index = questions[0][1]+1;
        if (next_index < questions.size()) {
            dp[next_index] = points;
        }
        for (std::size_t i = 1; i < questions.size(); ++i) {
            dp[i] = std::max(dp[i-1], dp[i]);
            points = dp[i] + questions[i][0];
            maxPoints = std::max(maxPoints, points);
            next_index = i + questions[i][1] + 1;
            if (next_index < questions.size()) {
                dp[next_index] = std::max(dp[next_index], points);
            }
        }
        return maxPoints;
    }
};