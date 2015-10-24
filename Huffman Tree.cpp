//Huffman Tree
//To be modified later

#include <iostream>
#include <stdio.h>
#include <deque>
#include <algorithm>
#include <vector>
using namespace std;
struct Node {
	char data;
	int freq;
	struct Node *left, *right,*parent;
};
bool comp(Node *a,Node *b) {
	return a->freq < b->freq;
}
void PreOrder(Node *root) {
	if (root) {
		cout << root->freq << " ";
		PreOrder(root->left);
		PreOrder(root->right);
	}
}
void FindAllPath(Node *root, vector<int> path,int i)
{
	if (root != NULL)
	{
		path.push_back(i);
		if (root->left == NULL && root->right == NULL)
		{
			cout << root->data << ":";
			for (vector<int>::iterator iter = path.begin()+1; iter != path.end(); iter++)
			{
				cout << *iter << " ";
			}
			cout << endl;
			return;
		}
		else
		{
			FindAllPath(root->left, path,0);
			FindAllPath(root->right, path,1);
		}
	}
}
;
Node* BuildHuffmanTree(deque<Node*> Q,int array[],char count[],int n) {
	for (int i = 0;i < n;i++) {
		Node *c = new Node;
		c->freq = array[i];
		c->data = count[i];
		c->left = c->right = NULL;
		Q.push_back(c);
	}

	for (int i = 0;i < n-1;i++) {
		sort(Q.begin(), Q.end(), comp);

		Node* x = Q.front();Q.pop_front();
		Node* y = Q.front();Q.pop_front();

		Node *z = new Node;
		z->data = '\0';
		z->parent = NULL;
		z->left = x;x->parent = z;
		z->right = y;y->parent = z;
		z->freq = x->freq + y->freq;

		Q.push_back(z);
	}
	return Q.front();
}
void main()
{

	//int array[7] = { 5,9,12,13,16,45 };
	//char count[7] = {'f','e','c','b','d','a'};
	int array[9] = { 1,1,2,3,5,8,13,21 };
	char count[9] = { 'a','b','c','d','e','f','g','h' };

	deque<Node*> Q;
	Node *z = new Node;
	z = BuildHuffmanTree(Q,array,count, 8);
	Q.clear();

	cout << "Weights:";
	PreOrder(z);
	cout << endl;
	vector<int> path;
	FindAllPath(z,path, 0);
}

