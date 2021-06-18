#include<string>
#include<algorithm>
#include<iostream>
#include<memory>
#include<vector>
#include<ranges>

using namespace std;
namespace ranges = std::ranges;

class Controller {
public:
	int Num;
	string Status;
	vector<weak_ptr<Controller>> others;
	explicit Controller(int i) :Num{ i }, Status{ "On" }{
		cout << "Creating Controller " << Num << endl;
	};
	~Controller()
	{
		cout << "Destroying Controller " << Num<<endl;
	}
	void checkStatus()const
	{
		for_each(others.begin(), others.end(), [](weak_ptr<Controller> c) {
				auto p = c.lock();//returns a SPtr
				if (p)
				{
					cout << " Status Of " << p->Num << " is " << p->Status << endl;
				}
				else {
					cout << "Null Object" << endl;
				}
			});
	}
};

void RunTest()
{
	vector<shared_ptr<Controller>>v_controller_sptr
	{
		make_shared<Controller>(0),
		make_shared<Controller>(1),
		make_shared<Controller>(2),
		make_shared<Controller>(3),
		make_shared<Controller>(4)
	};
	
	for (auto i = 0; i < v_controller_sptr.size(); ++i)
	{
		for_each(v_controller_sptr.begin(), v_controller_sptr.end(), [&](shared_ptr<Controller> p) {
			if (p->Num != i)
			{
				v_controller_sptr[i]->others.push_back(weak_ptr<Controller>(p));
				cout << "push back to v[" << i << "]: " << p->Num << endl;
			}
			});
	}
}