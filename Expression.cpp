/**********************************************************************************************//**
 * @file	Expression.cpp
 * @author  zhangle
 * @date	7/11/2016
 * @description		+ - * \
 * 					exp=1+2*(4+12)
 * @reference	http://blog.csdn.net/anye3000/article/details/7939203
 * 				http://blog.csdn.net/anye3000/article/details/7941231
 * Implements the expression.
 **************************************************************************************************/
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cctype>
using namespace std;
int getPri(char c){
	switch (c)
	{
	case '+':
	case '-':
		return 0; break;
	case '*':
	case '/':
		return 1; break;
	case '(':
	case ')':
		return -1; break;
	}
}
void Trans(string s,stack<char> &st,queue<char> &q){
	for (auto ch : s){
		if (isalnum(ch))
			q.push(ch);
		else if(ch=='(')
			st.push(ch);
		else if (ch == ')'){
			while (st.top() != '('){
				q.push(st.top());
				st.pop();
			}
			st.pop();
		}
		else if (ch == '+' || ch == '-'){
			while (!st.empty() && getPri(st.top()) >= getPri(ch)){
				q.push(st.top());
				st.pop();
			}
			st.push(ch);
		}
		else if (ch == '*' || ch == '/')
			st.push(ch);
		
	}
	while (!st.empty()){
		q.push(st.top());
		st.pop();
	}		
}
void Calculate(queue<char> &q, stack<int> &st){
	while (!q.empty()){
		char ch = q.front();
		if (isdigit(ch)){
			st.push(ch-'0');
			q.pop();
		}
		else{
			int front, back;
			int p;
			back = st.top(); st.pop();
			front = st.top(); st.pop();
			if (ch == '+') p = front + back;
			if (ch == '-') p = front - back;
			if (ch == '*') p = front * back;
			if (ch == '/') p = front / back;
			st.push(p);
			q.pop();
		}
	}
}
int main(){
	string s = "5+((1+2)*4)-3";
	stack<char> st1;
	stack<int> st2;
	queue<char> q;
	while (!st1.empty()) st1.pop();
	while (!st2.empty()) st2.pop();
	while (!q.empty()) q.pop();
	Trans(s, st1, q);
	Calculate(q, st2);
	cout << s + '=' << st2.top() << endl;
	system("pause");
	return 0;
}