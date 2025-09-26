#include <memory>
#include <list>
#include <cstdlib>
#include <iostream>

template <class T>
class FastAllocator {
public:
    typedef T value_type;
    FastAllocator(std::size_t size) {
        data = reinterpret_cast<T*>(std::malloc(size * sizeof(T)));
        if (!data)
            throw std::bad_alloc();
        current = data;
        end = data + size;
    }
    template<class U>
    constexpr FastAllocator(const FastAllocator <U>&) noexcept {
        std::cout << "Deleted";
    }
    
    T* allocate(std::size_t n) {
        if (current != end) {
            return current++;
        }
        return nullptr;
    }
    void deallocate(T *p, std::size_t n){};
    ~FastAllocator() {
        std::cout << "Deleted";
        std::free(reinterpret_cast<void *>(data));
    }
private:
    T *data;
    T *end;
    T *current;
};

struct Node
{
    Node(int tmp){
        value = tmp;
    };
    Node()=default;
    int value;
    std::list<unsigned int> tmp_list;
};


int main(void) {
    std::list<Node, FastAllocator<Node>> lst(FastAllocator<Node>{100});
    lst.emplace_back(1);
    lst.emplace_back(4);
    return 0;
}