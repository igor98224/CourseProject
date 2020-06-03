#pragma once
#include "Libraries.h"
#include "System.h"
#pragma once

class User :public System
{
public:
	int authorization() override;
	void showMenu() override;
	int signUp();
	void showUserMenu();
	int registerDelivery();
	void showRecordedDelivery();
	void showApprovedDelivery();
};

