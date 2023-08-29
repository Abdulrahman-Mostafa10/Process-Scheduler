
#include"processor.h"
#include"LinkedListprocess.h"
class FCFS:public processor
{
	state st;
	LinkedListprocess RDY;
	
	process *pr;//process in run 
	int busytime;
	int idletime;
	
public:
	FCFS(scheduler* sc);
	FCFS();
	virtual void insert(process* c);
	virtual state scheduleralgo();
	virtual state getState();
	virtual LinkedList<process*>* getRDYL() ;
	virtual LinkedQueue<process*>* getRDYQ() ;
	virtual double getFT();
	virtual process* getCurrPro();
	virtual process* Kill(int x);
	virtual process* getfirst();
	virtual process* getfirstnonchild();
	virtual double getrdyFT();
	virtual int getprocessorbusy() ;
	virtual int getprocessoridle() ;
	int RandomGen();
	virtual void setprocessorload(float);
	virtual void setprocessorutl(float);
};

