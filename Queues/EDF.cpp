#include "EDF.h"
#include"scheduler.h"


EDF::EDF(scheduler* sc) :processor(sc)
{
	Rn = 0;
	pr = nullptr;
	st = idle;
	FT = 0;
	idletime = 0;
	busytime = 0;
}
EDF::EDF()
{
}
void EDF::insert(process* c)
{
	if (pr)
	{
		if (c->getdeadline() < pr->getdeadline())
		{
			process* temp;
			temp = pr;
			pr = nullptr;
			pr = c;
			RDY.enqueueshortestDL(temp);
			FT = FT + c->getresttime();
			return;
		}
	}
	
	
		Rn++;
		RDY.enqueueshortestDL(c);
		FT = FT + c->getresttime();
	
}

state EDF::scheduleralgo()
{
	/*process* c = nullptr;*/
	//RDY.deletefirst(c);a
	//pr = c;
	//FT = pr->getCT() + SC->getCurrTime();
	//process* temp = nullptr;
	//RDY.peek(temp);
	//if (pr && temp && pr->getdeadline()>temp->getdeadline()){
	//	RDY.enqueueshortestDL(pr);
	//	RDY.dequeue(pr);
	//}

	if (st == idle)
	{
		RDY.dequeue(pr);
		if (pr)
		{
			pr->setstart(SC->getCurrTime());
			st = busy;
			//FT = FT - pr->getresttime();
			Rn--;

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

			SC->toTRM(tp);
		}


	}

	return st;
}

LinkedList<process*>* EDF::getRDYL()
{
	return nullptr;
}
LinkedQueue<process*>* EDF::getRDYQ()
{
	return &RDY;
}
process* EDF::Kill(int)
{
	return nullptr;
}
state EDF::getState()
{
	return st;
}
process* EDF::getCurrPro()
{
	return pr;
}

double EDF::getFT()
{
	return FT;
}
process* EDF::getfirst()
{
	process* s;
	if (RDY.dequeue(s))
	{
		if (s)
		{
			FT = FT - s->getresttime();
			Rn--;
		}
		return s;
	}
	else return nullptr;
}
process* EDF::getfirstnonchild()
{
	return nullptr;
}
double EDF::getrdyFT()
{

	if (pr)
	{
		return FT - pr->getresttime();
	}
	else
		return FT;

}
int EDF::getprocessorbusy()
{
	return busytime;
}
int EDF::getprocessoridle()
{
	return idletime;
}

void EDF::setprocessorload(float x)
{
	pload = x;
}

void EDF::setprocessorutl(float x)
{
	putl = x;
}

void EDF::overheat()
{
	int x, y, z, c;
	SC->getPinfo(x, y, z, c);
	if (z > 1)
	{
		st = overheated;
		cooling_dur = SC->getOver_dur();
		if (pr)
		{
			SC->MoveToRDY(pr);
			pr = nullptr;
		}
		process* temp;
		while (!RDY.isEmpty())
		{
			RDY.dequeue(temp);
			SC->MoveToRDY(temp);
		}
		FT = 0;
	}
}

void EDF::cooling()
{
	if (cooling_dur > 0)
		cooling_dur--;
	else {
		st = idle;
		SC->Cooled();
	}
}
