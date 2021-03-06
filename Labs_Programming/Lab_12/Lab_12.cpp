/********************************************************************
* Project Name	 :Lab_12											*
* Project Type	 :Win32 Console Application							*
* File Name		 :Lab_12.cpp										*
* Language		 :C, MAVS 2010 and above		                	*
* Programmer(2)	 :Крещук Николай, Плотников Кирилл, 8 бригада		*
* Created		 :01/11/18						                    *
* Last revision	 :10/11/18						                    *
* Comment		 :Работа с математическими функциями            	*
********************************************************************/
#include "pch.h"
#include <math.h>
#include <stdio.h>
#define EPS 0.000001

int GetNumbInNumerous(double);
double GetFuncValue(double, int);
double Factorial(double);

int main()
{
	const double MIN_VALUE = 0.;
	const double MAX_VALUE = 4.;
	const int ROWS = 5;

	const double STEP = 0.1;

	int elemInNumerous = 0;
	int calcElmsInNumerous = 0;
	int printedElms = 0;

	double numbElems = (MAX_VALUE - MIN_VALUE) / STEP + 1;
	double elemsInRow = numbElems / ROWS;
	double argX = 0;

	elemsInRow = ceil(elemsInRow);
	for (int i = 0; i < numbElems; i++)
	{
		argX = MIN_VALUE + STEP * i;

		calcElmsInNumerous = GetNumbInNumerous(argX);
		if (calcElmsInNumerous > elemInNumerous)
			elemInNumerous = calcElmsInNumerous;
	}

	for (int i = 0; i < ROWS; i++)
	{
		printf("\n");
		for (int j = 0; j < elemsInRow; j++)
		{
			if (printedElms == numbElems)
				break;

			printedElms++;
			printf("%10.5f", GetFuncValue(printedElms * STEP, elemInNumerous));
		}
	}

	printf("\n");
	system("pause");
	return 0;
}

int GetNumbInNumerous(double arg)
{
	double standFunc = exp(arg);
	double calcFunc = 1;

	int numbElements = 1;
	while (fabs(calcFunc - standFunc) > EPS)
	{
		calcFunc += pow(arg, numbElements) / Factorial(numbElements);
		numbElements++;
	}

	return numbElements;
}

double GetFuncValue(double arg, int countElems)
{
	double calcFunc = 1;
	for (int i = 1; i < countElems; i++)
		calcFunc += pow(arg, i) / Factorial(i);

	return calcFunc;
}

double Factorial(double argFact)
{
	double factorial = 1;
	for (int i = argFact; i > 0; i--)
		factorial *= i;

	return factorial;
}