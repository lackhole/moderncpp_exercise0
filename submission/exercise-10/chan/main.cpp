#include <iostream>
#include <cstdint>
#include <algorithm>

using namespace std;

template<typename T>
class MyVector {
public:
    MyVector(const int& size = 3) {
        data_ = new T[size];
        capacity_ = size;
        size_ = 0;
    }

    MyVector(const MyVector& t) : capacity_(t.capacity_), size_(t.size_) {
        data_ = new T[capacity_];
        copy(t.data_, t.data_ + t.size, data_);
    }

    MyVector(MyVector&& t) noexcept : capacity_(t.capacity_), size_(t.size_), data_(t.data_) {
        t.data_ = nullptr;
        t.size_ = 0;
        t.capacity_ = 0;
    }

    MyVector& operator=(const MyVector& t) {
        
        capacity_ = t.capacity_;
        size_ = t.size_;
        delete[] data_;
        
        data_ = new T[capacity_];
        copy(t.data_, t.data_ + t.size, data_);

        return *this;
    }

    MyVector& operator=(MyVector&& t) noexcept {

            delete[] data_;
            data_ = t.data_;
            capacity_ = t.capacity_;
            size_ = t.size_;

            t.data_ = nullptr;
            t.data_ = 0;
            t.capacity_ = 0;
        
        return *this;
    }

    ~MyVector() { delete[] data_; }

    void push_back(const T& data) {
        if (size_ >= capacity_) {
            // 용량 늘리기
            capacity_ = capacity_ * 2;
            // 메모리 새로 할당
            T* new_data = new T[capacity_];

            // 기존 데이터 복사
            copy(data_, data_ + size_, new_data);

            // 기존 메모리 해제
            delete[] data_;

            // 기존 포인터 대체
            data_ = new_data;
        }

        data_[size_] = data;
        size_++;
    }

    void pop_back(const T& data) {
        size_ = size_ > 0 ? size_ - 1 : 0;
    }

    /* return-type */
    T& operator[](size_t i) { return data_[i]; }

    const T& operator[](size_t i) const { return data_[i]; }

    size_t size() const { return size_; }

private:
    T* data_;
    size_t size_;
    size_t capacity_;
    // Define other member variables if necessary
};


// Use case
int main() {

    {
        MyVector<int> v;

        v.push_back(1); // v.size() == 1
        cout << v.size() << "\n";
        v.push_back(2); // v.size() == 2
        cout << v.size() << "\n";
        v.push_back(3); // v.size() == 3
        cout << v.size() << "\n";
        v.push_back(4); // v.size() == 4
        cout << v.size() << "\n";
        v.push_back(5); // v.size() == 5
        cout << v.size() << "\n\n";

        MyVector<int> v2 = move(v);

        cout << v2.size() << "\n";
        cout << v.size() << "\n";
        
    } // v 소멸


    return 0;
}