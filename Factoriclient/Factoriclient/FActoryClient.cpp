#include"Libraries.h"
#include"Manager.h"
#include"System.h"
#include"Admin.h"
#include"User.h"
#include "Expert.h"
SOCKET Socket;
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WORD wstock_matersionRequested;
	WSADATA wsaData;
	int err;
	wstock_matersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wstock_matersionRequested, &wsaData);
	if (err != 0) { return 1; }
	/*SOCKET */Socket = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in dest_addr;
	// указание адреса и порта сервера
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(1280);
	dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	connect(Socket, (sockaddr*)&dest_addr, sizeof(dest_addr));

	while (1)
	{
		int choice;
		cout << "1.Вход администратора." << endl;
		cout << "2.Вход клиента." << endl;
		cout << "3.Вход эксперта." << endl;
		cout << "4.Выход из программы." << endl;
		choice = check<int>(1, 4);
		System* systemW;
		Admin admin;
		User user;
		Expert expert;
		char msgChoice[5];
		_itoa_s(choice, msgChoice, 10);
		send(Socket, msgChoice, 5, 0);

		switch (choice)
		{
		case 1: system("cls"); systemW = &admin; systemW->authorization();  break;
		case 2: system("cls"); systemW = &user;  systemW->showMenu(); break;
		case 3: system("cls"); systemW = &expert; systemW->authorization();  break;
		case 4:system("cls"); closesocket(Socket); exit(0); break;
		default:system("cls"); cout << "Данные введены некорректно." << endl;
		}
	}
	WSACleanup();
	return 0;
}

