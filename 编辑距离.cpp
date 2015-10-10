//��һ���ַ����������ٲ���תΪ��һ���ַ���
//dp[i][j]��ʾ��һ���ַ�����ǰi���ַ�Ҫ�͵ڶ����ַ�����ǰj���ַ�ƥ����Ҫ�����ٲ�������
//��ʼ��dp[i][0]=i,���ڶ����ַ���Ϊ0��ֻ�ðѵ�һ���ַ���ȫɾ��������dp[i][0]=i
//ͬ��dp[0][j]=j
//״̬ת�Ʒ��̣���s1[i-1]==s2[j-1],����Ҫ��������ôdp[i][j]=dp[i-1][j-1]
//�������ǿ���������������ɾ�������룬�任������dp[i][j]=min(dp[i-1][j]+1,dp[i][j-1]+1,dp[i-1][j-1]+1)
//��ɾ���Ͳ��뿴����һ����������Ȼdp[i-1][j-1]+1��Ӧ���Ǳ任�ˡ�
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
