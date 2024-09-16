#include <iostream>
#include <memory>
#include <iostream>
#include <utility>

#ifdef _MSC_VER
#define MY_FUNCTION __FUNCSIG__ 
#else
#define MY_FUNCTION __PRETTY_FUNCTION__
#endif

int default_constructor_count = 0;
int copy_constructor_count = 0;
int move_constructor_count = 0;
int copy_assignnment_operator_count = 0;
int move_assignnment_operator_count = 0;
int destrucor_count = 0;


class MyApplication {
	public:
		MyApplication() {
			default_constructor_count++;
			std::cout << MY_FUNCTION << '\n';
		}

		MyApplication(const MyApplication&) {
			copy_constructor_count++;
			std::cout << MY_FUNCTION << '\n';
		}

		MyApplication(MyApplication&&) noexcept {
			move_constructor_count++;
			std::cout << MY_FUNCTION << '\n';
		}

		MyApplication& operator=(const MyApplication&) {
			copy_assignnment_operator_count++;
			std::cout << MY_FUNCTION << '\n';
			return *this;
		}

		MyApplication& operator=(MyApplication&&) noexcept {
			move_assignnment_operator_count++;
			std::cout << MY_FUNCTION << '\n';
			return *this;
		}

		~MyApplication() {
			destrucor_count++;
			std::cout << MY_FUNCTION << '\n';
		}
};


void TestUniquePtr() {
	// MyApplication 생성
	auto p = std::make_unique<MyApplication>();

	// MyApplication 유니크 포인터를 이동 시켰다. -> 그러면, MyApplication에서 정의한 이동생성자, 이동대입연산자가 호출되지 않는다. 
	auto p2 = std::move(p);
}

void TestSharedPtr() {
	// MyApplication 생성
	auto p = std::make_shared<MyApplication>();

	// std::shared_ptr의 복사 생성자 호출
	auto p2 = p;

	// p2 초기화
	p2.reset();

	// 약한 참조 객제 std::weak_ptr 생성.
	std::weak_ptr<MyApplication> weak_p = p;

	// auto::shared_ptr 반환
	auto lock = weak_p.lock();
	if (lock) {
		std::cout << "Acquired ownership\n";
	}
}


int main() {
	//MyApplication my_app;
	
	TestUniquePtr();
	std::cout << "기본 생성자 호출 횟수: " << default_constructor_count << "\n";
	std::cout << "복사 생성자 호출 횟수: " << copy_constructor_count << "\n";
	std::cout << "이동 생성자 호출 횟수: " << move_constructor_count << "\n";
	std::cout << "복사 대입 연산자 호출 횟수: " << copy_assignnment_operator_count << "\n";
	std::cout << "이동 대입 연산자 호출 횟수: " << move_assignnment_operator_count << "\n";
	std::cout << "소멸자 호출 횟수: " << destrucor_count << "\n";

	TestSharedPtr();
	std::cout << "기본 생성자 호출 횟수: " << default_constructor_count << "\n";
	std::cout << "복사 생성자 호출 횟수: " << copy_constructor_count << "\n";
	std::cout << "이동 생성자 호출 횟수: " << move_constructor_count << "\n";
	std::cout << "복사 대입 연산자 호출 횟수: " << copy_assignnment_operator_count << "\n";
	std::cout << "이동 대입 연산자 호출 횟수: " << move_assignnment_operator_count << "\n";
	std::cout << "소멸자 호출 횟수: " << destrucor_count << "\n";

	// 복사 생성자와 이동 생성자를 사용하는 것을 막고 싶을 때, 스마트 포인터를 쓰면된다. 
	return 0;
}
