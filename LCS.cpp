//算法导论最长公共子序列问题

#include<iostream>
#include<cstring>
using namespace std;

int c[100][100]; // c[i][j]表示序列S1前i个元素和S2的前j个元素的LCS
int b[100][100]; //便于求解最优解

void LCS_Length(char x[], char y[]);
void Print_LCS(char x[], int i, int j);

int main()
{
	char X[100], Y[100];

	while (cin >> X >> Y)
	{
		LCS_Length(X, Y);
		Print_LCS(X, strlen(X), strlen(Y));
		cout << endl;
	}
	return 0;
}

void LCS_Length(char x[], char y[])
{  
	int m = strlen(x);
	int n = strlen(y);
	for (int i = 0; i <= m; i++)
		c[i][0] = 0;
	for (int i = 0; i <= n; i++)
		c[0][i] = 0;

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (x[i] == y[j])
			{
				c[i + 1][j + 1] = c[i][j] + 1;
				b[i + 1][j + 1] = 0;
			}
			else if (c[i][j + 1] >= c[i + 1][j])
			{
				c[i + 1][j + 1] = c[i][j + 1];
				b[i + 1][j + 1] = 1;
			}
			else
			{
				c[i + 1][j + 1] = c[i + 1][j];
				b[i + 1][j + 1] = 2;
			}
		}
	}
}

void Print_LCS(char x[], int i, int j)
{
	if ((i == 0) || (j == 0))
		return;
	if (b[i][j] == 0)
	{
		Print_LCS(x, i - 1, j - 1);
		cout << x[i - 1] << ' ';
	}
	else if (b[i][j] == 1)
		Print_LCS(x, i - 1, j);
	else
		Print_LCS(x, i, j - 1);
}
