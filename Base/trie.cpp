#include <array>
#include <vector>
#include <string>

//Реализация через массив указателей
class Trie1 {
private:
    #define ARRAY_SIZE 'z'-'a'+1
    /*
    Структура префиксного дерева:
    Допустим, у нас ограниченное число символов, поэтому
    пускай будет вектор 
    */
    std::array<Trie1*, ARRAY_SIZE> sub_trees;
    bool is_leaf;
    std::size_t id;

    void add_substring(std::vector<std::string> &strings, std::string &current) {
        if (is_leaf) {
            strings.push_back(current);
        }
        for (unsigned int i = 0; i < ARRAY_SIZE; ++i) {
            if (sub_trees[i]) {
                current.push_back('a'+i);
                sub_trees[i]->add_substring(strings, current);
            }
        }
        if (current.size()) {
            current.pop_back();
        }
    }
    void add_substring2(std::vector<std::string> &strings, std::string &current) {
        if (is_leaf) {
            strings[id] = current;
        }
        for (unsigned int i = 0; i < ARRAY_SIZE; ++i) {
            if (sub_trees[i]) {
                current.push_back('a'+i);
                sub_trees[i]->add_substring2(strings, current);
            }
        }
        if (current.size()) {
            current.pop_back();
        }
    }
public:
    Trie1(){
        sub_trees.fill(nullptr);
        is_leaf = false;
    }

    ~Trie1() {
        for (unsigned int i = 0; i < ARRAY_SIZE; ++i) {
            if (sub_trees[i]) {
                delete sub_trees[i];
            }
        }
    }
    int insert(const std::string::iterator &iter, const std::string::iterator &end){
        if (iter != end) {
            sub_trees[*iter-'a'] = new Trie1();
            if (!sub_trees[*iter-'a']){
                return -1;
            }
            return sub_trees[*iter]->insert(std::next(iter), end);
        } else {
            is_leaf = true;
        }
        return 0;
    }
    int insert_symbol(const char ch) {
        auto &trie = sub_trees[ch-'a'];
        if (trie) {
            trie->is_leaf = true;
        } else {
            trie = new Trie1();
            if (!trie) {
                return -1;
            }
            trie->is_leaf = true;
        }
        return 0;
    }
    int insert_symbol(const char ch, std::size_t index) {
        auto &trie = sub_trees[ch-'a'];
        if (trie) {
            trie->is_leaf = true;
            trie->id = index;
        } else {
            trie = new Trie1();
            if (!trie) {
                return -1;
            }
            trie->is_leaf = true;
            trie->id = index;
        }
        return 0;
    }
    bool search(const std::string::iterator &iter, const std::string::iterator &end) {
        if (iter != end) {
            if (sub_trees[*iter-'a']) {
                return sub_trees[*iter-'a']->search(std::next(iter), end);
            }
        } else {
            if (is_leaf) {
                return true;
            }
        }
        return false;
    }
    //TODO: Это для задач поэтапного поиска (то есть двигая по одному символу)
    Trie1 *stateSearch(const char ch) {
        return sub_trees[ch-'a'];
    }
    
    bool isLeaf() {
        return is_leaf;
    }
    /*
    сохраним 
    */
    std::vector<std::string> createDictionary() {
        std::vector<std::string> result;
        std::string current;
        add_substring(result, current);
        return result;
    }
    std::vector<std::string> createDictionary(std::size_t maximum) {
        std::vector<std::string> result;
        std::string current;
        result.resize(maximum);
        add_substring2(result, current);
        return result;
    }
};

//TODO: Придумай реализацию с фиксированным размером памяти

//Для задачи, где известно, что все найденные подстроки не пересекаются и сумма всех размеров = размер строки

class Trie2 {
private:
    
};