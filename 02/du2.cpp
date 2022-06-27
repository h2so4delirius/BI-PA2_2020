#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <stdexcept>
#include <algorithm>
using namespace std;
#endif /* __PROGTEST__ */
struct man
{
	string addr="";
	int sum=0;
	int sum_exp=0;
	string name="";
	string account="";
};

class CIterator
{

public:
	CIterator(const vector<man*>& rtrr) {
		this->rtrr = rtrr;
	}
	bool                     AtEnd(void) const { return (i == rtrr.size()); }
	void                     Next(void) { i++; }
	string                   Name(void) const { return rtrr[i]->name; }
	string                   Addr(void) const{ return rtrr[i]->addr; }
	string                   Account(void) const { return rtrr[i]->account;}
private:
	unsigned int i = 0;
	vector<man*>rtrr;
};

class CTaxRegister
{
public:
	bool                     Birth(const string& name,
		const string& addr,
		const string& account) {
		man man_1;
		man_1.account = account;
		man_1.addr = addr;
		man_1.name = name;
		if (pocet == 0) {
			rtr1.reserve(rtr1.capacity() + 150000);
			pocet = 100000;
		}
		if (binary_search(rtr_by_account.begin(), rtr_by_account.end(), &man_1, [](man* const& man1, man* const& man2) {return (man1->account < man2->account); }))
			return false;
		if (binary_search(rtr_by_name.begin(), rtr_by_name.end(), &man_1, [](man* const& man1, man* const& man2) {
					if (man1->name == man2->name) {
						return (man1->addr < man2->addr);
					}
					else {
						return (man1->name < man2->name);
					}}))

			return false;
		auto it_by_ac = lower_bound(rtr_by_account.begin(), rtr_by_account.end(),&man_1, [](man *const &man1, man *const &man2) {return (man1->account < man2->account); });
		auto it_by_name = lower_bound(rtr_by_name.begin(), rtr_by_name.end(),&man_1, [](man*const &man1, man*const &man2) {
			if (man1->name == man2->name) {
				return (man1->addr < man2->addr);
			}
			else {
				return (man1->name < man2->name);
			}
			});
		pocet--;
		rtr1.push_back(man_1);
		rtr_by_name.insert(it_by_name,&rtr1.back());
		rtr_by_account.insert(it_by_ac, &rtr1.back());
		return true;
	}
	bool                     Death(const string& name,
		const string& addr) {
		man man_1;
		man_1.addr = addr;
		man_1.name = name;
		if (!binary_search(rtr_by_name.begin(), rtr_by_name.end(), &man_1, [](man* const& man1, man* const& man2) {
			if (man1->name == man2->name) {
				return (man1->addr < man2->addr);
			}
			else
				return (man1->name < man2->name); }))
			return false;
		auto it_by_name = lower_bound(rtr_by_name.begin(), rtr_by_name.end(), &man_1, [](man* const& man1, man* const& man2) {
			if (man1->name == man2->name) {
				return (man1->addr < man2->addr);
			}
			else
				return (man1->name < man2->name);
			});
		man_1.account=(*it_by_name)->account;
		rtr_by_name.erase(it_by_name);
		auto it_by_ac = lower_bound(rtr_by_account.begin(), rtr_by_account.end(), &man_1, [](man* const& man1, man* const& man2) {return (man1->account < man2->account); });
		rtr_by_account.erase(it_by_ac);
		return true;
	}
	bool                     Income(const string& account,
		int               amount) {
		man man_1;
		man_1.account = account;
		if (!binary_search(rtr_by_account.begin(), rtr_by_account.end(), &man_1, [](man* const& man1, man* const& man2) {return (man1->account < man2->account); }))
			return false;
		auto it_by_ac = lower_bound(rtr_by_account.begin(), rtr_by_account.end(), &man_1, [](man* const& man1, man* const& man2) {return (man1->account < man2->account); });
		(*it_by_ac)->sum += amount;
		return true;

	}

