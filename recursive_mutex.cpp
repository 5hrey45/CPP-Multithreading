#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

std::recursive_mutex rmut;

int fact(int n) {
	if (n <= 1)
	{
		std::cout << "returning 1\n";
		return n;
	}

	std::unique_lock ug(rmut);
	//std::lock_guard lg(rmut);
	//rmut.lock();
	int retval =  n * fact(n - 1);
	std::cout << "returning " << retval << std::endl;
	//rmut.unlock();
	ug.unlock();
	return retval;
}

int main() {
	fact(5);
}