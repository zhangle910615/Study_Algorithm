/**********************************************************************************************//**
 * @file	Tree.cpp
 * @author  zhangle
 * @date    7/4/2016
 * Implements the tree class.
 **************************************************************************************************/
#include <iostream>
#include <iterator>
#include <sstream>
#include <queue>
#include <vector>
using namespace std;
struct LNode{
	char data;
	struct LNode *lchild, *rchild;
	LNode(char x) :data(x), lchild(NULL), rchild(NULL){}
};
//建树
void BuildTree(LNode *&root){
	char ch;
	cin >> ch;
	if (ch == '#') root = NULL;
	else{
		root = new LNode(ch);
		BuildTree(root->lchild);
		BuildTree(root->rchild);
	}
}
//先序遍历
void PreOrder(LNode *&root){
	if (root){
		cout << root->data << "\t";
		PreOrder(root->lchild);
		PreOrder(root->rchild);
	}
}
//树的高度
int Height(LNode *root){
	int h1, h2;
	if (root == NULL) return 0;
	else{
		h1 = Height(root->lchild);
		h2 = Height(root->rchild);
		if (h1>h2) return h1 + 1;
		else return h2 + 1;
	}
}
//树的宽度，即每一层节点数
int num[100];
void LevelCount(LNode *root, int num[], int i){
	if (root){
		num[i]++;
		LevelCount(root->lchild, num, i + 1);
		LevelCount(root->rchild, num, i + 1);
	}
}
//某个节点的在第几层
int Level(LNode *root, char x, int h){
	int l;
	if (root){
		if (root->data == x)
			return h;
		else{
			l = Level(root->lchild, x, h + 1);
			if (l != 0)
				return l;
			else
				return Level(root->rchild, x, h + 1);
		}
	}
	else
		return 0;
}
//层次遍历
void PrintNodeByLevel(LNode *root){
	if (!root)	return;
	queue<LNode*> dq;
	LNode *tmp = NULL;
	dq.push(root);
	while (!dq.empty()){
		tmp = dq.front();
		cout << tmp->data << "\t";
		dq.pop();
		if (tmp->lchild){
			dq.push(tmp->lchild);
		}
		if (tmp->rchild){
			dq.push(tmp->rchild);
		}
	}
}
//判断二叉树是不是完全二叉树
bool IsCompleteBinaryTree(LNode *root){
	if (!root) return false;
	queue<LNode *> dq;
	LNode *tmp = NULL;
	bool LeafNode = false;
	dq.push(root);
	while (!dq.empty()){
		tmp = dq.front();
		dq.pop();
		if (LeafNode){
			if (tmp->lchild != NULL || tmp->rchild != NULL)
				return false;
		}
		else{
			if (tmp->lchild != NULL && tmp->rchild != NULL){
				dq.push(tmp->lchild);
				dq.push(tmp->rchild);
			}
			else if(tmp->lchild!=NULL && tmp->rchild==NULL){
				LeafNode = true;
				dq.push(tmp->lchild);
			}
			else if(tmp->lchild==NULL && tmp->rchild!=NULL){
				return false;
			}
			else{
				LeafNode = true;
			}
		}
	}
	return true;
}
//判断二叉树是不是平衡二叉树
bool IsAVL(LNode *root, int &height){
	if (!root){
		height = 0;
		return true;
	}
	int heightleft;
	bool resultleft = IsAVL(root->lchild, heightleft);
	int heigthright;
	bool resultright = IsAVL(root->rchild, heigthright);
	if (resultleft && resultright && abs(heightleft - heigthright) <= 1){
		height = max(heightleft, heigthright) + 1;
		return true;
	}
	else{
		height = max(heightleft, heigthright) + 1;
		return false;
	}
}

