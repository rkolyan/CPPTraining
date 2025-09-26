#include <vector>
#include <stack>
#include <array>

//TODO: Доделай эту задачу
class Solution {
    private:
        #define Nmax 1000
    public:
        std::vector<int> maxTargetNodes(std::vector<std::vector<int>>& edges1, std::vector<std::vector<int>>& edges2, int k) {
            
            /*
            1)Строим дерево 1
            Алгоритм построения следующий
            береём edges1.size() + 1 = n (так сказано по условию)
            создаём tree[n][1000], (std::vector<std::array<int, 1000>>)
            создаём counts[n] (std::vector<int> counts);
            мы не знаем, сколько значений в каждом массиве поэтому подсчитиываем
            */
            int N = edges1.size()+1;
            std::vector<std::array<int, Nmax>> tree(N);
            std::vector<int> counts(N, 0);
            for (const auto &subvector : edges1) {
                tree[subvector.front()][counts[subvector.front()]++] = subvector.back();
                tree[subvector.back()][counts[subvector.back()]++] = subvector.front();
                
            }
            std::stack<int, std::vector<int>> stack = [&]{
                std::vector<int> buffer;
                buffer.reserve(N * 2);
                return std::stack<int, std::vector<int>>(std::move(buffer));
            }();
            std::vector<int> sizes(N, 0);
            stack.push(0);
            stack.push(0);
            int parent = 0, index = 0;
            while (!stack.empty()) {
                index = stack.top();
                stack.pop();
                parent = stack.top();
                ++index;
                if (index < counts[])
                /*
                1)Извлекаем элемент из стека, просматриваем его и последний элемент из стека
                void build_sizes(int v, int p) {
                    s[v] = 1;
                    for (int i = 0; i < counts[v]; ++i) {
                        auto u = tree[v][i];
                        if (u != p && !used[u]) {
                            build_sizes(u, v);
                            s[v] += s[u];
                        }
                    }
                }
                Что происходит - мы кладём в стек сначала p, затем v, также сохраняем i потом опять v, u, потом опять u...
                Думаю достаточно будет положить родителя (p) и индекс i,
                потом tree[p][i] и уже его индекс j
                Затем tree[]
                3 состояния
                1)ENTER входим -> s[v] = 1, далее кладём элемент первого ребенка и делаем вызов ENTER; Если все дети помечены уже, то делаем EXIT
                2)NEXT_INDEX это когда мы просто увеличиваем s[parent] += s[tree[parent][index]], и увеличиваем индекс кладём в стек новые элементы (индекс и значение)
                3)EXIT - s[
                
                ENTER - кладем в стек [i, v] (i мы не используем в следующей итерации, вместо этого)
                */
            }
            /*
            2)Используем центроидную декомпозицию для поиска количества
            */
        }
    };