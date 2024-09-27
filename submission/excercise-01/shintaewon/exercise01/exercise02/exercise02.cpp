#include <iostream>
#include <algorithm>
#include<vector>

using namespace std;

int main()
{
	//리스트 선언
	vector<int> nums_vec;

	int temp_num, a;
	bool flag = false;

	//뒤쪽으로 요소 추가하기
	for (int i = 0; i < 10; i++) {
		cin >> temp_num;
		nums_vec.push_back(temp_num);
	}
	cin >> a;

	auto it = find(nums_vec.begin(), nums_vec.end(), a);

	if (it != nums_vec.end()) { // vector내에 a 존재함
		cout << it - nums_vec.begin(); // index 확인
		flag = true;
	}
	
	sort(nums_vec.begin(), nums_vec.end());

	if (flag == false) {
		int cnt = 0;
		while (cnt < nums_vec.size()) {
			
			if (a < nums_vec[cnt]) {//a가 만약 인덱스보다 크다면?
				cout << nums_vec[cnt];
				flag = true;
				break;
			}
			else {
				cnt++;
			}
		}
	}

	if (flag == false) {
		cout << -1;
	}
}
