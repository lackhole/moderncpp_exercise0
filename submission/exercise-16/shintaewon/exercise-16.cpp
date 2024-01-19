#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>

int main() { 
    std::atomic<int> x1(0);
    std::mutex mtx;
    int x2 = 0; 

    // atomic 사용
    auto start1 = std::chrono::steady_clock::now();
    std::thread th1([&]() {
        for (int i = 0; i < 100'000'000; ++i) {
            ++x1;
        }
        });
    std::thread th2([&]() {
        for (int i = 0; i < 100'000'000; ++i) {
            ++x1;
        }
        });

    th1.join();
    th2.join();

    auto end1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed1 = end1 - start1;

    std::cout << "x1: " << x1 << '\n';
    std::cout << "걸린 시간: " << elapsed1.count() << "\n";

    //mutex 사용
    auto start2 = std::chrono::steady_clock::now();
    std::thread th3([&]() {
        for (int i = 0; i < 100'000'000; ++i) {
            std::lock_guard<std::mutex> lock(mtx);
            ++x2;
        }
        });
    std::thread th4([&]() {
        for (int i = 0; i < 100'000'000; ++i) {
            std::lock_guard<std::mutex> lock(mtx);
            ++x2;
        }
        });

    th3.join();
    th4.join();

    auto end2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed2 = end2 - start2;

    std::cout << "x2: " << x2 << '\n';
    std::cout << "걸린 시간: " << elapsed2.count() << "\n";

    return 0;
}
