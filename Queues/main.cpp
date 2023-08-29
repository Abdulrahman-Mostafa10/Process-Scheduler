#pragma once
#include"scheduler.h"
using namespace std;
int main()
{
	scheduler* MainSys_tem = new scheduler("../f5.txt");
	MainSys_tem->Excute();
	return 0;
}