#include "RR.h"
#include"scheduler.h"
RR::RR(scheduler* sc) :processor(sc)
{
	
	pr = nullptr;
	st = idle;
	timeslice = sc->gettimeslice();
	FT = 0;
	idletime = 0;
	busytime = 0;
}
RR::RR()
{
}
void RR::insert(process* c)
{
	
	RDY.enqueue(c);
	FT = FT + c->getresttime();
}

state RR::scheduleralgo()
{
	

	if (st == idle)
	{
		RDY.dequeue(pr);
		if (pr)
		{
			pr->setstart(SC->getCurrTime());
			while (pr && pr->getresttime() < SC->getRTF())
			{
				st = idle;
				FT = FT - pr->getresttime();
				SC->MoveToRDY_SJF(pr);
				if (!RDY.dequeue(pr))
				{
					pr = nullptr;
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
		if (st==busy && pr->getworked() != timeslice)
		{
			st = busy;
			pr->setresttime(pr->getresttime() - 1);
			pr->setworked(pr->getworked() + 1);
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
			pr->setworked(0);
			FT = FT - pr->getresttime();
			st = idle;
			process* tp = pr;
			pr = nullptr;

			SC->toBLK(tp);
		}
		else if (pr->getworked() == timeslice)
		{
			pr->setworked(0);
			process* f = pr;
			
			RDY.enqueue(f);
		
			pr = nullptr;
			RDY.dequeue(pr);
			if (pr)
				pr->setstart(SC->getCurrTime());
			if (pr)
			{
				while (pr && pr->getresttime() < SC->getRTF())
				{
					
					st = idle;
					FT = FT - pr->getresttime();
					SC->MoveToRDY_SJF(pr);
					if (!RDY.dequeue(pr))
					{
						pr = nullptr;
						
					}
					
				}
				if (pr)
				{
					
					st = busy;
					pr->setresttime(pr->getresttime() - 1);
					pr->setworked(pr->getworked() + 1);
					FT--;
					busytime++;
				}
			}
			
		}
	}
	return st;
}


state RR::getState() {
	return st;
}

LinkedList<process*>* RR::getRDYL()
{
	return nullptr;
}

LinkedQueue<process*>* RR::getRDYQ()
{
	return &RDY;
}

process* RR::Kill(int)
{
	return nullptr;
}

process* RR::getCurrPro()
{
	return pr;
}
double RR::getFT()
{
	return FT;
}
process* RR::getfirst()
{
	process* s;
	if (RDY.dequeue(s))
	{
		if (s)
		{
			FT = FT - s->getresttime();
			
		}
		return s;
	}
	else return nullptr;
}
process* RR::getfirstnonchild()
{
	return nullptr;
}
double RR::getrdyFT()
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
int RR::getprocessoridle()
{
	return idletime;
}

void RR::setprocessorload(float x)
{
	pload = x;
}
void RR::setprocessorutl(float x)
{
	putl = x;
}
int RR::getprocessorbusy()
{
	return busytime;
}