#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cstdint>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <stdexcept>
using namespace std;


#endif /* __PROGTEST__ */
//class invalid_argument {
//};


class CBigInt
{
public:
	CBigInt() {
		namber.push_back(0);
		poloz = true;
	}
	CBigInt(int a) {
		string str;
		ostringstream stream;
		stream << a;
		str = stream.str();
		//cout << str;
		*this = CBigInt(str);
	}
	CBigInt(string a) {
		unsigned int start;
		if (a[0] == '-') { poloz = false; start = 1; }
		else { poloz = true; start = 0; }
		while (start != a.size()) {
			if (!(a[start] <= 57 && a[start] >= 48)) {
				throw std::invalid_argument("vfvfv");
			}
			int b = a[start] - 48;
			if (namber.size() == 1) {
				if (namber[0] == 0) {
					if (b != 0) {
						namber.clear();
						namber.push_back(b);
					}
				}
				else
					namber.push_back(b);
			}
			else
				namber.push_back(b);
			start++;
		}
		if (namber.size() == 1)
			if (namber[0] == 0)
				poloz = true;
	}
	/////////////////////////////////////////////////////======================================
	CBigInt& operator =(const CBigInt& range1) {
		poloz = range1.poloz;
		namber = range1.namber;
		return *this;
	}
	CBigInt& operator =(const string& range1) {
		CBigInt p(range1);
		*this = p;
		return *this;
	}
	CBigInt& operator =(const int& range1) {
		CBigInt p(range1);
		*this = p;
		return *this;
	}


	/////////////////////////////////////////////++++++++++++++++++++++++++++++++++++++++
	CBigInt& operator +=(const CBigInt& range1) {
		if (poloz && range1.poloz) {
			if (namber.size() >= range1.namber.size()) {
				namber = vec_plus(namber, range1.namber);
			}
			else if (namber.size() < range1.namber.size()) {
				namber = vec_plus(range1.namber, namber);
			}
		}
		else if (!poloz && !range1.poloz) {
			if (namber.size() >= range1.namber.size()) {
				namber = vec_plus(namber, range1.namber);
			}
			else if (namber.size() < range1.namber.size()) {
				namber = vec_plus(range1.namber, namber);
			}
			poloz = false;
		}
		else if (!poloz || !range1.poloz) {
			bool prov;
			if (namber.size() > range1.namber.size()) {
				namber = vec_minus(namber, range1.namber, prov);
			}
			else if (namber.size() < range1.namber.size()) {
				namber = vec_minus(range1.namber, namber, prov);
				if (poloz) { poloz = false; }
				else { poloz = true; }
			}
			else if (namber.size() == range1.namber.size()) {
				int i = range1.namber.size() - 1;
				while (i >= 0) {
					if (namber[i] > range1.namber[i]) {
						namber = vec_minus(namber, range1.namber, prov);
						break;
					}
					if (namber[i] < range1.namber[i]) {
						namber = vec_minus(range1.namber, namber, prov);
						if (poloz) { poloz = false; }
						else { poloz = true; }
						break;
					}
					if (namber[i] == range1.namber[i] && i == 0) {
						poloz = true;
						namber.clear();
						namber.push_back(0);
					}
					i--;
				}

			}

		}

		return *this;
	}

	CBigInt& operator +=(const int& range1) {
		CBigInt a(range1);
		*this += a;
		return *this;
	}


	CBigInt& operator +=(const string& range1) {
		CBigInt a(range1);
		*this += a;
		return *this;
	}


	///////////////////////////////////////////////////*************************
	CBigInt& operator *=(const CBigInt& range1) {
		if (range1.namber.size() == 1 && range1.namber[0] == 0) {
			namber.clear();
			namber.push_back(0);
			poloz = true;
			return *this;
		}
		if (!poloz && !range1.poloz) { poloz = true; }
		else if (!poloz || !range1.poloz) { poloz = false; }
		if (namber.size() >= range1.namber.size()) {
			namber = vec_krat(namber, range1.namber);
		}
		else if (namber.size() < range1.namber.size()) {
			namber = vec_krat(range1.namber, namber);
		}

		return *this;
	}
	CBigInt& operator *=(const int& range1) {
		CBigInt a(range1);
		*this *= a;
		return *this;
	}

	CBigInt& operator *=(const string& range1) {
		CBigInt a(range1);
		*this *= a;
		return *this;
	}



