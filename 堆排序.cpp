#include <iostream>
using namespace std;
void MaxHeapify(int *array,int length,int i){
	int left=i*2;
	int right=i*2+1;
	int largest=i;
	if(left<=length && array[left]>array[i])
		largest=left;
	else
		largest=i;
	if(right<=length && array[right]>array[largest])
		largest=right;
	if(largest!=i){
		int temp=array[largest];
		array[largest]=array[i];
		array[i]=temp;
		MaxHeapify(array,length,largest);
	}	
}
void BuildMaxHeap(int *array,int length){
	for(int i=length/2;i>=1;--i)
		MaxHeapify(array,length,i);	
}
void HeapSort(int *array,int length){
	BuildMaxHeap(array,length);
	for(int i=length;i>1;--i){
		int temp=array[1];
		array[1]=array[i];
		array[i]=temp;
		MaxHeapify(array,i-1,1);
	}
}
int main(){
	int n;
	cout<<"input number:";cin>>n;
	int *array=new int[n+1];
	cout<<"input array:";
	for(int i=1;i<=n;++i)
		cin>>array[i];
	HeapSort(array,n);
	for(int i=1;i<=n;++i)
		cout<<array[i]<<" ";
	cout<<endl;
	delete[] array;
	return 0;
}