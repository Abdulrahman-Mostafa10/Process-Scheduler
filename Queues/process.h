#pragma once
#include"LinkedQueue.h"
#include<iostream>
//#include<string>
using namespace std;
class process
{
	int  PID,
		 AT,
		 RT,
		 CT,
		 TT,
		 TRT,
		 WT,
		 NUM,//number of times that the process will need i/o 
		 o_iD,
		 worked,//the time that the process take in rr processor
		 starttime, 
		 resttime, //the time lift for the process to go to turmination
		 isforked; //number of times the process fork
	bool left,//is the child lift or righ not important but to make the left child who kill first 
		 ischild;
	process* parent;
	process* leftchild;
	process* rightchild;
	LinkedQueue<int> o_iduration;
	LinkedQueue<int> o_itime;

public:

	process();
	process(process& c);
	process(int id, int at, int ct, int num );
	//-------------------------------------------------------------
	// setters:

	void setPID(int id);
	void setAT(int at);
	void setRT();
	void setCT(int ct);
	void setTT(int tt);
	void setTRT();
	void setWT();
	void setNUM(int IO_t);
	void setstart(int x);
	void seto_iduration(int* o_i);
	void seto_itime(int* o_i);
	void seto_iD(int o_i);
	void setworked(int i);
	void setresttime(int i);
	void setischild(bool x);
	void setisforked(int x);
	void setparent(process* x);
	void setleftchild(process* x);
	void setrightchild(process* x);
	void setleft(bool);
	//-------------------------------------------------------------
	// getters:

	int getPID()const;
	int  getAT()const;
	int  getRT()const;
	int getCT()const;
	int  getTT()const;
	int  getTRT()const;
	int  getWT()const;
	int geto_iduration();
	int geto_iD();
	int getNUM() const;
	int geto_itime();
	int getresttime();
	int getworked();
	int getisforked();
	bool getischild();
	process* getparent();
	process* getleftchild();
	process* getrightchild();
	bool getleft();

	int peeko_itime();

	//-------------------------------------------------------------
	// operator overloading:

	bool operator==(process* c);
	bool operator < (process* c);
	bool operator>=(process* c);
	bool operator==(int i);
	friend ostream& operator << (ostream& out, process* c);
};
