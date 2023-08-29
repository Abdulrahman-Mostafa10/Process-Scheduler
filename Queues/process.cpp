#include"process.h"
process::process()
{
	o_iD = 0;
	starttime = -1;
}
process::process(process& c)
{
	PID = c.PID;
	AT = c.AT;
	CT = c.CT;
	NUM = c.NUM; 
	worked = c.worked;
	
	resttime = c.resttime;
}
process::process(int id, int at, int ct, int num)
{
	PID = id;
	AT = at;
	CT = ct;
	NUM = num;
	worked = 0;
	resttime = CT;
	parent = nullptr;
	leftchild = nullptr;
	rightchild = nullptr;
	o_iD=0;
	starttime = -1;
}

void process:: setPID(int id)
{
	PID = id;
}
void process:: setAT(int at)
{
	AT = at;
}
void process::setRT()
{
	RT = starttime - AT;
}
void process:: setCT(int ct)
{
	CT = ct;
	resttime = ct;
	worked = 0;
	ischild = false;
	isforked = 0;
	parent = nullptr;
	leftchild = nullptr;
	rightchild = nullptr;
}
void process:: setTT(int tt)
{
	TT = tt;
}
void process:: setTRT()
{
	TRT = TT - AT;
}
void process:: setWT()
{
	WT = TRT - CT;
}
void process::setNUM(int IO_t)
{
	NUM = IO_t;
}
void process::setstart(int x)
{
	if (starttime == -1)
	{
		starttime = x;
	}
}
void process:: seto_iduration(int* o_i)
{
	for (int i = 0; i < NUM; i++)
	{
		o_iD = o_iD + o_i[i];
		o_iduration.enqueue(o_i[i]);
	}
}
void process:: seto_itime(int* o_i)
{
	for (int i = 0; i < NUM; i++)
	{
		o_itime.enqueue(CT-(o_i[i]));
	}

}
void process::seto_iD(int o_i)
{
	o_iD = o_i;
}
void process:: setworked(int i)
{
	worked = i;
}
void process:: setresttime(int i)
{
	resttime = i;
}
void process:: setischild(bool c)
{
	ischild = c;
}
void process::setisforked(int x)
{
	isforked = x;
}
void process::setparent(process* x)
{
	parent = x;
}
void process::setleftchild(process* x)
{
	leftchild = x;
}
void process::setrightchild(process* x)
{
	rightchild = x;
}
void process::setleft(bool c)
{
	left = c;
}
///////////////////////////////
int process:: getPID()const
{
	return PID;
}
int process::  getAT()const
{
	return AT;
}
int  process:: getRT()const
{
	if (RT >= 0)
		return RT;
	else
		return TT - AT;
}
int process:: getCT()const
{
	return  CT;
}
int  process:: getTT()const
{
	return TT;
}
int process:: getTRT()const
{
	return  TRT;
}

int process:: getWT()const
{
	if (WT > 0)
		return WT;
	else
		return TRT;
}
int process:: geto_iduration()
{
	int i;
	o_iduration.dequeue(i);
	return i;
}
int process::geto_iD()
{
	return o_iD;
}
int process:: getNUM() const
{
	return NUM;
}
int process:: geto_itime()
{
	int i;
	o_itime.dequeue(i);
	return i;
}
int process:: getresttime()
{
	return resttime;
}
bool process:: operator==(process* c)
{
	if (getresttime() == c->getresttime())
		return true;
	else return false;
}
bool process::operator < (process* c)
{
	if (getresttime() < c->getresttime())
		return true;
	else return false;
}
bool process:: operator>=(process* c)
{
	if (getresttime() >= c->getresttime())
		return true;
	else return false;
}

int  process::getworked()
{
	return worked;
}

bool process:: operator==(int i)
{
	if (PID == i)
		return true;
	else return false;
}
int process::peeko_itime()
{
	int i;
	if (o_itime.peek(i))
		return i;
	return -1;
}
bool process::getischild()
{
	return ischild;
}
bool process::getleft()
{
	return left;
}
int process::getisforked()
{
	return isforked;
}

process* process::getparent()
{
	return parent;
}

process* process::getleftchild()
{
	return leftchild;
}
process* process::getrightchild()
{
	return rightchild;
}