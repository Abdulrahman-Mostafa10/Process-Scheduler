//#include"scheduler.h"
#include<windows.h>
class scheduler;
class UI
{
public:
	UI(scheduler* s);
	void ModeSel();				// mode selector
	//void excute();
	void UpdateUI();
	void end();
	~UI();

private:
	void printPros();			// printing the processors' ready lists
	void printBLK();			// printing the block
	void printRUN();			// printing the running processes
	void printTRM();			// printing the termination list
	scheduler* sch;
	int mode,
		fcfs_n,
		sjf_n,
		rr_n;
	HANDLE h;
};