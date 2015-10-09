#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
void swap(int &a, int &b){
	int temp = a;
	a = b;
	b = temp;
}
void insertsort(int a[], int n){
	for (int i = 1; i < n; ++i){
		int t = a[i];
		for (int j = i - 1; j >= 0; --j){
			if (a[j]>t){
				swap(a[j], a[j + 1]);
			}
			else
				break;
		}
		cout << "µÚ" <<i<<"´Î:";
		for (auto k = 0; k < n; k++)
			cout << a[k] << " ";
		cout << endl;
	}
}
int main(){
	int a[6] = { 8, 2, 4, 9, 3, 6 };
	for (auto i : a)
		cout << i << " ";
	cout << endl;
	insertsort(a, 6);
	for (auto i : a)
		cout << i << " ";
	cout << endl;
	system("pause");
	return 0;
}