#include <iostream>
#include <string>
using namespace std;

struct node{
	char v;
	node *left;
	node *right;
	node(char c){
		v = c;
		left = NULL;
		right = NULL;
	}
};

string A, B;

void genTree(node *t, string a, string b){
	int mid = 1;
	string la, lb, ra, rb;
	if (a.length()>0){
		if (b.find(a[0]) != string::npos){
			mid = b.find(a[0]);
		}
		lb = b.substr(0, mid);
		rb = b.substr(mid + 1, b.length());
		la = a.substr(1, lb.length());
		ra = a.substr(a.length() - rb.length(), a.length());
		//cout<<la<<" "<<ra<<endl;
		//cout<<lb<<" "<<rb<<endl;
		if (la.length()>0){
			t->left = new node(la[0]);
			genTree(t->left, la, lb);
		}
		if (ra.length()>0){
			t->right = new node(ra[0]);
			genTree(t->right, ra, rb);
		}
	}
}

void postOrder(node *t){
	if (t != NULL){
		postOrder(t->left);
		postOrder(t->right);
		cout << t->v;
	}
}

int main(int argc, char* argv[]){
	while (cin >> A >> B){
		node *root = new node(A[0]);
		genTree(root, A, B);
		postOrder(root);
		cout << endl;
	}
	return 0;
}