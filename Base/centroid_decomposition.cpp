/*
Итак, простая версия центроидной декомпозиции, которая имеет вычислительную сложность O(nlogn)
1)Итак пусть мы имеем дерево в виде матрицы g[n][m], где у каждой вершины i, есть максимум m детей
В начале надо для каждой вершины определить количество его потомков
*/

#include <vector>

constexpr int N = 10, M = 5;
//Дерево представленное в виде матрицы
int g[N][M];
//Количество вершин потомков (+ сам элемент)
int s[N];

//Вычисление количества потомков(+1) для каждой вершины в дереве
//v - номер вершины
int sizes(int v) {
    s[v] = 1;
    for (int u : g[v]) {
        s[v] += sizes(u);
    }
    return s[v];
}

//Поиск центроида
//TODO: Можно сделать и без рекурсии
int centroid(int v, int n_2) {
    for (int u : g[v]) {
        if (s[u] > n_2)
            return centroid(u, n_2);
    }
    return v;
}


//Далее идет пример на поиск кратчайших расстояний при центроидной декопозиции в дереве

int l = 179; // нужная нам длина
int ans = 0;
constexpr int maxn = 200;
// нам лень явно удалять вершины: заведем массив used -- была ли вершина удалена
bool used[maxn];
int s[maxn]; // размеры поддеревьев

//p - родительская вершина
void sizes_task(int v, int p) {
    s[v] = 1;
    for (int u : g[v]) {
        if (u != p && !used[u]) {
            sizes_task(u, v);
            s[v] += s[u];
        }
    }
}

int centroid_task(int v, int p, int n) {
    for (int u : g[v])
        if (u != p && !used[u] && s[u] > n/2)
            return centroid_task(u, v, n);
    return v;
}

// записывает в t[] глубины вершин
void dfs_task(int v, int p, int d, std::vector<int> &t) {
    t.push_back(d);
    for (int u : g[v])
        if (u != p && !used[u])
            dfs_task(u, v, d + 1, t);
}

//Сама задача поиска количества путей длины l
void solve(int v) {
    /* <единственный зависящий от конкретной задачи код> */
    sizes_task(v, -1);
    std::vector<int> d(s[v], 0);
    d[0] = 1;
    for (int u : g[v]) {
        if (!used[u]) {
            std::vector<int> t;
            dfs_task(u, v, 1, t);
            for (int x : t)
                if (x <= l)
                    ans += d[l-x];
            for (int x : t)
                d[x]++;
        }
    }
    /* </единственный зависящий от конкретной задачи код> */

    used[v] = 1;
    for (int u : g[v])
        if (!used[u])
            solve(centroid_task(u, v, s[u]));
}

/*
Ниже приведена классическая реализация за O(nlogn) (не для соревновательного программирования)
*/
