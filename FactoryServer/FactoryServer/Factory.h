#pragma once
#include"Libraries.h"
#include"Expert.h"
#pragma once
class Factory
{
	char FactoryName[20];
	char type[20];
public:
	void sendF();
	void add();
	void view();
	void MenuRun();
	Factory returnFactory(int num);
	void fileRead(vector<Factory>* factories);
	void fileRewrite(vector<Factory> factories);
	void  edit();
	void deletee();
	void search();
	void sort();
	friend ofstream& operator <<(ofstream& file, const Factory& ob);
	friend ifstream& operator >>(ifstream& file, Factory& ob);
	friend void runMethod();
};