	vector<int> vec_plus(const vector<int>& number1, const vector<int>& namber2) {
		vector<int>result = number1;
		int tmp = 0;


		//bool some=false;
		int j = namber2.size() - 1;
		for (int i = number1.size() - 1; i >= 0; i--) {
			if (j >= 0) {
				tmp += number1[i] + namber2[j];
			}
			else if (tmp) {
				tmp += number1[i];
			}
			else
				break;

			//result.insert(result.begin(), tmp % 10);
			result[i]= tmp % 10;
			if (tmp > 9) {
				tmp = 1;
			}
			else {
				tmp = 0;
			}
			j--;
		}
		if (tmp == 1) {
			result.insert(result.begin(), 1);
		}
		return result;
	}

	vector<int> vec_minus(const vector<int>& number1, const vector<int>& namber2, bool& znak) {
		vector<int>result=number1;
		int tmp = 0;
		//bool some = false;
		int j = namber2.size() - 1;
		for (int i = number1.size() - 1; i >= 0; i--) {
			if (j < 0) {
				if (tmp == 0)
					//result.insert(result.begin(), number1[i]);
					break;
				else {
					if ((number1[i] - tmp) >= 0) {
						//result.insert(result.begin(), number1[i] - tmp);
						result[i] = number1[i] - tmp;
						tmp = 0;
						break;
					}
					else {
						int g = number1[i] + 10;

						//result.insert(result.begin(), (g - tmp));
						result[i] = g - tmp;
						tmp = 1;
					}
				}
			}
			else {
				if (number1[i] < namber2[j] + tmp) {
					int g = number1[i] + 10;

					//result.insert(result.begin(), (g - namber2[j] - tmp));
					result[i] = g - namber2[j] - tmp;
					tmp = 1;
				}
				else {
					//result.insert(result.begin(), (number1[i] - namber2[j] - tmp));
					result[i] = number1[i] - namber2[j] - tmp;
					tmp = 0;
				}
			}


			j--;
		}
		if (tmp) {
			//cout << "!1" << endl;
			znak = false;
		}
		else { znak = true; }
		while (result[0] == 0) {
			if (result.size() == 1) { break; }
			result.erase(result.begin());
		}
		return result;
	}

	vector<int> vec_krat(const vector<int>& number1, const vector<int>& number2) {
		vector<int>result;

		int spider = 0;


		for (int i = number2.size() - 1; i >= 0; i--) {
			vector<int>result_1;
			int tmp = 0;
			bool some = false;
			for (int j = number1.size() - 1; j >= 0; j--) {
				tmp += number1[j] * number2[i];
				result_1.insert(result_1.begin(), tmp % 10);
				if (tmp > 9) {
					if (j == 0) { some = true; }
					tmp = (tmp - tmp % 10) / 10;
				}
				else {
					tmp = 0;
				}
			}
			if (some) { result_1.insert(result_1.begin(), tmp); }

			for (int p = 0; p < spider; p++) { result_1.push_back(0); }
			if (result_1.size() >= result.size()) {
				result = vec_plus(result_1, result);
			}
			else if (result_1.size() < result.size()) {
				result = vec_plus(result, result_1);
			}
			spider++;
		}
		return result;
	}

	//////////////////////////////////////////============================================================

	/////////////////////////////////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!=======================================


		//////////////////////////////////////////////////////////////////////////////////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		///////////////////////////////////////////////////////////////////////////////<<<<<<<<<<<<<<<<<<<<===============


		////////////////////////////////////////////////////////////////////////>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		////////////////////////////////////////////////////////////////////////////>>>>>>>>>>>>>>==================================
		// copying/assignment/destruction
		// int constructor
		// string constructor
		// operator +, any combination {CBigInt/int/string} + {CBigInt/int/string}
		// operator *, any combination {CBigInt/int/string} * {CBigInt/int/string}
		// operator +=, any of {CBigInt/int/string}
		// operator *=, any of {CBigInt/int/string}
		// comparison operators, any combination {CBigInt/int/string} {<,<=,>,>=,==,!=} {CBigInt/int/string}
		// output operator <<
		// input operator >>
	friend bool operator>>(istringstream& oss, CBigInt& x);
	friend ostream& operator<<(ostream& oss, const CBigInt& x);
	friend CBigInt operator*(CBigInt r1, CBigInt r2);
	friend CBigInt operator*(CBigInt r1, int  r2);
	friend CBigInt operator*(CBigInt r1, string r2);
	friend CBigInt operator*(string r2, CBigInt r1);
	friend CBigInt operator*(int r2, CBigInt r1);




