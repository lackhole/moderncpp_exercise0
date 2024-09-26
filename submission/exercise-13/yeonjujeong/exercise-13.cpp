#include <memory>
#include <iostream>
#include <utility>
using namespace std;

#ifdef _MSC_VER
#define MY_FUNC __FUNCSIG__
#else
#define MY_FUNC __PRETTY_FUNCTION__
#endif

int default_constructor_count = 0;
int copy_constructor_count = 0;
int move_constructor_count = 0;
int copy_operate_count = 0;
int move_operate_count = 0;
int destroy_count = 0;

class MyApplication {
public:
    MyApplication() {
        ++default_constructor_count;
        cout << MY_FUNC << '\n';
    }

    MyApplication(const MyApplication&) {
        ++copy_constructor_count;
        cout << MY_FUNC << '\n';
    }

    MyApplication(MyApplication&&) noexcept {
        ++move_constructor_count;
        cout << MY_FUNC << '\n';
    }

    MyApplication operator = (const MyApplication&) {
        ++copy_operate_count;
        cout << MY_FUNC << '\n';
        return *this;
    }

    MyApplication& operator = (MyApplication&&) {
        ++move_operate_count;
        cout << MY_FUNC << '\n';
        return *this;
    }

    ~MyApplication() {
        ++destroy_count;
        cout << MY_FUNC << '\n';
    }
};

void TestUniquePtr() {
    // MyApplication 생성
    auto p = std::make_unique<MyApplication>();

    // MyApplication 이동
    auto p2 = std::move(p);
}

void TestSharedPtr() {
    // MyApplication 생성
    auto p = std::make_shared<MyApplication>();

    // ?
    auto p2 = p;

    // p2 초기화
    p2.reset();

    // ?
    std::weak_ptr<MyApplication> weak_p = p;

    auto lock = weak_p.lock();
    if (lock) {
        std::cout << "Acquired ownership\n";
    }
}

int main() {
    TestUniquePtr();
    std::cout << "기본 생성자 호출 횟수: " << default_constructor_count << '\n';
    std::cout << "복사 생성자 호출 횟수: " << copy_constructor_count << '\n';
    std::cout << "이동 생성자 호출 횟수: " << move_constructor_count << '\n';
    std::cout << "복사 대입 연산자 호출 횟수: " << copy_operate_count << '\n';
    std::cout << "이동 대입 연산자 호출 횟수: " << move_operate_count << '\n';
    std::cout << "소멸자 호출 횟수: " << destroy_count << '\n';

    TestSharedPtr();
    std::cout << "기본 생성자 호출 횟수: " << default_constructor_count << '\n';
    std::cout << "복사 생성자 호출 횟수: " << copy_constructor_count << '\n';
    std::cout << "이동 생성자 호출 횟수: " << move_constructor_count << '\n';
    std::cout << "복사 대입 연산자 호출 횟수: " << copy_operate_count << '\n';
    std::cout << "이동 대입 연산자 호출 횟수: " << move_operate_count << '\n';
    std::cout << "소멸자 호출 횟수: " << destroy_count << '\n';

    return 0;
}


