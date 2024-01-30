#include <iostream>
#include <thread>
#include <mutex>

/*

// Lazy initialization (single threaded)
class Test
{
    public:
        void func() {}
};

Test *ptest = nullptr;  // variable to be initialized the first time it is used

void process() {
    if(!ptest)  // first time variable is used, checks if it is initialized
        ptest = new Test;   // if not initialized, initialize it
    ptest->func();  // then use it
}

*/

// in multi-threading the above code results in data race
// two threads can access and modify ptest at the same time which is not ideal

// Lazy initialization (multi threaded)
class Test
{
    public:
        void func() {}
};

Test *ptest = nullptr;  // variable to be initialized the first time it is used
std::mutex mut; // use a mutex to protect the resource

void process() {
    std::unique_lock ug(mut);   // can also use lock guard or good old mut.lock()
    if(!ptest)  // first time variable is used, checks if it is initialized
        ptest = new Test;   // if not initialized, initialize it
    ug.unlock();
    ptest->func();  // then use it
}

