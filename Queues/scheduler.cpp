#include "scheduler.h"
#include"RR.h"
#include"SJF.h"
#include"FCFS.h"
#include"UI.h"
#include<iostream>
#include<fstream>
#include"process.h"
using namespace std;
ostream& operator << (ostream& out, process* c)
{
	if (c)
	{
		out << "id=" << c->getPID();
		return out;
	}
}
int scheduler::gettimeslice()
{
	return timeslice;
}

scheduler::scheduler(string filename = "../f1.txt")
{
	ReadFile(filename); //function call that take the data from the file and insert it
	srand((unsigned)time(0)); // for random function
	pros_n = fcfs_n + sjf_n + rr_n;
	mainUI = new UI(this);
	pros = new processor * [pros_n];
	for (int i = 0; i < fcfs_n; i++)
	{
		pros[i] = new FCFS(this);
	}
	for (int i = fcfs_n; i < fcfs_n + sjf_n; i++)
	{
		pros[i] = new SJF(this);
	}
	for (int i = fcfs_n + sjf_n; i < pros_n; i++)
	{
		pros[i] = new RR(this);
	}
	// intializing the data members
	timestep = 0;
	num_R = 0;
	curr_blk_dur = 0;
	index = 0;
	Avg_WT = 0;
	Avg_RT = 0;
	Avg_TRT = 0;
	Avg_utl = 0;
	RTF_pre = 0;
	MaxW_pre = 0;
	Workstealing_pre = 0;
	forking_pre = 0;
	killing_pre = 0;
	total_TRT = 0;
	total_WT = 0;
	total_RT = 0;
}

void scheduler::Excute()
{
	mainUI->ModeSel();
	do
	{
		NewprocessesDistr();
		checkAndFinish();
		blkOperation();
		workstealing();
		Killing();
		mainUI->UpdateUI();
		timestep++;
	} while (TRM.getCount() != P_num);
	statistics_evaluation();
	writeFile();
	mainUI->end();
}


int scheduler::getCurrTime()
{
	return timestep;
}

LinkedList<process*>* scheduler::getFCFSRDY(int in)
{
	return pros[in]->getRDYL();
}

LinkedQueue<process*>* scheduler::getSJFRDY(int in)
{
	return pros[fcfs_n+in]->getRDYQ();
}

LinkedQueue<process*>* scheduler::getRRRDY(int in)
{
	return pros[fcfs_n+sjf_n + in]->getRDYQ();
}

LinkedQueue<process*>* scheduler::getEssQ(char sel)
{
	if (sel == 'b')
		return &BLK;
	else if (sel == 't')
		return &TRM;
	else
		return nullptr;
}

void scheduler::getPinfo(int& x, int& y, int& z)
{
	x = fcfs_n;
	y = sjf_n;
	z = rr_n;
}

int scheduler::getRnum()
{
	return num_R;
}

int scheduler::getRTF()
{
	return RTF;
}

int scheduler::getMAXW()
{
	return MaxW;
}

process* scheduler::getcurrpro(int ind)
{
	return pros[ind]->getCurrPro();
}
void scheduler::workstealing()
{
	if (timestep % STL == 0)
	{
		processor* max = pros[0];
		int from = 0;
		for (int i = 1; i < pros_n; i++)
		{
			if (max->getrdyFT() < pros[i]->getrdyFT())
			{
				from = i;
				max = pros[i];
			}
		}

		processor* min = pros[0];
		for (int i = 1; i < pros_n; i++)
		{
			if (min->getrdyFT() > pros[i]->getrdyFT())
			{

				min = pros[i];
			}
		}
		if (max->getrdyFT() != 0)
		{
			while ((max->getrdyFT() - min->getrdyFT()) / max->getrdyFT() > .4)
			{
				if (from >= 0 && from < fcfs_n)
				{

					process* ptr = nullptr;
					ptr = max->getfirstnonchild();
					if (ptr)
					{
						min->insert(ptr);
					}
					else
						break;
				}
				else
				{
					process* ptr = nullptr;
					ptr = max->getfirst();
					if (ptr)
					{
						min->insert(ptr);
					}

				}
			}
			Workstealing_pre++;
		}
	}
}
void scheduler::toTRM(process* S)
{
	S->setTT(timestep+1);
	S->setTRT();
	S->setWT();
	S->setRT();
	total_TRT = total_TRT + S->getTRT();
	total_WT = total_WT + S->getWT();
	total_RT = total_RT + S->getRT();
	if (S->getischild() == true)
	{
		if(S->getleft()==true)
		S->getparent()->setleftchild(nullptr);
		else
			S->getparent()->setrightchild(nullptr);
	}
	
	TRM.enqueue(S);
	if (S->getleftchild())
	{
		Kill_process(S->getleftchild()->getPID());
	}
	if (S->getrightchild())
	{
		Kill_process(S->getrightchild()->getPID());
	}
}
void scheduler::toBLK(process* S)
{
	BLK.enqueue(S);
}
void scheduler::statistics_evaluation()
{
	MaxW_pre = (MaxW_pre / P_num) * 100;
	RTF_pre = (RTF_pre / P_num) * 100;
	killing_pre = (killing_pre / P_num) * 100;
	forking_pre = (forking_pre / P_num) * 100;
	Workstealing_pre = (Workstealing_pre / P_num) * 100;
	float x, y, ut;
	ut = 0;
	for (int i = 0; i < pros_n; i++)
	{
		x = pros[i]->getprocessorbusy();
		y = pros[i]->getprocessoridle();
		pros[i]->setprocessorload((x / total_TRT) * 100);
		pros[i]->setprocessorutl((x / (x + y)) * 100);
		ut = ut + pros[i]->getprocessorutl();
	}
	Avg_utl = ut / pros_n;
	Avg_TRT = total_TRT / float(P_num);
	Avg_WT = total_WT / float(P_num);
	Avg_RT = total_RT / float(P_num);
}
void scheduler::MoveToRDY(process* c) {
	processor* tempro = pros[0];
	for (int i = 1; i < pros_n; i++)
	{
		if (tempro->getFT() > pros[i]->getFT())
		{
			tempro = pros[i];
		}
	}
	tempro->insert(c);
}

