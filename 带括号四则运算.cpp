#include<stack>
#include<iostream>
#include<deque>
#include<string>
using namespace std;

//�ж��Ƿ�Ϊ����
bool isPra(char c) 
{
	if(c=='('||c==')') 
		return true; 
	else 
		return false;
}

//��÷��ŵ�������
int getPri(char c) 
{
	switch(c) 
	{
	case '+':
	case '-':
		return 0;	//����ǼӼ�������0
		break;
	case '*':
	case '/':
		return 1;	//����ǳ˳�������1
		break;
	case '(':
	case ')':
		return -1;  //ע�⣬���ｫ������Ϊ������ȼ���������Ų��ᱻ��������������������
		break;
	 }
}

//�жϷ��ŵ�������
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
			//��������Ԫ��ֱ������������
			while(coll2.top()!='(') 
			{  
				char ch = coll2.top();
				coll3.push_back(ch);
				coll2.pop();
			}

			//������������ʱ��������������coll3(��׺���ʽ�У�
			coll2.pop();  
		}
	}
	else	//�����������
	{
		//ȡ��ջ��Ԫ�أ��뵱ǰ���Ž��������ԱȽ�
		char sym = coll2.top();  

		//�Ƚ������ŵ�������
		if(getPri(c)<=getPri(sym))  
		{
			//���c�������Ա�ջ������С����ڣ�����ջ��Ԫ��
			coll2.pop();
			//������ѹ��coll3����׺���ʽ����
			coll3.push_back(sym);
			//�ݹ����check,�Ƚϵ�ǰ����c����һ��ջ�����ŵ�������
			check(c,coll2,coll3);	
		}
		else 
		{
			//���c��ջ���������ȼ����ǽ�cѹ��coll2(������ջ����
			coll2.push(c);  
		}
	}
}

//��coll��ȡ��Ԫ�أ�����Ԫ�ص�coll2��coll3��
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
			//����check��������Բ�ͬ���������ͬ����
			check(c,coll2,coll3);  
		}

	}

	//��������������coll2��Ԫ��ȫ�������������׺���ʽ��
	while(!coll2.empty()) 
	{  
		char c = coll2.top();
		coll3.push_back(c);
		coll2.pop();
	}
}

//�����׺���ʽ
void calculate(deque<char>& coll3, stack<int>& coll4) 
{  
	while(!coll3.empty()) 
	{
		char c = coll3.front();
		coll3.pop_front();
		
		//����ǲ�������ѹ��ջ��
		if(c>='0'&&c<='9') 
		{
			//��ȥ'0'�ó�ƫ��ֵ����Ϊ��ʵ��ֵ�����ֱ��ת����int��������ԣ���Ϊchar ת��Ϊint�������ֵ������'1'�ı���ֵΪ49
			int op = c-'0';    
			coll4.push(op);     
		}
		else	 //����ǲ���������ջ�е���Ԫ�ؽ��м���
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
				coll4.push(op2/op1);  //ע����op2(op)op1������op1(op)op2
				break;
			}
		}
	}
}


int main()
{
	deque<char> coll1;  //ʢ����׺���ʽ
	stack<char> coll2;  //ʢ�Ų�����
	deque<char> coll3;	//ʢ�ź�׺���ʽ
	stack<int>coll4;	//�����׺���ʽ�ĸ�������
	string str;
	cout<<"��������ʽ����enter������"<<endl;
	cin>>str;
	for(int i=0;i!=str.size();++i) 
	{
		//��һ����ÿ���ַ�������ʹ��deque��Ϊdeque������ɾ����ӵ��ٶ����
		coll1.push_back(str[i]);  
	}
 
	//��coll��ȡ��Ԫ�أ�����Ԫ�ص�coll2��coll3��
	allocate(coll1,coll2,coll3); 

	//�����׺���ʽ
	calculate(coll3,coll4);  
	cout<<"������Ϊ:"<<coll4.top()<<endl;
}