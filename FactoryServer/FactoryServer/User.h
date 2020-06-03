#pragma once
#include "System.h"
#include"Libraries.h"
#include"Admin.h"
#include"Expert.h"
#pragma once

class User :public System
{
	char  login[20];
	char password[20];
	char goal[30];
	char wghtC[30];
	char surname[20];
	char name[20];
public:

	int authorization() override;
	void showMenu() override;
	int signUp();
	void showUserMenu();
	void registerDelivery();
	int viewRecordedRequests();
	int showAccaptedRequests();
	
	void sendF();
	friend ifstream& operator >>(ifstream& file, User& ob);
	friend void problemStatement();
	friend void runMethod();

};

