#include <iostream>
#include <cstdint>
#include <algorithm>

using namespace std;

template<typename T>
class MyVector {
private:
    T* data;
    std::size_t size;
    std::size_t capacity;

public:
    // 생성자
    MyVector() : data(nullptr), size(0), capacity(3) {
        data = new T[capacity]; // 동적메모리 할당
    }

    // 소멸자 
    ~MyVector() {
        delete[] data; // 동적메모리 해제
    }

    T& operator[](std::size_t i) {
        if (i < size) {
            return data[i];
        }
        throw std::out_of_range("Invalid index");
    }

    void push_back(const T& value) {
        if (size >= capacity) {
            // 메모리 새로 할당
            capacity *= 2;
            T* newData = new T[capacity];
            // 기존에 있던 메모리의 값을 새로 할당된 곳에 복사
            /*for (std::size_t i = 0; i < size; i++) {
                newData[i] = data[i];
            }*/
            copy(data, data + size, newData); // 복사 함수를 사용

            // 복사를 다했으므로 기존 메모리는 해제한다.
            delete[] data;

            // 기존 포인터 대체
            data = newData;
        }
        data[size] = value;
        size++;

        size_t c_size = get_size();
        cout << "v.get_size() == " << c_size << "\n";
    }

    void pop_back() {
        if (size > 0) {
            size--;
        }
    }

    size_t get_size() const {
        return size;
    }

    T& at(size_t index) {
        if (index >= 0 && index < size) {
            return data[index];
        }
        throw out_of_range("Invalid index");
    }
};

int main() {
    MyVector<int> v;

    v.push_back(1); // v.get_size() == 1
    v.push_back(2); // v.get_size() == 2
    v.push_back(3); // v.get_size() == 3
    v.push_back(4); // v.get_size() == 4
    v.push_back(5); // v.get_size() == 5

    return 0;
}