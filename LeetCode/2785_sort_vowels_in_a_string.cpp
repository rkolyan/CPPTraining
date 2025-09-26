#include <vector>
#include <string>
#include <algorithm>
#include <set>
//SUCCESS, самое простое решение, 60%, 14 ms на основе сортировки и сохранения позиций
class Solution {
public:
    std::string sortVowels(std::string s) {
        std::vector<int> positions;
        std::vector<char> vowels;
        positions.reserve(s.size());
        vowels.reserve(s.size());
        
        for (int i = 0; i < s.size(); ++i) {
            switch (s[i])
            {
            case 'A':
            case 'O':
            case 'E':
            case 'I':
            case 'U':
            case 'a':
            case 'o':
            case 'e':
            case 'i':
            case 'u':
                positions.push_back(i);
                vowels.push_back(s[i]);
            }
        }
        std::sort(vowels.begin(), vowels.end());
        for (int i = vowels.size()-1; i >= 0; --i) {
            s[positions[i]] = vowels[i];
        }
        return s;
    }
};


//Вот решение (мое же) побыстрее, уже 8ms, побеждает 85%
class Solution2 {
private:
    enum vowel_t {
        A,
        E,
        I,
        O,
        U,
        a,
        e,
        i,
        o,
        u,
        vowel_count
    };
public:
    std::string sortVowels(std::string s) {
        std::vector<int> positions;
        int counts[vowel_count] = {0};
        char syms[] = {'A','E','I','O','U','a','e','i','o','u'};
        positions.reserve(s.size());
        
        for (int i1 = 0; i1 < s.size(); ++i1) {
            switch (s[i1])
            {
            case 'A':
                counts[A]++;
                positions.push_back(i1);
                break;
            case 'O':
                counts[O]++;
                positions.push_back(i1);
                break;
            case 'E':
                counts[E]++;
                positions.push_back(i1);
                break;
            case 'I':
                counts[I]++;
                positions.push_back(i1);
                break;
            case 'U':
                counts[U]++;
                positions.push_back(i1);
                break;
            case 'a':
                counts[a]++;
                positions.push_back(i1);
                break;
            case 'o':
                counts[o]++;
                positions.push_back(i1);
                break;
            case 'e':
                counts[e]++;
                positions.push_back(i1);
                break;
            case 'i':
                counts[i]++;
                positions.push_back(i1);
                break;
            case 'u':
                counts[u]++;
                positions.push_back(i1);
            }
        }
        for (int i = positions.size()-1, j = u; i >= 0; --i) {
            while(!counts[j]) {
                --j;
            }
            s[positions[i]] = syms[j];
            --counts[j];
        }
        return s;
    }
};

//Решение с multiset теоретически быстрее, но из-за проблем с выделением памяти сильно медленней (70ms)
//Наверное, с ручным аллоктором памяти будет побыстрее
class Solution1 {
public:
    std::string sortVowels(std::string s) {
        std::vector<int> positions;
        std::multiset<char> vowels;
        positions.reserve(s.size());
        
        for (int i = 0; i < s.size(); ++i) {
            switch (s[i])
            {
            case 'A':
            case 'O':
            case 'E':
            case 'I':
            case 'U':
            case 'a':
            case 'o':
            case 'e':
            case 'i':
            case 'u':
                positions.push_back(i);
                vowels.emplace(s[i]);
            }
        }
        for (int i = vowels.size()-1; i >= 0; --i) {
            auto tmp_iter = vowels.begin();
            s[positions[i]] = *tmp_iter;
            vowels.extract(tmp_iter);
        }
        return s;
    }
};