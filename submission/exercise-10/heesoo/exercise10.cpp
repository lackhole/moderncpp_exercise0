#include <iostream>
#include <cstdint>


#ifdef _MSC_VER
#define MY_FUNCTION__ __FUNCSIG__
#else
#define MY_FUNCTION__ __PRETTY_FUNCTION__
#endif




class MyApplication {
public:
	MyApplication() {
		std::cout << MY_FUNCTION << '\n';
	}

	MyApplication(const MyApplication&) {
		std::cout << MY_FUNCTION << '\n';

	}

	MyApplication(MyApplication&&) noexcept {
		std::cout << MY_FUNCTION << '\n';

	}

	MyApplication& operator = (const MyApplication&) {
		std::cout << MY_FUNCTION << '\n';
		return *this;
	}

	MyApplication& operator = (MyApplication&&) noexcept {
		std::cout << MY_FUNCTION << '\n';
		return *this;
	}

	MyApplication() {
		std::cout << MY_FUNCTION << '\n';

		//소멸자
	}


};

template<typename T>
class MyVector {
public:
	MyVector()
		: data_(nullptr),
		capacity_(3),
		size_(0)
	{
		data_ = new T[capacity_];
	}

	MyVector(const MyVector& other)
		: capacity_(other.capacity_),
		size_(other.size_)
	{
		data_ = new T[capacity_];
		std::copy(other.data_, other.data_ + other.size, data_);
	}

	MyVector& operator = (const MyVector& other) {
		capacity_ = other.capacity_;
		size_other.size_;
		delete[] data_;

		data_ = new T[capacity_];
		std::copy(other.data_, other.data_ + other.size_, data_);
	}

	MyVector(MyVector&& other) noexcept
		: capacity_(other.capacity_),
		size(other.size_),
		data_(other.data_)
	{
		other.data_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	}

	~MyVector() {
		delete[] data_;
	}

	void push_back(const T& data) {
		if (size_ >= capacity_) {
			// 용량 늘리기
			capacity_ = capacity_ * 2;

			// 메모리 새로 할당
			T* new_data = new T[capacity_];

			// 기존 메모리 복사
			std::copy(data_, data_ + size_, new_data);

			// 기존 메모리 해제
			delete[] data_;

			// 기존 포인터 대체
			data_ = new_data
		}

		data_[size_] = data;
		size += 1;
	}

	void pop_back() {
		if (size_ > 0) {
			size -= 1;
			// data_[size_].~T();
		}
	}

	std::size_t size() const {
		return size_;
	}

	T& operator[](std::size_t index) {
		return data_[index];
	}

	const T& operator[](std::size_t index) const {
		return data_[index];
	}

	std::size_t size() const {
		return size_;
	}

private:
	T* data_;
	std::size_t capacity_;
	std::size_t size_;


};


int main() {

	std::vector<MyApplication> v;

	for (int i = 0; i < 10; i++) {
		v.
	}

	MyApplication a;
	MyApplication b = a;


	return 0;
}







