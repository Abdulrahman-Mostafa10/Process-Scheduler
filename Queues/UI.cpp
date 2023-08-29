#include"UI.h"
#include"scheduler.h"
UI::UI(scheduler* s)
{
	sch = s;
	mode = 0;
	sch->getPinfo(fcfs_n, sjf_n, rr_n);
	h = GetStdHandle(STD_OUTPUT_HANDLE);
}

void UI::ModeSel()
{
	if (!mode)
	{
		cout << "------------------ WELCOME --------------------" << endl;
		Sleep(1000);
		cout << "please select a mode:" << endl;
		cout << "PRESS  - 1 -  FOR interactive mode" << endl;
		cout << "PRESS  - 2 -  FOR step-by-step mode" << endl;
		cout << "PRESS  - 3 -  FOR silent mode" << endl;
		cin >> mode;
		while ((mode != 1) && (mode != 2) && (mode != 3) && (mode != -1)) {
			cout << "didn't get that" << endl;
			cout << "please select a mode:" << endl;
			cout << "PRESS  - 1 -  FOR interactive mode" << endl;
			cout << "PRESS  - 2 -  FOR step-by-step mode" << endl;
			cout << "PRESS  - 3 -  FOR silent mode" << endl;
			cin >> mode;
		}
		Sleep(1000);
		if (mode == 1)
		{
			cout << "INTERACTIVE MODE:" << endl;
		}
		else if (mode == 2)
		{
			cout << "STEP-BY-STEP MODE:" << endl;
		}
		else if (mode == 3)
		{
			cout << "SILENT MODE:" << endl;
		}
		Sleep(1000);
	}
}

void UI::printPros()
{
	LinkedList<process*>* templ;
	LinkedQueue<process*>* tempq;
	cout << "------------------ RDY processes --------------------" << endl;
	for (int i = 0; i < fcfs_n; i++)
	{
		cout << "Proccessor " << i + 1 << " [FCFS]: ";
		SetConsoleTextAttribute(h, 5);
		templ = sch->getFCFSRDY(i);
		cout << templ->GetCount() << " " << "RDY: ";
		templ->print();
		SetConsoleTextAttribute(h, 7);
	}
	for (int i = 0; i < sjf_n; i++)
	{
		cout << "Proccessor " << i + fcfs_n +1 << " [SJF]: ";
		SetConsoleTextAttribute(h, 3);
		tempq = sch->getSJFRDY(i);
		cout << tempq->getCount() << " " << "RDY: ";
		tempq->print();
		SetConsoleTextAttribute(h, 7);
	}
	for (int i = 0; i < rr_n; i++)
	{
		cout << "Proccessor " << i + fcfs_n+sjf_n+1 << " [RR]: ";
		SetConsoleTextAttribute(h, 2);
		tempq = sch->getRRRDY(i);
		cout << tempq->getCount() << " " << "RDY: ";
		tempq->print();
		SetConsoleTextAttribute(h, 7);
	}
}

void UI::printBLK()
{
	LinkedQueue<process*>* tempq;
	cout << "------------------ BLK processes --------------------" << endl;
	SetConsoleTextAttribute(h, 1);
	tempq = sch->getEssQ('b');
	cout << tempq->getCount() << " " << "BLK: ";
	tempq->print();
	SetConsoleTextAttribute(h, 7);

}

void UI::printRUN()
{
	process* temp;
	cout << "------------------ RUN processes --------------------" << endl;
	cout << sch->getRnum() << " RUN: ";
	for (int i = 0; i < fcfs_n + sjf_n + rr_n; i++)
	{
		SetConsoleTextAttribute(h, 6);
		temp = sch->getcurrpro(i);
		SetConsoleTextAttribute(h, 7);
		if (temp) {
			SetConsoleTextAttribute(h, 6);
			cout << temp;
			SetConsoleTextAttribute(h, 7);
			cout << " P(" << i + 1 << ") ";
		}
	}
	cout << endl;
}

void UI::printTRM()
{
	LinkedQueue<process*>* tempq;
	cout << "------------------ TRM processes --------------------" << endl;
	SetConsoleTextAttribute(h, 8);
	tempq = sch->getEssQ('t');
	cout << tempq->getCount() << " " << "TRM: ";
	tempq->print();
	SetConsoleTextAttribute(h, 7);

}

void UI::UpdateUI()
{
	if (mode != 3)
	{
		if (mode == 1)
		{
			while (cin.get() != '\n') {}	// to wait for enter press
		}
		else if (mode == 2)
		{
			Sleep(1000);					// to wait a second
		}
		cout << "Current Timestep : ";
		SetConsoleTextAttribute(h, 4);		// changing the colors
		cout << sch->getCurrTime() << endl; // printing the timestep
		SetConsoleTextAttribute(h, 7);
		printPros();						// printing the processors' ready lists
		printBLK();							// printing the block
		printRUN();							// printing the running processes
		printTRM();							// printing the termination list
		cout << "----------------------------------------------------------------------------------------------------------" << endl;
		if (mode == 1)
			cout << "press Enter to NEXT step" << endl;
	}
}

void UI::end()
{
	if (mode != 3 && mode != -1)
	{
		cout << "end the project" << endl;
		cout << "PRESS Q TO EXIT" << endl;
		while (cin.get() != 'q') {}		
		HWND myConsole = GetConsoleWindow(); //window handle
		ShowWindow(myConsole, 0); //handle window
	}
	else if (mode == -1)
	{
		HWND myConsole = GetConsoleWindow(); //window handle
		ShowWindow(myConsole, 0); //handle window
	}
}

UI::~UI()
{

}