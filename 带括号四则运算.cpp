#include<stack>
#include<iostream>
#include<deque>
#include<string>
using namespace std;

//判断是否为括号
bool isPra(char c) 
{
	if(c=='('||c==')') 
		return true; 
	else 
		return false;
}

//获得符号的优先性
int getPri(char c) 
{
	switch(c) 
	{
	case '+':
	case '-':
		return 0;	//如果是加减，返回0
		break;
	case '*':
	case '/':
		return 1;	//如果是乘除，返回1
		break;
	case '(':
	case ')':
		return -1;  //注意，这里将括号设为最低优先级，因此括号不会被弹出，除非遇到右括号
		break;
	 }
}

//判断符号的优先性
void check(char c, stack<char>& coll2, deque<char>& coll3) 
{  
	if(coll2.empty()) 
	{
		coll2.push(c);
		return;
	}
 
	if(isPra(c)) 
	{
		if(c=='(') 
			coll2.push(c);
		else 
		{
			//弹出所有元素直到遇到左括号
			while(coll2.top()!='(') 
			{  
				char ch = coll2.top();
				coll3.push_back(ch);
				coll2.pop();
			}

			//当遇到左括号时，弹出但不加入coll3(后缀表达式中）
			coll2.pop();  
		}
	}
	else	//如果不是括号
	{
		//取出栈顶元素，与当前符号进行优先性比较
		char sym = coll2.top();  

		//比较两符号的优先性
		if(getPri(c)<=getPri(sym))  
		{
			//如果c的优先性比栈顶符号小或等于，弹出栈顶元素
			coll2.pop();
			//并将其压入coll3（后缀表达式）中
			coll3.push_back(sym);
			//递归调用check,比较当前符号c与下一个栈顶符号的优先性
			check(c,coll2,coll3);	
		}
		else 
		{
			//如果c比栈顶符号优先级大，那将c压入coll2(操作符栈）中
			coll2.push(c);  
		}
	}
}

//从coll中取出元素，分配元素到coll2和coll3中
void allocate(deque<char>& coll1, stack<char>& coll2, deque<char>& coll3) 
{  
	while(!coll1.empty()) 
	{
		char c = coll1.front();
		coll1.pop_front();

		if(c>='0'&&c<='9')
		{
			coll3.push_back(c);
		}
		else 
		{
			//调用check函数，针对不同情况作出不同操作
			check(c,coll2,coll3);  
		}

	}

	//如果输入结束，将coll2的元素全部弹出，加入后缀表达式中
	while(!coll2.empty()) 
	{  
		char c = coll2.top();
		coll3.push_back(c);
		coll2.pop();
	}
}

//计算后缀表达式
void calculate(deque<char>& coll3, stack<int>& coll4) 
{  
	while(!coll3.empty()) 
	{
		char c = coll3.front();
		coll3.pop_front();
		
		//如果是操作数，压入栈中
		if(c>='0'&&c<='9') 
		{
			//减去'0'得出偏移值，即为真实数值（如果直接转换成int，结果不对，因为char 转换为int是其编码值，例如'1'的编码值为49
			int op = c-'0';    
			coll4.push(op);     
		}
		else	 //如果是操作符，从栈中弹出元素进行计算
		{ 
			int op1 = coll4.top();
			coll4.pop();
			int op2 = coll4.top();
			coll4.pop();
			switch(c) 
			{
			case '+':
				coll4.push(op2+op1);
				break;
			case '-':
				coll4.push(op2-op1);
				break;
			case '*':
				coll4.push(op2*op1);
				break;
			case '/':
				coll4.push(op2/op1);  //注意是op2(op)op1而不是op1(op)op2
				break;
			}
		}
	}
}


int main()
{
	deque<char> coll1;  //盛放中缀表达式
	stack<char> coll2;  //盛放操作符
	deque<char> coll3;	//盛放后缀表达式
	stack<int>coll4;	//计算后缀表达式的辅助容器
	string str;
	cout<<"请输入表达式，按enter结束："<<endl;
	cin>>str;
	for(int i=0;i!=str.size();++i) 
	{
		//逐一加入每个字符，这里使用deque因为deque在两端删除添加的速度最快
		coll1.push_back(str[i]);  
	}
 
	//从coll中取出元素，分配元素到coll2和coll3中
	allocate(coll1,coll2,coll3); 

	//计算后缀表达式
	calculate(coll3,coll4);  
	cout<<"计算结果为:"<<coll4.top()<<endl;
}