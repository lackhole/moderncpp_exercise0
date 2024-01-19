#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>


int main() {
	namespace chrono = std::chrono;

	// Use std::atomic
	std::atomic<int> x1 = 0;




	auto t1 = chrono::steady_clock::now();

	// 시간 측정
	std::thread th1([&]() {
		for (int i = 0; i < 100'000'000; i++) {
			// x1.fetch_add(1);
			x1 += 1;
		}
		});

	std::thread th2([&]() {
		for (int i = 0; i < 100'000'000; i++) {
			// x1.fetch_add(1);
			x1 += 1;
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
	auto dt = chrono::duration_cast <chrono::milliseconds>(t2 - t1);
	std::cout << "Took " << dt.count() << "ms\n";






	// Use std::mutex
	int x2 = 0;
	std::mutex m;

	auto t3 = chrono::steady_clock::now();

	// 시간 측정
	std::thread th3([&]() {
		for (int i = 0; i < 100'000'000; i++) {
			std::lock_guard<std::mutex> lck(m);
			x2 += 1;
		}
		});

	std::thread th4([&]() {
		for (int i = 0; i < 100'000'000; i++) {
			std::lock_guard<std::mutex> lck(m);
			x2 += 1;
		}
		});


	if (th3.joinable()) {
		th3.join();
	}

	if (th4.joinable()) {
		th4.join();
	}

	auto t4 = chrono::steady_clock::now();

	std::cout << x2 << '\n';
	auto dt2 = chrono::duration_cast <chrono::milliseconds>(t4 - t3);
	std::cout << "Took " << dt2.count() << "ms\n";
	


	return 0;
}
