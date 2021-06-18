// MoveSemantics_SmartPointers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;
class MyInt
{
	int _i;

public:
	MyInt(int i) :_i(i) { cout << "Ctor called" << endl; }
	~MyInt() { cout << "Dtor called" << endl; }
	//MyInt(const MyInt& i) :_i(i._i) { cout << "CCtor Called" << endl; }
	MyInt(const MyInt& i)  = delete;//this function  is deleted no cctor is available
	MyInt& operator=(const MyInt& i) 
	{ 
		_i = i._i; 
		cout << "= operator Called" << endl;
		return *this;
	}
	MyInt(const MyInt&& i) :_i{ i._i } { cout << "mctor called" << endl; }
	MyInt& operator=(const MyInt&& i)
	{
		_i = i._i;
		cout << "M_= operator Called" << endl;
		return *this;
	}
	


};

MyInt RetMyInt()
{
	MyInt i{ 20 };
	return i;
}
void moves()
{
	MyInt myint0(10);
	{
		//MyInt myint1{ myint0 };//thus this will give errordue to =delete
		MyInt myint1_{ std::move(myint0) };
		MyInt myint2=RetMyInt();
		//myint2 = myint1;
		myint2 = std::move(myint1_);
	}
} 

void f(int& r)
{
	std::cout << "lvalue f" << std::endl;
}
void f(int&& r)
{
	std::cout << "rvalue f" << std::endl;
}

void rlvalue()
{
	int i{ 10 };
	int& ri{ i };
	int&& rvr{ 20 };
	f(i);//l
	f(ri);//l
	f(rvr);//l..rvalue cant be used in next line..still we are using....a var referencing rvalue is different
	//rvalue ref is itself an lvalue
	f(30);//r
	f(std::move(i));


	}

void SmartPointersmain()
{
	{
		MyInt* op1{ new MyInt(20) };
		MyInt* op2{ nullptr };
		op2 = op1;
		//no feeing of memory
	}
	{
		unique_ptr<MyInt> s{ new MyInt(20) };//instad of new call make_unique
		unique_ptr<MyInt> p{ make_unique<MyInt>(20) };
		unique_ptr<MyInt> q{ move(p) };
		unique_ptr<MyInt> t{ move(s) };
		unique_ptr<MyInt> r;
		//r = q;//error
		//so
		r = move(q);
		//uniue ptr automaticlaly call dtor
	}
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
