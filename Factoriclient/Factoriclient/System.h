#pragma once
#include"Libraries.h"
#pragma once
class System
{
protected:
	char surname[20];
	char name[20];
public:
	virtual int authorization() = 0;
	virtual void showMenu() = 0;
};


