#include"processor.h"
#include"process.h"

class SJF :public processor
{
	state st;
	LinkedQueue <process*> RDY;
	process* pr;//process in run 
	int idletime;
	int busytime;
public:
	SJF(scheduler* sc);
	SJF();
	virtual void insert(process* c);
	virtual state scheduleralgo();
	virtual LinkedList<process*>* getRDYL() ;
	virtual LinkedQueue<process*>* getRDYQ();
	virtual process* Kill(int);
	virtual double getFT();
	virtual process* getCurrPro();
	state getState();
	virtual process* getfirst();
	virtual process* getfirstnonchild();
	virtual double getrdyFT();
	virtual int getprocessorbusy() ;
	virtual int getprocessoridle() ;
	virtual void setprocessorload(float);
	virtual void setprocessorutl(float);

};
