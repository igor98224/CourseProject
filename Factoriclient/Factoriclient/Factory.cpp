#include "Factory.h"
#include"Manager.h"
#include"Exeption.h"
extern SOCKET Socket;
void Factory::add()
{
	cout << "Добавление новой фабрики." << endl;
	cout << "Введите название фабрики." << endl;
	char markOfFactory[20];
	do
	{
		cin >> markOfFactory;
		try
		{
			if (!testLetters(markOfFactory)) { throw Exeption("Данные введены некорректно. Повторите ввод."); }

		}
		catch (const Exeption e)
		{

			cout << e.errorMessage << endl;

		}

	} while (!testLetters(markOfFactory));
	send(Socket, markOfFactory, 20, 0);
	system("cls");

	char type1[20] = "курицы";
	char type2[20] = "гуси";
	char type3[20] = "другие продукты";
	cout << "Выберите назначение фабрики." << endl;
	cout << "1. курицы" << endl;
	cout << "2. гуси" << endl;
	cout << "3. другие продукты" << endl;
	int choice = check<int>(1, 3);
	if (choice == 1) send(Socket, type1, 20, 0);
	if (choice == 2) send(Socket, type2, 20, 0);
	if (choice == 3) send(Socket, type3, 20, 0);

	system("cls");
	char fileIsOpen[30];
	recv(Socket, fileIsOpen, sizeof(fileIsOpen), 0);
	cout << fileIsOpen << endl;

}
int  Factory::view()
{
	cout << "Просмотр фабрик." << endl;
	char numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	int numberOfRecords = atoi(numberOfRecordsC);
	if (numberOfRecords == 0)
	{
		cout << "Записей нет." << endl;
	}
	else
	{
		char markOfFactory[20];
		char type[20];


		cout << "______________________________________________" << endl
			<< "|" << "№" << setw(3) << "|" << setw(5) << "Название фабрики" << setw(2) << "|"
			<< "Вес доставки" << setw(7) << "|" << endl
			<< "|___|_________________|_______________________|" << endl;
		for (int i = 0; i < numberOfRecords; i++)
		{
			recv(Socket, markOfFactory, 20, 0);
			recv(Socket, type, 20, 0);
			cout << "|" << i + 1 << setw(3) << "|" << markOfFactory << setw(18 - strlen(markOfFactory)) << "|" << type
				<< setw(24 - strlen(type)) << "|" << endl
				<< "|___|_________________|_______________________|" << endl;

		}

	}
	return numberOfRecords;
}

