#include "Factory.h"
#include"Manager.h"
extern SOCKET Socket2;
void Factory::add()
{
	recv(Socket2, FactoryName, 20, 0);
	recv(Socket2, type, 20, 0);

	changeNumberOfRecords(1, 1);
	string puth = "Factory.txt";
	ofstream file;
	file.open(puth, ofstream::app);
	if (file.is_open())
	{
		file << FactoryName << endl;
		file << type << endl;
		file.close();
		char message[30] = "Информация успешно добавлена.";
		send(Socket2, message, 30, 0);
	}
	else
	{
		char message[20] = "Файл не был открыт.";
		send(Socket2, message, 20, 0);
	}

}
void Factory::view()
{
	vector<Factory> cars;
	fileRead(&cars);

	int numberOfRecords = returnNumberOfRecords(1);
	char  numberOfRecordsC[5];
	_itoa_s(numberOfRecords, numberOfRecordsC, 5, 10);
	send(Socket2, numberOfRecordsC, 5, 0);

	for (int i = 0; i < numberOfRecords; i++)
	{
		send(Socket2, cars[i].FactoryName, 20, 0);
		send(Socket2, cars[i].type, 20, 0);
	}
}
void  Factory::MenuRun()
{
	int a = 0;
	do
	{
		char msgChoice[5];
		recv(Socket2, msgChoice, sizeof(msgChoice), 0);
		int choice = atoi(msgChoice);

		switch (choice)
		{
		case 1: add();  break;
		case 2: view(); break;
		case 3: edit();  break;
		case 4: deletee(); break;
		case 5: search();  break;
		case 6: sort();  break;
		case 7: a = 4;  break;
		}

	} while (a != 4);
}
void Factory::fileRead(vector<Factory>* factories)
{
	string puth = "Factory.txt";
	ifstream file;
	file.open(puth);
	if (!file.is_open())
	{
		cout << "Файл не был открыт." << endl;
	}
	else
	{
		int numberOfDoctors = returnNumberOfRecords(1);
		Factory car;
		for (int i = 0; i < numberOfDoctors; i++)
		{
			file >> car;
			cout << car.type << endl;
			factories->push_back(car);
		}

	}
	file.close();
}
void Factory::sendF()
{
	send(Socket2, FactoryName, 20, 0);
	send(Socket2, type, 20, 0);
}
Factory Factory::returnFactory(int num)
{
	vector<Factory> cars;
	fileRead(&cars);
	return cars[num - 1];
}
ofstream& operator <<(ofstream& file, const Factory& ob)
{
	file << ob.FactoryName << endl;
	file << ob.type << endl;
	return file;
}
ifstream& operator >>(ifstream& file, Factory& ob)
{
	file >> ob.FactoryName;
	file >> ob.type;
	return file;
}
void  Factory::edit()
{
	view();
	vector<Factory> cars;
	fileRead(&cars);

	char numRecC[5]; int numRec;
	recv(Socket2, numRecC, 5, 0);
	numRec = atoi(numRecC);

	char pC[5]; int p;
	recv(Socket2, pC, 5, 0);
	p = atoi(pC);
	switch (p)
	{
	case 1: recv(Socket2, cars[numRec].FactoryName, 20, 0); fileRewrite(cars); break;
	case 3: recv(Socket2, cars[numRec].type, 20, 0); fileRewrite(cars); break;
	}
	char message[30] = "Информация успешно изменена.";
	send(Socket2, message, 30, 0);
	view();
}
void  Factory::search()
{

}
void  Factory::deletee()
{
	char pC[5]; int p;
	recv(Socket2, pC, 5, 0);
	p = atoi(pC);
	vector<Factory> cars;
	fileRead(&cars);

	if (p == 1)
	{
		int numberOfRecords = returnNumberOfRecords(1);
		view();
		char numRecC[5]; int numRec;
		recv(Socket2, numRecC, 5, 0);
		numRec = atoi(numRecC);
		string puth = "Factory.txt";
		ofstream file;
		file.open(puth);
		if (file.is_open())
		{
			for (int i = 0; i < numRec; i++)
			{
				file << cars[i];
			}
			for (int i = numRec; i < numberOfRecords; i++)
			{
				file << cars[i];
			}
			file.close();
			changeNumberOfRecords(2, 1);
		}

	}
	else {
		string puth = "Factory.txt";
		ofstream file;
		file.open(puth);
		file.close();
		changeNumberOfRecords(3, 1);
	}
	char message[30] = "Информация успешно удалена.";
	send(Socket2, message, 30, 0);
}
void  Factory::sort()
{
	char pC[5]; int p;
	recv(Socket2, pC, 5, 0);
	p = atoi(pC);
	vector<Factory> cars;
	fileRead(&cars);
	int numberOfRecords = returnNumberOfRecords(1);
	char  numberOfRecordsC[5];
	_itoa_s(numberOfRecords, numberOfRecordsC, 5, 10);
	send(Socket2, numberOfRecordsC, 5, 0);
	if (p == 1)
	{
		for (int j = 0; j < numberOfRecords; j++)
		{
			for (int i = 0; i < numberOfRecords - 1; i++)
			{
				if (strcmp(cars[i].FactoryName, cars[i + 1].FactoryName) > 0) swap(cars[i], cars[i + 1]);

			}
		}

		for (int i = 0; i < numberOfRecords; i++)
		{
			send(Socket2, cars[i].FactoryName, 20, 0);
			send(Socket2, cars[i].type, 20, 0);
		}
	}
	else
	{
		for (int j = 0; j < numberOfRecords; j++)
		{
			for (int i = 0; i < numberOfRecords - 1; i++)
			{
				if (strcmp(cars[i].type, cars[i + 1].type) > 0) swap(cars[i], cars[i + 1]);

			}
		}
		for (int i = 0; i < numberOfRecords; i++)
		{
			send(Socket2, cars[i].FactoryName, 20, 0);
			send(Socket2, cars[i].type, 20, 0);
		}
	}


}
void Factory::fileRewrite(vector<Factory> factories)
{
	string puth = "Factory.txt";
	ofstream file;
	file.open(puth);
	if (file.is_open())
	{
		for (int i = 0; i < returnNumberOfRecords(1); i++)
		{
			file << factories[i];
		}
		file.close();
	}
}