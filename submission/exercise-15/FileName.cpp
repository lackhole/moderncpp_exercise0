#include <thread>
#include <iostream>

int x = 0;

int main() {

	std::thread th1 = std::thread([&]() {//원본을 변경할려면 캡쳐본을 가져온다.
		
		for (int i = 0; i < 100000000; i++) {
			x += 1;
		}
		});
	
	std::thread th2 = std::thread([&]() {//원본을 변경할려면 캡쳐본을 가져온다.

		for (int i = 0; i < 100000000; i++) {
			x += 1;
		}
		});
	
	if (th1.joinable())
		th1.join();
	
	if (th2.joinable())
		th2.join();

	//2억이 안나오는 이유 ->원자성 
	//
	// 
	//


		std::cout << x << '\n';

	return 0;
}