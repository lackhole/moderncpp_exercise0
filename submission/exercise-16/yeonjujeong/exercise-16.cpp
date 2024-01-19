#include <iostream>
#include <atomic>
#include <chrono>
#include <thread>
#include <mutex>
using namespace std;

int main() {
//	namespace chrono = std::chrono;

	//operation using atomic
	atomic<int> x1 = 0; //atomic operation

	auto t1 = chrono::steady_clock::now();
	thread th1([&]() {
		for (int i = 0; i < 100'000'000; i++) {
			x1 += 1;
		}
	});

	thread th2([&]() {
		for (int i = 0; i < 100'000'000; i++) {
			x1 += 1;
		}
	});

	//wait for finishing thread
	if (th1.joinable()) th1.join();
	if (th2.joinable()) th2.join();

	auto t2 = chrono::steady_clock::now();

	cout << x1 << '\n'; // 200,000,000
	auto dt = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
	cout << "Took " << dt.count() << "ms\n"; // 2,475ms


	//operation using mutex
	int x2 = 0;
	mutex m;

	auto t3 = chrono::steady_clock::now();
	thread th3([&]() {
		for (int i = 0; i < 100'000'000; i++) {
			lock_guard<mutex> lck(m);
			x2 += 1;
		}
	});

	thread th4([&]() {
		for (int i = 0; i < 100'000'000; i++) {
			lock_guard<mutex> lck(m);
			x2 += 1;
		}
	});
	if (th3.joinable()) th3.join();
	if (th4.joinable()) th4.join();
	auto t4 = chrono::steady_clock::now();

	cout << "mutex ver\n";
	cout << x2 << '\n'; // 200,000,000
	auto dt2 = chrono::duration_cast<chrono::milliseconds>(t4 - t3);
	cout << "Took " << dt2.count() << "ms\n"; // 3,100ms
	return 0;
}