	//friend bool operator>=(const CBigInt& range1,const const CBigInt& range2)const;
	friend bool operator==(const CBigInt& range1, const CBigInt& range2);
	friend 	bool operator<(const CBigInt& range2, const CBigInt& range1);
	friend bool operator<=(const CBigInt& range2, const CBigInt& range1);


	friend CBigInt operator+(CBigInt r1, CBigInt r2);
	friend CBigInt operator+(CBigInt r1, int r2);
	friend CBigInt operator+(CBigInt r1, string r2);
	friend CBigInt operator+(int r2, CBigInt r1);
	friend CBigInt operator+(string r2, CBigInt r1);
	void getpol() { cout << poloz << endl; }
	void prnt() {
		if (!poloz) { cout << "-"; }
		for (auto t : namber) { cout << t; }
		cout << endl;
		return;
	}

private:
	vector<int>namber;
	bool poloz = false;
};


bool operator==(const CBigInt& range1, const CBigInt& range2) {
	if (range2.namber.size() != range1.namber.size() || range2.poloz != range1.poloz) { return false; }
	for (unsigned int i = 0; i < range2.namber.size(); i++) {
		if (range2.namber[i] != range1.namber[i]) { return false; }
	}
	return true;
}
bool operator==(const string& range1, const CBigInt& range2) {
	CBigInt pop(range1);
	return (range2 == pop);
}
bool operator==(const int& range1, const CBigInt& range2) {
	CBigInt pop(range1);
	return (range2 == pop);
}
bool operator==(const CBigInt& range2, const string& range1) {
	CBigInt pop(range1);
	return (range2 == pop);
}
bool operator==(const CBigInt& range2, const int& range1) {
	CBigInt pop(range1);
	return (range2 == pop);
}






bool operator!=(const CBigInt& range1, const CBigInt& range2) {
	return(!(range1 == range2));
}
bool operator!=(const string& range1, const CBigInt& range2) {
	CBigInt pop(range1);
	return !(range2 == pop);
}
bool operator!=(const int& range1, const CBigInt& range2) {
	CBigInt pop(range1);
	return !(range2 == pop);
}
bool operator!=(const CBigInt& range2, const string& range1) {
	CBigInt pop(range1);
	return !(range2 == pop);
}
bool operator!=(const CBigInt& range2, const int& range1) {
	CBigInt pop(range1);
	return !(range2 == pop);
}





bool operator<(const CBigInt& range2, const CBigInt& range1) {
	if (!range2.poloz && range1.poloz) { return true; }
	if (range2.poloz && !range1.poloz) { return false; }
	if ((range2.namber.size() < range1.namber.size()) && (range2.poloz && range1.poloz)) { return true; }
	if ((range2.namber.size() > range1.namber.size()) && (range2.poloz && range1.poloz)) { return false; }
	if ((range2.namber.size() > range1.namber.size()) && (!range2.poloz && !range1.poloz)) { return true; }
	if ((range2.namber.size() < range1.namber.size()) && (!range2.poloz && !range1.poloz)) { return false; }
	if (!range2.poloz && !range1.poloz) {
		for (unsigned int i = 0; i < range2.namber.size(); i++) {
			if (range2.namber[i] > range1.namber[i]) { return true; }
			else if (range2.namber[i] < range1.namber[i]) { return false; }
		}
	}
	else if (range2.poloz && range1.poloz) {
		for (unsigned int i = 0; i < range2.namber.size(); i++) {
			if (range2.namber[i] < range1.namber[i]) { return true; }
			else if (range2.namber[i] > range1.namber[i]) { return false; }
		}
	}
	return false;
}
bool operator<(const CBigInt& range2, const string& range1) {
	CBigInt pop(range1);
	return (range2 < pop);
}
bool operator<(const CBigInt& range2, const int& range1) {
	CBigInt pop(range1);
	return (range2 < pop);
}
bool operator<(const int& range2, const CBigInt& range1) {
	CBigInt pop(range2);
	return (pop < range1);
}
bool operator<(const string& range2, const CBigInt& range1) {
	CBigInt pop(range2);
	return (pop < range1);
}




