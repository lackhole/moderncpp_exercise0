#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class MyVector {
    public:
        MyVector(): capacity_(3), size_(0){
            data_ = new T[3];
        }
        ~MyVector(){
            delete[] data_;
        }
        T operator[](std::size_t i){
            if (i<size_)
                return data_[i];
            else
                return (T)-1;
        }

        const T operator[](std::size_t i) const{
            if (i<size_)
                return data_[std::move(i)];
            else
                return (T)-1;
        }
        void push_back(T n){
            if (size_ == capacity_-1){
                capacity_ *= 2;
                T* temp = new T[capacity_];
                std::copy(data_,data_+(int)size_,temp);
                delete[] data_;
                data_ = temp;
            }
            data_[size_] = n;
            size_++;
        }
        
        void pop_back(){
            size_--;
        }

        std::size_t size() const {
            return size_;
        }

        MyVector(const MyVector& other) 
                : capacity_(other.capacity_),
                size_(other.size_)
        {
            data_ = new T[capacity_];
            std::copy(other,other+(int)size_,data_);
        }
        MyVector(MyVector&& other) {
            std::cout << "rvalue" << std::endl;
            capacity_ = other.capacity_;
            size_ = other.size_;
            data_ = other.data_;
            other.capacity_ = 0;
            other.size_ = 0;
            other.data_ = nullptr;
        }
        MyVector& operator=(const MyVector& other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = new T[capacity_];
        std::copy(other,other+(int)size_,data_);
        return *this;
        }

        MyVector& operator=(MyVector&& other) { 
            std::cout << "rvalue = " << std::endl;
            capacity_ = other.capacity_;
            size_ = other.size_;
            data_ = other.data_;
            other.capacity_ = 0;
            other.size_ = 0;
            other.data_ = nullptr;
            return *this;
        }
    private:
        T* data_;
        int capacity_;
        size_t size_;
    
  
    
  
};


// Use case
int main() {

  {
    MyVector<int> v;
    
    v.push_back(1); // v.size() == 1
    v.push_back(2); // v.size() == 2
    v.push_back(3); // v.size() == 3
    v.push_back(4); // v.size() == 4
    v.push_back(5); // v.size() == 5
    
    
    MyVector<int> v2 = std::move(v);
    v = std::move(v2);

    std::cout << v.size() << std::endl;
    std::cout << v2.size() << std::endl;
    // v2.size() == 5 
    // v.size() == 0
    
  } // v, v2 소멸


  return 0;
}