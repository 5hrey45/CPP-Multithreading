#include <iostream>
#include <thread>
#include <mutex>

using namespace std::literals;
std::mutex mut1, mut2;

// to avoid deadlock, a single thread can acquire lock for all the mutexes using
// a scoped_lock
// scoped_lock takes mutltiple mutexes as arguments and locks them in order in constructor
// and unlocks them in revserse order in destructor

void task1() {
	std::cout << "Thread 1 is trying to lock mutex 1 and 2...\n";
	std::scoped_lock sl(mut1, mut2);
	std::cout << "Thread 1 has locked mutex 1 and 2\n";
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread 1 is releasing all mutexes\n";
}

void task2() {
	std::cout << "Thread 2 is trying to lock mutex 1 and 2...\n";
	std::scoped_lock sl(mut1, mut2);
	std::cout << "Thread 2 has locked mutex 1 and 2\n";
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread 2 is releasing all mutexes\n";
}

int main() {
	std::thread t1(task1);
	std::thread t2(task2);

	t1.join();
	t2.join();
}