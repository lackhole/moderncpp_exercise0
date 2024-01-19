#include <thread>
#include <iostream>
#include <atomic>
#include <mutex>
#include <chrono>

int main() {
	namespace chrono = std::chrono; // 네이밍 단축

	std::atomic<int> x1 = 0;

	auto t1 = chrono::steady_clock::now();// 시작 시간 설정

	// 시간 측정
	std::thread th1([&]() {
		for (int i = 0; i < 100000000; i++) {
			x1.fetch_add(1);
		}


		});
	std::thread th2([&]() {
		for (int i = 0; i < 100000000; i++) {
			x1.fetch_add(1);
		}
		});

	if (th1.joinable()) {
		th1.join();
	}
	if (th2.joinable()) {
		th2.join();
	}
	auto t2 = chrono::steady_clock::now();


	std::cout << x1 << '\n';

	auto dt = chrono::duration_cast<chrono::milliseconds>(t2 - t1);

	std::cout << "Took" << dt.count() << '\n';
	////////////////////////




	return 0;
}