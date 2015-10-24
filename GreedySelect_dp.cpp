//算法导论 第16章 贪心算法 活动选择
//动态规划解决方法  时间复杂度o(n^3)
#include <iostream>
#include <stdlib.h>
using namespace std;
#define N 11
void dynamic_activity_selector(int *s, int *f, int c[N + 1][N + 1], int ret[N + 1][N + 1]) {
	int i, j, k;
	int temp;
	for (int j = 1;j <= N;j++)
		for (i = j;i <= N;i++)
			c[i][j] = 0;
	for (j = 2;j <= N;j++) {
		for (i = 1;i < j;i++) {
			for (k = i + 1;k < j;k++) {
				if (s[k] >= f[i] && f[k] <= s[j]) {
					temp = c[i][k] + c[k][j] + 1;
					if (c[i][j] < temp) {
						c[i][j] = temp;
						ret[i][j] = k;
					}
				}
			}
		}
	}
}
void trace_route(int ret[N + 1][N + 1], int i, int j) {
	if (i < j) {
		trace_route(ret, i, ret[i][j]);
		if (ret[i][j] != 0)
			printf("a%d ", ret[i][j]);
//		trace_route(ret, ret[i][j], j);
	}
}
int main() {
	int s[N + 1] = { -1,1,3,0,5,3,5,6,8,8,2,12 };
	int f[N + 1] = { -1,4,5,6,7,8,9,10,11,12,13,14 };
	int c[N + 1][N + 1] = { 0 };
	int ret[N + 1][N + 1] = { 0 };
	int i, j;
	dynamic_activity_selector(s, f, c, ret);
	printf("c[i][j]的值如下所示：\n");
	for (i = 1;i <= N;i++){
		for (j = 1;j <= N;j++)
		      printf("%d ", c[i][j]);
	    printf("\n");
	}
	printf("最大子集的个数为: %d\n", c[1][N] + 2);
	printf("ret[i][j]的值如下所示：\n");
	for (i = 1;i <= N;i++){
		for (j = 1;j <= N;j++)
			 printf("%d ", ret[i][j]);
		 printf("\n");
	}
	printf("最大子集为:{ a1 ");
	trace_route(ret, 1, N);
	printf("a%d}\n", N);

	system("pause");
	return 0;
}