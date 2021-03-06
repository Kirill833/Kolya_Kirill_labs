﻿/**********************************************************************
* Project Name	 :Lab_1												  *
* Project Type	 :Win32 Console Application							  *
* File Name		 :Lab_1.cpp											  *
* Language		 :C++, MAVS 2010 and above		                      *
* Programmer(2)	 :Крещук Николай, Плотников Кирилл, вариант №7		  *
* Created		 :17/04/18						                      *
* Last revision	 :20/09/18						                      *
* Comment		 :Работа с алгоритмами		                          *
**********************************************************************/

#include "pch.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

// Количество элементов.
const int N = 20;

struct table
{
	char key;
	int value;
};

void PrintTable(table table[N])
{
	for (int i = 0; i < N; i++)
		cout << "Key: " << table[i].key << " Value: " << table[i].value << endl;
}

void SortTable(table tableSorted[N])
{
	table temp;

	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			if (tableSorted[i].key > tableSorted[j].key)
			{
				temp = tableSorted[i];
				tableSorted[i] = tableSorted[j];
				tableSorted[j] = temp;
			}
		}
	}
}

void AlgorithmS(table tableAlgS[N], char searchKey)
{
	bool find = false;

	// Счётчик цикла.
	int i = 0;
	int numbersOfPasses = 0;

	// Алгоритм S.
	while (i < N)
	{
		if (searchKey == tableAlgS[i].key)
		{
			find = true;
			break;
		}
		numbersOfPasses++;
		i++;
	}

	cout << "Algorithm S: ";

	if (find)
		cout << "Search successful." << endl;
	else
		cout << "Search unsuccessful." << endl;

	cout << "Numbers of passes: " << numbersOfPasses << endl;
}

void AlgorithmQ(table tableAlgS[N + 1], char searchKey)
{
	tableAlgS[N].key = searchKey;

	int i = 0;
	int numbersOfPasses = 0;

	// Алгоритм Q.
	while (tableAlgS[i].key != tableAlgS[N].key)
	{
		numbersOfPasses++;
		i++;
	}
	
	cout << "Algorithm Q: ";
	if (i < N)
		cout << "Search successful." << endl;
	else
		cout << "Search unsuccessful." << endl;

	cout << "Numbers of passes: " << numbersOfPasses << endl;
}

void AlgorithmT(table tableAlgT[N + 1], char searchKey)
{
	tableAlgT[N].key = (char)126;

	int i = 0;
	int numbersOfPasses = 0;

	while (i <= N)
	{
		if (searchKey <= tableAlgT[i].key)
		{
			cout << "Algorithm T: ";

			if (searchKey == tableAlgT[i].key)
				cout << "Search successful." << endl;
			else
				cout << "Search unsuccessful." << endl;
			break;
		}

		numbersOfPasses++;
		i++;
	}

	cout << "Numbers of passes: " << numbersOfPasses << endl;

}

void AlgorithmB(table tableAlgB[N], char searchKey)
{
	int iStart = 0;
	int iEnd = N;
	int iMiddle;
	int numbersOfPasses = 0;

	cout << "Algorithm B: ";

	while (iStart < iEnd)
	{
		iMiddle = (iStart + iEnd) / 2;
		if (searchKey < tableAlgB[iMiddle].key)
		{
			cout << "paraziti";
			iEnd = iMiddle;
		}
		else
		{
			if (searchKey == tableAlgB[iMiddle].key)
			{
				cout << "Search successful." << endl;
				cout << "Numbers of passes: " << numbersOfPasses << endl;
				cout << "paraziti";
				// Как только нашли совпадение, выходим из функции.
				return;
			}
			else
			{
				iStart = iMiddle + 1;
			}
		}
		numbersOfPasses++;
	}
	cout << "Search unsuccessful." << endl;
	cout << "Numbers of passes: " << numbersOfPasses << endl;
}

void ReadFile(table tableKeys[N])
{
	ifstream file;
	file.open("Test.txt");

	for (int i = 0; i < N; i++)
		file >> tableKeys[i].key;
}

int main()
{
	// Искомый ключ.
	char searchKey;
	srand(time(NULL));

	table tableWithKeys[N + 1];

	// Заполняем столбец значений случайными данными.
	for (int i = 0; i < N; i++)
		tableWithKeys[i].value = rand();

	ReadFile(tableWithKeys);
	PrintTable(tableWithKeys);

	cout << "Enter a key: ";
	cin >> searchKey;

	AlgorithmS(tableWithKeys, searchKey);
	AlgorithmQ(tableWithKeys, searchKey);

	SortTable(tableWithKeys);

	AlgorithmT(tableWithKeys, searchKey);
	AlgorithmB(tableWithKeys, searchKey);

	system("pause");
	return 0;
}