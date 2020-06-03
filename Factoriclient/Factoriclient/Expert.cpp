#include "Expert.h"
#include"Manager.h"
extern SOCKET Socket;
int Expert::authorization()
{
	char login[20];
	char password[17];
	cout << "������� �����" << endl;
	cin >> login;
	send(Socket, login, 20, 0);
	cout << "������� ������" << endl;
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
	/*cin >> password;*/
	send(Socket, password, 17, 0);
	char result[2];
	recv(Socket, result, 2, 0);
	if (atoi(result) == 1)
	{
		system("cls");
		cout << "���� �������� �������." << endl;
		system("pause");
		system("cls");
		showMenu();
		return 1;
	}
	else
	{
		system("cls");
		cout << "����� ��� ������ ������� �������." << endl;
		system("pause");
		system("cls");
		return 0;
	}
}
void Expert::showMenu()
{
	int a = 0;
	do
	{
		cout << "����:" << endl;
		cout << "1.������������ ������� ������� ������ ���������" << endl;
		cout << "2.���������� ������������." << endl;
		cout << "3.��������� �����." << endl;
		int choice = check<int>(1, 3);
		char msgChoice[5];
		_itoa_s(choice, msgChoice, 10);
		send(Socket, msgChoice, 5, 0);

		switch (choice)
		{
		case 1: system("cls"); startMetod();  break;
		case 2: system("cls"); showApprovedDelivery(); break;
		case 3: a = 4; system("cls"); break;
		default:system("cls"); cout << "������ ������� �����������." << endl;
		}

	} while (a != 4);
}
int Expert::startMetod()
{
r:;
	int numberOfRecords; char numberOfRecordsC[5];
	recv(Socket, numberOfRecordsC, 5, 0);
	numberOfRecords = atoi(numberOfRecordsC);
	if (numberOfRecords != 0)
	{
		char numberOfRoateC[5]; int  numberOfRoate; /*���������� ������� ��������*/
		recv(Socket, numberOfRoateC, 5, 0);  numberOfRoate = atoi(numberOfRoateC);
		if (numberOfRoate == 0)
		{
			cout << "����������� ��������." << endl;
		}
		else
		{

			/*�� ����� ��������� ��� ��������, ��� ������� ������� ������ ��������� ���������.*/
			for (int i = 0; i < numberOfRoate; i++)
			{
				char surname[20];   recv(Socket, surname, 20, 0);
				char name[20];      recv(Socket, name, 20, 0);
				char goal[30];  	recv(Socket, goal, 30, 0);
				char wghtC[30];       recv(Socket, wghtC, 30, 0);
				cout << i + 1 << "| " << surname << setw(15 - strlen(surname)) << "|" << name
					<< setw(15 - strlen(name)) << "|" << goal << setw(34 - strlen(goal)) << "|" << wghtC << endl;
			}
			cout << "�������� �������� ��� ������ �������." << endl;
			int nR = check<int>(1, numberOfRoate);
			char nRC[5]; _itoa_s(nR, nRC, 10); send(Socket, nRC, 5, 0);
			char FactoryName[20]; char type[20];
			/*����� ������������ �������, ������� ������������� �������� ������� ��������.*/
			{
				system("cls");
				cout << "��� ������ �������� ���� ������� �������." << endl;
				cout << "_____________________________________________" << endl
					<< "|" << "�" << setw(3) << "|" << setw(5) << "�������� ������" << setw(2) << "|"
					<< "��� ��������" << setw(7) << "|" << endl
					<< "|___|_________________|_______________________|" << endl;
				for (int i = 0; i < 3; i++)
				{
					recv(Socket, FactoryName, 20, 0);
					recv(Socket, type, 20, 0);

					cout << "|" << i + 1 << setw(3) << "|" << FactoryName << setw(18 - strlen(FactoryName)) <<"|" << type
						<< setw(24 - strlen(type)) << "|" << endl
						<< "|___|_________________|_______________________|" << endl;
				}
			}

			cout << "1. ���������� �������� � ���� ���������." << endl;
			cout << "2. �������� ��������." << endl;
			int choice = check<int>(1, 2);
			char msgChoice[5]; _itoa_s(choice, msgChoice, 10); send(Socket, msgChoice, 5, 0);
			if (choice == 2) goto r;
			else
			{
				double marks[18]; double a, b;
				char markC[20];   int k = 0;
				/*���� ��������� ������.*/
				for (int i = 0; i < 3; i++)
				{

					cout << "������� ������ ���������." << endl;
					cout << "C���� ������ ����� ���� ������ 1. " << endl << endl;
					cout << "������� �" << i + 1 << ":" << endl;
					cout << " ������������ 1 � 2 �������." << endl;
					do
					{
						cout << " ������ 1-��: "; a = check<double>(0.0, 1.0);
						cout << " ������ 2-��: "; b = check<double>(0.0, 1.0);;

					} while (!compareMarks(a, b));
					marks[k] = a; k++; marks[k] = b; k++;
					sprintf(markC, "%f", a); send(Socket, markC, 20, 0);
					sprintf(markC, "%f", b); send(Socket, markC, 20, 0);
					cout << endl << " ������������ 1 � 3 �������." << endl;
					do
					{
						cout << " ������ 1-��: ";  a = check<double>(0.0, 1.0);;
						cout << " ������ 3-��: ";  b = check<double>(0.0, 1.0);;

					} while (!compareMarks(a, b));
					marks[k] = a; k++; marks[k] = b; k++;
					sprintf(markC, "%f", a); send(Socket, markC, 20, 0);
					sprintf(markC, "%f", b); send(Socket, markC, 20, 0);
					cout << endl << " ������������ 2 � 3 �������." << endl;
					do
					{
						cout << " ������ 2-��: "; a = check<double>(0.0, 1.0);;
						cout << " ������ 3-��: "; b = check<double>(0.0, 1.0);;

					} while (!compareMarks(a, b));
					marks[k] = a; k++; marks[k] = b; k++;
					sprintf(markC, "%f", a); send(Socket, markC, 20, 0);
					sprintf(markC, "%f", b); send(Socket, markC, 20, 0);
				}
				/*����� �������� ������� � �����.*/
				{
					char summ[20];  double sum[6];
					system("cls");
					for (int i = 0; i < 6; i++)
					{
						recv(Socket, summ, 20, 0);
						sum[i] = stod(summ);
					}
					cout << "____________________________" << endl
						<< "|   |p1<->p2|p1<->p3|p2<->p3|" << endl
						<< "|___|_______|_______|_______|" << endl;
					int m = 0;
					for (int i = 0; i < 3; i++)
					{
						if (marks[0 + m] == 1 || marks[1 + m] == 1 || marks[2 + m] == 1 || marks[3 + m] == 1 || marks[4 + m] == 1 || marks[5 + m] == 1 ||
							marks[0 + m] == 0 || marks[1 + m] == 0 || marks[2 + m] == 0 || marks[3 + m] == 0 || marks[4 + m] == 0 || marks[5 + m] == 0)
						{
							cout << "| �" << i + 1 << "|" << setprecision(1) << marks[0 + m] << "  |" << setprecision(1) << marks[1 + m] << "  |" << setprecision(1) << marks[2 + m]
								<< "  |" << setprecision(1) << marks[3 + m] << "  |" << setprecision(1) << marks[4 + m] << "  |" << setprecision(1) << marks[5 + m] << "  |" << endl
								<< "|___|___|___|___|___|___|___|" << endl;
						}
						else
						{
							cout << "| �" << i + 1 << "|" << setprecision(1) << marks[0 + m] << "|" << setprecision(1) << marks[1 + m] << "|" << setprecision(1) << marks[2 + m]
								<< "|" << setprecision(1) << marks[3 + m] << "|" << setprecision(1) << marks[4 + m] << "|" << setprecision(1) << marks[5 + m] << "|" << endl
								<< "|___|___|___|___|___|___|___|" << endl;

						}
						m += 6;
					}
					cout << "|Sum|";
					for (int i = 0; i < 6; i++)
					{
						if (sum[i] == 1 || sum[i] == 2 || sum[i] == 3 || sum[i] == 0)
						{
							cout << sum[i] << "  |";
						}
						else
						{
							cout << setprecision(2) << sum[i] << "|";
						}

					}
					cout << endl << "|___|___|___|___|___|___|___|" << endl << endl;

					char fpC[20]; double fp1, fp2, fp3;
					recv(Socket, fpC, 20, 0); fp1 = stod(fpC);
					recv(Socket, fpC, 20, 0); fp2 = stod(fpC);
					recv(Socket, fpC, 20, 0); fp3 = stod(fpC);

					char wC[20]; double w1, w2, w3;
					recv(Socket, wC, 20, 0); w1 = stod(wC);
					recv(Socket, wC, 20, 0); w2 = stod(wC);
					recv(Socket, wC, 20, 0); w3 = stod(wC);

					cout << "������-������������ fp." << endl;
					cout << "fp1-" << fp1 << "  fp2-" << fp2 << "  fp3-" << fp3 << endl;
					cout << endl << "��� �������� w." << endl;
					cout << "w1-" << w1 << "  w2-" << w2 << "  w3-" << w3 << endl;

				}
				/*����� ����������� � ����������� ����������.*/

				char resC[5]; recv(Socket, resC, 5, 0); int res = atoi(resC);

				if (res == 1)      cout << "������ ������� ����������������." << endl;
				else if (res == 2) cout << "������ ������� ����������������." << endl;
				else if (res == 3) cout << "������ ������� ����������������." << endl;
				else if (res == 4) cout << "������ � ������ ������� ����������������." << endl;
				else if (res == 5) cout << "������ � ������ ������� ����������������." << endl;
				else if (res == 6) cout << "������ � ������ ������� ����������������." << endl;
				else if (res == 0) cout << "��� ������� ������." << endl;
				cout << "_____________________________________________" << endl
					<< "|" << "�" << setw(3) << "|" << setw(5) << "�������� �������" << setw(2) <<  "|"
					<< "��� ��������" << setw(7) << "|" << endl
					<< "|___|_________________|_______________________|" << endl;

				for (int i = 0; i < 3; i++)
				{
					recv(Socket, FactoryName, 20, 0);
					recv(Socket, type, 20, 0);
					if (res == 1 || res == 2 || res == 3)
					{
						if (i == res - 1)
						{
							cout << "|" << i + 1 << setw(3) << "|" << FactoryName << setw(18 - strlen(FactoryName)) << "|" << type
								<< setw(24 - strlen(type)) << "|" << endl
								<< "|___|_________________|_______________________|" << endl;
						}

					}
					else if (res == 4)
					{
						if (i == 0 || i == 1)
						{
							cout << "|" << i + 1 << setw(3) << "|" << FactoryName << setw(18 - strlen(FactoryName)) << "|" << type
								<< setw(24 - strlen(type)) << "|" << endl
								<< "|___|_________________|_______________________|" << endl;
						}

					}
					else if (res == 5)
					{
						if (i == 0 || i == 2)
						{
							cout << "|" << i + 1 << setw(3) << "|" << FactoryName << setw(18 - strlen(FactoryName)) << "|" << type
								<< setw(24 - strlen(type)) << "|" << endl
								<< "|___|_________________|_______________________|" << endl;
						}

					}
					else if (res == 6)
					{
						if (i == 1 || i == 2)
						{
							cout << "|" << i + 1 << setw(3) << "|" << FactoryName << setw(18 - strlen(FactoryName)) << "|" << type
								<< setw(24 - strlen(type)) << "|" << endl
								<< "|___|_________________|_______________________|" << endl;
						}

					}
					else if (res == 0)
					{

						cout << "|" << i + 1 << setw(3) << "|" << FactoryName << setw(18 - strlen(FactoryName)) <<"|" << type
							<< setw(24 - strlen(type)) << "|" << endl
							<< "|___|_________________|_______________________|" << endl;

					}
				}
				int finalRes;
				if (res > 3 || res == 0)
				{
					cout << "�������� ����� �������." << endl;
					finalRes = check<int>(1, 3) - 1;

				}
				else
				{
					finalRes = res - 1;
				}
				char finalC[5];
				_itoa_s(finalRes, finalC, 10);
				send(Socket, finalC, 5, 0);


				char msgChoice[28];
				recv(Socket, msgChoice, 28, 0);
				cout << msgChoice << endl;
				changeNumberOfRecords(2, 3);
			}
		}

	}
	return 0;
}
void  Expert::showApprovedDelivery()
{
	char numberC[5];
	recv(Socket, numberC, 5, 0);
	int number = atoi(numberC);
	char wghtC[5];
	char goal[5];
	if (number == 0)
	{
		cout << "� ��� ����������� ���������� ��������." << endl;
	}
	else
	{
		string goal1 = "�������� ����.";
		string goal2 = "�������� �����.";
		string goal3 = "�������� ������ ���������.";
		string goal4 = "������� �������.";
		string Ggoal;

		string km1 = "������ ����.";
		string km2 = "������� ����.";
		string km3 = "������� ����.";
		string km;
		for (int i = 0; i < number; i++)
		{
			recv(Socket, goal, 5, 0);
			recv(Socket, wghtC, 5, 0);
			int a = atoi(goal);
			int b = atoi(wghtC);
			if (a == 1) Ggoal = goal1;
			if (a == 2) Ggoal = goal2;
			if (a == 3) Ggoal = goal3;
			if (a == 4) Ggoal = goal4;

			if (b == 1) km = km1;
			if (b == 2) km = km2;
			if (b == 3) km = km3;
			char surname[20];
			char name[20];
			recv(Socket, surname, 20, 0);
			recv(Socket, name, 20, 0);
			char markOfFactory[20];
			char type[20];
			recv(Socket, markOfFactory, 20, 0);
			recv(Socket, type, 20, 0);
			cout << i + 1 << "| " << surname << setw(13 - strlen(surname)) << "|" << name
				<< setw(13 - strlen(name)) << "|" << Ggoal << setw(32 - Ggoal.size()) << "|" << km << setw(35 - km.size()) << "|"
				<< markOfFactory << setw(15 - strlen(markOfFactory))  << endl;
		}

	}

}