	bool                     Income(const string& name,
		const string& addr,
		int               amount) {
		man man_1;
		man_1.addr = addr;
		man_1.name = name;
		if (!binary_search(rtr_by_name.begin(), rtr_by_name.end(), &man_1, [](man* const& man1, man* const& man2) {
			if (man1->name == man2->name) {
				return (man1->addr < man2->addr);
			}
			else
			{
				return (man1->name < man2->name);
			} }))
			return false;
		auto it_by_name = lower_bound(rtr_by_name.begin(), rtr_by_name.end(), &man_1, [](man* const& man1, man* const& man2) {
				if (man1->name == man2->name) {
					return (man1->addr < man2->addr);
				}
				else {
					return (man1->name < man2->name);
				}
				});
			(*it_by_name)->sum += amount;
			return true;
	}
	bool                     Expense(const string& account,
		int               amount) {
		man man_1;
		man_1.account = account;
		if (!binary_search(rtr_by_account.begin(), rtr_by_account.end(), &man_1, [](man* const& man1, man* const& man2) {return (man1->account < man2->account); }))
			return false;
		auto it_by_ac = lower_bound(rtr_by_account.begin(), rtr_by_account.end(), &man_1, [](man* const& man1, man* const& man2) {return (man1->account < man2->account); });
		(*it_by_ac)->sum_exp += amount;
		return true;
	}
	bool                     Expense(const string& name,
		const string& addr,
		int               amount) {
		man man_1;
		man_1.addr = addr;
		man_1.name = name;
		bool kok = binary_search(rtr_by_name.begin(), rtr_by_name.end(), &man_1, [](man* const& man1, man* const& man2) {
			if (man1->name == man2->name) {
				return (man1->addr < man2->addr);
			}
			else
			{
				return (man1->name < man2->name);
			}
			return false; });
			if(!kok)
			return false;
			auto it_by_name = lower_bound(rtr_by_name.begin(), rtr_by_name.end(), &man_1, [](man* const& man1, man* const& man2) {
				if (man1->name == man2->name) {
					return (man1->addr < man2->addr);
				}
				else {
					return (man1->name < man2->name);
				}
				return false;
				});
			(*it_by_name)->sum_exp += amount;
			return true;
	}
	bool                     Audit(const string& name,
		const string& addr,
		string& account,
		int& sumIncome,
		int& sumExpense) const {
		man man_1;
		man_1.addr = addr;
		man_1.name = name;
		if (!binary_search(rtr_by_name.begin(), rtr_by_name.end(), &man_1, [](man* const& man1, man* const& man2) {
			if (man1->name == man2->name) {
				return (man1->addr < man2->addr);
			}
			else {
				return (man1->name < man2->name);
			}
			}))
			return false;
		auto it_by_name = lower_bound(rtr_by_name.begin(), rtr_by_name.end(), &man_1, [](man* const& man1, man* const& man2) {
				if (man1->name == man2->name) {
					return (man1->addr < man2->addr);
				}
				else {
					return (man1->name < man2->name);
				}
				});
		account = (*it_by_name)->account;
		sumIncome = (*it_by_name)->sum;
		sumExpense = (*it_by_name)->sum_exp;
		return true;
	}
	CIterator                ListByName(void) const{
		CIterator k(rtr_by_name);
		return k;
	}

	/*void prnt() {
		for (auto i : rtr1) {
			cout << i.account << " " << i.addr << " " << i.name << " " << i.sum << " " << i.sum_exp<<endl;
		}
		cout << "no" << endl;
		for (auto i : rtr_by_account) {
			cout << i->account << " " << i->addr << " " << i->name << " " << i->sum << " " << i->sum_exp << endl;
		}
		cout << "acc" << endl;
		for (auto i : rtr_by_name) {
			cout << i->account << " " << i->addr << " " << i->name << " " << i->sum << " " << i->sum_exp << endl;
		}
		return;
	}*/
private:
	int pocet = 0;
	vector<man>rtr1;
	vector<man*>rtr_by_account;
	vector<man*>rtr_by_name;
};

