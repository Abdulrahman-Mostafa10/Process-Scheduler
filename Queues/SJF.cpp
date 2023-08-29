#include "SJF.h"
#include"scheduler.h"


SJF::SJF(scheduler* sc) :processor(sc)
{
	//Rn = 0;
	pr = nullptr;
	st = idle;
	FT = 0;
	idletime = 0;
	busytime = 0;
}
SJF::SJF()
{
}
void SJF::insert(process* c)
{
	//Rn++;
	RDY.enqueueshortest(c);
	FT = FT + c->getresttime();
}

state SJF::scheduleralgo()
{
	/*process* c = nullptr;*/
	//RDY.deletefirst(c);a
	//pr = c;
	//FT = pr->getCT() + SC->getCurrTime();

	if (st == idle)
	{
		RDY.dequeue(pr);
		if (pr)
		{
			pr->setstart(SC->getCurrTime());
			st = busy;
			//FT = FT - pr->getresttime();
			//Rn--;

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
	}
	return st;
}
//bool SJF::run()
//{
//	if (!RDY.isEmpty())
//	{
//		//process* c;
//		RDY.dequeue(pr);
//		Rn--;
//		//pr = c;
//		//FT = pr->getCT() + SC->getCurrTime();
//		state = true;
//	}
//	return state;
//}

LinkedList<process*>* SJF::getRDYL()
{
	return nullptr;
}
LinkedQueue<process*>* SJF::getRDYQ()
{
	return &RDY;
}
process* SJF::Kill(int)
{
	return nullptr;
}
state SJF::getState()
{
	return st;
}
process* SJF::getCurrPro()
{
	return pr;
}

//string SJF::rs()
//{
//	return string();
//}
double SJF::getFT()
{
	return FT;
}
process* SJF::getfirst()
{
	process* s;
	if (RDY.dequeue(s))
	{
		if (s)
		{
			FT = FT - s->getresttime();
			//Rn--;
		}
		return s;
	}
	else return nullptr;
}
process* SJF::getfirstnonchild()
{
	return nullptr;
}
double SJF::getrdyFT()
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
int SJF::getprocessorbusy()
{
	return busytime;
}
int SJF::getprocessoridle()
{
	return idletime;
}



void SJF::setprocessorload(float x)
{
	pload = x;
}

void SJF::setprocessorutl(float x)
{
	putl = x;
}
