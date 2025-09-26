#include <iostream>
#include <vector>
#include <climits>

//SUCCESS

void choose(int index_old, int index_new, int num, int wasted, int day,
    const std::vector<int> &dp_old, std::vector<int> &dp_new,
    const std::vector<int> &wasted_old, std::vector<int> &wasted_new,
    const std::vector<std::vector<int>> &days_old, std::vector<std::vector<int>> &days_new) {
    dp_new[index_new] = dp_old[index_old] + num;
    wasted_new[index_new] = wasted_old[index_old] + wasted;
    days_new[index_new] = days_old[index_old];
    if (wasted) {
        days_new[index_new].push_back(day);
    }
}

void choose_up_or_other(int k_up, int k_other, int k_new,
    int num, int day,
    const std::vector<int> &dp_old, std::vector<int> &dp_new,
    const std::vector<int> &wasted_old, std::vector<int> &wasted_new,
    const std::vector<std::vector<int>> &days_old, std::vector<std::vector<int>> &days_new) {
    int tmp_up = dp_old[k_up], tmp_other = dp_old[k_other] + num;
    if (tmp_up < tmp_other) {
        choose(k_up, k_new, 0, 1, day,
        dp_old, dp_new,
        wasted_old, wasted_new,
        days_old, days_new);
    } else {
        choose(k_other, k_new, num, 0, day,
        dp_old, dp_new,
        wasted_old, wasted_new,
        days_old, days_new);
    }
}

void choose_up_or_down(int k, int num, int day,
    const std::vector<int> &dp_old, std::vector<int> &dp_new,
    const std::vector<int> &wasted_old, std::vector<int> &wasted_new,
    const std::vector<std::vector<int>> &days_old, std::vector<std::vector<int>> &days_new) {
    choose_up_or_other(k+1, k-1, k, num, day,
        dp_old, dp_new,
        wasted_old, wasted_new,
        days_old, days_new);
}

void choose_up_or_center(int k, int num, int day,
    const std::vector<int> &dp_old, std::vector<int> &dp_new,
    const std::vector<int> &wasted_old, std::vector<int> &wasted_new,
    const std::vector<std::vector<int>> &days_old, std::vector<std::vector<int>> &days_new) {
    choose_up_or_other(k+1, k, k, num, day,
        dp_old, dp_new,
        wasted_old, wasted_new,
        days_old, days_new);
}

void choose_up(int k, int num, int day,
    const std::vector<int> &dp_old, std::vector<int> &dp_new,
    const std::vector<int> &wasted_old, std::vector<int> &wasted_new,
    const std::vector<std::vector<int>> &days_old, std::vector<std::vector<int>> &days_new) {
    choose(k+1, k, 0, 1, day,
        dp_old, dp_new,
        wasted_old, wasted_new,
        days_old, days_new);
}

void choose_center(int k, int num, int day,
    const std::vector<int> &dp_old, std::vector<int> &dp_new,
    const std::vector<int> &wasted_old, std::vector<int> &wasted_new,
    const std::vector<std::vector<int>> &days_old, std::vector<std::vector<int>> &days_new) {
    choose(k, k, num, 0, day,
        dp_old, dp_new,
        wasted_old, wasted_new,
        days_old, days_new);
}

void choose_down(int k, int num, int day,
    const std::vector<int> &dp_old, std::vector<int> &dp_new,
    const std::vector<int> &wasted_old, std::vector<int> &wasted_new,
    const std::vector<std::vector<int>> &days_old, std::vector<std::vector<int>> &days_new) {
    choose(k-1, k, num, 0, day,
        dp_old, dp_new,
        wasted_old, wasted_new,
        days_old, days_new);
}

void init_blocked(int k, 
    std::vector<int> &dp,
    std::vector<int> &wasted,
    std::vector<std::vector<int>> &days) {
    dp[k] = -1;
    wasted[k] = -1;
    days[k] = {};
}

