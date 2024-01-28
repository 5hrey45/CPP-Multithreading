#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::literals;
std::timed_mutex mtx;

void task1() {
	std::cout << "Task1 trying to lock the mutex\n";
	std::lock_guard lg(mtx);
	// mtx.lock();
	std::cout << "Task1 has locked the mutex\n";
	std::this_thread::sleep_for(1s);
	// mtx.unlock();
	std::cout << "Task1 has unlocked the mutex\n";
}

void task2() {
	std::unique_lock ug(mtx, std::defer_lock);
	std::this_thread::sleep_for(100ms);
	std::cout << "task2 trying to lock the mutex\n";
	while (!ug.try_lock_for(1s)) {
		std::cout << "task2 could not lock the mutex\n";
		std::this_thread::sleep_for(100ms);
	}
	std::cout << "task2 has locked the mutex\n";
	mtx.unlock();
}

int main() {
	std::thread t1(task1), t2(task2);

	t1.join();
	t2.join();

}