#ifndef __PROGTEST__
int main(void)
{
	string acct;
	int    sumIncome, sumExpense;
	CTaxRegister b1;
	assert(b1.Birth("John Smith", "Oak Road 23", "123/456/789"));
	assert(b1.Birth("Jane Hacker", "Main Street 17", "Xuj5#94"));
	assert(b1.Birth("Peter Hacker", "Main Street 17", "634oddT"));
	assert(b1.Birth("John Smith", "Main Street 17", "Z343rwZ"));
	assert(b1.Income("Xuj5#94", 1000));
	assert(b1.Income("634oddT", 2000));
	assert(b1.Income("123/456/789", 3000));
	assert(b1.Income("634oddT", 4000));
	assert(b1.Income("Peter Hacker", "Main Street 17", 2000));
	assert(b1.Expense("Jane Hacker", "Main Street 17", 2000));
	assert(b1.Expense("John Smith", "Main Street 17", 500));
	assert(b1.Expense("Jane Hacker", "Main Street 17", 1000));
	assert(b1.Expense("Xuj5#94", 1300));
	assert(b1.Audit("John Smith", "Oak Road 23", acct, sumIncome, sumExpense));
	assert(acct == "123/456/789");
	assert(sumIncome == 3000);
	assert(sumExpense == 0);
	assert(b1.Audit("Jane Hacker", "Main Street 17", acct, sumIncome, sumExpense));
	assert(acct == "Xuj5#94");
	assert(sumIncome == 1000);
	assert(sumExpense == 4300);
	assert(b1.Audit("Peter Hacker", "Main Street 17", acct, sumIncome, sumExpense));
	assert(acct == "634oddT");
	assert(sumIncome == 8000);
	assert(sumExpense == 0);
	assert(b1.Audit("John Smith", "Main Street 17", acct, sumIncome, sumExpense));
	assert(acct == "Z343rwZ");
	assert(sumIncome == 0);
	assert(sumExpense == 500);
	CIterator it = b1.ListByName();
	assert(!it.AtEnd()
		&& it.Name() == "Jane Hacker"
		&& it.Addr() == "Main Street 17"
		&& it.Account() == "Xuj5#94");
	it.Next();
	assert(!it.AtEnd()
		&& it.Name() == "John Smith"
		&& it.Addr() == "Main Street 17"
		&& it.Account() == "Z343rwZ");
	it.Next();
	assert(!it.AtEnd()
		&& it.Name() == "John Smith"
		&& it.Addr() == "Oak Road 23"
		&& it.Account() == "123/456/789");
	it.Next();
	assert(!it.AtEnd()
		&& it.Name() == "Peter Hacker"
		&& it.Addr() == "Main Street 17"
		&& it.Account() == "634oddT");
	it.Next();
	assert(it.AtEnd());

	assert(b1.Death("John Smith", "Main Street 17"));

	CTaxRegister b2;
	assert(b2.Birth("John Smith", "Oak Road 23", "123/456/789"));
	assert(b2.Birth("Jane Hacker", "Main Street 17", "Xuj5#94"));
	assert(!b2.Income("634oddT", 4000));
	assert(!b2.Expense("John Smith", "Main Street 18", 500));
	assert(!b2.Audit("John Nowak", "Second Street 23", acct, sumIncome, sumExpense));
	assert(!b2.Death("Peter Nowak", "5-th Avenue"));
	assert(!b2.Birth("Jane Hacker", "Main Street 17", "4et689A"));
	assert(!b2.Birth("Joe Hacker", "Elm Street 23", "Xuj5#94"));
	assert(b2.Death("Jane Hacker", "Main Street 17"));
	assert(b2.Birth("Joe Hacker", "Elm Street 23", "Xuj5#94"));
	assert(b2.Audit("Joe Hacker", "Elm Street 23", acct, sumIncome, sumExpense));
	assert(acct == "Xuj5#94");
	assert(sumIncome == 0);
	assert(sumExpense == 0);
	assert(!b2.Birth("Joe Hacker", "Elm Street 23", "AAj5#94"));

	return 0;
}
#endif /* __PROGTEST__ */