void scheduler::MoveToRDY_FCFS(process* c)
{
	processor* tempro = pros[0];
	for (int i = 1; i < fcfs_n; i++)
	{
		if (tempro->getFT() > pros[i]->getFT())
		{
			tempro = pros[i];
		}
	}
	tempro->insert(c);
}

void scheduler::MoveToRDY_SJF(process* c)
{
	RTF_pre++;
	processor* tempro = pros[fcfs_n];
	for (int i = fcfs_n + 1; i < fcfs_n + sjf_n; i++)
	{
		if (tempro->getFT() > pros[i]->getFT())
		{
			tempro = pros[i];
		}
	}
	tempro->insert(c);

}

void scheduler::MoveToRDY_RR(process* c)
{
	MaxW_pre++;
	processor* tempro = pros[fcfs_n + sjf_n];
	for (int i = fcfs_n + sjf_n + 1; i < pros_n; i++)
	{
		if (tempro->getFT() > pros[i]->getFT())
		{
			tempro = pros[i];
		}
	}
	tempro->insert(c);

}

// function to distrbute the new processes on the processors
void scheduler::NewprocessesDistr()
{
	process* temp = nullptr;
	NEW.peek(temp);
	while (temp && temp->getAT() == timestep)
	{
		if (NEW.dequeue(temp))
		{
			MoveToRDY(temp);
			NEW.peek(temp);

		}
		else break;
	}

}


void scheduler::checkAndFinish()
{
	num_R = 0;
	for (int i = 0; i < pros_n; i++)
	{
		if (pros[i]->scheduleralgo() == busy)
		{
			num_R++;

		}

	}
}

void scheduler::blkOperation() { // o_i durr = 0 is NOT HANDELED
	process* temp;
	if (!BLK.isEmpty() && curr_blk_dur == 0)
	{
		BLK.peek(temp);
		curr_blk_dur = temp->geto_iduration();
	}
	if (curr_blk_dur == 1)
	{
		curr_blk_dur--;
		BLK.dequeue(temp);
		MoveToRDY(temp);
	}
	if (curr_blk_dur != 0)
	{
		curr_blk_dur--;
	}
}

int scheduler::RandomGen()
{
	return rand() % 100;
	return 0;
}

void scheduler::fork(process* f,int i)
{
	process* temp = new process(++P_num,getCurrTime(),f->getresttime(),0);
	temp->setCT(f->getresttime());
	temp->setparent(f);
	if (i == 1)
	{
		f->setleftchild(temp);
		temp->setleft(true);
	}
	if (i == 2)
	{
		f->setrightchild(temp);
		temp->setleft(false);
	}
	//f->setisforked(true);
	temp->setischild(true);
	MoveToRDY_FCFS(temp);
	//FRK.enqueue(temp);
	forking_pre++;
}
int scheduler::getforkprobalbilty()
{
	return F_P;
}

