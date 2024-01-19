#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>
#include <condition_variable>


int main() {
	

	int x1 = 0;
	std::mutex m;
	std::condition_variable cv;
	bool wakeUp = false;

	std::thread th1([&]() {
		for (int i = 0; i < 100'000'000; i++) {
			std::lock_guard<std::mutex> lck(m);
			x1 += 1;
		}
		cv.notify_all();
	});

	std::thread th2([&]() {
		for (int i = 0; i < 100'000'000; i++) {
			std::lock_guard<std::mutex> lck(m);
			x1 += 1;
		}
		cv.notify_all();
	});


	std::thread th3([&]() {
		std::unique_lock<std::mutex> lck(m);

		cv.wait( , [&]() {
			return x1 == 200'000'000;

		})

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
