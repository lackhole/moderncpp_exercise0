#include <iostream>
using namespace std;

class MyBaseClass {
public:
	virtual void Hello() {
		cout << "This is Base\n";
	}
};

class MyDerivedClass : public MyBaseClass {
public:
	void Hello() {
		cout << "This is Derived\n";
	}
};

int main() {
	std::unique_ptr<MyBaseClass> p = std::make_unique<MyDerivedClass>();
	p->Hello();

	return 0;
}
