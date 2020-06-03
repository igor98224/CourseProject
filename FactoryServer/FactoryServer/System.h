#pragma once
#include"Libraries.h"
#pragma once
class System
{
protected:
	string login;
	string password;
public:
	virtual int authorization() = 0;
	virtual void showMenu() = 0;
};
