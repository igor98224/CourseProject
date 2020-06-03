#include "User.h"
#include "Manager.h"
#include"Factory.h"
extern SOCKET Socket2;
int User::signUp()
{
	recv(Socket2, surname, 20, 0);
	recv(Socket2, name, 20, 0);

	char loginC[20];
	char passwordC[20];
	recv(Socket2, loginC, 20, 0);
	recv(Socket2, passwordC, 20, 0);

	ofstream file;
	string puth = "UserAccount.txt";
	file.open(puth, ofstream::app);

	if (file.is_open())
	{
		file << surname << endl;
		file << name << endl;
		file << loginC << endl;
		file << passwordC << endl;
		changeNumberOfRecords(1, 5);
		file.close();
		char msg[37] = "Пользователь успешно зарегистрирован";
		send(Socket2, msg, 37, 0);
	}
	else
	{
		char msg[37] = "Сбой регистрации. Повторите снова.";
		send(Socket2, msg, 37, 0);
	}
	return 0;
}

void  User::showMenu()
{
	int a = 0;
	do
	{
		char msgChoice[5];
		recv(Socket2, msgChoice, sizeof(msgChoice), 0);
		int choice = atoi(msgChoice);
		switch (choice)
		{
		case 1: authorization(); break;
		case 2: signUp(); break;
		case 3: a = 4; system("cls"); break;
		}

	} while (a != 4);
}
int User::authorization()
{
	char  login[20];
	char password[20];
	recv(Socket2, login, 20, 0);
	recv(Socket2, password, 20, 0);
	ifstream file;
	string puth = "UserAccount.txt";
	file.open(puth);
	if ((file.is_open()))
	{

		int numberOfAccount = returnNumberOfRecords(5);
		vector<User> users;
		User user;
		for (int i = 0; i < numberOfAccount && !file.eof(); i++)
		{
			string m;
			getline(file, m);
			strcpy(user.surname, m.c_str());

			getline(file, m);
			strcpy(user.name, m.c_str());

			string p, l;
			getline(file, l);
			getline(file, p);
			for (int i = 0; i < l.size(); i++) l[i] = l[i] + 7;
			for (int i = 0; i < p.size(); i++) p[i] = p[i] + 7;
			strcpy(user.login, l.c_str());
			strcpy(user.password, p.c_str());

			users.push_back(user);
		}
		int m = -1;
		for (int i = 0; i < numberOfAccount; i++)
		{
			if ((strcmp(users[i].password, password) == 0) && (strcmp(users[i].login, login) == 0))
			{

				send(Socket2, "1", 2, 0);
				send(Socket2, users[i].surname, 20, 0);
				send(Socket2, users[i].name, 20, 0);

				strcpy(surname, users[i].surname);
				strcpy(name, users[i].name);

				showMenu();
				return 1;
			}

		}
		if (m == -1)
		{
			send(Socket2, "0", 2, 0);
			char msg[54] = "Пользователь с таким логином и паролем не существует.";
			char msg1[20] = "Повторите еще раз.";
			send(Socket2, msg, 54, 0);
			send(Socket2, msg1, 20, 0);
			return 0;
		}

	}
	file.close();
	return 0;

}
void  User::showUserMenu()
{
	int a = 0;
	do
	{
		char msgChoice[5];
		recv(Socket2, msgChoice, 5, 0);
		int choice = atoi(msgChoice);
		switch (choice)
		{
		case 1: registerDelivery();  break;
		case 2: a = 4; system("cls"); break;
		}

	} while (a != 4);

}
void  User::registerDelivery()
{
	recv(Socket2, goal, 30, 0);
	recv(Socket2, wghtC, 30, 0);
	recv(Socket2, surname, 20, 0);
	recv(Socket2, name, 20, 0);

	ofstream file;
	string puth = "Roate.txt";
	file.open(puth, ofstream::app);
	if (file.is_open())
	{
		file << goal << endl;
		file << wghtC << endl;
		file << surname << endl;
		file << name << endl;

		changeNumberOfRecords(1, 2);
		file.close();
		char msg[37] = "Маршрут успешно зарегистрирован";
		send(Socket2, msg, 37, 0);
	}
	else
	{
		char msg[37] = "Сбой регистрации. Повторите снова.";
		send(Socket2, msg, 37, 0);
	}

}
int  User::viewRecordedRequests()
{
	ifstream file;
	string puth = "Roate.txt";
	file.open(puth);
	vector< User> users;
	int numberOfRecords = returnNumberOfRecords(2);

	char numberOfRecordsC[5];
	_itoa_s(numberOfRecords, numberOfRecordsC, 10);
	send(Socket2, numberOfRecordsC, 5, 0);

	if (numberOfRecords != 0)
	{
		if (file.is_open())
		{
			User user;
			string m;
			for (int i = 0; i < numberOfRecords; i++)
			{
				file >> user;
				if ((strcmp(user.surname, surname) == 0) && (strcmp(user.name, name) == 0))
				{
					users.push_back(user);
				}
			}
			char number[5];
			_itoa_s(users.size(), number, 10);
			send(Socket2, number, 5, 0);
			if (users.size() != 0)
			{
				for (int i = 0; i < users.size(); i++)
				{
					send(Socket2, users[i].goal, 30, 0);
					send(Socket2, users[i].wghtC, 30, 0);
				}

			}
			else return 0;
		}
		else return 0;
	}
	else return 0;
	return 0;
}
int  User::showAccaptedRequests()
{
	ifstream file;
	string puth = "RoateFinal.txt";
	file.open(puth);

	int numberOfRecords = returnNumberOfRecords(4);

	char numberOfRecordsC[5];
	_itoa_s(numberOfRecords, numberOfRecordsC, 10);
	send(Socket2, numberOfRecordsC, 5, 0);

	if (numberOfRecords != 0)
	{
		if (file.is_open())
		{
			typedef pair< User, Factory> pair;
			vector<pair> data;

			User user;
			Factory factory;
			string m;

			for (int i = 0; i < numberOfRecords; i++)
			{
				file >> user;
				file >> factory;
				if ((strcmp(user.surname, surname) == 0) && (strcmp(user.name, name) == 0))
				{
					data.push_back(pair(user, factory));
				}
			}
			char number[5];
			_itoa_s(data.size(), number, 10);
			send(Socket2, number, 5, 0);
			if (data.size() != 0)
			{
				vector<pair>::iterator n;
				for (n = data.begin(); n != data.end(); ++n)
				{
					send(Socket2, n->first.goal, 5, 0);
					send(Socket2, n->first.wghtC, 5, 0);
					n->second.sendF();
				}

			}
			else return 0;
		}
		else return 0;
	}
	else return 0;
	return 0;

}
void User::sendF()
{
	send(Socket2, goal, 5, 0);
	send(Socket2, wghtC, 5, 0);
	send(Socket2, surname, 20, 0);
	send(Socket2, name, 20, 0);
}
ifstream& operator >>(ifstream& file, User& ob)
{
	file >> ob.goal;
	file >> ob.wghtC;
	file >> ob.surname;
	file >> ob.name;
	return file;
}