bool operator<=(const CBigInt& range2, const CBigInt& range1) {
	if (!range2.poloz && range1.poloz) { return true; }
	if (range2.poloz && !range1.poloz) { return false; }
	if ((range2.namber.size() < range1.namber.size()) && (range2.poloz && range1.poloz)) { return true; }
	if ((range2.namber.size() > range1.namber.size()) && (range2.poloz && range1.poloz)) { return false; }
	if ((range2.namber.size() > range1.namber.size()) && (!range2.poloz && !range1.poloz)) { return true; }
	if ((range2.namber.size() < range1.namber.size()) && (!range2.poloz && !range1.poloz)) { return false; }
	if (!range2.poloz && !range1.poloz) {
		for (unsigned int i = 0; i < range2.namber.size(); i++) {
			if (range2.namber[i] > range1.namber[i]) { return true; }
			else if (range2.namber[i] < range1.namber[i]) { return false; }
		}
	}
	else if (range2.poloz && range1.poloz) {
		for (unsigned int i = 0; i < range2.namber.size(); i++) {
			if (range2.namber[i] < range1.namber[i]) { return true; }
			else if (range2.namber[i] > range1.namber[i]) { return false; }
		}
	}
	return true;
}
bool operator<=(const CBigInt& range2, const string& range1) {
	CBigInt pop(range1);
	return (range2 <= pop);
}
bool operator<=(const CBigInt& range2, const int& range1) {
	CBigInt pop(range1);
	return (range2 <= pop);
}
bool operator<=(const int& range2, const CBigInt& range1) {
	CBigInt pop(range2);
	return (pop <= range1);
}
bool operator<=(const string& range2, const CBigInt& range1) {
	CBigInt pop(range2);
	return (pop <= range1);
}


bool operator>(const CBigInt& range2, const CBigInt& range1) {
	return !(range2 <= range1);
}
bool operator>(const CBigInt& range2, const int& range1) {
	return !(range2 <= range1);
}
bool operator>(const CBigInt& range2, const string& range1) {
	return !(range2 <= range1);
}
bool operator>(const string& range2, const CBigInt& range1) {
	return !(range2 <= range1);
}
bool operator>(const int& range2, const CBigInt& range1) {
	return !(range2 <= range1);
}


bool operator>=(const CBigInt& range2, const CBigInt& range1) {
	return !(range2 < range1);
}
bool operator>=(const CBigInt& range2, const long long& range1) {
	return !(range2 < range1);
}
bool operator>=(const CBigInt& range2, const string& range1) {
	return !(range2 < range1);
}
bool operator>=(const string& range2, const CBigInt& range1) {
	return !(range2 < range1);
}
bool operator>=(const long long& range2, const CBigInt& range1) {
	return !(range2 < range1);
}




CBigInt operator*(CBigInt r1, CBigInt r2) {
	r1 *= r2;
	return r1;
}
CBigInt operator*(CBigInt r1, string r2) {
	r1 *= r2;
	return r1;
}
CBigInt operator*(CBigInt r1, int r2) {
	r1 *= r2;
	return r1;
}
CBigInt operator*(string r2, CBigInt r1) {
	r1 *= r2;
	return r1;
}
CBigInt operator*(int r2, CBigInt r1) {
	r1 *= r2;
	return r1;
}
CBigInt operator+(CBigInt r1, CBigInt r2) {
	r1 += r2;
	return r1;
}
CBigInt operator+(CBigInt r1, string r2) {
	r1 += r2;
	return r1;
}
CBigInt operator+(CBigInt r1, int r2) {
	r1 += r2;
	return r1;
}
CBigInt operator+(string r2, CBigInt r1) {
	r1 += r2;
	return r1;
}
CBigInt operator+(int r2, CBigInt r1) {
	r1 += r2;
	return r1;
}



bool operator>>(istringstream& oss, CBigInt& x) {
	string copy = "";
	string range1;
	range1 = oss.str();
	//cout << range1;
	bool get = false;
	for (auto i : range1) {
		//cout << i;
		if ((i <= 57 && i >= 48) || (i == ' ' || i == '-')) {
			if (i <= 57 && i >= 48) {
				get = true;
				copy += i;
				//continue;
			}
			if ((i == '-' || i == ' ') && get) { break; }
			if (i == '-' && !get) {
				get = true;
				copy += i;
			}

		}
		else { break; }
	}
	if (copy == "" || copy == "-") {
		return false;
	}
	else {
		//cout << copy << endl;
		CBigInt p(copy);
		x = p;
		return true;
	}
	return false;
}





