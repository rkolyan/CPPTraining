#include <iostream>
#include <vector>

int main(void) {
    //unsigned int N = 0;
    constexpr unsigned int MOD = 1000000007;
    std::size_t size = 9999;
    //std::cin >> N;
    std::vector<unsigned int> arr(10000, std::rand() % 1000);
    std::vector<std::vector<unsigned int>> dp(size, std::vector<unsigned int>(size));
    long result = 0;
    for (int i = 0; i < 9999; ++i) {
        dp[i][0] = arr[i+1] - arr[i];
    }
    for (int i = 1; i < 9999; ++i) {
        for (int d = 1; d <= i; ++d) {
            dp[i][d] = dp[i-1][d-1] + dp[i][0];
            for (int l = 1; l <= d; ++l) {
                if (dp[i-l][d-l] == dp[i][l]) {
                    result += 1;
                }           
            }
            result %= MOD;
        }
    }
    std::cout << result << std::endl;
}