void scheduler::ReadFile(string file = "f1.txt")
{
	ifstream inputfile;
	inputfile.open(file, ios::in);
	bool flag = inputfile.is_open();
	while (!inputfile.eof())
	{
		inputfile >> fcfs_n >> sjf_n >> rr_n >> timeslice >> RTF >> MaxW >> STL >> F_P >> P_num;
		int index = 0;

		process* my_processes = new process[P_num];
		int AT, CT, PID, IO_t;

		for (int i = 0; i < P_num; i++)
		{
			inputfile >> AT >> PID >> CT >> IO_t;

			my_processes[i].setAT(AT);
			my_processes[i].setPID(PID);
			my_processes[i].setCT(CT);
			my_processes[i].setNUM(IO_t);

			if (IO_t)
			{
				int x = IO_t;
				if (x)
				{
					int* IO_period = new int[x];
					int* IO_lasting_time = new int[x];

					char ignore;
					int j = 0;

					if (IO_t == 1)
					{
						inputfile >> ignore;
						inputfile >> IO_period[j];
						inputfile >> ignore;
						inputfile >> IO_lasting_time[j];
						j++;

						inputfile >> ignore;
					}
					else
					{
						int k = 0;
						for (; k < IO_t - 1; k++)
						{
							inputfile >> ignore;
							inputfile >> IO_period[j];
							inputfile >> ignore;
							inputfile >> IO_lasting_time[j];
							inputfile >> ignore;
							j++;
							inputfile >> ignore;
						}
						if (IO_t - 1 == k)
						{
							inputfile >> ignore;
							inputfile >> IO_period[j];
							inputfile >> ignore;
							inputfile >> IO_lasting_time[j];
							j++;

							inputfile >> ignore;
						}
						k = 0;
					}
					my_processes[i].seto_itime(IO_period);
					my_processes[i].seto_iduration(IO_lasting_time);
				}
			}

			NEW.enqueue(&my_processes[i]);
		}
		int x;
		pair1 temp_pair;
		inputfile >> x;
		while (!inputfile.eof())
		{
			temp_pair.timestep = x;
			inputfile >> x;
			temp_pair.Id = x;
			signalkill.enqueue(temp_pair);
			inputfile >> x;
		}
	}
}
void scheduler::Kill_process(int id)
{
	bool kill_flag = false;

	process* process_to_kill = nullptr;
	for (int i = 0; i < fcfs_n; i++)
	{
		process_to_kill = pros[i]->Kill(id);

		if (process_to_kill)
		{
			kill_flag = true;
			toTRM(process_to_kill);

			break;
		}
	}
}
void scheduler::Killing()
{
	pair1 temp_pair = { -1,-1 };
	while (signalkill.peek(temp_pair))
	{
		if (temp_pair.timestep == timestep)
		{
			signalkill.dequeue(temp_pair);
			Kill_process(temp_pair.Id);
			killing_pre++;
		}
		else break;
	}

}
void scheduler::writeFile()
{
	process* temp;
	ofstream of("output.txt");
	of << "TT" << '\t' << "PID" << '\t' << "AT" << '\t' << "CT" << '\t' << "IO_D" << '\t' << "|  "<<'\t' << "WT" << '\t' << "RT" << '\t' << "TRT" << endl;
	for (int i = 0; i < P_num; i++)
	{
		TRM.dequeue(temp);
		of << temp->getTT() << '\t' << temp->getPID() << '\t' << temp->getAT() << '\t' << temp->getCT() << '\t' << temp->geto_iD() << '\t' << "|  "<<'\t' << temp->getWT() << '\t' << temp->getRT() << '\t' << temp->getTRT() << endl;
	}
	of.precision(3);
	of << endl;
	of << "Processes: " << P_num << endl;
	of << "Avg WT = " << Avg_WT << '\t' << "Avg RT = " << Avg_RT << '\t' << "Avg TRT = " << Avg_TRT << endl;
	of << "Migration %: " << '\t' << "RTF= " << RTF_pre << "%" << '\t' << "MAxW= " << MaxW_pre << "%" << endl;
	of << "Work steal %: " << Workstealing_pre << "%" << endl;
	of << "Forked processes %: " << forking_pre << endl;
	of << "killed processes %: " << killing_pre << endl;
	of << endl;
	of << "Processors: " << pros_n << "[" << fcfs_n << " FCFS, " << sjf_n << " SJF, " << rr_n << " RR "<< "]" << endl;
	of << "Processors Load: " << endl;
	for (int i = 0; i < pros_n; i++)
	{
		of << "P" << i + 1 << "= " << pros[i]->getprocessorload() << "%     ";
	}
	of << endl;
	of << "Processors Utiliz: " << endl;
	for (int i = 0; i < pros_n; i++)
	{
		of << "P" << i + 1 << "= " << pros[i]->getprocessorutl() << "%     ";
	}
	of << endl;
	of << "Avg Utilization: " << Avg_utl << endl;

	of.close();
}

