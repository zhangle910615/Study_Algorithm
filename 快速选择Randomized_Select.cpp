#include <iostream>
#include <random>
using namespace std;
int Random(int p,int r){
	uniform_int_distribution<unsigned> u(p,r);
	default_random_engine e;
	return u(e);
}
int Randomized_Partition(int *array,int p,int r){
	swap(array[Random(p,r)], array[r]);
	int x = array[r];
	int i = p - 1;
	for (int j = p; j < r; ++j){
		if (array[j] < x){
			i++;
			swap(array[i], array[j]);
		}
	}
	swap(array[i + 1], array[r]);
	return i + 1;
}
int Randomized_Select(int *array, int p, int r, int i){
	if (p == r)
		return array[p];
	int q = Randomized_Partition(array, p, r);
	int k = q - p + 1;
	if (k == i)
		return array[q];
	else if (k > i)
		return Randomized_Select(array, p, q - 1, i);
	else
		return Randomized_Select(array, q + 1, r, i-k);
}
int main(){
	int n;
	cout << "input number:";
	cin >> n;
	cout << "input array:";
	int *array = new int[n+1];
	for (int i = 1; i <= n; i++)
		cin >> array[i];
	cout << "which:";
	int k; cin >> k;
	cout << "the " << k << "th is:" << Randomized_Select(array, 1, n, k) << endl;

	delete[] array;
	system("pause");
	return 0;
}