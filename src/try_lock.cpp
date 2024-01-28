#include <iostream>
#include <thread>
#include <mutex>

using namespace std::literals;
std::mutex mtx;

void task1() {
	std::cout << "Task1 trying to lock the mutex\n";
	mtx.lock();
	std::cout << "Task1 has locked the mutex\n";
	std::this_thread::sleep_for(500ms);
	mtx.unlock();
	std::cout << "Task1 has unlocked the mutex\n";
}

void task2() {
	std::this_thread::sleep_for(100ms);
	std::cout << "task2 trying to lock the mutex\n";
	while (!mtx.try_lock()) {
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