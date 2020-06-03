#include "Factory.h"
#include"Manager.h"
#include"Exeption.h"
extern SOCKET Socket;
void Factory::add()
{
	cout << "���������� ����� �������." << endl;
	cout << "������� �������� �������." << endl;
	char markOfFactory[20];
	do
	{
		cin >> markOfFactory;
		try
		{
			if (!testLetters(markOfFactory)) { throw Exeption("������ ������� �����������. ��������� ����."); }

		}
		catch (const Exeption e)
		{

			cout << e.errorMessage << endl;

		}

	} while (!testLetters(markOfFactory));
	send(Socket, markOfFactory, 20, 0);
	system("cls");

	char type1[20] = "������";
	char type2[20] = "����";
	char type3[20] = "������ ��������";
	cout << "�������� ���������� �������." << endl;
	cout << "1. ������" << endl;
	cout << "2. ����" << endl;
	cout << "3. ������ ��������" << endl;
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
	cout << "�������� ������." << endl;
	char numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	int numberOfRecords = atoi(numberOfRecordsC);
	if (numberOfRecords == 0)
	{
		cout << "������� ���." << endl;
	}
	else
	{
		char markOfFactory[20];
		char type[20];


		cout << "______________________________________________" << endl
			<< "|" << "�" << setw(3) << "|" << setw(5) << "�������� �������" << setw(2) << "|"
			<< "��� ��������" << setw(7) << "|" << endl
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
		cout << "����:" << endl;
		cout << "1.���������� ������������." << endl;
		cout << "2.�������� �����������." << endl;
		cout << "3.�������������� �����������." << endl;
		cout << "4.�������� �����������." << endl;
		cout << "5.���������� �����������." << endl;
		cout << "6.��������� �����." << endl;
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
		default:system("cls"); cout << "������ ������� �����������." << endl;
		}

	} while (a != 4);
}
void  Factory::edit()
{
	int numberOfRecords = view();;
	cout << "�������� ����� ������ ��� ��������������." << endl;
	int numRec = check<int>(1, numberOfRecords) - 1;
	char numRecC[5];
	_itoa_s(numRec, numRecC, 10);
	send(Socket, numRecC, 5, 0);

	system("cls");
	cout << "�������� ���� ��� ��������������." << endl;
	cout << "1.�������� ������������." << endl;
	cout << "2.��� ����� ��������." << endl;
	int p = check<int>(1, 3);
	char pC[5];
	_itoa_s(p, pC, 10);
	send(Socket, pC, 5, 0);
	switch (p)
	{
	case 1:
		cout << "������� ������������." << endl;
		char markOfFactory[20];
		do
		{
			cin >> markOfFactory;
			try
			{
				if (!testLetters(markOfFactory)) { throw Exeption("������ ������� �����������. ��������� ����."); }

			}
			catch (const Exeption e)
			{

				cout << e.errorMessage << endl;

			}

		} while (!testLetters(markOfFactory));
		send(Socket, markOfFactory, 20, 0); break;

	case 2:
		char type1[20] = "������";
		char type2[20] = "����";
		char type3[20] = "������ ��������";
		cout << "������� ��� ��������." << endl;
		cout << "1. ������" << endl;
		cout << "2. ����" << endl;
		cout << "3. ������ ��������" << endl;
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

	cout << "�����." << endl;
	cout << "1.�� �������� �������." << endl;
	cout << "3.��� ����� ��������." << endl;
	int p = check<int>(1, 3);
	char pC[5];
	_itoa_s(p, pC, 10);
	send(Socket, pC, 5, 0);

	switch (p)
	{
	case 1:
		cout << "������� �������� �������." << endl;
		char markOfFactory[20];
		do
		{
			cin >> markOfFactory;
			try
			{
				if (!testLetters(markOfFactory)) { throw Exeption("������ ������� �����������. ��������� ����."); }

			}
			catch (const Exeption e)
			{

				cout << e.errorMessage << endl;

			}

		} while (!testLetters(markOfFactory));
		send(Socket, markOfFactory, 20, 0);

		break;

	case 3:
		char type1[20] = "������";
		char type2[20] = "����";
		char type3[20] = "������ ��������";
		cout << "������� ��� ��������." << endl;
		cout << "1. ������" << endl;
		cout << "2. ����" << endl;
		cout << "3. ������ ��������" << endl;
		int choice = check<int>(1, 3);
		if (choice == 1) send(Socket, type1, 20, 0);
		if (choice == 2) send(Socket, type2, 20, 0);
		if (choice == 3) send(Socket, type3, 20, 0); break;
	}


}
void  Factory::deletee()
{
	cout << "1.������� ������������ ������." << endl;
	cout << "2.������� ���." << endl;
	int p = check<int>(1, 2);
	char pC[5];
	_itoa_s(p, pC, 10);
	send(Socket, pC, 5, 0);
	if (p == 1)
	{
		int  numberOfRecords = view();
		cout << "�������� ������ ��� ��������." << endl;
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
	cout << "1.����������� �� �������� ������������." << endl;
	cout << "2.����������� �� ���� ����� ��������." << endl;
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
		cout << "������� ���." << endl;
	}
	else
	{
		cout << "_______________________________________________________________________" << endl
			<< "|" << "�" << setw(3) << "|" << setw(5) << "�������� ������������" << setw(2) << "|"
			<< "��� �� ����������" << setw(7) << "|" << endl
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