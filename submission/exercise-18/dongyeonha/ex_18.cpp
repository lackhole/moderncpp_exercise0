#include <atomic>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

int main() {

	int x1 = 0;
	std::mutex m;
	std::condition_variable cv;

	std::thread th1([&]() {
		for (int i = 0; i < 100000000; ++i) {
			std::lock_guard<std::mutex> lck(m);
			x1 += 1;
		}
		cv.notify_all();
	});

	std::thread th2([&]() {
		for (int i = 0; i < 100000000; ++i) {
			std::lock_guard<std::mutex> lck(m);
			x1 += 1;
		}
		cv.notify_all();
	});

	std::thread th3([&]() {
		std::unique_lock<std::mutex> lck(m);
		cv.wait(lck, [&]() {
			return x1 == 200000000;
		});
		std::cout << x1 << '\n';
	});

	if (th1.joinable()) {
		th1.join();
	}

	if (th2.joinable()) {
		th2.join();
	}

	if (th3.joinable()) {
		th3.join();
	}


	return 0;
}