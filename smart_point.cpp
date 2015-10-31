#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;

void main() {
	// shared_ptr代表的是“共享所有权”（shared ownership）的指针。多个智能指针可以指向同一个对象，当指向该对象的最后一个指针销毁的时候，
	//该对象自动销毁，释放空间。与shared_ptr相关的其他一些类包括：weak_ptr，bad_weak_ptr，enable_shared_from_this等。shared_ptr是采用引
	//用计数的智能指针，当引用个数为0的时候，即会释放指向对象的空间。shared_ptr有效地防治了悬挂指针（dangling points）的产生。
	cout << "shared_ptr:" << endl;
	shared_ptr<string> pNico(new string("nico"));
	shared_ptr<string> pJutta(new string("jutta"));
	(*pNico)[0] = 'N';
	pJutta->replace(0, 1, "J");
	cout << *pNico << endl;
	cout << *pJutta << endl;
	vector<shared_ptr<string>> whoMadeCoffee;
	whoMadeCoffee.push_back(pJutta);
	whoMadeCoffee.push_back(pJutta);
	whoMadeCoffee.push_back(pNico);
	whoMadeCoffee.push_back(pJutta);
	whoMadeCoffee.push_back(pNico);

	for (auto ptr : whoMadeCoffee)
		cout << *ptr << " ";
	cout << endl;

	*pNico = "Nicolai";
	for (auto ptr : whoMadeCoffee)
		cout << *ptr << " ";
	cout << endl;
	//为什么最后对whoMadeCoffee[0]对象的引用是4呢？第一个是pJutta指针本身，算一个引用，然后还有三个副本：
	//whoMadeCoffee[0]、whoMadeCoffee[1]、whoMadeCoffee[3]，所以总共加起来就是4个。
	cout << "use_count:" << whoMadeCoffee[0].use_count() << endl;
	whoMadeCoffee.clear();
	cout << "use_count:" << pJutta.use_count() << endl;
	

	cout << endl<<"unique_ptr:" << endl;
	//unique_ptr代表的是“排他所有权”（exclusive ownership）的指针。对于一个对象，该指针确保任何时候只有
	//一个智能指针指向该对象。当然，你可以转移所有权，让该指针释放对该对象的引用，让其他指针指向该对象。
	//unique_ptr有效地防治了内存泄露（resource leaks）。
	unique_ptr<string> pStr(new string("Hello"));
	cout << *pStr << "\n";
	*pStr = "ni hao";
	cout << *pStr << endl;
	string *pOtherStr = pStr.release();
	if (pStr == nullptr)
		cout << *pOtherStr << endl;
	delete pOtherStr;

	//智能指针的使用和普通指针类似，但是需要记住智能指针不能使用delete关键字显示释放空间。
	//但是我们可以在智能指针的构造函数中自定义我们释放空间时要做的操作。
}
