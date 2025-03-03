//
// Created by rkolyan on 11.04.2024.
//

#include <iostream>
#include <vector>
#include <array>
#include <map>

struct TriangleProp {
    double square_geron;
    double p;
    bool operator<(const TriangleProp &other) const{
        return p < other.p || square_geron < other.square_geron;
    }
    TriangleProp(double p, double geron) {
        this->square_geron = geron;
        this->p = p;
    }
};

int main(void) {
    int N = 0, a = 0, b = 0, c = 0;
    std::map<TriangleProp, size_t, std::less<TriangleProp>> counts;
    double p = 0, geron = 0;
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        std::cin >> a;
        std::cin >> b;
        std::cin >> c;
        p = static_cast<double>(a + b + c) / 2;
        geron = p * (p - a) * (p - b) * (p - c);
        counts[TriangleProp(p, geron)]++;
    }
    std::cout << counts.begin()->second << std::endl;
    return 0;
}