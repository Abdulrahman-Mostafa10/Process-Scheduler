#include"processor.h"
#include"process.h"
#include"EDFQ.h"

class EDF :public processor
{
	state st;
	EDFQ RDY;
	int Rn; // ready number
	process* pr;
	int idletime;
	int busytime;
public:
	EDF(scheduler* sc);
	EDF();
	virtual void insert(process* c);
	virtual state scheduleralgo();
	virtual LinkedList<process*>* getRDYL();
 	virtual LinkedQueue<process*>* getRDYQ();
	virtual process* Kill(int);
	virtual double getFT();
	virtual process* getCurrPro();
	state getState();
	virtual process* getfirst();
	virtual process* getfirstnonchild();
	virtual double getrdyFT();
	virtual int getprocessorbusy();
	virtual int getprocessoridle();
	virtual void setprocessorload(float);
	virtual void setprocessorutl(float);
	virtual void overheat() ;
	virtual void cooling();
};
