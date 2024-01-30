#include <iostream>
#include <thread>
#include <random>

// we are using mt19937 random enigne and uniform distribution for generating
// random numbers

// if we use thread local_variable, each thread will get it's own copy of random number engine object
// and the output of both the threads will be the same.

// thread_local std::mt19937 mt;
std::mt19937 mt; // each thread will produce different random numbers as output

void func() {
    std::uniform_int_distribution<int> dist(0, 100);

    for(int i = 0; i < 10; i++)
        std::cout << dist(mt) << " ";
}

int main() {
    std::cout << "Thread 1's random values: \n";
    std::thread t1(func);
    t1.join();

    std::cout << std::endl;

    std::cout << "Thread 2's random values: \n";
    std::thread t2(func);
    t2.join();
}