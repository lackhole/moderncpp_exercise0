#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>


int main() {

	namespace chrono = std::chrono;

	// Use std::atomic
	std::atomic<int> x1 = 0;

	auto t1 = chrono::steady_clock::now();

	// 시간 측정
	std::thread th1([&x1]() {
		for (int i = 0; i < 100'000'000; ++i) {
			x1.fetch_add(1);
			//x1 += 1;
		}
		});
	std::thread th2([&x1]() {
		for (int i = 0; i < 100'000'000; ++i) {
			x1.fetch_add(1);
			//x1 += 1;
		}
		});

	if (th1.joinable())
	{
		th1.join();
	}
	if (th2.joinable())
	{
		th2.join();
	}

	auto t2 = chrono::steady_clock::now();
	auto dt = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
	std::cout << x1 << std::endl;
	std::cout << dt.count() << 'ms' << std::endl;

	std::mutex m;
	int x2 = 0;

	auto t3 = chrono::steady_clock::now();

	std::thread th3 = std::thread([&]() {
		for (int i = 0; i < 100'000'000; ++i) {
			std::lock_guard<std::mutex> lck(m);
			x2 += 1;
		}
		});

	std::thread th4 = std::thread([&]() {
		for (int i = 0; i < 100'000'000; ++i) {
			std::lock_guard<std::mutex> lck(m);
			x2 += 1;
		}
		});

	if (th3.joinable())
	{
		th3.join();
	}
	if (th4.joinable())
	{
		th4.join();
	}

	auto t4 = chrono::steady_clock::now();
	auto dt2 = chrono::duration_cast<chrono::milliseconds>(t4 - t3);
	std::cout << x2 << std::endl;
	std::cout << dt2.count() << 'ms' << std::endl;

	return 0;
}
