#include <iostream>
#include <string>
#include <vector>

//SUCCESS, но скорость = 3ms, выигрывает только 41 %
//TODO: Они достигают быстродействия используя ранк, надо будет в Кормене почитать про него, также просто добавляя пары всех возможных эквивалентностей в отсортированном порядке, чтобы в процессе обработки рекурсивных вызовов родителей было как можно меньше
//TODO: Мне тоже можно было бы осуществлять вызов через рекурсию, а потом при выходе из неё обновлять родителя, но мне впадлу переделывать
class Solution {
    private:
        class DSF {
        private:
            inline std::string::value_type FIND_INDEX(const std::string::value_type sym) {
                return sym - 'a';
            }
            std::vector<int> parents;
            int find_update_parent(int child) {
                int parent = -1, previous = child;
                if (parents[child] != -1) {
                    parent = parents[child];
                    child = parent;
                }
                while (parents[child] != -1) {
                    parent = parents[child];
                    parents[previous] = parent;
                    previous = child;
                    child = parent;
                }
                return parent;
            }
        public:
            DSF() {
                parents.resize(FIND_INDEX('z') + 1, -1);
            };
            void createEquivalence(const std::string::value_type sym1, const std::string::value_type sym2) {
                if (sym1 == sym2) {
                    return;
                }
                auto i1 = FIND_INDEX(sym1);
                auto i2 = FIND_INDEX(sym2);
                if (i2 < i1) {
                    std::swap(i1, i2);
                }
                int parent1 = find_update_parent(i1);
                int parent2 = find_update_parent(i2);
                if (parent2 == -1) {
                    if (parent1 == -1) {
                        parents[i2] = i1;
                    } else {
                        if (parent1 < i2) {
                            parents[i2] = parent1;
                        } else if (parent1 > i2) {
                            parents[parent1] = i2;
                        }
                    }
                } else {
                    if (parent1 == -1) {
                        if (parent2 < i1) {
                            parents[i1] = parent2;
                        } else if (parent2 > i1) {
                            parents[parent2] = i1;
                        }
                    } else {
                        if (parent1 < parent2) {
                            parents[parent2] = parent1;
                        } else if (parent1 > parent2) {
                            parents[parent1] = parent2;
                        }
                    }
                }
            }
            std::string createEquivalentString(const std::string &input) {
                std::string result;
                int parent = 0;
                result.reserve(input.size());
                for (const auto &element : input) {
                    parent = find_update_parent(FIND_INDEX(element));
                    if (parent != -1) {
                        result.push_back(parent + 'a');
                    } else {
                        result.push_back(element);
                    }
                }
                return result;
            }
        };
    public:
        std::string smallestEquivalentString(std::string s1, std::string s2, std::string baseStr) {
            DSF dsf;
            for (unsigned int i = 0; i < s1.size(); ++i) {
                dsf.createEquivalence(s1[i], s2[i]);
            }
            return dsf.createEquivalentString(baseStr);
            /*
            М-даааа, итак, даны строки s1, s2, которые между символами на равных позициях ставят отношение эквивалентности
            то есть если s1 = "abc", s2 = "cde", то a~c, b~d, c~e (из последнего вытекает, что a~e)
            И дана baseStr, нужно найти согласно выведеным отношениям лексикографически минимальную эквивалентную строку
            1-я мысль - создание леса непересекающихся множеств и там же обновлять корень
            */
            
        }
    };

int main(void) {
    Solution sol;
    std::cout << sol.smallestEquivalentString("parker", "morris", "parser") << std::endl;
    std::cout << sol.smallestEquivalentString("hello", "world", "hold") << std::endl;
    std::cout << sol.smallestEquivalentString("leetcode", "programs", "sourcecode") << std::endl;
}