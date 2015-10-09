#include <iostream>
using namespace std;
int main(){
	int n;
	while(cin>>n){
		if(n==0) return 0;
		int *array=new int[n];
		for(int i=0;i<n;++i)
			cin>>array[i];
		int sum=0,max=-999999;
		int start=array[0];
		int end=array[0];
		int k=start;
		for(int i=0;i<n;++i){
			sum+=array[i];
			if(sum>max){
				max=sum;
				end=array[i];
				start=k;
			}
			if(sum<0){
				sum=0;
				if(i<n-1)
					k=array[i+1];
			}				
		}
		if(max<0)
			cout<<0<<" "<<array[0]<<" "<<array[n-1]<<endl;
		else
			cout<<max<<" "<<start<<" "<<end<<endl;
		delete[] array;
	}
	return 0;
}