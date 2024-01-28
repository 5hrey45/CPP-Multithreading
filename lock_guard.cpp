#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std::literals;

class Vector {
    std::mutex mut;
    std::vector<int> vec;

    public:
        void push_back(int &i) {
            std::lock_guard lg(mut);
            vec.push_back(i);
        }

        void print() {
            std::lock_guard lg(mut);
            for(const auto &num: vec) {
                std::cout << num << " ";
            }
        }
};

void func(Vector &vec) {
    for(int i = 0; i < 5; i++) {
        vec.push_back(i);
        std::this_thread::sleep_for(50ms);
        vec.print();
    }
}

int main() {
    Vector vec;
    std::thread t1(func, std::ref(vec));
    std::thread t2(func, std::ref(vec));
    std::thread t3(func, std::ref(vec));

    t1.join();
    t2.join();
    t3.join();
}