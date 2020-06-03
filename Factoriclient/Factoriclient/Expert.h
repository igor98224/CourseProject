#pragma once
#pragma once
#include "Libraries.h"
#include "System.h"
class Expert :public System
{
public:
	int authorization() override;
	void showMenu() override;
	void showApprovedDelivery();
	int startMetod();
};

