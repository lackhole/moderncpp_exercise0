#include <memory>
#include <iostream>
#include <utility>

int default_constructor_count = 0;
int copy_constructor_count = 0;
int move_constructor_count = 0;
int copy_assignment_count = 0;
int move_assignment_count = 0;
int desctructor_count = 0;

class MyApplication {
    public:
        MyApplication() {
            std::cout << __PRETTY_FUNCTION__ << '\n';
            default_constructor_count += 1;
        }

        MyApplication(const MyApplication&) {
            std::cout << __PRETTY_FUNCTION__ << '\n';
            copy_constructor_count += 1;
        }

        MyApplication(MyApplication&&) noexcept {
            std::cout << __PRETTY_FUNCTION__ << '\n';
            copy_assignment_count += 1;
        }

        MyApplication& operator=(const MyApplication&) {
            std::cout << __PRETTY_FUNCTION__ << '\n';
            move_constructor_count += 1;
            return *this;
        }

        MyApplication& operator=(MyApplication&&) noexcept  {
            std::cout << __PRETTY_FUNCTION__ << '\n';
            move_assignment_count += 1;
            return *this;
        }

        ~MyApplication() {
            std::cout << __PRETTY_FUNCTION__ << '\n';
            desctructor_count += 1;
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
    std::cout << "기본 생성자 호출 횟수: " << default_constructor_count << "\n";
    std::cout << "복사 생성자 호출 횟수: " << copy_constructor_count << "\n";
    std::cout << "이동 생성자 호출 횟수: " << move_constructor_count << "\n";
    std::cout << "복사 대입 연산자 호출 횟수: " << copy_assignment_count << "\n";
    std::cout << "이동 대입 연산자 호출 횟수: " << move_assignment_count << "\n";
    std::cout << "소멸자 호출 횟수: " << desctructor_count << "\n";

    TestSharedPtr();
    std::cout << "기본 생성자 호출 횟수: " << default_constructor_count << "\n";
    std::cout << "복사 생성자 호출 횟수: " << copy_constructor_count << "\n";
    std::cout << "이동 생성자 호출 횟수: " << move_constructor_count << "\n";
    std::cout << "복사 대입 연산자 호출 횟수: " << copy_assignment_count << "\n";
    std::cout << "이동 대입 연산자 호출 횟수: " << move_assignment_count << "\n";
    std::cout << "소멸자 호출 횟수: " << desctructor_count << "\n";

    return 0;
}