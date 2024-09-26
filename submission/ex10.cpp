#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

template<typename T>
class MyVector {
private:
    T* element;
    size_t capacity;
    size_t size;

public:
    // 기본 생성자
    MyVector() : element(nullptr), capacity(3), size(0) {}

    // 소멸자
    ~MyVector() {
        delete[] element;
    }

    // 복사생성자
    MyVector(const MyVector& other) : element(new T[other.capacity]), capacity(other.capacity), size(other.size) {
        std::copy(other.element, other.element + other.size, element);
    }

    // 복사대입생성자
    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            delete[] element;
            element = new T[other.capacity];
            capacity = other.capacity;
            size = other.size;
            std::copy(other.element, other.element + other.size, element);
        }
        return *this;
    }


    MyVector(MyVector&& other) noexcept : element(other.element), capacity(other.capacity), size(other.size) {
        other.element = nullptr;
        other.capacity = 0;
        other.size = 0;
    }

    MyVector& operator=(MyVector&& other) noexcept {
        if (this != &other) {
            delete[] element;
            element = other.element;
            capacity = other.capacity;
            size = other.size;

            other.element = nullptr;
            other.capacity = 0;
            other.size = 0;
        }
        return *this;
    }

    void push_back(const T& value) {
        if (element == nullptr || size >= capacity) {
            // 메모리 새로 할당
            capacity *= 2;
            T* newData = new T[capacity];
            // 기존에 있던 메모리의 값을 새로 할당된 곳에 복사
            /*for (std::size_t i = 0; i < size; i++) {
                newData[i] = data[i];
            }*/
            copy(element, element + size, newData); // 복사 함수를 사용

            // 복사를 다했으므로 기존 메모리는 해제한다.
            delete[] element;

            // 기존 포인터 대체
            element = newData;
        }
        element[size] = value;
        size++;

        //cout << "v.get_size() == " << size << "\n";
    }

    size_t size() const {
        return size;
    }

};

int main() {
    MyVector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    MyVector<int> v2 = std::move(v);

    std::cout << "v.get_size() = " << v.size() << "\n";
    std::cout << "v2.get_size() = " << v2.size() << "\n";

    return 0;
}