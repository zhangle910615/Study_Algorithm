#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

int main(){
	vector<int> nums;

	nums.push_back(1);
	nums.push_back(1);
	nums.push_back(2);
	nums.push_back(3);
	nums.push_back(3);
	nums.push_back(4);
	nums.push_back(4);

	int n1 = 0;
	vector<int>::iterator it = nums.begin();
	for (; it != nums.end() ; it++){
		n1 ^= *it;
	}
	cout << n1 << endl;
	system("pause");
	return 0;
}