#include <vector>
#include <queue>
#include <cmath>

//SUCCESS, решение медленное, 661 ms, победил только 10%, потому что старался использовать не вещественные числа, а использовать собственное представление дроби
//А так алгоритм везде приблизительно одинаковый
/*
Вот пример алгоритма, скорость работы 29 ms (боже, что он делает...)
//NBM
class Solution {
private:
    static constexpr uint8_t VSH = 17;
    static constexpr uint VMASK = (1u << VSH) - 1u;

public:
    static double maxAverageRatio(vector<vector<int>>& classes, uint s) {
        const uint n = classes.size();
        if (n == 1) {
            const auto &x = classes.front();
            const uint p = x[0], t = x[1];
            return (double)(p + s) / (t + s);
        }
        vector<uint64_t> &qvec = (vector<uint64_t>&)classes;
        uint64_t *const qdata = qvec.data();
        const auto cmp = [](const uint64_t a, const uint64_t b) {
            const uint t = a >> VSH, p = a & VMASK, u = b >> VSH, v = b & VMASK;
            return (t - p) * (u + 1ull) * u < (u - v) * (t + 1ull) * t;
        };
        uint m = 0;
        double res = 0.;
        for (const auto &x : classes) {
            const uint p = x[0], t = x[1];
            if (p != t)
                qdata[m++] = (uint64_t(t) << VSH) + p;
            res += (double)p / t;
        }
        switch (m) {
            case 0:
                qvec.clear();
                return 1.;
            case 1: {
                const auto x = *qdata;
                qvec.clear();
                const uint p = x & VMASK, t = x >> VSH;
                return (double)(p + s) / (t + s);
            }
        }
        make_heap(qdata, qdata + m, cmp);
        while (true) {
            const uint64_t x = *qdata;
            const uint t = x >> VSH, p = x & VMASK, l = t - p;
            pop_heap(qdata, qdata + m--, cmp);
            const uint64_t y = *qdata;
            const uint u = y >> VSH, v = y & VMASK;
            const uint z = floor(sqrt((t - p) * (u + 1ull) * u / double(u - v) + 0.75)),
                       f = (s + m) / (m + 1u) / 4u,
                       d = max(z, t + f + !f) - t,
                       e = min(d, s);
            res += (p + e) / double(t + e) - p / (double) t;
            s -= e;
            if (!s) break;
            qdata[m++] = x + e + (uint64_t(e) << VSH);
            push_heap(qdata, qdata + m, cmp);
        }
        qvec.clear();
        return res / n;
    }
};
*/

class Solution {
private:
    double roundToDecimal(double value, int decimalPlaces) {
        double factor = std::pow(10.0, decimalPlaces);
        return std::round(value * factor) / factor;
    }
    class Fraction {
    private:
        long _p, _q;
    public:
        Fraction(long x, long y) : _p{x}, _q{y} {}
        bool operator<(const Fraction &other) const {
            if (_p * other._q - other._p * _q < 0) {
                return false;
            }
            return true;
        }
        Fraction &operator++() {
            _p++;
            _q++;
            return *this;
        }
        Fraction calculateFunction() {
            return Fraction(_p-_q, _q*(_q+1));
        }
        double getResult() const {
            if (!_q) {
                return -1;
            }
            return static_cast<double>(_p) / _q;
        }
    };
    class FractionPair {
    private:
        Fraction _fraction, _func_result;
    public:
        FractionPair(long x, long y) : _fraction(x,y), _func_result(x-y, y*(y+1)) {}
        FractionPair &operator++() {
            ++_fraction;
            _func_result = _fraction.calculateFunction();
            return *this;
        }
        bool operator<(const FractionPair &other) const {
            return _func_result < other._func_result;
        }
        double getResult() const {
            return _fraction.getResult();
        }
    };
public:
    double maxAverageRatio(std::vector<std::vector<int>>& classes, int extraStudents) {
        /*
        Итак, нам нужно максимально повысить средний показатель проходных баллов p = sum(pass[i]/total[i])/n  (classes[i] = [pass[i], total[i]])
        добавляя в любом случае сдающих студентов в тот или иной класс.
        Итак, тут явно нужно использовать очередь приоритетов, нужно иметь дробь с наименьшим значение в знаменателе и наи большее в числителе, и тогда при
        увеличении числителя и знаменятеля будут наибольшие увеличенния значения вероятности, проверим математически

        Итак есть дробь x/y и дробь (x+d)/(y+d)
        x/y ? (x+d)/(y+d)
        x(y+d) ? y(x+d)
        xd ? yd
        x ? y

        Ну, или нам нужно вычислить максимальное (x+d)/(y+d) - x/y
        f(x,y,d) = (x - y)d/((y+d)y)
        Производная по x: f_x = d/((y+d)y) - y положительна, d тоже

        Итак, ладно, опустим доказательноство, будем добавлять в класс по одному студенту по следующему алгоритму
        : в начале приоритет у дробей с а наименьшим знаменателем, потому что delta = 1/p будет максимальна с минимальным p
        Далее
        f(x,y) = f(x,y,1)
        (x+1)/(y+1) - x/y = ((xy + y) - (xy + x)) / (y(y+1))

        Короче, очередь приоритетов
        пусть x = pass[i], y = total[i], вычисляем дробь p/q = f(x,y)
        Далее, кладем в очередь приоритетов, сравнивая дроби p/q, приоритет будет по максимуму
        Далее, алгоритм - вытаскиваем элемент, увелчиваем его x,y на 1, вычисляем заново p/q и кладём опять в очередь
        В конце на основе очереди приоритетов посчитываем максимальное среднее значение.
        */
        double result = 0;
        std::priority_queue<FractionPair, std::vector<FractionPair>, std::less<FractionPair>> pq = [&]{
            std::vector<FractionPair> tmp_buf;
            tmp_buf.reserve(classes.size());
            std::priority_queue<FractionPair, std::vector<FractionPair>, std::less<FractionPair>> tmp_pq(std::less<FractionPair>(), std::move(tmp_buf));
            return tmp_pq;
        }();

        for (const auto &cls : classes) {
            pq.emplace(cls[0], cls[1]);
        }
        while (extraStudents) {
            auto cur = pq.top();
            pq.pop();
            ++cur;
            pq.push(cur);
            --extraStudents;
        }
        while(!pq.empty()) {
            result += pq.top().getResult();
            pq.pop();
        }
        return roundToDecimal(result / classes.size(), 5);
    }
};

#include <iostream>

int main(void) {
    std::vector<std::vector<int>> classes1 = {{1,2},{3,5},{2,2}}, classes2 = {{2,4},{3,9},{4,5},{2,10}};
    Solution sol;

    std::cout << sol.maxAverageRatio(classes1, 2) << std::endl;
    std::cout << sol.maxAverageRatio(classes2, 4) << std::endl;

    return 0;
}