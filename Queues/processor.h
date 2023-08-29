#ifndef _PROCESSORCODE_H_
#define _PROCESSORCODE_H_
enum state { idle, busy };//enum for states 
#include"process.h"
#include"LinkedQueue.h"
#include"LinkedList.h"
class scheduler;
class processor
{
protected:
	scheduler* SC;
	double FT;
	float pload,
		  putl;
public:
	processor(scheduler* sc) { SC = sc; }
	processor() {};
	virtual void insert(process* c) = 0;
	virtual state scheduleralgo() = 0;
	virtual state getState() = 0;
	virtual process* Kill(int) = 0;
	virtual LinkedList<process*>* getRDYL() = 0;
	virtual LinkedQueue<process*>* getRDYQ() = 0;
	virtual double getFT() = 0;//getter for the full time to use in normal insertion
	virtual double getrdyFT() = 0; //getter for the rdy full time to use in stealing
	virtual process* getCurrPro() = 0;//getter for the process in the run 
	virtual process* getfirst() = 0; //getter for first child
	virtual process* getfirstnonchild() = 0; // getter for first non child
	virtual int getprocessorbusy() = 0; //getter for number of steps the processor being busy 
	virtual int getprocessoridle() = 0; //getter for number of steps the processor being idle
	virtual float getprocessorload() { return pload; };//getter for pload
	virtual float getprocessorutl() { return putl; }; //getter for utilization
	virtual void setprocessorload(float) = 0; //setter for pload
	virtual void setprocessorutl(float) = 0;//setter for utilization
 





};
#endif