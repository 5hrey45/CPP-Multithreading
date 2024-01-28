#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void print(std::string s) {
	mtx.lock();
	for (int i = 0; i < 5; i++)
	{
		std::cout << s[0] << s[1] << s[2] << std::endl;
	}
	// never forget to unlock the mutex to free up the resource
	mtx.unlock();
}

int main() {
	std::thread thr1(print, "abc");
	std::thread thr2(print, "def");
	std::thread thr3(print, "xyz");

	// do not forget to join the thread, otherwise results in zombie threads
	thr1.join();
	thr2.join();
	thr3.join();

}
