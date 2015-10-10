//把一个字符串经过最少步数转为另一个字符串
//dp[i][j]表示第一个字符串的前i个字符要和第二个字符串的前j个字符匹配需要的最少操作次数
//初始化dp[i][0]=i,若第二个字符串为0，只好把第一个字符串全删掉，所以dp[i][0]=i
//同理，dp[0][j]=j
//状态转移方程：若s1[i-1]==s2[j-1],则不需要操作，那么dp[i][j]=dp[i-1][j-1]
//否则，我们可能有三步操作，删除，插入，变换，所以dp[i][j]=min(dp[i-1][j]+1,dp[i][j-1]+1,dp[i-1][j-1]+1)
//把删除和插入看作是一个操作，自然dp[i-1][j-1]+1对应的是变换了。
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <string>
using namespace std;
int dp[1010][1010];
string s1;
string s2;
int main()
{
	int l1, l2;
	while (cin >> s1>>s2)
	{
		l1 = (int)s1.size();
		l2 = (int)s2.size();
		for (int i = 0; i <= l1; i++)
			for (int j = 0; j <= l2; j++)
				dp[i][j] = 0;
		for (int i = 1; i <= l1; i++) dp[i][0] = i;
		for (int j = 1; j <= l2; j++) dp[0][j] = j;
		for (int i = 1; i <= l1; i++){
			for (int j = 1; j <= l2; j++)
			{
				if (s1[i - 1] == s2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
				else dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1), dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
			}
		}
		cout << dp[l1][l2] << endl;
	}
}
