#include <iostream>
#include <thread>
using namespace std;



int x;

int main() {

	thread th1 = thread([&]() {
		for (int i = 0; i < 100'000'000; i++) {
			x++;
		}
	});

	thread th2 = thread([&]() {
		for (int i = 0; i < 100'000'000; i++) {
			x++;
		}
	});

	// do something
	if (th1.joinable()) {
		th1.join();
	}

	if (th2.joinable()) {
		th2.join();
	}

	std::cout << x << '\n';

	return 0;
}
