//
// Created by rkolyan on 18.01.2025.
//

#include <map>
#include <cmath>
#include <iostream>

#define EPSILON 1E-8

class Triangle {
public:
    Triangle(int a, int b, int c) {
        _rsqr = ((double)((-a + b + c) * (a - b + c) * (a + b - c))) / (a + b + c) ;
    }
    bool operator==(const Triangle &triangle) const {
        return std::abs(_rsqr - triangle._rsqr) < EPSILON;
    }
    bool operator<(const Triangle &triangle) const {
        return _rsqr < triangle._rsqr;
    }
private:
    double _rsqr;
};

int main(int argc, char **argv) {
    int n = 0, a = 0, b = 0, c = 0;
    std::map<Triangle, int> counts;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a >> b >> c;
        counts[Triangle(a, b, c)]++;
    }
    int maximum = 0;
    for (auto & count : counts) {
        if (count.second > maximum)
            maximum = count.second;
    }
    std::cout << maximum;
    return 0;
}