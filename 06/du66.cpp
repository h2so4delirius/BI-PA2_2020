#ifndef __PROGTEST__
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <memory>
#include <functional>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

/**
    * @brief main abstract class for all cells  
*/
class C_FATHER {
public:

	/**
    * @brief abstract method that makes output for cell 
    * @param[in] ostringstream& oss -> output string stream
	* @param[in] unsigned int poz_1 -> position in height 
	* @param[in] int unsigned vysota ->  max height of text
	* @param[in] unsigned int vysota_all -> max height of cell
    */
	virtual void vypis(ostringstream& oss,unsigned int poz_1, int unsigned vysota,unsigned int vysota_all) = 0;
	/**
    * @brief abstract method that makes output for cell
	  @return width of cell
	*/
	virtual unsigned int getmax_s() = 0;
	/**
    * @brief abstract method that output for cell
	  @return height of cell
	*/
	virtual unsigned int getmax_v() = 0;
	/**
    * @brief abstract method that return data of cell
	  * @return data in vector of all rows
	*/
	virtual vector<string> getstr() const = 0;
  /**
    * @brief abstract method that return type of class
	  * @return type of class
	*/
	virtual unsigned int get_num() = 0;
  /**
    * @brief abstract method that return align of text
	  * @return align of text
	*/
	virtual bool getALIGN() const = 0;
	virtual ~C_FATHER() {};
};
/**
    * @brief child class of C_FATHER that represnts empty cell
*/
class CEmpty :public C_FATHER
{
public:
	/**
    * @brief virtual method that makes output for cell 
    * @param[in] ostringstream& oss -> output string stream
	* @param[in] unsigned int poz_1 -> position in height 
	* @param[in] int unsigned vysota ->  max height of text
	* @param[in] unsigned int vysota_all -> max height of cell
    */
	 void vypis(ostringstream& oss,unsigned  int poz_1,unsigned int vysota,unsigned int vysota_all);
  /**
    * @brief virtual method that return type of class
	  * @return type of class
	*/
	 unsigned int get_num() { return 1; }
  /**
    * @brief virtual method that return data of cell
	  * @return data in vector of all rows
	*/
	 vector<string> getstr() const { vector<string>p; return p; }
  /**
    * @brief virtual method that return align of text
	  * @return align of text
	*/
	 bool getALIGN() const { return 1; }
	/**
    * @brief virtual method that makes output for cell
	  @return width of cell
	*/
	  unsigned int getmax_s() { return 0; }
	/**
    * @brief virtual method that makes output for cell
	  @return width of cell
	*/
	  unsigned int getmax_v() { return 0; }
};
//---------------------------------------------------------------------------------------------------
	 void CEmpty::vypis(ostringstream& oss,unsigned  int poz_1,unsigned int vysota,unsigned int vysota_all) {
		oss << "|";
		for (unsigned int i = 0; i < poz_1; i++) {
			//cout << " ";
			oss << " ";
		}
		return;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
    * @brief child class of C_FATHER that represnts empty cell
*/
class CText :public C_FATHER
{
public:
	/**
    * @brief virtual method that makes output for cell 
    * @param[in] ostringstream& oss -> output string stream
	* @param[in] unsigned int poz_1 -> position in height 
	* @param[in] int unsigned vysota ->  max height of text
	* @param[in] unsigned int vysota_all -> max height of cell
    */
	void vypis(ostringstream& oss,unsigned  int poz_1, int unsigned vysota,unsigned  int vysotaota_all);\
	/**
        * @brief default constructor
	* @param[in] string str -> text of cell 
	* @param[in] bool ALIGN -> align 
	*/ 

	CText(string str, bool ALIGN);
	/**
        * @brief default constructor
	* @param[in] vector<string> str -> text of cell 
	* @param[in] bool ALIGN -> align 
	*/ 

	CText(vector<string> str, bool ALIGN);
	/**
        * @brief chnge old text to new text
	* @param[in] string str -> text of cell 
	*/ 
	void SetText(string str);
    /**
    * @brief virtual method that return data of cell
	  * @return data in vector of all rows
	*/
	vector<string> getstr() const{ return obrazek; }
  /**
    * @brief virtual method that return align of text
	  * @return align of text
	*/
	bool getALIGN() const{ return ALIGN; }
	/**
        * @brief set new  width of text
	* @param[in] int max_s -> width of text
	*/ 
	void setmax_s( int max_s) { this->max_s=max_s; }
	/**
        * @brief set new  height of text
	* @param[in] int max_v -> height of text
	*/ 
	void setmax_v( int max_v) { this->max_v=max_v; }
	/**
    * @brief virtual method that makes output for cell
	  @return width of cell
	*/
	unsigned int getmax_s() { return max_s; }
	/**
    * @brief virtual method that makes output for cell
	  @return width of cell
	*/
	unsigned int getmax_v() { return obrazek.size(); }

  /**
    * @brief virtual method that return type of class
	  * @return type of class
	*/
	unsigned int get_num() { return 2; }



	static const bool ALIGN_LEFT = false;
	static const bool ALIGN_RIGHT = true;
private:
	bool ALIGN=false;
	unsigned int max_s=0;
	unsigned int max_v=0;
	vector<string>obrazek;
};
//--------------------------------------------------------------------------------------------------------------------------------

void CText::vypis(ostringstream& oss,unsigned  int poz_1, int unsigned vysota,unsigned  int vysotaota_all) {
		oss << "|";
		bool flag = false;
		for (unsigned int i = 0; i < poz_1;) {
			if (!ALIGN) {
				if (i == 0 && vysota < obrazek.size()&&!flag&&vysota>=0) {
					for (auto it = obrazek[vysota].begin(); it < obrazek[vysota].end(); it++) {
						oss << *it;
						i++;
					}
					flag = true;
				}
				else {
					i++;
					oss << " ";
				}
			}
			else {
				if (vysota < obrazek.size()) {
					if (i >= poz_1 - obrazek[vysota].size() && !flag&&vysota>=0) {
						for (auto it = obrazek[vysota].begin(); it < obrazek[vysota].end(); it++) {
							oss << *it;
							i++;
						}
						flag = true;
					}
					else {
						i++;
						oss << " ";
					}
				}
				else {
					i++;
					oss << " ";
				}
			}
		}
		return;
	}

CText::CText(string str, bool ALIGN) {
		this->ALIGN = ALIGN;
		string a="";
		for (unsigned  int i = 0; i < str.size();i++) {
			if(str[i]!='\n')
				a += str[i];
			if (str[i] == '\n'||i==str.size()-1) {
				if (a.size() > max_s) { max_s = a.size(); }
				obrazek.push_back(a);
				a = "";
				if (i == str.size() - 1 && str[i] == '\n') {
					obrazek.push_back("");
				}
			}
		}
		max_v = obrazek.size();
	}


	CText::CText(vector<string> str, bool ALIGN) {
		this->obrazek = str;
		this->ALIGN = ALIGN;
	}


    void CText::SetText(string str) {
		max_s=0;
		obrazek.clear();
		unsigned  int poz_1 = 0;
		string a = "";
		for (unsigned int i = 0; i < str.size(); i++) {
			if (str[i] != '\n')
				a += str[i];
			poz_1 += 1;
			if (str[i] == '\n' || i == str.size() - 1) {
				obrazek.push_back(a);
				a = "";
				
				if (str[i] == '\n'&&str!=""&&poz_1!=0) { poz_1--; }
				
				if (poz_1 > max_s) { max_s = poz_1; }
				poz_1 = 0;
			}
		}
		max_v = obrazek.size();
		return;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
    * @brief child class of C_FATHER that represnts empty cell
*/
class CImage :public C_FATHER
{
public:
	/**
    	* @brief virtual method that makes output for cell 
    	* @param[in] ostringstream& oss -> output string stream
	* @param[in] unsigned int poz_1 -> position in height 
	* @param[in] int unsigned vysota ->  max height of text
	* @param[in] unsigned int vysota_all -> max height of cell
    	*/
	void vypis(ostringstream& oss,unsigned int poz_1,int unsigned vysota,unsigned int alt_max);
	/*
    	* @default constructor
	*/
	CImage(){}
	/*
    	* @default constructor
	* @param[in] vector<string>a -> text of cell 
	* @param[in] int max_s -> max weight of text
	* @param[in] int max_v -> max height of text
	*/	
	CImage(vector<string>a, int max_s, int max_v);
	/*    	
	* @default set new string of cell
	* @param[in] string a -> string of cell
	*/	
	CImage& AddRow(string a);
    	/**
    	* @brief virtual method that return data of cell
	* @return data in vector of all rows
	*/
	vector<string> getstr()const { return obrazek; }
	/**
    * @brief virtual method that makes output for cell
	  @return width of cell
	*/
	unsigned int getmax_s() { return max_s; }
	/**
    	* @brief virtual method that makes output for cell
	* @return height of cell
	*/
	unsigned int getmax_v() { return obrazek.size(); }
    /**
    * @brief virtual method that return align of text
	  * @return align of text
	*/
	bool getALIGN() const { return 1; }
    /**
    * @brief virtual method that return type of class
	  * @return type of class
	*/
	unsigned int get_num() { return 3; }
private:
	vector<string>obrazek;
	unsigned int max_s=0;
	unsigned int max_v = 0;
};
//-----------------------------------------------------------------------------------------------------------------------
	void CImage::vypis(ostringstream& oss,unsigned int poz_1,int unsigned vysota,unsigned int alt_max) {
		oss << "|";
		unsigned int wid = (poz_1 - max_s) / 2;
		unsigned int alt = (alt_max - max_v) / 2;
		if (vysota < alt||vysota>=alt+max_v) {
			for (unsigned  int i = 0; i < poz_1; i++) {
				oss << " ";
			}
		}
		else {
			unsigned  int i = 0;
			while (i < poz_1) {
				if (i < wid|| i>=wid + max_s) {
					oss << " ";
					i++;
				}
				else if(obrazek.size()!=0){
					if(vysota-alt<obrazek.size()&&vysota-alt>=0){
						oss << obrazek[vysota-alt];
						i += obrazek[vysota-alt].size();
					}
				}
				else{
					oss << " ";
					i++;					
				}

			}
		}
		return;
	}


	CImage::CImage(vector<string>a, int max_s, int max_v){
		obrazek = a;
		this->max_s = max_s;
		this->max_v = max_v;
	}

	CImage& CImage::AddRow(string a) {
		max_v++;
		string b = a;
		obrazek.push_back(b);
		if (b.size() > max_s) { max_s = b.size(); }
		return *this;
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CTable
{
public:
	/*
    *@brief operator = make copy
    *@param[in] CTable copy -> copy
	*@return copy
	*/
	CTable& operator=( CTable &copy);
	/*
    *@brief default constructor
    */
	CTable(){}
	/*
    *@brief default destructor
    */
	~CTable();
	/*
    *@brief default constructor
    *@param[in] CTable copy -> copy
    */
	CTable(CTable& copy);
	/*
    *@brief default constructor
    *@param[in] unsigned int x -> height of table
    *@param[in] unsigned int y -> weight of table
    */
	CTable(unsigned int x, unsigned int y);
	/*
    *@brief get cell
    *@param[in] unsigned int x -> position
    *@param[in] unsigned int y -> position
	*@return cell of table
    */
	C_FATHER& GetCell(unsigned int x,unsigned int y);
	/*
    *@brief set cell
    *@param[in] unsigned int x -> position
    *@param[in] unsigned int y -> position
    *@param[in] CText text -> cell
    */
	void SetCell(unsigned int x,unsigned  int y,CText text);
	/*
    *@brief set cell
    *@param[in] unsigned int x -> position
    *@param[in] unsigned int y -> position
    *@param[in] CImage text -> cell
    */
	void SetCell(unsigned int x, unsigned int y, CImage text);
	/*
    *@brief set cell
    *@param[in] unsigned int x -> position
    *@param[in] unsigned int y -> position
    *@param[in]  CEmpty text -> cell
    */
	void SetCell(unsigned int x, unsigned int y, CEmpty text);
	/*
    *@brief set cell
    *@param[in] unsigned int x -> position
    *@param[in] unsigned int y -> position
    *@param[in] C_FATHER text -> cell
    */
	void SetCell(unsigned int x, unsigned int y, C_FATHER &text);
	/*
    *@brief set cell
    *@param[in] ostringstream oss,CTable b -> ostringstream
	*@return ostringstream -> table
    */
	friend ostringstream& operator << (ostringstream&oss,CTable&b);


private:
	unsigned  int x, y;
	vector<unsigned int>max_s;
	vector<unsigned int>max_v;
	vector<vector<C_FATHER*>>obrazek;
};
//----------------------------------------------------------------------------------------------------------------------

	ostringstream& operator << (ostringstream&oss,CTable&b) {
		for (unsigned int i = 0; i < b.y; i++) {
			b.max_s[i] = 0;
		}
		for (unsigned int i = 0; i <b.x; i++) {
			b.max_v[i] = 0;
		}
		
		for (unsigned int i = 0; i < b.x; i++) {
			for (unsigned int j = 0; j < b.y; j++) {
				if (b.obrazek[i][j]->getmax_s()>b.max_s[j]) {
					
					b.max_s[j]=b.obrazek[i][j]->getmax_s();
				}
				if (b.obrazek[i][j]->getmax_v() > b.max_v[i]) {
					b.max_v[i] = b.obrazek[i][j]->getmax_v();
				}
		}
		}
		for (auto i : b.max_s) {
			oss << "+";
			for (unsigned int j = 0; j < i; j++) {
				oss << "-";
			}
		}
		oss <<"+"<< endl;
		for (unsigned  int i = 0; i < b.x; i++) {
			for (unsigned  int p = 0; p < b.max_v[i]; p++) {
				for (unsigned  int j = 0; j < b.y; j++) {
					b.obrazek[i][j]->vypis(oss,b.max_s[j],p, b.max_v[i]);
				}
				oss <<"|"<< endl;
			}
			for (auto i : b.max_s) {
				oss << "+";
				for (unsigned int j = 0; j < i; j++) {
					oss << "-";
				}
			}
			oss << "+" << endl;
		}
		
		return oss;
	}


	CTable& CTable::operator=( CTable &copy) {
			for (unsigned int i = 0; i < x; i++) {
				for (unsigned int j = 0; j < y; j++) {
					delete obrazek[i][j];
				}
				obrazek[i].clear();
			}
			obrazek.clear();
			this->max_s = copy.max_s;
			this->max_v = copy.max_v;
			this->x = copy.x;
			this->y = copy.y;
			for (unsigned int i = 0; i < x; i++) {
				vector<C_FATHER*>k;
				for (unsigned int j = 0; j < y; j++) {
					CEmpty* poz_1 = new CEmpty();
					k.push_back(poz_1);

				}
				obrazek.push_back(k);
			}
			for (unsigned int i = 0; i < copy.x; i++) {
				for (unsigned int j = 0; j < copy.y; j++) {
					SetCell(i, j, copy.GetCell(i, j));
				}
			}
			return *this;
		
	}



	CTable::CTable(CTable& copy) {
		this->max_s = copy.max_s;
		this->max_v = copy.max_v;
		this->x = copy.x;
		this->y = copy.y;
		for ( unsigned int i = 0; i < x; i++) {
			vector<C_FATHER*>k;
			for ( unsigned int j = 0; j < y; j++) {
				CEmpty* poz_1 = new CEmpty();
				k.push_back(poz_1);

			}
			obrazek.push_back(k);
		}
		for (unsigned int i = 0; i < x; i++) {
			for (unsigned int j = 0; j < y;j++) {
				SetCell(i, j, copy.GetCell(i, j));
			}
		}
	}
	CTable::CTable(unsigned int x, unsigned int y) {
		this->x = x;
		this->y = y;
		for(unsigned  int i=0;i<y;i++){ max_s.push_back(0);}
		for (unsigned  int i = 0; i < x; i++) {
			vector<C_FATHER*>k;
			for (unsigned  int j = 0; j < y; j++) {
				CEmpty *poz_1=new CEmpty();
				k.push_back(poz_1);
				
			}
			obrazek.push_back(k);
			max_v.push_back(0);
		}
	}
	C_FATHER& CTable::GetCell(unsigned int x,unsigned int y) {
		return *obrazek[x][y];
	}
	void CTable::SetCell(unsigned int x,unsigned  int y,CText text) {
		delete obrazek[x][y];
		CText* poz_1 = new CText(text.getstr(),text.getALIGN());
		
		poz_1->setmax_s(text.getmax_s());
		poz_1->setmax_v(text.getmax_v());
		obrazek[x][y] = poz_1;
		return;
	}
	void CTable::SetCell(unsigned int x, unsigned int y, CImage text) {
		
		delete obrazek[x][y];
		CImage* poz_1 = new CImage(text.getstr(),text.getmax_s(),text.getmax_v());
		obrazek[x][y] = poz_1;
		return;
	}
	void CTable::SetCell(unsigned int x, unsigned int y, CEmpty text) {
		delete obrazek[x][y];
		CEmpty* poz_1 = new CEmpty();
		obrazek[x][y] = poz_1;
		return;
	}
	void CTable::SetCell(unsigned int x, unsigned int y, C_FATHER &text) {
		if(obrazek[x][y]==&text){return;}
		if (text.get_num() == 1) {
			delete obrazek[x][y];
			CEmpty* poz_1 = new CEmpty();
			obrazek[x][y] = poz_1;
			return;
		}
		if (text.get_num() == 2) {
			delete obrazek[x][y];
			CText* poz_1 = new CText(text.getstr(), text.getALIGN());
			poz_1->setmax_s(text.getmax_s());
			poz_1->setmax_v(text.getmax_v());
			obrazek[x][y] = poz_1;
			return;
		}
		if (text.get_num() == 3) { 
			delete obrazek[x][y];
			CImage* poz_1 = new CImage(text.getstr(), text.getmax_s(), text.getmax_v());
			obrazek[x][y] = poz_1;
			return;
		}
		return;

	}
	
	CTable::~CTable() {
		for (unsigned  int i = 0; i < x; i++) {
			for (unsigned  int j = 0; j < y; j++) {
				delete obrazek[i][j];
			}
		}
	}



#ifndef __PROGTEST__
int main(void)
{
	ostringstream oss;
	CTable t0(3, 2);
	t0.SetCell(0, 0, CText("Hello,\n"
		"Hello Kitty", CText::ALIGN_LEFT));
	t0.SetCell(1, 0, CText("Lorem ipsum dolor sit amet", CText::ALIGN_LEFT));
	t0.SetCell(2, 0, CText("Bye,\n"
		"Hello Kitty", CText::ALIGN_RIGHT));
	t0.SetCell(1, 1, CImage()
		.AddRow("###                   ")
		.AddRow("#  #                  ")
		.AddRow("#  # # ##   ###    ###")
		.AddRow("###  ##    #   #  #  #")
		.AddRow("#    #     #   #  #  #")
		.AddRow("#    #     #   #  #  #")
		.AddRow("#    #      ###    ###")
		.AddRow("                     #")
		.AddRow("                   ## ")
		.AddRow("                      ")
		.AddRow(" #    ###   ###   #   ")
		.AddRow("###  #   # #     ###  ")
		.AddRow(" #   #####  ###   #   ")
		.AddRow(" #   #         #  #   ")
		.AddRow("  ##  ###   ###    ## "));
	t0.SetCell(2, 1, CEmpty());
	oss.str("");
	oss.clear();
	oss << t0;
	assert(oss.str() ==
		"+--------------------------+----------------------+\n"
		"|Hello,                    |                      |\n"
		"|Hello Kitty               |                      |\n"
		"+--------------------------+----------------------+\n"
		"|Lorem ipsum dolor sit amet|###                   |\n"
		"|                          |#  #                  |\n"
		"|                          |#  # # ##   ###    ###|\n"
		"|                          |###  ##    #   #  #  #|\n"
		"|                          |#    #     #   #  #  #|\n"
		"|                          |#    #     #   #  #  #|\n"
		"|                          |#    #      ###    ###|\n"
		"|                          |                     #|\n"
		"|                          |                   ## |\n"
		"|                          |                      |\n"
		"|                          | #    ###   ###   #   |\n"
		"|                          |###  #   # #     ###  |\n"
		"|                          | #   #####  ###   #   |\n"
		"|                          | #   #         #  #   |\n"
		"|                          |  ##  ###   ###    ## |\n"
		"+--------------------------+----------------------+\n"
		"|                      Bye,|                      |\n"
		"|               Hello Kitty|                      |\n"
		"+--------------------------+----------------------+\n");
	t0.SetCell(0, 1, t0.GetCell(1, 1));
	t0.SetCell(2, 1, CImage()
		.AddRow("*****   *      *  *      ******* ******  *")
		.AddRow("*    *  *      *  *      *            *  *")
		.AddRow("*    *  *      *  *      *           *   *")
		.AddRow("*    *  *      *  *      *****      *    *")
		.AddRow("****    *      *  *      *         *     *")
		.AddRow("*  *    *      *  *      *        *       ")
		.AddRow("*   *   *      *  *      *       *       *")
		.AddRow("*    *    *****   ****** ******* ******  *"));
	dynamic_cast<CText&> (t0.GetCell(1, 0)).SetText("Lorem ipsum dolor sit amet,\n"
		"consectetur adipiscing\n"
		"elit. Curabitur scelerisque\n"
		"lorem vitae lectus cursus,\n"
		"vitae porta ante placerat. Class aptent taciti\n"
		"sociosqu ad litora\n"
		"torquent per\n"
		"conubia nostra,\n"
		"per inceptos himenaeos.\n"
		"\n"
		"Donec tincidunt augue\n"
		"sit amet metus\n"
		"pretium volutpat.\n"
		"Donec faucibus,\n"
		"ante sit amet\n"
		"luctus posuere,\n"
		"mauris tellus");
	oss.str("");
	oss.clear();
	oss << t0;
	assert(oss.str() ==
		"+----------------------------------------------+------------------------------------------+\n"
		"|Hello,                                        |          ###                             |\n"
		"|Hello Kitty                                   |          #  #                            |\n"
		"|                                              |          #  # # ##   ###    ###          |\n"
		"|                                              |          ###  ##    #   #  #  #          |\n"
		"|                                              |          #    #     #   #  #  #          |\n"
		"|                                              |          #    #     #   #  #  #          |\n"
		"|                                              |          #    #      ###    ###          |\n"
		"|                                              |                               #          |\n"
		"|                                              |                             ##           |\n"
		"|                                              |                                          |\n"
		"|                                              |           #    ###   ###   #             |\n"
		"|                                              |          ###  #   # #     ###            |\n"
		"|                                              |           #   #####  ###   #             |\n"
		"|                                              |           #   #         #  #             |\n"
		"|                                              |            ##  ###   ###    ##           |\n"
		"+----------------------------------------------+------------------------------------------+\n"
		"|Lorem ipsum dolor sit amet,                   |                                          |\n"
		"|consectetur adipiscing                        |          ###                             |\n"
		"|elit. Curabitur scelerisque                   |          #  #                            |\n"
		"|lorem vitae lectus cursus,                    |          #  # # ##   ###    ###          |\n"
		"|vitae porta ante placerat. Class aptent taciti|          ###  ##    #   #  #  #          |\n"
		"|sociosqu ad litora                            |          #    #     #   #  #  #          |\n"
		"|torquent per                                  |          #    #     #   #  #  #          |\n"
		"|conubia nostra,                               |          #    #      ###    ###          |\n"
		"|per inceptos himenaeos.                       |                               #          |\n"
		"|                                              |                             ##           |\n"
		"|Donec tincidunt augue                         |                                          |\n"
		"|sit amet metus                                |           #    ###   ###   #             |\n"
		"|pretium volutpat.                             |          ###  #   # #     ###            |\n"
		"|Donec faucibus,                               |           #   #####  ###   #             |\n"
		"|ante sit amet                                 |           #   #         #  #             |\n"
		"|luctus posuere,                               |            ##  ###   ###    ##           |\n"
		"|mauris tellus                                 |                                          |\n"
		"+----------------------------------------------+------------------------------------------+\n"
		"|                                          Bye,|*****   *      *  *      ******* ******  *|\n"
		"|                                   Hello Kitty|*    *  *      *  *      *            *  *|\n"
		"|                                              |*    *  *      *  *      *           *   *|\n"
		"|                                              |*    *  *      *  *      *****      *    *|\n"
		"|                                              |****    *      *  *      *         *     *|\n"
		"|                                              |*  *    *      *  *      *        *       |\n"
		"|                                              |*   *   *      *  *      *       *       *|\n"
		"|                                              |*    *    *****   ****** ******* ******  *|\n"
		"+----------------------------------------------+------------------------------------------+\n");
	CTable t1(t0);
	t1.SetCell(1, 0, CEmpty());
	t1.SetCell(1, 1, CEmpty());
	oss.str("");
	oss.clear();
	oss << t0;
	assert(oss.str() ==
		"+----------------------------------------------+------------------------------------------+\n"
		"|Hello,                                        |          ###                             |\n"
		"|Hello Kitty                                   |          #  #                            |\n"
		"|                                              |          #  # # ##   ###    ###          |\n"
		"|                                              |          ###  ##    #   #  #  #          |\n"
		"|                                              |          #    #     #   #  #  #          |\n"
		"|                                              |          #    #     #   #  #  #          |\n"
		"|                                              |          #    #      ###    ###          |\n"
		"|                                              |                               #          |\n"
		"|                                              |                             ##           |\n"
		"|                                              |                                          |\n"
		"|                                              |           #    ###   ###   #             |\n"
		"|                                              |          ###  #   # #     ###            |\n"
		"|                                              |           #   #####  ###   #             |\n"
		"|                                              |           #   #         #  #             |\n"
		"|                                              |            ##  ###   ###    ##           |\n"
		"+----------------------------------------------+------------------------------------------+\n"
		"|Lorem ipsum dolor sit amet,                   |                                          |\n"
		"|consectetur adipiscing                        |          ###                             |\n"
		"|elit. Curabitur scelerisque                   |          #  #                            |\n"
		"|lorem vitae lectus cursus,                    |          #  # # ##   ###    ###          |\n"
		"|vitae porta ante placerat. Class aptent taciti|          ###  ##    #   #  #  #          |\n"
		"|sociosqu ad litora                            |          #    #     #   #  #  #          |\n"
		"|torquent per                                  |          #    #     #   #  #  #          |\n"
		"|conubia nostra,                               |          #    #      ###    ###          |\n"
		"|per inceptos himenaeos.                       |                               #          |\n"
		"|                                              |                             ##           |\n"
		"|Donec tincidunt augue                         |                                          |\n"
		"|sit amet metus                                |           #    ###   ###   #             |\n"
		"|pretium volutpat.                             |          ###  #   # #     ###            |\n"
		"|Donec faucibus,                               |           #   #####  ###   #             |\n"
		"|ante sit amet                                 |           #   #         #  #             |\n"
		"|luctus posuere,                               |            ##  ###   ###    ##           |\n"
		"|mauris tellus                                 |                                          |\n"
		"+----------------------------------------------+------------------------------------------+\n"
		"|                                          Bye,|*****   *      *  *      ******* ******  *|\n"
		"|                                   Hello Kitty|*    *  *      *  *      *            *  *|\n"
		"|                                              |*    *  *      *  *      *           *   *|\n"
		"|                                              |*    *  *      *  *      *****      *    *|\n"
		"|                                              |****    *      *  *      *         *     *|\n"
		"|                                              |*  *    *      *  *      *        *       |\n"
		"|                                              |*   *   *      *  *      *       *       *|\n"
		"|                                              |*    *    *****   ****** ******* ******  *|\n"
		"+----------------------------------------------+------------------------------------------+\n");
	oss.str("");
	oss.clear();
	oss << t1;
	assert(oss.str() ==
		"+-----------+------------------------------------------+\n"
		"|Hello,     |          ###                             |\n"
		"|Hello Kitty|          #  #                            |\n"
		"|           |          #  # # ##   ###    ###          |\n"
		"|           |          ###  ##    #   #  #  #          |\n"
		"|           |          #    #     #   #  #  #          |\n"
		"|           |          #    #     #   #  #  #          |\n"
		"|           |          #    #      ###    ###          |\n"
		"|           |                               #          |\n"
		"|           |                             ##           |\n"
		"|           |                                          |\n"
		"|           |           #    ###   ###   #             |\n"
		"|           |          ###  #   # #     ###            |\n"
		"|           |           #   #####  ###   #             |\n"
		"|           |           #   #         #  #             |\n"
		"|           |            ##  ###   ###    ##           |\n"
		"+-----------+------------------------------------------+\n"
		"+-----------+------------------------------------------+\n"
		"|       Bye,|*****   *      *  *      ******* ******  *|\n"
		"|Hello Kitty|*    *  *      *  *      *            *  *|\n"
		"|           |*    *  *      *  *      *           *   *|\n"
		"|           |*    *  *      *  *      *****      *    *|\n"
		"|           |****    *      *  *      *         *     *|\n"
		"|           |*  *    *      *  *      *        *       |\n"
		"|           |*   *   *      *  *      *       *       *|\n"
		"|           |*    *    *****   ****** ******* ******  *|\n"
		"+-----------+------------------------------------------+\n");
	t1 = t0;
	t1.SetCell(0, 0, CEmpty());
	t1.SetCell(1, 1, CImage()
		.AddRow("  ********                    ")
		.AddRow(" **********                   ")
		.AddRow("**        **                  ")
		.AddRow("**             **        **   ")
		.AddRow("**             **        **   ")
		.AddRow("***         ********  ********")
		.AddRow("****        ********  ********")
		.AddRow("****           **        **   ")
		.AddRow("****           **        **   ")
		.AddRow("****      **                  ")
		.AddRow(" **********                   ")
		.AddRow("  ********                    "));
	oss.str("");
	oss.clear();
	oss << t0;
	assert(oss.str() ==
		"+----------------------------------------------+------------------------------------------+\n"
		"|Hello,                                        |          ###                             |\n"
		"|Hello Kitty                                   |          #  #                            |\n"
		"|                                              |          #  # # ##   ###    ###          |\n"
		"|                                              |          ###  ##    #   #  #  #          |\n"
		"|                                              |          #    #     #   #  #  #          |\n"
		"|                                              |          #    #     #   #  #  #          |\n"
		"|                                              |          #    #      ###    ###          |\n"
		"|                                              |                               #          |\n"
		"|                                              |                             ##           |\n"
		"|                                              |                                          |\n"
		"|                                              |           #    ###   ###   #             |\n"
		"|                                              |          ###  #   # #     ###            |\n"
		"|                                              |           #   #####  ###   #             |\n"
		"|                                              |           #   #         #  #             |\n"
		"|                                              |            ##  ###   ###    ##           |\n"
		"+----------------------------------------------+------------------------------------------+\n"
		"|Lorem ipsum dolor sit amet,                   |                                          |\n"
		"|consectetur adipiscing                        |          ###                             |\n"
		"|elit. Curabitur scelerisque                   |          #  #                            |\n"
		"|lorem vitae lectus cursus,                    |          #  # # ##   ###    ###          |\n"
		"|vitae porta ante placerat. Class aptent taciti|          ###  ##    #   #  #  #          |\n"
		"|sociosqu ad litora                            |          #    #     #   #  #  #          |\n"
		"|torquent per                                  |          #    #     #   #  #  #          |\n"
		"|conubia nostra,                               |          #    #      ###    ###          |\n"
		"|per inceptos himenaeos.                       |                               #          |\n"
		"|                                              |                             ##           |\n"
		"|Donec tincidunt augue                         |                                          |\n"
		"|sit amet metus                                |           #    ###   ###   #             |\n"
		"|pretium volutpat.                             |          ###  #   # #     ###            |\n"
		"|Donec faucibus,                               |           #   #####  ###   #             |\n"
		"|ante sit amet                                 |           #   #         #  #             |\n"
		"|luctus posuere,                               |            ##  ###   ###    ##           |\n"
		"|mauris tellus                                 |                                          |\n"
		"+----------------------------------------------+------------------------------------------+\n"
		"|                                          Bye,|*****   *      *  *      ******* ******  *|\n"
		"|                                   Hello Kitty|*    *  *      *  *      *            *  *|\n"
		"|                                              |*    *  *      *  *      *           *   *|\n"
		"|                                              |*    *  *      *  *      *****      *    *|\n"
		"|                                              |****    *      *  *      *         *     *|\n"
		"|                                              |*  *    *      *  *      *        *       |\n"
		"|                                              |*   *   *      *  *      *       *       *|\n"
		"|                                              |*    *    *****   ****** ******* ******  *|\n"
		"+----------------------------------------------+------------------------------------------+\n");
	oss.str("");
	oss.clear();
	oss << t1;
	assert(oss.str() ==
		"+----------------------------------------------+------------------------------------------+\n"
		"|                                              |          ###                             |\n"
		"|                                              |          #  #                            |\n"
		"|                                              |          #  # # ##   ###    ###          |\n"
		"|                                              |          ###  ##    #   #  #  #          |\n"
		"|                                              |          #    #     #   #  #  #          |\n"
		"|                                              |          #    #     #   #  #  #          |\n"
		"|                                              |          #    #      ###    ###          |\n"
		"|                                              |                               #          |\n"
		"|                                              |                             ##           |\n"
		"|                                              |                                          |\n"
		"|                                              |           #    ###   ###   #             |\n"
		"|                                              |          ###  #   # #     ###            |\n"
		"|                                              |           #   #####  ###   #             |\n"
		"|                                              |           #   #         #  #             |\n"
		"|                                              |            ##  ###   ###    ##           |\n"
		"+----------------------------------------------+------------------------------------------+\n"
		"|Lorem ipsum dolor sit amet,                   |                                          |\n"
		"|consectetur adipiscing                        |                                          |\n"
		"|elit. Curabitur scelerisque                   |        ********                          |\n"
		"|lorem vitae lectus cursus,                    |       **********                         |\n"
		"|vitae porta ante placerat. Class aptent taciti|      **        **                        |\n"
		"|sociosqu ad litora                            |      **             **        **         |\n"
		"|torquent per                                  |      **             **        **         |\n"
		"|conubia nostra,                               |      ***         ********  ********      |\n"
		"|per inceptos himenaeos.                       |      ****        ********  ********      |\n"
		"|                                              |      ****           **        **         |\n"
		"|Donec tincidunt augue                         |      ****           **        **         |\n"
		"|sit amet metus                                |      ****      **                        |\n"
		"|pretium volutpat.                             |       **********                         |\n"
		"|Donec faucibus,                               |        ********                          |\n"
		"|ante sit amet                                 |                                          |\n"
		"|luctus posuere,                               |                                          |\n"
		"|mauris tellus                                 |                                          |\n"
		"+----------------------------------------------+------------------------------------------+\n"
		"|                                          Bye,|*****   *      *  *      ******* ******  *|\n"
		"|                                   Hello Kitty|*    *  *      *  *      *            *  *|\n"
		"|                                              |*    *  *      *  *      *           *   *|\n"
		"|                                              |*    *  *      *  *      *****      *    *|\n"
		"|                                              |****    *      *  *      *         *     *|\n"
		"|                                              |*  *    *      *  *      *        *       |\n"
		"|                                              |*   *   *      *  *      *       *       *|\n"
		"|                                              |*    *    *****   ****** ******* ******  *|\n"
		"+----------------------------------------------+------------------------------------------+\n");

	return 0;
}
#endif /* __PROGTEST__ */