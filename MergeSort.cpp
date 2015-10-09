#include <iostream>  
using namespace std;
void merge(int *data, int p, int q, int r)
{
	int n1, n2, i, j, k;
	int *left = NULL, *right = NULL;
	n1 = q - p + 1;
	n2 = r - q;

	left = (int *)malloc(sizeof(int)*(n1));
	right = (int *)malloc(sizeof(int)*(n2));
	for (i = 0; i<n1; i++)  //�������鸳ֵ  
		left[i] = data[p + i];
	for (j = 0; j<n2; j++)  //�������鸳ֵ  
		right[j] = data[q + 1 + j];

	i = j = 0;
	k = p;
	while (i<n1 && j<n2) //������Ԫ��ֵ�����Ƚϣ����ϲ���data����  
	{
		if (left[i] <= right[j])
			data[k++] = left[i++];
		else
			data[k++] = right[j++];
	}

	for (; i<n1; i++) //�����������Ԫ��ʣ�࣬��ʣ��Ԫ�غϲ���data����  
		data[k++] = left[i];
	for (; j<n2; j++) //�����������Ԫ��ʣ�࣬��ʣ��Ԫ�غϲ���data����  
		data[k++] = right[j];
}

void mergeSort(int *data, int p, int r)
{
	int q;
	if (p < r) //ֻ��һ�����޼�¼ʱ��������   
	{
		q = (int)((p + r) / 2);      //��data����ֳ�����     
		mergeSort(data, p, q);   //�ݹ���������  
		mergeSort(data, q + 1, r); //�ݹ���������  
		merge(data, p, q, r);    //�ϲ�����  
	}
}
int main()
{
	int n;
	int* input = NULL;
	//��������      
	cout << "����������ĳ���: ";
	cin >> n;
	input = (int *)malloc(sizeof(int)*(n));
	cout << "������鸳ֵ: ";
	for (int i = 0; i<n; ++i)
	{
		cin >> input[i];
	}
	//��������      
	mergeSort(input, 0, n - 1);
	//������      
	for (int i = 0; i<n; ++i)
		cout << input[i] << " ";
	cout << endl;
	system("pause");
	return 0;
}