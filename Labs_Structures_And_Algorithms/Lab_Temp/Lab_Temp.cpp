﻿/**********************************************************************
* Project Name	 :Lab_3												  *
* Project Type	 :Win32 Console Application							  *
* File Name		 :Lab_3.cpp											  *
* Language		 :C++, MAVS 2010 and above		                      *
* Programmer(2)	 :Крещук Николай, Плотников Кирилл, вариант №7		  *
* Created		 :28/10/18											  *
* Last revision	 :28/10/18						                      *
* Comment		 :Работа с очередью			                          *
**********************************************************************/

#include "pch.h"
#include <iostream>

using namespace std;

// Размер очереди.
const int N = 20;

int number = 0;

struct QueueCycleArray
{
	int data;
	QueueCycleArray *prev;
};

QueueCycleArray *Tail;

void Creation(QueueCycleArray *Q)
{
	QueueCycleArray *newEl = new QueueCycleArray();

	const int NUMBER_OF_ELEMENTS = 20;

	for (int i = 0; i < NUMBER_OF_ELEMENTS; i++)
	{
		newEl->data = NUMBER_OF_ELEMENTS * 10;
		newEl->prev = new QueueCycleArray();
		newEl = newEl->prev;
	}
	Tail->prev = newEl;

}

void PrintQueue(QueueCycleArray *Q)
{
	int i = 1;
	int j = Q->first;

	if (Q->first == Q->last)
	{
		cout << "Список пуст." << endl;
		return;
	}

	while (j % N != Q->last)
	{
		cout << "Элемент: " << Q->data[j] << " Индекс: " << i++ << endl;
		j = (j + 1) % N;
	}
}

void AddElement(QueueCycleArray *Q)
{
	if ((Q->last + 1) % N == Q->first)
	{
		cout << "Список заполен." << endl;
		return;
	}

	Q->data[Q->last] = number++;
	Q->last = (Q->last + 1) % N;
}

void DeleteElement(QueueCycleArray *Q)
{
	if (Q->first == Q->last)
	{
		cout << "Список пуст." << endl;
		return;
	}

	Q->first = (Q->first + 1) % N;
}

void ClearQueue(QueueCycleArray *Q)
{
	Q->first = 0;
	Q->last = 0;
}

void main()
{
	setlocale(LC_ALL, "Rus");
	QueueCycleArray Q;
	char number;

	cout << "1. Создать список." << endl;
	cout << "2. Вывод списка." << endl;
	cout << "3. Добавление элемента в список." << endl;
	cout << "4. Удалить элемент." << endl;
	cout << "5. Удалить список." << endl;
	cout << "0. Выйти." << endl;
	cout << "Номер команды: ";

	do
	{
		cin >> number;
		switch (number)
		{
		case '1':
			Creation(&Q);
			break;

		case '2':
			PrintQueue(&Q);
			break;

		case '3':
			AddElement(&Q);
			break;

		case '4':
			DeleteElement(&Q);
			break;

		case '5':
			ClearQueue(&Q);
			break;

		case '0':
			break;
		default:
			cout << "Команда не определена." << endl;
			break;
		}
	} while (number != '0');
	system("pause");
}