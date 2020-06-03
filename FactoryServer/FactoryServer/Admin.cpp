#include "Admin.h"
#include"Factory.h"
#include"Libraries.h"
#include "User.h"
#include"Manager.h"

extern SOCKET Socket2;
void problemStatement();
int Admin::authorization()
{
	char login[20];
	char password[17];
	recv(Socket2, login, sizeof(login), 0);
	recv(Socket2, password, sizeof(password), 0);

	ifstream file;
	string puth = "AdminAut.txt";
	file.open(puth);
	Admin admin;
	if ((file.is_open()))
	{
		getline(file, admin.login);
		getline(file, admin.password);
	}
	file.close();

	for (int i = 0; i < admin.login.size(); i++) admin.login[i] = admin.login[i] + 7;
	for (int i = 0; i < admin.password.size(); i++) admin.password[i] = admin.password[i] + 7;

	char result[2];
	if ((admin.password == password) && (admin.login == login))
	{
		_itoa_s(1, result, sizeof(result), 10);
		send(Socket2, result, 2, 0);
		showMenu();
	}
	else {
		_itoa_s(0, result, sizeof(result), 10);
		send(Socket2, result, 2, 0);
	}

	return 0;
}
void Admin::showMenu()
{
	int a = 0;
	do
	{
		char msgChoice[5];
		recv(Socket2, msgChoice, sizeof(msgChoice), 0);
		int choice = atoi(msgChoice);
		Factory Factory;

		switch (choice)
		{
		case 1:Factory.MenuRun(); break;
		case 2:problemStatement(); break;
		case 3: a = 4; break;
		}

	} while (a != 4);
}

void problemStatement()
{
	ifstream file;
	string puth = "Roate.txt";
	file.open(puth);
	int number = 0;

	int numberOfRecords = returnNumberOfRecords(2);

	char numberOfRecordsC[5];
	_itoa_s(numberOfRecords, numberOfRecordsC, 10);
	send(Socket2, numberOfRecordsC, 5, 0);

	if (numberOfRecords != 0)
	{
		if (file.is_open())
		{
			vector<User> users;
			User user;
			for (int i = 0; i < numberOfRecords; i++)
			{
				file >> user;
				users.push_back(user);
			}
			char number[5];
			_itoa_s(users.size(), number, 10);   /* Перевожу количество записей в char*/
			send(Socket2, number, 5, 0);
			if (users.size() != 0)
			{
				for (int i = 0; i < users.size(); i++)    /*Енто цикл))*/
				{
					send(Socket2, users[i].goal, 30, 0);   /* Отправляем:)*/
					send(Socket2, users[i].wghtC, 30, 0);
					send(Socket2, users[i].surname, 20, 0);
					send(Socket2, users[i].name, 20, 0);
				}

				char nRC[5]; int nR;
				recv(Socket2, nRC, 5, 0);   nR = atoi(nRC);
			r:;
				Factory factory;
				factory.view();
				factory.view();

				char repeatC[5]; int repeat;
				recv(Socket2, repeatC, 5, 0); repeat = atoi(repeatC);
				if (repeat == 1)
				{
					char car1C[5]; int car1;
					char car2C[5]; int car2;
					char car3C[5]; int car3;

					recv(Socket2, car1C, 5, 0); car1 = atoi(car1C);
					recv(Socket2, car2C, 5, 0); car2 = atoi(car2C);
					recv(Socket2, car3C, 5, 0); car3 = atoi(car3C);

					vector<Factory> cars;
					cars.push_back(factory.returnFactory(car1));
					cars.push_back(factory.returnFactory(car2));
					cars.push_back(factory.returnFactory(car3));

					string puth = "RoutToExpert.txt";
					ofstream file;
					file.open(puth, ofstream::app);
					if (file.is_open())
					{
						file << users[nR].goal << endl;
						file << users[nR].wghtC << endl;

						file << users[nR].surname << endl;
						file << users[nR].name << endl;
						file << cars[0];
						file << cars[1];
						file << cars[2];
						file.close();

						changeNumberOfRecords(1, 3);

						string puth1 = "Roate.txt";
						ofstream file;
						file.open(puth1);
						if (file.is_open())
						{
							for (int i = 0; i < nR; i++)
							{
								file << users[i].goal << endl;
								file << users[i].wghtC << endl;
								file << users[i].surname << endl;
								file << users[i].name << endl;

							}
							for (int i = nR; i < numberOfRecords; i++)
							{
								file << users[i].goal << endl;
								file << users[i].wghtC << endl;
								file << users[i].surname << endl;
								file << users[i].name << endl;
							}
						}
						file.close();
						changeNumberOfRecords(2, 2);
						char message[30] = "Информация успешно добавлена.";
						send(Socket2, message, 30, 0);
					}
					else
					{
						char message[30] = "Файл не был открыт.";
						send(Socket2, message, 30, 0);
					}

				}
				else
				{
					goto r;
				}
			}
		}
	}
}