// Autopark_Server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include"Libraries.h"
#include"Admin.h"
#include"User.h"
#include"Expert.h"

int numcl = 0;
DWORD WINAPI ThreadFunc(LPVOID client_socket);
SOCKET SocketServer = socket(AF_INET, SOCK_STREAM, 0);
sockaddr_in local_addr;
SOCKET client_socket;
sockaddr_in client_addr;
SOCKET Socket2;
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0) { return 1; }

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(1280);
	local_addr.sin_addr.s_addr = 0;
	bind(s, (sockaddr*)&local_addr, sizeof(local_addr));
	int c = listen(s, 5);

	cout << "СЕРВЕР ГОТОВ К РАБОТЕ." << endl;
	cout << endl;
	// извлекаем сообщение из очереди
	SOCKET client_socket;
	// сокет для клиента
	sockaddr_in client_addr; // адрес клиента (заполняется системой)
	int client_addr_size = sizeof(client_addr);
	// цикл извлечения запросов на подключение из очереди
	while ((client_socket = accept(s, (sockaddr*)&client_addr, &client_addr_size))) {
		numcl++;
		if (numcl)
			cout << numcl << " клиент подключен." << endl;
		else
			cout << "Нет подключенных клиентов." << endl;
		// вызов нового потока для обслуживания клиента
		DWORD thID;// thID идентификатор типа DWORD
		CreateThread(NULL, NULL, ThreadFunc, &client_socket, NULL, &thID);
	}
	return 0;
}
DWORD WINAPI ThreadFunc(LPVOID client_socket) {

	Admin admin;
	User user;
	Expert expert;
	Socket2 = ((SOCKET*)client_socket)[0];
	int t = 0;
	char msgChoice[5];

	do
	{
		recv(Socket2, msgChoice, sizeof(msgChoice), 0);
		int choice = atoi(msgChoice);

		switch (choice)
		{
		case 1: admin.authorization(); break;
		case 2: user.showMenu(); break;
		case 3: expert.authorization(); break;
		case 4:	closesocket(Socket2); break;
		}

	} while (t == 0);
	WSACleanup();
	return 0;
}

