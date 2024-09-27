#include <iostream>

#ifdef _MSC_VER
#define MY_FUNCTION __FUNCSIG__ 
#else
#define MY_FUNCTION __PRETTY_FUNCTION__
#endif

int default_constructor_count = 0;
int copy_constructor_count = 0;
int move_constructor_count = 0;
int copy_assign_operator_count = 0;
int move_assign_operator_Count = 0;
int destructor_count = 0;
class MyApplication {
 public:
	 MyApplication() {
		 std::cout << MY_FUNCTION << '\n';
         default_constructor_count +=1;
	 }

	 MyApplication(const MyApplication&) {
		 std::cout << MY_FUNCTION << '\n';
         copy_constructor_count += 1;
	 }

	 MyApplication(MyApplication&&) noexcept {
		 std::cout << MY_FUNCTION << '\n';
         move_constructor_count += 1;
	 }

	 MyApplication& operator=(const MyApplication&) {
		 std::cout << MY_FUNCTION << '\n';
         copy_assign_operator_count += 1;
		 return *this;
	 }

	 MyApplication& operator=(MyApplication&&) noexcept  {
		 std::cout << MY_FUNCTION << '\n';
         move_assign_operator_Count += 1;
		 return *this;
	 }

	 ~MyApplication() {
        destructor_count += 1;
		 std::cout << MY_FUNCTION << '\n';
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

  // sharedptr의 복사생성자 호출
  auto p2 = p;

  // p2 초기화
  p2.reset();

  // 약한 참조 객체 weak_ptr생성 (약한소유권)
  std::weak_ptr<MyApplication> weak_p = p;

  // shared_ptr반환
  auto lock = weak_p.lock();
  if (lock) {
    std::cout << "Acquired ownership\n";
  }
}

int main() {
	// print: MyApplication::MyApplication()
	MyApplication a;

	// print: MyApplication::MyApplication(const MyApplication&)
	MyApplication b = a;


	// print: MyApplication::~MyApplication()   (b destroyed)
	// print: MyApplication::~MyApplication()   (a destroyed)
	return 0;
}