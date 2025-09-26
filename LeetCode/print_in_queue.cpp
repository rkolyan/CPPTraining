#include <functional>
//#include <algorithm>

class Foo {
    public:
        Foo() : _done{true, true} {
        }
    
        void first(std::function<void()> printFirst) {
            
            // printFirst() outputs "first". Do not change or remove this line.
            printFirst();
            _done[0] = false;
        }
    
        void second(std::function<void()> printSecond) {
            
            // printSecond() outputs "second". Do not change or remove this line.
            while (_done[0]);
            printSecond();
            _done[1] = false;
        }
    
        void third(std::function<void()> printThird) {
            
            // printThird() outputs "third". Do not change or remove this line.
            while (_done[0]);
            printThird();
        }
    private:
        bool _done[2];
    };