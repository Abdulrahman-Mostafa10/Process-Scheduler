#include"LinkedQueue.h"
#include"process.h"
#include"Linkedlist.h"
struct pair1
{
public:
	int timestep;
	int Id;
};
class RR;
class SJF;
class FCFS;
class processor;
class UI;
class scheduler
{
	UI* mainUI;
	LinkedQueue<process*> BLK;
	LinkedQueue<process*> TRM;
	LinkedQueue<process*> NEW;
	LinkedQueue<pair1> signalkill;
	LinkedQueue<process*> FRK;
	processor** pros;

	int
		timestep,
		timeslice,
		RTF,				//rate of forking
		MaxW,				//max wait
		STL,				//stealling
		F_P,				//fork probablity
		P_num,				//processes number
		num_R,				// running number
		fcfs_n,				// fcfs processors number
		sjf_n,				// sjf processors number
		rr_n,				// rr processors number
		pros_n,				//total number of processors
		curr_blk_dur,		//current duration for block
		index,				// for input file handling
		total_WT,			// total TRT in the system
		total_RT,			// total TRT in the system
		total_TRT;			// total TRT in the system

	float 
		Avg_WT,				// avarage waiting time
		Avg_RT,				// avarage round time
		Avg_TRT,			// avarage turn around time
		Avg_utl,			// avarage utlization
		RTF_pre,			// RTF migration precentage
		MaxW_pre,			// MaxW migration precentage
		Workstealing_pre,	// workstealing precentage
		forking_pre,		// forking precentage
		killing_pre;		// killing precentage

public:

	scheduler(string);
	void Excute(); // to excute the system

	//-----------------------------------------------------------------------
	// getters:

	int gettimeslice(),					// timeslice getter
		getCurrTime(),					// timestep getter
		getRnum(),						// running number getter
		getRTF(),						// RTF getter
		getMAXW(),						// max waiting time getter
		getforkprobalbilty();			// fork probability getter
	void getPinfo(int&, int&, int&);	// processors numbers getter
	process* getcurrpro(int);			// current process getter
	//		Ready lists pointer getters:
	LinkedList<process*>* getFCFSRDY(int);
	LinkedQueue<process*>* getSJFRDY(int);
	LinkedQueue<process*>* getRRRDY(int);
	LinkedQueue<process*>* getEssQ(char);

	//-----------------------------------------------------------------------
	// Operational functions:

	void MoveToRDY(process* c),		// to move processes to the ready lists of the processors equally
		MoveToRDY_FCFS(process* c), // to move processes to the ready lists of the FCFS processors ---> (child handling)
		MoveToRDY_SJF(process* c),	// to move processes to the ready lists of the SJF processors ---> (RTF migration)
		MoveToRDY_RR(process* c),   // to move processes to the ready lists of the RR processors ---> (MaxW migration)
		NewprocessesDistr(),		// function to distrbute the new processes on the processors
		toTRM(process* S),			// to terminat the process
		toBLK(process* S),			// to go to block for io
		blkOperation(),				// to get processes out of the block
		checkAndFinish();			// to check and finish the running state
	int RandomGen();				// to generate random numbers
	void fork(process*,int i),		// forking
		 ReadFile(string),			// to read the input file
		 writeFile(),				// to read the input file
		 workstealing(),			// workstealing
		 Kill_process(int i),		// to kill a process by id
		 Killing(),					// main killing function
		 statistics_evaluation();	// to calculate the stats
};
