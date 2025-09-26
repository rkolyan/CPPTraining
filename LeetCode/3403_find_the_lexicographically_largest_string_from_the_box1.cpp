#include <iostream>
#include <string>
#include <list>

//SUCCESS, решение победило 68 %, так как я использовал наивную реализацию, у меня 68 ms (потому что в худшем случае у меня решение где-то квадратичной сложности)
/*
Следующее решение 0 ms:
Я тоже в начале хотел воспользоваться методом скользящего окна, но че-то впадлу было думать и написал наивную реализацию
class Solution {
 public:
  string answerString(string word, int numFriends) {
    if (numFriends == 1)
      return word;
    const string s = lastSubstring(word);
    const size_t sz = word.length() - numFriends + 1;
    return s.substr(0, min(s.length(), sz));
  }

 private:
  // Same as 1163. Last Substring in Lexicographical Order
  string lastSubstring(string s) {
    int i = 0;
    int j = 1;
    int k = 0;

    while (j + k < s.length())
      if (s[i + k] == s[j + k]) {
        ++k;
      } else if (s[i + k] > s[j + k]) {
        // Skip s[j..j + k) and advance to s[j + k + 1] to find a possible
        // lexicographically larger substring since s[i..i + k) == s[j..j + k)
        // and s[i + k] > s[j + k).
        j = j + k + 1;
        k = 0;
      } else {
        // Skip s[i..i + k) and advance to s[i + k + 1] or s[j] to find a
        // possible lexicographically larger substring since
        // s[i..i + k) == s[j..j + k) and s[i + k] < s[j + k).
        // Note that it's unnecessary to explore s[i + k + 1..j) if
        // i + k + 1 < j since they are already explored by j.
        i = max(i + k + 1, j);
        j = i + 1;
        k = 0;
      }

    return s.substr(i);
  }
};
*/

class Solution {
    public:
        std::string answerString(std::string word, int numFriends) {
            if (numFriends == 1) {
                return word;
            }
            std::string result;
            const auto N = word.size() - numFriends + 1;
            result.reserve(N);
            std::list<int> indexes;
            std::string::value_type max_sym = 'a';
            for (const auto &sym : word) {
                max_sym = std::max(sym, max_sym);
            }
            result.push_back(max_sym);
            for (int i = 0; i < word.size(); ++i) {
                if (word[i] == max_sym) {
                    indexes.push_back(i+1);
                }
            }
            while (result.size() != N && !indexes.empty())
            {
                max_sym = 0;
                for (auto iter = indexes.begin(), tmp = indexes.begin(); iter != indexes.end();) {
                    if (*iter == word.size()) {
                        tmp = std::next(iter);
                        indexes.erase(iter);
                        iter = tmp;
                    } else {
                        if (word[*iter] > max_sym) {
                            max_sym = word[*iter];
                        }
                        ++iter;
                    }
                }
                for (auto iter = indexes.begin(), tmp = indexes.begin(); iter != indexes.end();) {
                    if (word[*iter] < max_sym) {
                        tmp = std::next(iter);
                        indexes.erase(iter);
                        iter = tmp;
                    } else {
                        ++(*iter);
                        ++iter;
                    }
                }
                if (max_sym > 0) {
                    result.push_back(max_sym);
                }
            }
            return result;
        }
    };

int main(void) {
    Solution sol;
    std::cout << sol.answerString("dbca", 2) << std::endl;
    std::cout << sol.answerString("gggg", 4) << std::endl;
    std::cout << sol.answerString("xkhxkjabcdegc", 6) << std::endl;
    return 0;
}