#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <memory>
#include <functional>
#include <stdexcept>
#endif /* __PROGTEST */
using namespace std;

#ifndef __PROGTEST__
class CTimeStamp
{
public:
	CTimeStamp(int               year,
		int               month,
		int               day,
		int               hour,
		int               minute,
		int               sec) {
		this->day = day;
		this->hour = hour;
		this->minute = minute;
		this->sec = sec;
		this->year = year;
		this->month = month;
	}
	int            Compare(const CTimeStamp& x) const {
		if (year != x.year) {
			if (year > x.year)
				return 1;
			else
				return -1;
		}
		if (month != x.month) {
			if (month > x.month)
				return 1;
			else
				return -1;
		}
		if (day != x.day) {
			if (day > x.day)
				return 1;
			else
				return -1;
		}
		if (hour != x.hour) {
			if (hour > x.hour)
				return 1;
			else
				return -1;
		}
		if (minute != x.minute) {
			if (minute > x.minute)
				return 1;
			else
				return -1;
		}
		if (sec > x.sec)
			return 1;
		if (sec == x.sec)
			return 0;
		else
			return -1;
		return 1;
	}

	friend ostream& operator << (ostream& os, const CTimeStamp& x)
	{
		
		return os << x.year << '-' << setw(2) << setfill('0') << x.month << '-' << setw(2) << setfill('0') << x.day << ' ' << setw(2) << setfill('0') << x.hour << ':' << setw(2) << setfill('0') << x.minute << ':' << setw(2) << setfill('0') << x.sec;
		//"2014-03-31 15:24:13"
	}
private:
	int               year;
	int               month;
	int               day;
	int               hour;
	int               minute;
	int               sec;
};
//=================================================================================================
class CMailBody
{
public:
	CMailBody(int               size,
		const char* data) {
		m_Size = size;
		m_Data = data;
	}
	// copy cons/op=/destructor is correctly implemented in the testing environment
	friend ostream& operator <<                           (ostream& os,
		const CMailBody& x)
	{
		return os << "mail body: " << x.m_Size << " B";
	}
private:
	int            m_Size;
	const char* m_Data;
};
//=================================================================================================
class CAttach
{
public:
	CAttach(int               x)
		: m_X(x),
		m_RefCnt(1)
	{
		//m_X = x;
		//m_RefCnt = 1;
	}
	CAttach(const CAttach& x) {
		m_X = x.m_X;
		m_RefCnt = x.m_RefCnt;
	}
	void           AddRef(void) const
	{
		m_RefCnt++;
	}
	void           Release(void) const
	{
		if (!--m_RefCnt)
			delete this;
	}
private:
	int            m_X;
	mutable int    m_RefCnt;
	//CAttach(const CAttach& x);
	CAttach& operator =                              (const CAttach& x) {
		m_RefCnt =x.m_RefCnt;
		m_X = x.m_X;
		return *this;
	}
	~CAttach(void) = default;
	friend ostream& operator <<                           (ostream& os,
		const CAttach& x)
	{
		return os << "attachment: " << x.m_X << " B";
	}
};
//=================================================================================================
#endif /* __PROGTEST__, DO NOT remove */


class CMail
{
public:
	CMail(const CTimeStamp& timeStamp,
		const string& from,
		const CMailBody& body,
		const CAttach* attach)
		:timeStamp(timeStamp), from(from), body(body), attach(attach) {
		if(attach)attach->AddRef();
	}
	const string& From(void) const { return from; }
	const CMailBody& Body(void) const { return body; }
	const CTimeStamp& TimeStamp(void) const { return timeStamp; }
	const CAttach* Attachment(void) const { return attach; }

	friend ostream& operator <<                           (ostream& os,
		const CMail& x){
		os << x.timeStamp << ' ' << x.from << " "<< x.body;
		if (x.Attachment())
			os <<" + "<<*x.attach;
		//os << endl;
		return os;
	}
	CMail& operator= (const CMail& o) {
		timeStamp = o.timeStamp;
		from = o.from;
		body = o.body;
		attach = o.attach;
		if (attach)attach->AddRef();
		return *this;
	}
	
private:
	CTimeStamp timeStamp;
	string from;
	CMailBody body;
	const CAttach* attach;
};
//=================================================================================================
class CMailBox
{
public:
	CMailBox(void) {
		list<CMail>p;
		box["inbox"] = p;
	}
	bool           Delivery(const CMail& mail) {
		auto it = lower_bound(box["inbox"].begin(), box["inbox"].end(), mail, cmp());
		CMail ppp = mail;
		box["inbox"].insert(it, ppp);
		auto it1 = lower_bound(all.begin(), all.end(), mail, cmp());
		all.insert(it1,ppp);
		return true;
	}
	bool           NewFolder(const string& folderName) {
		if (box.find(folderName)!=box.end()) { return false; }
		list<CMail>p;
		box[folderName] = p;
		return true;
	}

