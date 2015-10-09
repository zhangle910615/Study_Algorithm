#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <Stack>
#include <Queue>
using namespace std;
#define Element char
#define format "%c"

typedef struct Node {
	Element data;
	struct Node *lchild;
	struct Node *rchild;
} *Tree;

int index = 0;  //ȫ����������

//������������,���������˳���������
//������������������'#'��ʾ
void treeNodeConstructor(Tree &root, Element data[]){
	Element e = data[index++];
	if (e == '#'){
		root = NULL;
	}
	else{
		root = (Node *)malloc(sizeof(Node));
		root->data = e;
		treeNodeConstructor(root->lchild, data);  //�ݹ鹹��������
		treeNodeConstructor(root->rchild, data);  //�ݹ鹹��������
	}
}

//������ȱ���
void depthFirstSearch(Tree root){
	stack<Node *> nodeStack;  //ʹ��C++��STL��׼ģ���
	nodeStack.push(root);
	Node *node;
	while (!nodeStack.empty()){
		node = nodeStack.top();
		printf(format, node->data);  //���������
		nodeStack.pop();
		if (node->rchild){
			nodeStack.push(node->rchild);  //�Ƚ�������ѹջ
		}
		if (node->lchild){
			nodeStack.push(node->lchild);  //�ٽ�������ѹջ
		}
	}
}

//������ȱ���
void breadthFirstSearch(Tree root){
	queue<Node *> nodeQueue;  //ʹ��C++��STL��׼ģ���
	nodeQueue.push(root);
	Node *node;
	while (!nodeQueue.empty()){
		node = nodeQueue.front();
		nodeQueue.pop();
		printf(format, node->data);
		if (node->lchild){
			nodeQueue.push(node->lchild);  //�Ƚ����������
		}
		if (node->rchild){
			nodeQueue.push(node->rchild);  //�ٽ����������
		}
	}
}
int main() {

	//��ͼ��ʾ�Ķ����������������,������'#'��ʾ���������������������
	Element data[15] = { 'A', 'B', 'D', '#', '#', 'E', '#', '#', 'C', 'F', '#', '#', 'G', '#', '#' };
	Tree tree;
	treeNodeConstructor(tree, data);
	printf("������ȱ������������: ");
	depthFirstSearch(tree);
	printf("\n\n������ȱ������������: ");
	breadthFirstSearch(tree);
	printf("\n");
	system("pause");
	return 0;

}