#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <vector>

using namespace std::literals;

int x = 5;
std::shared_mutex smut;

void read() {
	std::shared_lock sg(smut);
    // multiple threads can access x at the same time
    // start of critical section
    std::this_thread::sleep_for(100ms);
    // since the mutex is shared, each thread sleeps for 100 ms at the same time, (concurrently)
    // total time spent sleeping = 100 ms
	std::cout << x << std::endl;
    // end of critical section
}

void write() {
	std::lock_guard lg(smut);
    // start of critical section
    // only one thread can modify x at any given time
	x++;
    // end of critical section  
	std::cout << "x is now: " << x << std::endl;
}

int main() {
	std::vector<std::thread> threads;

	for (int i = 0; i < 20; i++) {
		threads.push_back(std::thread(read));
	}

	threads.push_back(std::thread(write));
	threads.push_back(std::thread(write));

	for (int i = 0; i < 20; i++) {
		threads.push_back(std::thread(read));
	}

	for (auto &thr : threads) {
		thr.join();
	}
}