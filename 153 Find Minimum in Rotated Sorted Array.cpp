#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
	vector<int> nums;
	nums.push_back(5);
	nums.push_back(6);
	nums.push_back(7);
	nums.push_back(8);
	nums.push_back(9);
	nums.push_back(2);
	nums.push_back(3);
	int len = nums.size();
	if (len == 1) return nums[0];
	int left = 0, right = len - 1;
	while (nums[left] > nums[right]) { // good idea  
		int mid = (left + right) / 2;
		if (nums[mid] > nums[right]) {
			left = mid + 1;
		}
		else {
			right = mid; // be careful, not mid-1, as num[mid] maybe the minimum  
		}
	}
	cout << nums[left] << endl;
	system("pause");
	return 0;
}