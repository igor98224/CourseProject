#include "User.h"
#include"Manager.h"
extern SOCKET Socket;
int User::authorization()
{
	char  login[20];
	char password[20];

	cout << "Введите логин" << endl;
	cin >> login;
	cout << "Введите пароль" << endl;
	int j = 0;
	while (j != 16)
	{
		password[j] = _getch();
		if (password[j] == '\r')
			break;
		if (password[j] == '\b')
		{
			printf("\b \b");
			j--;
		}
		else if (password[j] != '\0')
		{
			printf("*");
			j++;
		}
	}
	password[j] = '\0';
	send(Socket, login, 20, 0);
	send(Socket, password, 20, 0);

	char choiceC[2];
	int choice;
	recv(Socket, choiceC, 2, 0);
	choice = atoi(choiceC);
	if (choice == 1)
	{
		recv(Socket, surname, 20, 0);
		recv(Socket, name, 20, 0);
		system("cls");
		cout << "Пользователь " << surname << " " << name << " авторизован." << endl;
		showUserMenu();
	}
	if (choice == 0)
	{
		char msg[54];
		char msg1[20];
		recv(Socket, msg, 54, 0);
		recv(Socket, msg1, 20, 0);
		cout << msg << endl;
		cout << msg1 << endl;
	}
	return 0;
}
int  User::signUp()
{
	cout << "Регистрация нового пользователя." << endl;
	cout << "Введите фамилию." << endl;
	char surname[20];
	do {
		cin >> surname;
	} while (!testLetters(surname));
	send(Socket, surname, 20, 0);

	char name[20];
	cout << "Введите имя." << endl;
	do {
		cin >> name;
	} while (!testLetters(name));
	send(Socket, name, 20, 0);

	string login;
	string password;
	cout << "Введите логин" << endl;
	cin >> login;

	cout << "Введите пароль" << endl;
	cin >> password;

	for (int i = 0; i < login.size(); i++) login[i] = login[i] - 7;
	for (int i = 0; i < password.size(); i++) password[i] = password[i] - 7;

	int sizeP = password.length() + 1;
	char* passwordC = new char[sizeP];
	strcpy(passwordC, password.c_str());
	send(Socket, passwordC, sizeP, 0);

	int sizeL = login.length() + 1;
	char* loginC = new char[sizeL];
	strcpy(loginC, login.c_str());
	send(Socket, passwordC, sizeL, 0);

	delete[] passwordC;
	delete[] loginC;

	char msg[37];
	recv(Socket, msg, 37, 0);
	cout << msg << endl;
	return 0;
}
void  User::showMenu()
{
	int a = 0;
	do
	{
		cout << "Меню:" << endl;
		cout << "1.Авторизация." << endl;
		cout << "2.Регистрация." << endl;
		cout << "3.Вернуться назад." << endl;
		int choice = check<int>(1, 3);
		char msgChoice[5];
		_itoa_s(choice, msgChoice, 10);
		send(Socket, msgChoice, 5, 0);

		switch (choice)
		{
		case 1:system("cls"); authorization(); break;
		case 2: system("cls"); signUp(); break;
		case 3: a = 4; system("cls"); break;
		default:system("cls"); cout << "Данные введены некорректно." << endl;
		}

	} while (a != 4);
}
void  User::showUserMenu()
{
	int a = 0;
	do
	{
		cout << "Меню:" << endl;
		cout << "1.Создание доставки." << endl;
		cout << "2.Вернуться назад." << endl;
		int choice = check<int>(1, 4);
		char msgChoice[5];
		_itoa_s(choice, msgChoice, 10);
		send(Socket, msgChoice, 5, 0);

		switch (choice)
		{
		case 1: system("cls"); registerDelivery(); system("cls");  break;
		case 2: a = 4; system("cls"); break;
		default:system("cls"); cout << "Данные введены некорректно." << endl;
		}

	} while (a != 4);

}
int  User::registerDelivery()
{
	cout << "Введите данные о доставке." << endl << endl;
	char goal1[30] = "Доставка_куриц";    char km1[30] = "Легкий_груз";
	char goal2[30] = "Доставка_птиц";   char km2[30] = "средний_груз";
	char goal3[30] = "Доставка_других_продуктов";            char km3[30] = "тяжелый_груз";
	char goal4[30] = "Деловая поездка";
	cout << "Выберете цель поездки." << endl;
	cout << "1. " << goal1 << endl;
	cout << "2. " << goal2 << endl;
	cout << "3. " << goal3 << endl;
	cout << "4. " << goal4 << endl;
	int goal = check<int>(1, 4);
	switch (goal)
	{
	case 1: send(Socket, goal1, 30, 0); break;
	case 2: send(Socket, goal2, 30, 0); break;
	case 3: send(Socket, goal3, 30, 0); break;
	case 4: send(Socket, goal4, 30, 0); break;
	}
	cout << "Выберете тип груза доставки ." << endl;
	cout << "1." << km1 << endl;
	cout << "2." << km2 << endl;
	cout << "3." << km3 << endl;
	int  km = check<int>(1, 3);
	switch (km)
	{
	case 1: send(Socket, km1, 30, 0); break;
	case 2: send(Socket, km2, 30, 0); break;
	case 3: send(Socket, km3, 30, 0); break;

	}

	send(Socket, surname, 20, 0);
	send(Socket, name, 20, 0);
	char msg[37];
	recv(Socket, msg, 37, 0);
	system("cls");
	cout << msg << endl;
	system("pause");
	return 0;
}
void  User::showRecordedDelivery()
{
	int numberOfRecords; char numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	numberOfRecords = atoi(numberOfRecordsC);
	if (numberOfRecords != 0)
	{
		char numberC[5];
		recv(Socket, numberC, 5, 0);
		int number = atoi(numberC);
		char wghtC[30];
		char goal[30];
		if (number == 0)
		{
			cout << "Зарегистрированные доставки отсутствуют." << endl;
		}
		else
		{
			for (int i = 0; i < number; i++)
			{
				recv(Socket, goal, 30, 0);
				recv(Socket, wghtC, 30, 0);
				cout << i + 1 << "| " << surname << setw(15 - strlen(surname)) << "|" << name
					<< setw(15 - strlen(name)) << "|" << goal << setw(34 - strlen(goal)) << "|" << wghtC << endl;
			}

		}
	}
	else
	{
		cout << "У вас отстутсвуют одобренные доставки." << endl;
	}

}
void  User::showApprovedDelivery()
{
	int numberOfRecords; char numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	numberOfRecords = atoi(numberOfRecordsC);
	if (numberOfRecords != 0)
	{
		char numberC[5];
		recv(Socket, numberC, 5, 0);
		int number = atoi(numberC);

		if (number == 0)
		{
			cout << "У вас отстутсвуют одобренные доставки." << endl;
		}
		else
		{
			char wghtC[30];
			char goal[30];

			char markOfVenicle[20];
			char registrNumber[20];
			char type[20];
			for (int i = 0; i < number; i++)
			{
				recv(Socket, goal, 30, 0);
				recv(Socket, wghtC, 30, 0);

				recv(Socket, markOfVenicle, 20, 0);
				recv(Socket, registrNumber, 20, 0);
				recv(Socket, type, 20, 0);
				cout << i + 1 << "| " << surname << setw(15 - strlen(surname)) << "|" << name
					<< setw(15 - strlen(name)) << "|" << goal << setw(34 - strlen(goal)) << "|" << wghtC << setw(25 - strlen(wghtC)) << "|"
					<< markOfVenicle << setw(15 - strlen(markOfVenicle)) << "|" << registrNumber << endl;
			}

		}
	}
	else
	{
		cout << "У вас отстутсвуют одобренные доставки." << endl;
	}
}