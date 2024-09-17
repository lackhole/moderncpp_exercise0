#include <iostream>
#include <list>

using namespace std;

list<int> lst;
int n, a, b;

int main()
{

	for (int i = 0; i < 10; i++) {
		cin >> n;
		lst.push_back(n);
	}
	cin >> a >> b;


	//list<int>::iterator iter = lst.begin();

	lst.remove_if([&](int x) { return x > a && x <= b; });

	for (int num : lst) {
		cout << num << " ";
	}

	return 0;
}