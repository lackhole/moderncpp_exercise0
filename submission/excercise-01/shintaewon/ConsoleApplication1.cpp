#include <iostream>
#include<list>

using namespace std;

int main()
{
	//리스트 선언
	list<int> nums_list;

	int temp_num, a, b;

	//뒤쪽으로 요소 추가하기
	for (int i = 0; i < 10; i++) {
		cin >> temp_num;
		nums_list.push_back(temp_num);
	}

	cin >> a >> b;

	int bigger = max(a, b);
	int smaller = min(a, b);

	auto it1 = find(nums_list.begin(), nums_list.end(), smaller+1);

	auto it2 = find(nums_list.begin(), nums_list.end(), bigger+1);
	nums_list.erase(it1, it2);

	copy(nums_list.begin(), nums_list.end(), ostream_iterator<int>(cout, " "));
}
