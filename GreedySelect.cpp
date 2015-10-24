//算法导论 第16章 贪心算法 活动选择 o(n)
#include <iostream>
#include <stdlib.h>
using namespace std;
int GreedySelect(int *s, int *f, int length, int *c) {
	int i = 1,j = 2;
	c[1] = 1;
	for (int m = 2;m <= length;++m) {
		if (s[m] >=f[i]) {
			c[j++] = m;
			i = m;
		}
	}
	return j;
}
int main() {
	int s[12] = { 0,1,3,0,5,3,5,6,8,8,2,12 };
	int f[12] = { 0,4,5,6,7,8,9,10,11,12,13,14 };
	int a[13];
	int i = GreedySelect(s, f, 11, a);
	for (int j = 1;j < i;j++)
		cout << a[j] << " ";
	cout << endl;
	system("pause");
	return 0;
}