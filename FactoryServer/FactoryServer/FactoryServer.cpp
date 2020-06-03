// Autopark_Server.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
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

	cout << "������ ����� � ������." << endl;
	cout << endl;
	// ��������� ��������� �� �������
	SOCKET client_socket;
	// ����� ��� �������
	sockaddr_in client_addr; // ����� ������� (����������� ��������)
	int client_addr_size = sizeof(client_addr);
	// ���� ���������� �������� �� ����������� �� �������
	while ((client_socket = accept(s, (sockaddr*)&client_addr, &client_addr_size))) {
		numcl++;
		if (numcl)
			cout << numcl << " ������ ���������." << endl;
		else
			cout << "��� ������������ ��������." << endl;
		// ����� ������ ������ ��� ������������ �������
		DWORD thID;// thID ������������� ���� DWORD
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

