/**********************************************************************************************//**
 * @file	SegmentTree.cpp
 *
 * Implements the segment tree class.
 **************************************************************************************************/

#include <iostream>
using namespace std;
typedef struct node{
	int i, j;
	int cover;
	struct node *lchild, *rchild;
}ITree;
//建立线段树
ITree* CreateTree(int a, int b){
	if (b < a) return NULL;
	ITree *r = new ITree;
	r->cover = 0; r->i = a; r->j = b;
	if (b - a>1){
		r->lchild = CreateTree(a, (a + b) / 2);
		r->rchild = CreateTree((a + b) / 2, b);
	}
	else
		r->lchild = r->rchild = NULL;
	return r;
}
//线段树的插入
void InsertTree(ITree *r, int a, int b){
	if (a <= r->i && r->j <= b)
		r->cover++;
	else{
		int mid = (r->i + r->j) / 2;
		if (b <= mid)
			InsertTree(r->lchild, a, b);
		else if (mid <= a)
			InsertTree(r->rchild, a, b);
		else{
			InsertTree(r->lchild, a, mid);
			InsertTree(r->rchild, mid, b);
		}
	}
}
//线段树删除
void DelTree(ITree *r, int a, int b){
	if (a <= r->i && r->j <= b)
		r->cover--;
	else{
		int mid = (r->i + r->j) / 2;
		if (b <= mid)
			DelTree(r->lchild, a, b);
		else if (mid <= a)
			DelTree(r->rchild, a, b);
		else{
			DelTree(r->lchild, a, mid);
			DelTree(r->rchild, mid, b);
		}
	}
}
int Count(ITree *r){
	if (r->cover > 0)
		return (r->j - r->i);
	else if (r->j - r->i == 1)
		return 0;
	else
		return Count(r->lchild) + Count(r->rchild);
	
}
void fun(){
	ITree *r = new ITree;
	r = CreateTree(1, 10);
	InsertTree(r, 3, 6);
	InsertTree(r, 7, 9);
	cout << "Count=" << Count(r) << endl;
	DelTree(r,7, 9);
	cout << "Count=" << Count(r) << endl;
}