ostream& operator<<(ostream& oss, const CBigInt& x) {
	//string result = "";
	if (!x.poloz) { oss << '-'; }
	for (auto t : x.namber) {
		char p = t + 48;
		oss << p;
	}
	return oss;
}


#ifndef __PROGTEST__
static bool equal(const CBigInt& x, const char* val)
{
	ostringstream oss;
	oss << x;
	//cout << oss.str();
	return oss.str() == val;
}
int main(void)
{
	CBigInt a, b;
	istringstream is;
	a = 10;

	a += 20;
	assert(equal(a, "30"));
	a *= 5;
	assert(equal(a, "150"));
	b = a + 3;
	assert(equal(b, "153"));
	b = a * 7;
	assert(equal(b, "1050"));
	assert(equal(a, "150"));
	a = 10;
	a += -20;
	assert(equal(a, "-10"));
	a *= 5;
	assert(equal(a, "-50"));
	b = a + 73;
	assert(equal(b, "23"));
	b = a * -7;
	assert(equal(b, "350"));
	assert(equal(a, "-50"));
	a = "12345678901234567890";
	a += "-99999999999999999999";
	assert(equal(a, "-87654321098765432109"));
	a *= "54321987654321987654";
	a.prnt();
	cout << "-4761556948575111126880627366067073182286" <<endl;
	assert(equal(a, "-4761556948575111126880627366067073182286"));
	a *= 0;
	assert(equal(a, "0"));
	a = 10;
	b = a + "400";
	assert(equal(b, "410"));
	b = a * "15";
	assert(equal(b, "150"));
	assert(equal(a, "10"));
	is.clear();
	is.str(" 1234");
	assert(is >> b);
	assert(equal(b, "1234"));
	is.clear();
	is.str(" 12 34");
	is >> b;
	assert(is >> b);
	assert(equal(b, "12"));
	is.clear();
	is.str("999z");
	assert(is >> b);
	assert(equal(b, "999"));
	is.clear();
	is.str("abcd");
	assert(!(is >> b));
	is.clear();
	is.str("- 758");
	assert(!(is >> b));
	try
	{
		a = "-xyz";
		assert("missing an exception" == NULL);
	}
	catch (const invalid_argument& e)
	{
	}

	a = "73786976294838206464";
	assert(a < "1361129467683753853853498429727072845824");
	assert(a <= "1361129467683753853853498429727072845824");
	assert(!(a > "1361129467683753853853498429727072845824"));
	assert(!(a >= "1361129467683753853853498429727072845824"));
	assert(!(a == "1361129467683753853853498429727072845824"));
	assert(a != "1361129467683753853853498429727072845824");
	assert(!(a < "73786976294838206464"));
	assert(a <= "73786976294838206464");
	assert(!(a > "73786976294838206464"));
	assert(a >= "73786976294838206464");
	assert(a == "73786976294838206464");
	assert(!(a != "73786976294838206464"));
	assert(a < "73786976294838206465");
	assert(a <= "73786976294838206465");
	assert(!(a > "73786976294838206465"));
	assert(!(a >= "73786976294838206465"));
	assert(!(a == "73786976294838206465"));
	assert(a != "73786976294838206465");
	a = "2147483648";
	/*assert(!(a < -2147483648));
	assert(!(a <= -2147483648));
	assert(a > -2147483648);
	assert(a >= -2147483648);
	assert(!(a == -2147483648));
	assert(a != -2147483648);
	*/

	///////////////////////////////////////////
	/*a = "0000000001";
	a.prnt();
	a = "-000000000";
	a.prnt();
	a = "000000000000";
	a.prnt();
	a = "-00001";
	a.prnt();*/
		/*assert(!(a == "1361129467683753853853498429727072845824"));
		a=10;
		a="10"+a;
		a=10+a;
		a=a+a;
		a=2;
		a+=2*a;
		a+="2"*a;
		a+=2+2+a+2;
		a.prnt();*/

	return 0;
}
#endif /* __PROGTEST__ */