//统计节点个数 
int count_tree(LNode* root){
	if (root){
		return (count_tree(root->lchild) + count_tree(root->rchild) + 1);
	}
	return 0;
}
//二叉树查找
LNode *Search(LNode *&root, char x){
	if (!root) return NULL;
	if (root->data == x){
		return root;
	}
	else{
		if (!Search(root->lchild, x))
			return Search(root->rchild, x);
		return root;
	}
}
//判断两个二叉树是否相似,1相似，0不相似,结构相同即相似
int Like(LNode *&t1, LNode *&t2){
	if (t1 == NULL && t2 == NULL)
		return 1;
	if (t1 == NULL || t2==NULL)
		return 0;
	return Like(t1->lchild, t2->lchild) && Like(t1->rchild, t2->rchild);
}
//判断两个二叉树是否相同，1相同，0不同
int Same(LNode *&t1, LNode *&t2){
	if (t1 == NULL && t2 == NULL)
		return 1;
	if ((t1 == NULL && t2 != NULL) || (t1 != NULL && t2 == NULL) || t1->data!=t2->data)
		return 0;
	return Same(t1->lchild, t2->lchild) && Same(t1->rchild, t2->rchild);
}
//复制树
LNode *CopyTree(LNode *T){
	LNode *p, *q, *s;
	if (T == NULL) return NULL;
	p = CopyTree(T->lchild);
	q = CopyTree(T->rchild);
	s = new LNode(T->data);
	s->lchild = p;
	s->rchild = q;

}
//输出值为x的节点的所有祖先
int ancestor(LNode *&T, char x){
	if (T == NULL) return 0;
	if (T->data == x) return 1;
	if (ancestor(T->lchild, x) || ancestor(T->rchild, x)){
		cout << T->data << "\t";
		return 1;
	}
}
//输出两个节点最近公共节点
bool FindPath(LNode *root, vector<char> &path, int key){
	if (root == NULL) return false;
	path.push_back(root->data);
	if (root->data == key) return true;
	bool find = (FindPath(root->lchild, path, key) || FindPath(root->rchild, path, key));
	if (find) return true;
	path.pop_back();
	return false;
}
int FindLCA(LNode *root, int key1, int key2){
	vector<char> path1, path2;
	bool find1 = FindPath(root, path1, key1);
	bool find2 = FindPath(root, path2, key2);
	if (find1 && find2){
		int ans;
		for (int i = 0; i < (int)path1.size(); i++){
			if (path1[i] != path2[i])
				break;
			else
				ans = path1[i];
		}
		return ans;
	}
	return -1;
}
//先序序列与中序序列构造二叉树
LNode *CreateBT1(char *pre, char *in, int n){
	if (n <= 0) return NULL;
	LNode *s = new LNode(*pre);
	char *p;
	int k;
	for (p = in; p < in + n; p++)
		if (*p == *pre)
			break;
	k = p-in;
	s->lchild = CreateBT1(pre+1, in, k);
	s->rchild = CreateBT1(pre + k + 1, p + 1, n - k - 1);
	return s;
}
//中序和后序构造二叉树
LNode *CreateBT2(char *in, char *post, int n){
	if (n <= 0) return NULL;
	char r = *(post + n - 1);
	LNode *s = new LNode(r);
	char *p;
	int k;
	for (p = in; p < in + n; p++)
		if (*p == r)
			break;
	k = p - in;
	s->lchild = CreateBT2(in, post, k);
	s->rchild = CreateBT2(p + 1, post + k, n - k - 1);
	return s;

}
void test(){
	LNode *root = NULL;
	BuildTree(root);
	ancestor(root, 'e');
	cout << endl;
	cout << "-------------------" << endl;
	cout << "先序遍历:" << endl;
	PreOrder(root);
	cout << endl;
	cout << "节点个数:" << count_tree(root) << endl;
	cout << "树的高度:" << Height(root) << endl;
	for (int i = 0; i<100; ++i)
		num[i] = 0;
	LevelCount(root, num, 0);
	cout << "每一层节点数:" << endl;
	for (int i = 0; i<Height(root); i++){
		cout << i + 1 << ":" << num[i] << endl;
	}
	cout << "层次遍历:" << endl;
	PrintNodeByLevel(root);
	cout << endl;
	cout << "b在第(0):" << Level(root, 'b', 0) << "层" << endl;
	cout << "-------------------" << endl;
	LNode *root2 = NULL;
	BuildTree(root2);
	cout << "Like?:" << Like(root, root2) << endl;
	cout << "Same?:" << Same(root, root2) << endl;
	cout << "-------------------" << endl;
	cout << IsCompleteBinaryTree(root) << endl;
}