int calculateBestPayStrategy2(const std::vector<int> &buf, int &minsum, int &K1, int &K2, std::vector<int> &days) {
    std::vector<int> dp_prev{0}, dp_cur{0}, wasted_prev{0}, wasted_cur{0};
    std::vector<bool> mask_prev{true}, mask_cur{true};
    std::vector<std::vector<int>> days_prev{{}}, days_cur{{}};

    dp_prev.reserve(100);
    dp_cur.reserve(100);
    wasted_prev.reserve(100);
    wasted_cur.reserve(100);
    days_prev.reserve(100);
    days_cur.reserve(100);
    mask_prev.reserve(100);
    mask_cur.reserve(100);
    for (int day = 1; day <= buf.size(); ++day) {
        const auto &num = buf[day-1];
        if (num > 100) {
            for (int k = static_cast<int>(dp_prev.size())-2; k > 0; --k) {
                if (mask_prev[k-1]) {
                    if (mask_prev[k+1]) {
                        //Сравнить какой подрезультат меньше, и c приоритетом где больше купонов
                        //choose_up_and_other
                        choose_up_or_down(k, num, day,
                            dp_prev, dp_cur,
                            wasted_prev, wasted_cur,
                            days_prev, days_cur);
                    } else {
                        //взять значение снизу (+билет)
                        //choose_down
                        choose_down(k, num, day,
                            dp_prev, dp_cur,
                            wasted_prev, wasted_cur,
                            days_prev, days_cur);
                    }
                    mask_cur[k] = true;
                } else if (mask_prev[k+1]) {
                    //взять значение сверху (-билет)
                    choose_up(k, num, day,
                        dp_prev, dp_cur,
                        wasted_prev, wasted_cur,
                        days_prev, days_cur);
                    //choose_up
                    mask_cur[k] = true;
                } else {
                    init_blocked(k, dp_cur, wasted_cur, days_cur);
                    mask_cur[k] = false;
                }
            }
            if (dp_prev.size() > 1) {
                //самое верхнее значение в любом случае только снизу брать (+билет)
                choose_down(dp_cur.size()-1, num, day,
                    dp_prev, dp_cur,
                    wasted_prev, wasted_cur,
                    days_prev, days_cur);
                mask_cur.back() = mask_prev[mask_prev.size()-2];
                //самое нижнее значение можно взять только сверху (-билет)
                choose_up(0, num, day,
                    dp_prev, dp_cur,
                    wasted_prev, wasted_cur,
                    days_prev, days_cur);
                mask_cur[0] = mask_prev[1];
            } else {
                //обнулить все значения
                init_blocked(0, dp_cur, wasted_cur, days_cur);
                mask_cur[0] = false;
            }
            
            //новое самое верхнее значение берём снизу
            dp_cur.push_back(0);
            dp_prev.push_back(0);
            days_cur.push_back({});
            days_prev.push_back({});
            wasted_cur.push_back(0);
            wasted_prev.push_back(0);
            mask_cur.push_back(mask_prev.back());
            mask_prev.push_back(false);
            choose_down(dp_cur.size()-1, num, day,
                dp_prev, dp_cur,
                wasted_prev, wasted_cur,
                days_prev, days_cur);
        } else {
            for (int k = static_cast<int>(dp_prev.size())-2; k >= 0; --k) {
                if (mask_prev[k]) {
                    if (mask_prev[k+1]) {
                        choose_up_or_center(k, num, day,
                            dp_prev, dp_cur,
                            wasted_prev, wasted_cur,
                            days_prev, days_cur);
                    } else {
                        choose_center(k, num, day,
                            dp_prev, dp_cur,
                            wasted_prev, wasted_cur,
                            days_prev, days_cur);
                    }
                    mask_cur[k] = true;
                } else if (mask_prev[k+1]) {
                    choose_up(k, num, day,
                        dp_prev, dp_cur,
                        wasted_prev, wasted_cur,
                        days_prev, days_cur);
                    mask_cur[k] = true;
                } else {
                    init_blocked(k, dp_cur, wasted_cur, days_cur);
                    mask_cur[k] = false;
                }
            }
            choose_center(dp_cur.size()-1, num, day,
                dp_prev, dp_cur,
                wasted_prev, wasted_cur,
                days_prev, days_cur);
            mask_cur[mask_cur.size()-1] = mask_prev[mask_cur.size()-1];
        }
        std::swap(dp_cur, dp_prev);
        std::swap(wasted_cur, wasted_prev);
        std::swap(days_cur, days_prev);
        std::swap(mask_cur, mask_prev);
    }

    K1 = 0, K2 = 0, minsum = INT_MAX;
    for (int k = dp_prev.size()-1; k >= 0; --k) {
        if (mask_prev[k] && minsum > dp_prev[k]) {
            minsum = dp_prev[k];
            K1 = k;
            K2 = wasted_prev[k];
            days = days_prev[k];
        }
    }
    return 0;
}


int main() 
{
	std::size_t n = 0;
    std::vector<int> buf;
    std::cin >> n;
    buf.resize(n);
    for (auto &num : buf) {
        std::cin >> num;
    }
    
    /*
    Алгоритм следующий:
    У нас есть dp[i][k] - выражающее потраченную сумму за i+1 обедов (1 обед в день) с оставшимися k купонами
    также есть массив q[i] - которое хранит максимальное количество сохранившихся купонов в день
    Если buf[i] <= 100:
        dp[i][k] = max(dp[i-1][k] + buf[i], dp[i-1][k+1])
    иначе:
        dp[i][k] = max(dp[i-1][k-1] + buf[i], dp[i-1][k+1])
    Итак, нам достаточно хранить только dp_prev и dp_cur
    Требуется ещё и сохранить потраченное и оставшееся количество купонов (последнего должно быть желательно побольше)

    Гавно, нужно ещё и дни сохранять, когда он купоны получил
    */
    int K1, K2, minsum;
    std::vector<int> days;
    calculateBestPayStrategy2(buf, minsum, K1, K2, days);

    std::cout << minsum << std::endl;
    std::cout << K1 << ' ' << K2 << std::endl;
    for (const auto &day : days) {
        std::cout << day << std::endl;
    }
	return 0;
}
