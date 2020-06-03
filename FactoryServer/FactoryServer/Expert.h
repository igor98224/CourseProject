#pragma once
#include "System.h"
#include"Libraries.h"
#pragma once
class Expert :public System
{
public:
	int authorization() override;
	void showMenu() override;
	void showAccaptedRequests();
};