void  Factory::showMenu()
{
	int a = 0;
	do
	{
		cout << "Меню:" << endl;
		cout << "1.Добавление птицефабрики." << endl;
		cout << "2.Просмотр птицефабрик." << endl;
		cout << "3.Редактирование птицефабрик." << endl;
		cout << "4.Удаление птицефабрик." << endl;
		cout << "5.Сортировка птицефабрик." << endl;
		cout << "6.Вернуться назад." << endl;
		int choice = check<int>(1, 7);
		char msgChoice[5];
		_itoa_s(choice, msgChoice, 10);
		send(Socket, msgChoice, 5, 0);
		switch (choice)
		{
		case 1:system("cls"); add();  break;
		case 2:system("cls"); view();  break;
		case 3:system("cls"); edit();  break;
		case 4:system("cls"); deletee();  break;
		case 5:system("cls"); sort();  break;
		case 6: a = 4; system("cls"); break;
		default:system("cls"); cout << "Данные введены некорректно." << endl;
		}

	} while (a != 4);
}
void  Factory::edit()
{
	int numberOfRecords = view();;
	cout << "Выберете номер записи для редактирования." << endl;
	int numRec = check<int>(1, numberOfRecords) - 1;
	char numRecC[5];
	_itoa_s(numRec, numRecC, 10);
	send(Socket, numRecC, 5, 0);

	system("cls");
	cout << "Выберете поле для редактирования." << endl;
	cout << "1.Название птицефабрики." << endl;
	cout << "2.Тип груза доставки." << endl;
	int p = check<int>(1, 3);
	char pC[5];
	_itoa_s(p, pC, 10);
	send(Socket, pC, 5, 0);
	switch (p)
	{
	case 1:
		cout << "Введите птицефабрику." << endl;
		char markOfFactory[20];
		do
		{
			cin >> markOfFactory;
			try
			{
				if (!testLetters(markOfFactory)) { throw Exeption("Данные введены некорректно. Повторите ввод."); }

			}
			catch (const Exeption e)
			{

				cout << e.errorMessage << endl;

			}

		} while (!testLetters(markOfFactory));
		send(Socket, markOfFactory, 20, 0); break;

	case 2:
		char type1[20] = "курицы";
		char type2[20] = "гуси";
		char type3[20] = "другие продукты";
		cout << "Введите вид доставки." << endl;
		cout << "1. курицы" << endl;
		cout << "2. гуси" << endl;
		cout << "3. другие продукты" << endl;
		int choice = check<int>(1, 3);
		if (choice == 1) send(Socket, type1, 20, 0);
		if (choice == 2) send(Socket, type2, 20, 0);
		if (choice == 3) send(Socket, type3, 20, 0); break;
	}

	system("cls");
	char fileIsOpen[30];
	recv(Socket, fileIsOpen, sizeof(fileIsOpen), 0);
	cout << fileIsOpen << endl;
	view();
}
void  Factory::search()
{

	cout << "Поиск." << endl;
	cout << "1.По названию фабрики." << endl;
	cout << "3.Тип груза доставки." << endl;
	int p = check<int>(1, 3);
	char pC[5];
	_itoa_s(p, pC, 10);
	send(Socket, pC, 5, 0);

	switch (p)
	{
	case 1:
		cout << "Введите название фабрики." << endl;
		char markOfFactory[20];
		do
		{
			cin >> markOfFactory;
			try
			{
				if (!testLetters(markOfFactory)) { throw Exeption("Данные введены некорректно. Повторите ввод."); }

			}
			catch (const Exeption e)
			{

				cout << e.errorMessage << endl;

			}

		} while (!testLetters(markOfFactory));
		send(Socket, markOfFactory, 20, 0);

		break;

	case 3:
		char type1[20] = "курицы";
		char type2[20] = "гуси";
		char type3[20] = "другие продукты";
		cout << "Введите вид доставки." << endl;
		cout << "1. курицы" << endl;
		cout << "2. гуси" << endl;
		cout << "3. другие продукты" << endl;
		int choice = check<int>(1, 3);
		if (choice == 1) send(Socket, type1, 20, 0);
		if (choice == 2) send(Socket, type2, 20, 0);
		if (choice == 3) send(Socket, type3, 20, 0); break;
	}


}
void  Factory::deletee()
{
	cout << "1.Удалить определенную запись." << endl;
	cout << "2.Удалить все." << endl;
	int p = check<int>(1, 2);
	char pC[5];
	_itoa_s(p, pC, 10);
	send(Socket, pC, 5, 0);
	if (p == 1)
	{
		int  numberOfRecords = view();
		cout << "Выберете запись для удаления." << endl;
		int numRec = check<int>(1, numberOfRecords) - 1;
		char numRecC[5];
		_itoa_s(numRec, numRecC, 10);
		send(Socket, numRecC, 5, 0);
	}
	char fileIsOpen[30];
	recv(Socket, fileIsOpen, sizeof(fileIsOpen), 0);
	cout << fileIsOpen << endl;
}
void  Factory::sort()
{
	cout << "1.Сортировать по названию птицефабрики." << endl;
	cout << "2.Сортировать по типу груза доставки." << endl;
	int p = check<int>(1, 2);
	char pC[5];
	_itoa_s(p, pC, 10);
	send(Socket, pC, 5, 0);

	char markOfFactory[20];
	char type[20];
	char numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	int numberOfRecords = atoi(numberOfRecordsC);
	if (numberOfRecords == 0)
	{
		cout << "Записей нет." << endl;
	}
	else
	{
		cout << "_______________________________________________________________________" << endl
			<< "|" << "№" << setw(3) << "|" << setw(5) << "Название птицефабрики" << setw(2) << "|"
			<< "Тип по назначению" << setw(7) << "|" << endl
			<< "|___|_________________|_______________________|" << endl;
		for (int i = 0; i < numberOfRecords; i++)
		{
			recv(Socket, markOfFactory, 20, 0);
			recv(Socket, type, 20, 0);
			cout << "|" << i + 1 << setw(3) << "|" << markOfFactory << setw(18 - strlen(markOfFactory)) << "|" << type
				<< setw(24 - strlen(type)) << "|" << endl
				<< "|___|_________________|_______________________|" << endl;

		}

	}


}