// TODO: лекции могут дать информацию?

#include "pch.h"
#include <iostream>
#include <ctime>

// Количество элементов в списке.
const int N = 19;

// Максимальное значение элемента.
const int MAX_VALUE = 50;

struct Queue
{
	double data[N];
};

Queue *head;
Queue *tail;

void Enqueue();

int main()
{

}

void Enqueue()
{
	srand(time(NULL));

	Queue *newElement;
	
	if (!head)
	{
		newElement->data[0] = rand() % MAX_VALUE;
		head = newElement;
		return;
	}



}