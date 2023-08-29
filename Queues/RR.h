#include"processor.h"
class RR :public processor
{
	state st;//state it is enum 
	LinkedQueue <process*> RDY;
	process* pr;//process in run 
	int timeslice;
	int idletime;
	int busytime;
public:
	RR(scheduler* sc);
	RR();
	virtual void insert(process* c);
	virtual state scheduleralgo();
	virtual state getState();
	virtual LinkedList<process*>* getRDYL() ;
	virtual LinkedQueue<process*>* getRDYQ();
	virtual double getFT();
	virtual process* Kill(int);
	virtual process* getCurrPro();
	virtual process* getfirst();
	virtual process* getfirstnonchild();
	virtual double getrdyFT();
	virtual int getprocessorbusy();
	virtual int getprocessoridle() ;
	virtual void setprocessorload(float) ;
	virtual void setprocessorutl(float) ;

};

