#include <iostream>
#include <string>
using namespace std;
struct Node{
	char data;
	struct Node *left, *right;
};
void BuildTree(Node *&T){
	char ch;
	cin >> ch;
	if (ch == '#') T = NULL;
	else{
		T = new Node;
		T->data = ch;
		BuildTree(T->left);
		BuildTree(T->right);
	}
}
void PreOrder(Node *T){
	if (T != NULL){
		cout << T->data;
		PreOrder(T->left);
		PreOrder(T->right);
	}
}
void InOrder(Node *T){
	if (T != NULL){
		InOrder(T->left);
		cout << T->data;
		InOrder(T->right);
	}
}
void PostOrder(Node *T){
	if (T != NULL){
		PostOrder(T->left);
		PostOrder(T->right);
		cout << T->data;
	}
}
int Height(Node *T){
	int h1, h2;
	if (T == NULL) return 0;
	else{
		h1 = Height(T->left);
		h2 = Height(T->right);
		if (h1 > h2) return h1 + 1;
		else
			return h2 + 1;
	}
}
int num[100];
void levcount(Node *T, int L, int num[]){
	if (T){
		num[L]++;
		levcount(T->left, L + 1, num);
		levcount(T->right, L + 1, num);
	}
}
Node *CopyTree(Node *T){
	Node *p, *q, *s;
	if (T == NULL) return NULL;
	p = CopyTree(T->left);
	q = CopyTree(T->right);
	s = new Node;
	s->data = T->data;
	s->left = p;
	s->right = q;
}
int main() {
	Node *T=new Node;
	BuildTree(T);
	cout << "PreOrder:"; PreOrder(T); cout << endl;
	cout << "InOrder:"; InOrder(T); cout << endl;
	cout << "PostOrder:"; PostOrder(T); cout << endl;
	cout << "Height:" << Height(T) << endl;
	for (int i = 0; i < Height(T); ++i)
		num[i] = 0;
	levcount(T, 0, num);
	cout << "每层节点个数";
	for (int i = 0; i < Height(T); ++i)
		cout << num[i] << " ";
	cout << endl;
	cout << "CopyTree:"; PreOrder(CopyTree(T));
	cout << endl;
	return 0;
}
