#include"FCFS.h"
#include"scheduler.h"



FCFS::FCFS(scheduler* sc) :processor(sc)
{
	
	pr = nullptr;
	st = idle;
	FT = 0;
	busytime = 0;
	idletime = 0;
	srand((unsigned)time(0));
}

FCFS::FCFS()
{
}

void FCFS::insert(process* c)
{
	
	RDY.InsertEnd(c);
	FT = FT + c->getresttime();
}

state FCFS::scheduleralgo()
{
	if (st == idle)
	{
		RDY.DeleteFirst(pr);
		if (pr)
		{
			pr->setstart(SC->getCurrTime());
			while (pr &&(SC->getCurrTime() - pr->getAT()) > SC->getMAXW() && !pr->getischild())
			{
				FT = FT - pr->getresttime();
				
				SC->MoveToRDY_RR(pr);
				if (!RDY.DeleteFirst(pr))
				{
					pr = nullptr;
					st = idle;
				}
			}
			if (pr) {
				st = busy;
				
			}
		}
		else
			idletime++;
	}
	if (pr)
	{
		if (st == busy)
		{
			st = busy;
			pr->setresttime(pr->getresttime() - 1);
			FT--;
			busytime++;
		}
		if (pr->getresttime() == 0)
		{
			st = idle;
			process* tp = pr;
			pr = nullptr;

			SC->toTRM(tp);
		}
		else if (pr->peeko_itime() == pr->getresttime())
		{
			st = idle;
			pr->geto_itime();
			FT = FT - pr->getresttime();
			st = idle;
			process* tp = pr;
			pr = nullptr;

			SC->toBLK(tp);
		}

		int i = RandomGen();
		if (i > 0 && i < SC->getforkprobalbilty())
		{
			if (pr)
			{
				if (pr->getisforked() == 1)
				{
					SC->fork(pr, 2);
					pr->setisforked(2);
				}
				else if (pr->getisforked() == 0)
				{
					SC->fork(pr, 1);
					pr->setisforked(1);
				}

			}
		}


	}
	return st;
	
}






state FCFS::getState()
{
	return st;
}

LinkedList<process*>* FCFS::getRDYL()
{
	return &RDY;
}

LinkedQueue<process*>* FCFS::getRDYQ()
{
	return nullptr;
}


double FCFS::getFT() 
{
	return FT;
}

process* FCFS::Kill(int x)
{

	process* z;
	bool flag = RDY.DeleteNode(x, z);
	if (flag)
	{
		FT = FT - z->getresttime();
		return z;

	}
	else if (pr && pr->getPID() == x) {
		st = idle;
		FT = FT - pr->getresttime();
		process* temp;
		temp = pr;
		pr = nullptr;
		return temp;
	}
	else return nullptr;
}



process* FCFS::getCurrPro()
{
	return pr;
}
process* FCFS::getfirst()
{
	process* s = nullptr;
	RDY.DeleteFirst(s);
	if (s)
	{
		FT = FT - s->getresttime();
		
	}
	return s;
}
process* FCFS::getfirstnonchild()
{
	process* s = nullptr;
	s = RDY.getnonchild();
	if (s)
	{
		FT = FT - s->getresttime();
	}
	return s;
}
double FCFS::getrdyFT()
{

	if (pr)
	{
		
		return FT - pr->getresttime();
	}
	else
	{
		
		return FT;
	}
}
int FCFS::getprocessoridle()
{
	return idletime;
}
void FCFS::setprocessorload(float x)
{
	pload = x;

}
void FCFS::setprocessorutl(float x)
{
	putl = x;

}
int FCFS::getprocessorbusy()
{
	return busytime;
}

int FCFS::RandomGen()
{
	int k = rand() % 100;
	return k ;
	return 0;
}
