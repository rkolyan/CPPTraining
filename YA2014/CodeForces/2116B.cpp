#include <iostream>
#include <vector>

#define MOD 998244353
#define CACHE_SIZE 100000

//SUCCESS

long subcalculate(int n, std::vector<int> &cache) {
    if (n == -1) {
        return 0;
    }
    if (cache.size() < n + 1) {
        long tmp;
        for (int i = n + 1 - cache.size(); i > 0; --i) {
            tmp = cache.back();
            tmp = (tmp * 2) % MOD;
            cache.push_back(static_cast<int>(tmp));
        }
    }
    return cache[n];
}

int calculate(int n1, int n2, std::vector<int> &cache) {
    return static_cast<int>((subcalculate(n1, cache) + subcalculate(n2, cache)) % MOD);
}

std::vector<int> find_r_array(const std::vector<int> &p, const std::vector<int> &q) {
    std::vector<int> r(p.size()), pre_p(p.size()), pre_jp(p.size()), pre_q(p.size()), pre_jq(p.size());
    std::vector<int> cache;
    cache.reserve(CACHE_SIZE);
    cache.push_back(1);
    int max_p = 0, max_jp = 0, max_q = 0, max_jq = 0;
    for (unsigned int i = 0; i < r.size(); ++i) {
        if (p[i] > max_p) {
            max_p = p[i];
            max_jp = i;
        }
        if (q[i] > max_q) {
            max_q = q[i];
            max_jq = i;
        }
        pre_jp[i] = max_jp;
        pre_p[i] = max_p;
        pre_jq[i] = max_jq;
        pre_q[i] = max_q;
    }
    int p1, q1, p2, q2 = 0;
    for (unsigned int i = 0; i < r.size(); ++i) {
        p1 = pre_p[i];
        q1 = q[i - pre_jp[i]];
        p2 = p[i - pre_jq[i]];
        q2 = pre_q[i];
        if (p1 > q2) {
            r[i] = calculate(p1, q1, cache);
        } else if (p1 == q2) {
            if (q1 < p2) {
                r[i] = calculate(p2, q2, cache);
            } else {
                r[i] = calculate(p1, q1, cache);
            }
        } else {
            r[i] = calculate(p2, q2, cache);
        }
    }
    return r;
}

int main(void) {
    unsigned int t = 0, n = 0;
    std::vector<int> p, q, r;
    std::cin >> t;
    for (unsigned int ti = 0; ti < t; ++ti) {
        std::cin >> n;
        p.resize(n);
        q.resize(n);
        for (auto &element : p) {
            std::cin >> element;
        }
        for (auto &element : q) {
            std::cin >> element;
        }
        r = find_r_array(p, q);
        for (const auto &element : r) {
            std::cout << element << ' ';
        }
        std::cout << std::endl;
    }
}