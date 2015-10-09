#include <iostream>
using namespace std;
void swap(int &a,int &b){
	int temp=a;
	a=b;
	b=temp;
}
int Partition(int *array,int p,int r){
	int x=array[r];     //以最后一个作为主元(pivot element)
	int i=p-1;
	for(int j=p;j<r;++j){
		if(array[j]<x){
			i++;
			swap(array[i],array[j]);
		}
	}
	swap(array[r],array[i+1]);
	return i+1;
}
void QuickSort(int *array,int p,int r){
	if(p<r){
		int q=Partition(array,p,r);
		QuickSort(array,p,q-1);
		QuickSort(array,q+1,r);		
	}
}
int main(){
	int n;
	cout<<"input number:";cin>>n;
	int *array=new int[n+1];
	cout<<"input array:";
	for(int i=1;i<=n;++i)
		cin>>array[i];
	QuickSort(array,1,n);
	for(int i=1;i<=n;++i)
		cout<<array[i]<<" ";
	cout<<endl;
	delete[] array;
	return 0;
}