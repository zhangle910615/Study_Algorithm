#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;
class U_Ptr {
	friend class HasPtr;
	int *ip;
	size_t use;
	U_Ptr(int *p) :ip(p), use(1) {
		cout << "U_Ptr constructor called!" << endl;
	}
	~U_Ptr() {
		delete ip;
		cout<< "U_Ptr distructor called!" << endl;
	}
};
class HasPtr {
public:
	HasPtr(int *p, int i) :ptr(new U_Ptr(p)), val(i) {
		cout << "HasPtr constructor called!" << "use = " << ptr->use << endl;
	}
	HasPtr(const HasPtr& orig) :ptr(orig.ptr), val(orig.val) {
		++ptr->use;
		cout << "HasPtr copy constructor called!" << "use = " << ptr->use << endl;
	}
	HasPtr& operator=(const HasPtr&);
	~HasPtr() {
		cout << "HasPtr distructor called!" << "use = " << ptr->use << endl;
		if (--ptr->use == 0) {
			delete ptr;
		}
	}
	int *get_ptr() const {
		return ptr->ip;
	}
	int get_int() const {
		return val;
	}
	void set_ptr(int *p)const {
		ptr->ip = p;
	}
	void set_int(int i) {
		val = i;
	}
	int get_ptr_val() const{
		return *ptr->ip;
	}
	void set_ptr_val(int i) {
		*ptr->ip = i;
	}
private:
	U_Ptr *ptr;
	int val;
};
void main() {
	int *pi = new int(42);
	HasPtr *hpa = new HasPtr(pi, 100);
	HasPtr *hpb = new HasPtr(*hpa);
	HasPtr *hpc = new HasPtr(*hpb);
	HasPtr hpd = *hpa;

	cout << hpa->get_ptr_val() << " " << hpb->get_ptr_val() << endl;
	hpc->set_ptr_val(10000);
	cout << hpa->get_ptr_val() << " " << hpb->get_ptr_val() << endl;
	hpd.set_ptr_val(10);
	cout << hpa->get_ptr_val() << " " << hpb->get_ptr_val() << endl;
	delete hpa;
	delete hpb;
	delete hpc;
	cout << hpd.get_ptr_val() << endl;
}

HasPtr & HasPtr::operator=(const HasPtr &rhs)
{
	++rhs.ptr->use;
	if (--ptr->use == 0)
		delete ptr;
	ptr = rhs.ptr;
	val = rhs.val;
	return *this;

}