	bool           MoveMail(const string& fromFolder,
		const string& toFolder) {
		if (box.find(fromFolder) == box.end()) { return false; }
		if (box.find(toFolder) == box.end()) { return false; }
		if (box[toFolder].size() == 0) {
			box[toFolder] = box[fromFolder];
			box[fromFolder].clear();
			return true;
		}
		for(auto it=box[fromFolder].begin();it!=box[fromFolder].end();it++){
			auto it4 = lower_bound(box.at(toFolder).begin(), box.at(toFolder).end(), *it, cmp());
			box[toFolder].insert(it4, *it);
		}
		box[fromFolder].clear();
		return true;
	}
	list<CMail>    ListMail(const string& folderName,
		const CTimeStamp& from,
		const CTimeStamp& to) const {
		list<CMail>result;
		CMail pop(from, "", CMailBody(0, ""), nullptr);
		auto it = lower_bound(box.at(folderName).begin(), box.at(folderName).end(),pop,cmp());
		if (it != box.at(folderName).end()) {
			while (it != box.at(folderName).end()) {
				if (it->TimeStamp().Compare(to) > 0)
					break;
				result.push_back(*it);
				it++;
			}
		}
		return result;

	}
	set<string>    ListAddr(const CTimeStamp& from,
		const CTimeStamp& to) const {
		set<string>result;
		CMail pop(from, "", CMailBody(0, ""), nullptr);
		auto it = lower_bound(all.begin(), all.end(), pop, cmp());
		if (it != all.end()) {
			while (it != all.end()) {
				if (it->TimeStamp().Compare(to)>0)
					break;
				result.insert(it->From());
				it++;
			}
		}
		return result;
	}
private:
	struct cmp
	{
		bool operator() (const CMail& x, const CMail& y) const{
			int p = (x.TimeStamp().Compare(y.TimeStamp()));
			if (p < 0)
				return 1;
			else
				return 0;
		}

	};
	map<string, list<CMail>>box;
	list<CMail>all;

};
//=================================================================================================
#ifndef __PROGTEST__
static string showMail(const list<CMail>& l)
{
	ostringstream oss;
	for (const auto& x : l)
		oss << x << endl;
	return oss.str();
}
static string showUsers(const set<string>& s)
{
	ostringstream oss;
	for (const auto& x : s)
		oss << x << endl;
	return oss.str();
}
int main(void)
{
	list<CMail> mailList;
	set<string> users;
	CAttach* att;

	CMailBox m0;
	assert(m0.Delivery(CMail(CTimeStamp(2014, 3, 31, 15, 24, 13), "user1@fit.cvut.cz", CMailBody(14, "mail content 1"), nullptr)));
	assert(m0.Delivery(CMail(CTimeStamp(2014, 3, 31, 15, 26, 23), "user2@fit.cvut.cz", CMailBody(22, "some different content"), nullptr)));
	att = new CAttach(200);
	assert(m0.Delivery(CMail(CTimeStamp(2014, 3, 31, 11, 23, 43), "boss1@fit.cvut.cz", CMailBody(14, "urgent message"), att)));
	assert(m0.Delivery(CMail(CTimeStamp(2014, 3, 31, 18, 52, 27), "user1@fit.cvut.cz", CMailBody(14, "mail content 2"), att)));
	att->Release();
	att = new CAttach(97);
	assert(m0.Delivery(CMail(CTimeStamp(2014, 3, 31, 16, 12, 48), "boss1@fit.cvut.cz", CMailBody(24, "even more urgent message"), att)));
	att->Release();

	assert(showMail(m0.ListMail("inbox",
		CTimeStamp(2000, 1, 1, 0, 0, 0),
		CTimeStamp(2050, 12, 31, 23, 59, 59))) == "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B + attachment: 200 B\n"
		"2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
		"2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B\n"
		"2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B + attachment: 97 B\n"
		"2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 200 B\n");
	assert(showMail(m0.ListMail("inbox",
		CTimeStamp(2014, 3, 31, 15, 26, 23),
		CTimeStamp(2014, 3, 31, 16, 12, 48))) == "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B\n"
		"2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B + attachment: 97 B\n");
	assert(showUsers(m0.ListAddr(CTimeStamp(2000, 1, 1, 0, 0, 0),
		CTimeStamp(2050, 12, 31, 23, 59, 59))) == "boss1@fit.cvut.cz\n"
		"user1@fit.cvut.cz\n"
		"user2@fit.cvut.cz\n");
	assert(showUsers(m0.ListAddr(CTimeStamp(2014, 3, 31, 15, 26, 23),
		CTimeStamp(2014, 3, 31, 16, 12, 48))) == "boss1@fit.cvut.cz\n"
		"user2@fit.cvut.cz\n");

	CMailBox m1;
	assert(m1.NewFolder("work"));
	assert(m1.NewFolder("spam"));
	assert(!m1.NewFolder("spam"));
	assert(m1.Delivery(CMail(CTimeStamp(2014, 3, 31, 15, 24, 13), "user1@fit.cvut.cz", CMailBody(14, "mail content 1"), nullptr)));
	att = new CAttach(500);
	assert(m1.Delivery(CMail(CTimeStamp(2014, 3, 31, 15, 26, 23), "user2@fit.cvut.cz", CMailBody(22, "some different content"), att)));
	att->Release();
	assert(m1.Delivery(CMail(CTimeStamp(2014, 3, 31, 11, 23, 43), "boss1@fit.cvut.cz", CMailBody(14, "urgent message"), nullptr)));
	att = new CAttach(468);
	assert(m1.Delivery(CMail(CTimeStamp(2014, 3, 31, 18, 52, 27), "user1@fit.cvut.cz", CMailBody(14, "mail content 2"), att)));
	att->Release();
	assert(m1.Delivery(CMail(CTimeStamp(2014, 3, 31, 16, 12, 48), "boss1@fit.cvut.cz", CMailBody(24, "even more urgent message"), nullptr)));
	assert(showMail(m1.ListMail("inbox",
		CTimeStamp(2000, 1, 1, 0, 0, 0),
		CTimeStamp(2050, 12, 31, 23, 59, 59))) == "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B\n"
		"2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
		"2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B\n"
		"2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B\n"
		"2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B\n");
	assert(showMail(m1.ListMail("work",
		CTimeStamp(2000, 1, 1, 0, 0, 0),
		CTimeStamp(2050, 12, 31, 23, 59, 59))) == "");
	assert(m1.MoveMail("inbox", "work"));
	assert(showMail(m1.ListMail("inbox",
		CTimeStamp(2000, 1, 1, 0, 0, 0),
		CTimeStamp(2050, 12, 31, 23, 59, 59))) == "");
	assert(showMail(m1.ListMail("work",
		CTimeStamp(2000, 1, 1, 0, 0, 0),
		CTimeStamp(2050, 12, 31, 23, 59, 59))) == "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B\n"
		"2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
		"2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B\n"
		"2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B\n"
		"2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B\n");
	assert(m1.Delivery(CMail(CTimeStamp(2014, 3, 31, 19, 24, 13), "user2@fit.cvut.cz", CMailBody(14, "mail content 4"), nullptr)));
	att = new CAttach(234);
	assert(m1.Delivery(CMail(CTimeStamp(2014, 3, 31, 13, 26, 23), "user3@fit.cvut.cz", CMailBody(9, "complains"), att)));
	att->Release();
	assert(showMail(m1.ListMail("inbox",
		CTimeStamp(2000, 1, 1, 0, 0, 0),
		CTimeStamp(2050, 12, 31, 23, 59, 59))) == "2014-03-31 13:26:23 user3@fit.cvut.cz mail body: 9 B + attachment: 234 B\n"
		"2014-03-31 19:24:13 user2@fit.cvut.cz mail body: 14 B\n");
	assert(showMail(m1.ListMail("work",
		CTimeStamp(2000, 1, 1, 0, 0, 0),
		CTimeStamp(2050, 12, 31, 23, 59, 59))) == "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B\n"
		"2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
		"2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B\n"
		"2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B\n"
		"2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B\n");
	assert(m1.MoveMail("inbox", "work"));
	assert(showMail(m1.ListMail("inbox",
		CTimeStamp(2000, 1, 1, 0, 0, 0),
		CTimeStamp(2050, 12, 31, 23, 59, 59))) == "");
	assert(showMail(m1.ListMail("work",
		CTimeStamp(2000, 1, 1, 0, 0, 0),
		CTimeStamp(2050, 12, 31, 23, 59, 59))) == "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B\n"
		"2014-03-31 13:26:23 user3@fit.cvut.cz mail body: 9 B + attachment: 234 B\n"
		"2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
		"2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B\n"
		"2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B\n"
		"2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B\n"
		"2014-03-31 19:24:13 user2@fit.cvut.cz mail body: 14 B\n");

	return 0;
}
#endif /* __PROGTEST__ */
