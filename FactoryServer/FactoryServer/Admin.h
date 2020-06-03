#pragma once
#include"Libraries.h"
#include"System.h"
#pragma once
class Admin :public System
{
public:
	int  authorization() override;
	void showMenu() override;
};

