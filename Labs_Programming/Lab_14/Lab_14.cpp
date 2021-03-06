#include "pch.h"
#include <math.h>
#include <stdio.h>
#include <gl\glut.h>

#define NUMB_POS_X 78
#define NUMB_POS_Y 25

void CheckIntervals(double[]);
void Round(double, double *);
double FuncValue(double);
void PrintFuncValues(double, double, double[]);

int main()
{
	glutInit(NULL, NULL);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(100, 100);

	// Границы отрезка.
	double xArgs[] = { (-M_PI / 2), 5. };

	// Max и min значения функции на отрезке.
	double yValues[] = { (-M_PI / 2), 5. };

	double scaleX = (xArgs[1] - xArgs[0]) / NUMB_POS_X;
	double scaleY = (yValues[1] - yValues[0]) / NUMB_POS_Y;

	CheckIntervals(xArgs);
	CheckIntervals(yValues);

	PrintFuncValues(scaleX, scaleY, xArgs);
}

void PrintFuncValues(double scaleX, double scaleY, double xArgs[])
{
	double yCur = scaleY * NUMB_POS_Y;
	double xCur = 0;
	double yValue = 0.0;
	double tempX = 0;
	double tempY = yCur;

	int isPrint = 0;

	for (int i = 0; i <= NUMB_POS_Y; i++)
	{
		xCur = xArgs[0];
		tempX = xCur;
		for (int j = 0; j <= NUMB_POS_X; j++)
		{
			yValue = FuncValue(xCur);
			Round(modf(tempX, &xCur), &xCur);
			Round(modf(tempY, &yCur), &yCur);
			Round(modf(yValue, &yValue), &yValue);
			if (yValue == yCur)
			{
				if (xCur >= xArgs[0] && xCur <= xArgs[1])
				{
					printf("#");
					isPrint = 1;
				}
			}
			else
			{
				isPrint = 0;
			}

			if (isPrint == 0 && xCur == 0)
				printf("|");
			else if (yCur != 0)
				printf(" ");

			if (isPrint == 0 && yCur == 0)
				printf("_");

			tempX += scaleX;
		}

		isPrint = 0;
		printf("\n");
		tempY -= scaleY;
	}
}

void CheckIntervals(double interval[])
{
	if (interval[0] > 0 && interval[1] > 0)
		interval[0] = 0;
	else if (interval[0] < 0 && interval[1] < 0)
		interval[1] = 0;
}

void Round(double fract, double *value)
{
	if (fract >= 0)
	{
		if (fabs(fract) >= 0.5)
			*value = ceil(*value + fract);
		else
			*value = floor(*value + fract);
	}
	else
	{
		if (fabs(fract) >= 0.5)
			*value = floor(*value + fract);
		else
			*value = ceil(*value + fract);
	}
}

double FuncValue(double arg)
{
	//return 2 * sin(arg) + 3 * cos(2 * arg);
	return arg;
}