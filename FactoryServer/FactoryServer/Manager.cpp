#include "Manager.h"
#include "Libraries.h"
bool checkString(string checker)
{
	for (int n = 0; n < checker.size(); n++)
		if ((isdigit((unsigned char)checker[n]) || checker[n] == ' '))
		{
			cout << "Данные введены некорректно." << endl;
			return false;
		}
	return true;
}
const bool operator > (const string& s1, const string& s2)
{

	if (strcmp(s1.c_str(), s2.c_str()) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}

}

const bool operator == (const string& s1, const string& s2)
{

	if (strcmp(s1.c_str(), s2.c_str()) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}

}
bool checkStringGender(string checker)
{

	if (checker == "М" || checker == "Ж" || checker == "M")
	{
		return true;
	}
	cout << "Данные введены некорректно." << endl;
	return false;
}
int returnNumberOfRecords(int choice)
{
	int const SIZE = 5;
	int numberOfRecords[SIZE];
	int m;
	string puth = "NumberOfRecords.txt";
	ifstream file;
	file.open(puth);
	if (!file.is_open())
	{
		cout << "Файл не был открыт." << endl;
	}
	else
	{
		for (int i = 0; i < SIZE; i++)
		{
			string num;
			file >> num;
			numberOfRecords[i] = atoi(num.c_str());

		}
		m = numberOfRecords[choice - 1];
	}
	file.close();
	return m;

}
void changeNumberOfRecords(int c, int choice)
{
	int const SIZE = 5;
	int numberOfRecords[SIZE];
	string puth = "NumberOfRecords.txt";
	ifstream file;
	file.open(puth);
	if (!file.is_open())
	{
		cout << "Файл не был открыт." << endl;
	}
	else
	{
		for (int i = 0; i < SIZE; i++)
		{
			string num;
			file >> num;
			numberOfRecords[i] = atoi(num.c_str());

		}

	}
	if (c == 1)
	{
		numberOfRecords[choice - 1]++;
	}
	if (c == 2)
	{
		numberOfRecords[choice - 1]--;
	}
	if (c == 3)
	{
		numberOfRecords[choice - 1] = 0;
	}

	file.close();

	ofstream file1;
	file1.open(puth);
	if (!file1.is_open())
	{
		cout << "Файл не был открыт." << endl;
	}
	else
	{
		for (int i = 0; i < SIZE; i++)
		{
			file1 << numberOfRecords[i] << endl;
		}

	}
	file1.close();
}
void toChar(string s, char q[])
{
	for (int n = 0; n < s.size(); n++)
	{
		q[n] = s[n];
	}
}

