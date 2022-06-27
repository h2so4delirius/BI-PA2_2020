#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;
#endif /* __PROGTEST__ */
class drevo
{
public:
	drevo* left=NULL;
	drevo* right=NULL;
	char symbol = ' ';
};







void pidr(vector<int>pop,unsigned int &i,drevo *uk,bool &bug) {
	if(pop.size()<=i){
		bug=false;
		return;			
	}
	if (pop[i] == 1) {
		if(pop.size()<=i+8){
			bug=false;
			return;			
			}
		uint8_t p = pop[i+8];

		for(int j=7,x=1;j>0;j--,x++){
			//cout << pop[i + j];
			if (pop[i + j] == 1) {
				int po = 2;
				for (int k = 1; k < x; k++)
					po *= 2;
				p += po;
			}
		}
		//cout<<endl<<(char)p<<endl;
		i += 9;
		//drevo *kk= new drevo;
		uk->symbol = (char)p;

	}
	else {
		
		drevo *l=new drevo;
		drevo *r=new drevo;
		uk->left = l;
		uk->right = r;
		i++;
		pidr(pop, i, uk->left,bug);
		pidr(pop, i, uk->right,bug);
	}

	return;
}


void bit(uint8_t p, vector<int> &lol) {
	for (int i = 0; i < 8; i++) {
		uint8_t tmp = p;
		tmp <<= i;
		tmp >>= 7;
		lol.push_back(tmp);
	}
	return;
}


bool decompressFile(const char* inFileName, const char* outFileName)
{
	string resenie="";
	
	vector<drevo>dre;
	vector<int>lol;
	uint8_t p;
	ifstream in(inFileName, ios::binary | ios::in);
	if (!in.good()) {
		in.close();
		return false;
	}
	in.seekg(0, ios::end);
	int size = (int)in.tellg();
	in.seekg(0, ios::beg);
	if (size==0) {
		ofstream out(outFileName, ios::binary);
		if (!out.good() && !out.is_open()) {
			out.close();
			return false;
		}
		out << resenie;
		out.close();
		in.close();
	}
	//cout << sizeOfFile << endl;
	drevo* ppp=NULL;
	ppp = new drevo;
	for (int i = 0; i < size; i++)
		{
		if (!in.read((char*)& p, sizeof(uint8_t)))
			return false;
		if (p > 255)
			return false;
		bit(p,lol);
		}
	in.close();
	unsigned int i = 0;
	bool bug=true;
	pidr(lol,i,ppp,bug);
	if(!bug)return false;
	//cout << lol.size()<<endl;
	//cout << i << endl;
	int pocet;
	for(auto p:lol)cout<<p;
	cout<<endl;
	while (true)
	{
		if (lol.size() == i)
			return false;
		bool per=false;
		if (lol[i] == 0) {
			per = true;
			i++;
			pocet = lol[i + 11];
			for (int j = 10, x = 1; j >= 0; j--, x++) {
				if (lol[i + j] == 1) {
					int po = 2;
					for (int k = 1; k < x; k++)
						po *= 2;
					pocet += po;
				}
			}
			//cout << pocet << endl;
			i += 12;
		}
		else {
			pocet = 4096;
			i++;
		}

		
		for (int j=0;j<pocet;j++) {
			//cout << resenie<<endl;
			drevo* spusk = ppp;
			while (1) {
				if (lol.size() == i) {
					return false;
				}
				if (lol[i] == 0) {
					i++;
					spusk = spusk->left;
					if ((spusk->left == NULL) && (spusk->right == NULL)) {
						resenie += spusk->symbol;
						break;
					}
					if ((spusk->left == NULL))
						return false;
					if ((spusk->right == NULL))
						return false;
					
				}
				else {
					i++;
					spusk = spusk->right;
					if ((spusk->left == NULL )&& (spusk->right == NULL)) {
						resenie += spusk->symbol;
						break;
					}
					if ((spusk->left == NULL))
						return false;
					if ((spusk->right == NULL))
						return false;
				}
				
			}
		}


		if (per)
			
			break;
	}
	cout << resenie;
	ofstream out(outFileName, ios::binary);
	if (!out.good()&&!out.is_open()) {
		out.close();
		return false;
	}
	
	/*for(auto kk:resenie){
		if(!out.write((char*)&p,sizeof(char))){
		      out.close();
		      return false; 
		}
	}*/
	if(!(out << resenie)){out.close();return false;}
	out.close();


	return true;
}

bool compressFile(const char* inFileName, const char* outFileName)
{

	// keep this dummy implementation (no bonus) or implement the compression (bonus)
	return false;
}
#ifndef __PROGTEST__
bool identicalFiles(const char* fileName1, const char* fileName2)
{
		return false;
}

int main(void)
{
	assert(decompressFile("tests/test0.huf", "tempfile"));
	assert(identicalFiles("tests/test0.orig", "tempfile"));

	assert(decompressFile("tests/test1.huf", "tempfile"));
	assert(identicalFiles("tests/test1.orig", "tempfile"));

	assert(decompressFile("tests/test2.huf", "tempfile"));
	assert(identicalFiles("tests/test2.orig", "tempfile"));

	assert(decompressFile("tests/test3.huf", "tempfile"));
	assert(identicalFiles("tests/test3.orig", "tempfile"));

	assert(decompressFile("tests/test4.huf", "tempfile"));
	assert(identicalFiles("tests/test4.orig", "tempfile"));

	assert(!decompressFile("tests/test5.huf", "tempfile"));




	//assert(decompressFile("tests/extra0.huf", "tempfile"));
	//assert(identicalFiles("tests/extra0.orig", "tempfile"));

	//assert(decompressFile("tests/extra1.huf", "tempfile"));
	//assert(identicalFiles("tests/extra1.orig", "tempfile"));

	//assert(decompressFile("tests/extra2.huf", "tempfile"));
	//assert(identicalFiles("tests/extra2.orig", "tempfile"));

	//assert(decompressFile("tests/extra3.huf", "tempfile"));
	//assert(identicalFiles("tests/extra3.orig", "tempfile"));

	//assert(decompressFile("tests/extra4.huf", "tempfile"));
	//assert(identicalFiles("tests/extra4.orig", "tempfile"));

	//assert(decompressFile("tests/extra5.huf", "tempfile"));
	//assert(identicalFiles("tests/extra5.orig", "tempfile"));

	//assert(decompressFile("tests/extra6.huf", "tempfile"));
	//assert(identicalFiles("tests/extra6.orig", "tempfile"));

	//assert(decompressFile("tests/extra7.huf", "tempfile"));
	//assert(identicalFiles("tests/extra7.orig", "tempfile"));

	//assert(decompressFile("tests/extra8.huf", "tempfile"));
	//assert(identicalFiles("tests/extra8.orig", "tempfile"));

	//assert(decompressFile("tests/extra9.huf", "tempfile"));
	//assert(identicalFiles("tests/extra9.orig", "tempfile"));
	
	return 0;
}
#endif /* __PROGTEST__ */
