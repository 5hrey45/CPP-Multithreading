#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std::literals;

int x = 5;
std::mutex mut;

void read() {
	std::lock_guard lg(mut);
	// start of critical section
	std::this_thread::sleep_for(100ms);
	// since the mutex is exclusive and not shared, each thread sleeps for 100 ms sequentially
	// total time spent = so number of threads * 100 ms to completed the read operation
	// use shared mutex to improve performance (if the operation is non modifying)
	std::cout << x << std::endl;
	// end of critical section
}

void write() {
	std::lock_guard lg(mut);
	// start of critical section
	x++;
	// end of critical sectioin
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