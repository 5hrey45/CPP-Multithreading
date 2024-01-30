#include <iostream>
#include <thread>
#include <mutex>

using namespace std::literals;
std::mutex mut1, mut2;

// to avoid deadlock, acquire the locks in same order
// thread 1 and thread 2 both try to lock mutex 1 first
// successful thread then tries to lock mutex 2

void task1() {
	std::cout << "Thread 1 is trying to lock mutex 1...\n";
	std::unique_lock ug1(mut1);
	std::cout << "Thread 1 has locked mutex 1\n";
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread 1 is trying to lock mutex 2...\n";
	std::unique_lock ug2(mut2);
	std::cout << "Thread 1 has locked mutex 2\n";
	std::this_thread::sleep_for(50ms);
	ug1.unlock();
	ug2.unlock();
	std::cout << "Thread 1 has unlocked all mutexes\n";
}

void task2() {
	std::cout << "Thread 2 is trying to lock mutex 1...\n";
	std::unique_lock ug1(mut1);
	std::cout << "Thread 2 has locked mutex 1\n";
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread 2 is trying to lock mutex 2...\n";
	std::unique_lock ug2(mut2);
	std::cout << "Thread 2 has locked mutex 2\n";
	std::this_thread::sleep_for(50ms);
	ug1.unlock();
	ug2.unlock();
	std::cout << "Thread 2 has unlocked all mutexes\n";
}

int main() {
	std::thread t1(task1);
	std::thread t2(task2);

	t1.join();
	t2.join();
}