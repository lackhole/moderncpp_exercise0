#include <iostream>
#include <memory>
#include <utility>

//#ifdef _MSC_VER
//#define MY_FUNCTION __FUNCSIG__
//#else
//#define MY_FUNCTION __FUNCSIG__
//#endif
using namespace std;
/*
* exercise-13.cpp
*
* by jekim
* 2023-12-18
*/


int default_constructor_count = 0;
int copy_constructor_count = 0;
int move_constructor_count = 0;
int copy_assignment_count = 0;
int move_assignment_count = 0;
int destructor_count = 0;

class MyApplication {
public:
	// default constructor
	MyApplication() {
		//cout << MY_FUNCTION << '\n'; 
		++default_constructor_count;
	}

	// copy constructor
	MyApplication(const MyApplication& r) { 
		//cout << MY_FUNCTION << '\n'; 
		++copy_constructor_count;
	}

	// move constructor
	MyApplication(MyApplication&& other) noexcept {
		//cout << MY_FUNCTION << '\n'; 
		++move_constructor_count;
	}

	// copy assignment operator
	MyApplication& operator=(const MyApplication& other) {
		//cout << MY_FUNCTION << '\n';
		++copy_assignment_count;
		return *this;
	}

	// move assignment operator
	MyApplication& operator=(MyApplication&& other) noexcept {
		//cout << MY_FUNCTION << '\n';
		++move_assignment_count;
		return *this;
	}

	//destructor
	~MyApplication() { 
		//cout << MY_FUNCTION << '\n'; 
		++destructor_count;
	}
};

void TestUniquePtr() {
	// MyApplication 생성 -> default constructor 호출 O
	auto p = make_unique<MyApplication>();

	// MyApplication 이동 -> unique_ptr 을 이동시킨 것이기 때문에 move constructor 호출 X
	auto p2 = move(p);
}

void TestSharedPtr() {
	// MyApplication 생성 -> default constructor 호출 O
	auto p = make_shared<MyApplication>();
	
	// shared_ptr의 복사 생성자 호출 -> shared_ptr을 복사한 것일 뿐 copy constructor 호출 X
	auto p2 = p;

    // p2 초기화
	p2.reset();

    // 순환 참조 방지를 위한 weak_ptr, 소유는 나중에 얻을 수 있음
    // 약한 참조 객체 weak_ptr 생성
	weak_ptr<MyApplication> weak_p = p;

    // shared_ptr 반환
	auto lock = weak_p.lock();

    // p가 아직 해제되지 않았기 때문에 if문 진입
	if (lock)
		cout << "Acquired ownership\n";
}


int main() {
	cout << "#### TestUniquePtr() \n";
	TestUniquePtr();
	std::cout << "기본 생성자 호출 횟수: " << default_constructor_count << '\n';
	std::cout << "복사 생성자 호출 횟수: " << copy_constructor_count << '\n';
	std::cout << "이동 생성자 호출 횟수: " << move_constructor_count << '\n';
	std::cout << "복사 대입 연산자 호출 횟수: " << copy_assignment_count << '\n';
	std::cout << "이동 대입 연산자 호출 횟수: " << move_assignment_count << '\n';
	std::cout << "소멸자 호출 횟수: " << destructor_count << '\n';

	cout << "#### TestSharedPtr() \n";
	TestSharedPtr();
	std::cout << "기본 생성자 호출 횟수: " << default_constructor_count << '\n';
	std::cout << "복사 생성자 호출 횟수: " << copy_constructor_count << '\n';
	std::cout << "이동 생성자 호출 횟수: " << move_constructor_count << '\n';
	std::cout << "복사 대입 연산자 호출 횟수: " << copy_assignment_count << '\n';
	std::cout << "이동 대입 연산자 호출 횟수: " << move_assignment_count << '\n';
	std::cout << "소멸자 호출 횟수: " << destructor_count << '\n';

	return 0;
}