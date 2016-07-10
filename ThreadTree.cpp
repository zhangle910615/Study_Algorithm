/**********************************************************************************************//**
 * @file	ThreadTree.cpp
 * @author	zhangle
 * @date	7/9/2016
 * Implements the InOrder thread tree class.
 **************************************************************************************************/

#include <iostream>
using namespace std;
using ElemType = char;
typedef struct node{
	ElemType data;
	int ltag, rtag;
	struct node *lchild,*rchild;
}TBTNode;
TBTNode *pre;
// 对二叉树进行中序线索化
void Thread(TBTNode *&p){
	if (p != NULL){
		Thread(p->lchild);
		if (p->lchild == NULL){
			p->lchild = pre;
			p->ltag = 1;
		}
		else{
			p->ltag = 0;
		}
		if (pre->rchild == NULL){
			pre->rchild = p;
			pre->rtag = 1;
		}
		else
			pre->rtag = 0;
		pre = p;
		Thread(p->rchild);
	}
}
TBTNode *CreateThread(TBTNode *b){
	TBTNode *root;
	root = new TBTNode;
	root->ltag = 0; root->rtag = 1;
	root->rchild = b;
	if (b == NULL)
		root->lchild = root;
	else{
		root->lchild = b;
		pre = root;
		Thread(b);
		pre->rchild = root;
		pre->rtag = 1;
		root->rtag = 1;
		root->rchild = pre;
	}
	return root;
}
void ThInOrder(TBTNode *tb){
	TBTNode *p = tb->lchild;
	while (p != tb){
		while (p->ltag == 0)
			p = p->lchild;
		cout << p->data;
		while (p->rtag = 1 && p->rchild != tb){
			p = p->rchild;
			cout << p->data;
		}
		p = p->rchild;
	}
}