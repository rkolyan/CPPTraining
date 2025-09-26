#include <iostream>
#include <vector>

//SUCCESS
//TODO: Надо будет доделать ту версию с большими числами

int main(void) {
    std::size_t N = 0;
    std::vector<int> a;
    std::vector<int> b;

    std::cin >> N;
    N++;

    a.resize(N);
    for (auto &elem : a) {
        std::cin >> elem;
    }
    b.reserve(N+1);
    b.push_back(-a[0]);
    if (a[1] != 1) {
        b.resize(N+1);
        b[1] = 1;
        b[2] = a[1] - 1;
        for (unsigned int i = 2; i < N; i++) {
            b[i+1] = a[i];
        }
    } else {
        b.resize(N-1);
        b[1] = 1 + a[2];
        for (unsigned int i = 3; i < N; i++) {
            b[i-1] = a[i];
        }
    }
    if (b.back() == 1) {
        b.pop_back();
        if (b.size()) {
            b.back()++;
        }
    }
    std::cout << b.size() - 1 << std::endl;
    for (const auto &elem : b) {
        std::cout << elem << ' ';
    }
    return 0;
}