#include <iostream>
#include <fstream>
using namespace std;
typedef struct node{
	int data;
	int rank;
	int parent;
}UFSTree;
void Make_set(UFSTree t[],int N){
	for (int i = 1; i <= N; i++){
		t[i].data = i;
		t[i].rank = 0;
		t[i].parent = i;
	}
}
int Find_set(UFSTree t[], int x){
	if (x != t[x].parent)
		return Find_set(t, t[x].parent);
	else
		return x;
}
void Union(UFSTree t[], int x, int y){
	x = Find_set(t, x);
	y = Find_set(t, y);
	if (t[x].rank > t[y].rank)
		t[y].parent = x;
	else{
		t[x].parent = y;
		if (t[x].rank == t[y].rank)
			t[y].rank++;
	}
}
int main(){
	UFSTree t[100];
	int N, M, Q;
	ifstream input("data.txt");
	input >> N >> M;
	Make_set(t, N);
	for (int i = 0; i < M; i++){
		int a, b;
		input >> a >> b;
		Union(t, a, b);
	}
	input >> Q;
	for (int i = 0; i < Q; i++){
		int a, b;
		input >> a >> b;
		if (Find_set(t, a) == Find_set(t, b))
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
	system("pause");
	return 0;
}
//data.txt
// 10 7
// 2 4
// 5 7
// 1 3
// 8 9
// 1 2
// 5 6
// 2 3
// 3
// 3 4
// 7 10
// 8 9
