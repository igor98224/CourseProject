#include "Admin.h"
#include"Libraries.h"
#include "Manager.h"
#include"Factory.h"
#include"User.h"
extern SOCKET Socket;
int Admin::authorization()
{
	char login[20];
	char password[17];
	cout << "Введите логин" << endl;
	cin >> login;
	send(Socket, login, 20, 0);
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

	send(Socket, password, 17, 0);
	char result[2];
	recv(Socket, result, sizeof(result), 0);
	if (atoi(result) == 1)
	{
		system("cls");
		cout << "Вход выполнен успешно." << endl;
		system("pause");
		system("cls");
		showMenu();
		return 1;
	}
	else
	{
		system("cls");
		cout << "Логин или пароль введены неверно." << endl;
		system("pause");
		system("cls");
		return 0;
	}

}
void Admin::showMenu()
{
	int a = 0;
	do
	{
		cout << "Меню:" << endl;
		cout << "1.Управление птицефермой." << endl;
		cout << "2.Создание доставки" << endl;
		cout << "3.Вернуться назад." << endl;
		int choice = check<int>(1, 3);
		char msgChoice[5];
		_itoa_s(choice, msgChoice, 10);
		send(Socket, msgChoice, 5, 0);
		Factory factory;
		switch (choice)
		{
		case 1:system("cls"); factory.showMenu(); break;
		case 2: system("cls"); problemStatement(); break;
		case 3: a = 4; system("cls"); break;
		default:system("cls"); cout << "Данные введены некорректно." << endl;
		}

	} while (a != 4);
}
void Admin::problemStatement()
{
	int numberOfRecords; char numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	numberOfRecords = atoi(numberOfRecordsC);
	if (numberOfRecords != 0)
	{
		char surname[20];
		char name[20];

		char numberC[5];
		recv(Socket, numberC, 5, 0);
		int number = atoi(numberC);

		char wghtC[30];
		char goal[30];

		for (int i = 0; i < number; i++)
		{
			recv(Socket, goal, 30, 0);
			recv(Socket, wghtC, 30, 0);
			recv(Socket, surname, 20, 0);
			recv(Socket, name, 20, 0);
			cout << i + 1 << "| " << surname << setw(30 - strlen(surname)) << "|" << name
				<< setw(12 - strlen(name)) << "|" << goal << setw(34 - strlen(goal)) << "|" << wghtC << endl;
		}

		cout << "Выберете доставку в нужную фабрику." << endl;
		int nR = check<int>(1, number) - 1;
		char nRC[5];
		_itoa_s(nR, nRC, 10);
		send(Socket, nRC, 5, 0);
	r:;
		Factory factory;
		int numCars = factory.view();
		cout << "Выберете три Птицефабрики." << endl;
		int car1 = check<int>(1, numCars);
		int car2 = check<int>(1, numCars);
		int car3 = check<int>(1, numCars);

		system("cls");
		factory.view();
		cout << "Ваш выбор:" << endl;
		cout << "Фабрика №" << car1 << endl;
		cout << "Фабрика №" << car2 << endl;
		cout << "Фабрика №" << car3 << endl;

		cout << " 1. Подтвердить выбор" << endl;
		cout << " 2. Повторить выбор" << endl;
		int choice = check<int>(1, 2);
		char repeat[5];
		_itoa_s(choice, repeat, 10);
		send(Socket, repeat, 5, 0);
		if (choice == 1)
		{
			char car1C[5];
			char car2C[5];
			char car3C[5];
			_itoa_s(car1, car1C, 10);
			_itoa_s(car2, car2C, 10);
			_itoa_s(car3, car3C, 10);

			send(Socket, car1C, 5, 0);
			send(Socket, car2C, 5, 0);
			send(Socket, car3C, 5, 0);
		}
		else
		{
			system("cls");
			goto r;
		}
		system("cls");
		char fileIsOpen[30];
		recv(Socket, fileIsOpen, 30, 0);
		cout << fileIsOpen << endl;
		changeNumberOfRecords(2, 2);
	}
}