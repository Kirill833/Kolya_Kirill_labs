/**********************************************************************
* Project Name	 :Lab_13											  *
* Project Type	 :Win32 Console Application							  *
* File Name		 :Lab_13.cpp										  *
* Language		 :C, MAVS 2010 and above		                      *
* Programmer(2)	 :Крещук Николай, Плотников Кирилл, 8 бригада		  *
* Created		 :22/11/18						                      *
* Last revision	 :22/11/18						                      *
* Comment		 :Работа с математическими функциями                  *
**********************************************************************/

#include "pch.h"
#include "stdio.h"
#include "math.h"
#include "float.h"

double GetFuncValue(double);
double GetAnswerEquation(double, double, double);

double GetIntegral(double, double, double, int, int*);
double GetIntegralFuncValue(double);
double GetSumNumerous(double, double, int);

int main()
{
	double eps = FLT_EPSILON * 2;
	double leftBorder = 0;
	double rightBorder = M_PI / 2;

	double epsIntgl = 0.0005;
	double leftBorderIntgl = 0;
	double rigthBorderIntgl = M_PI / 6;

	int numb = 10;
	int it = 0;
	double answer = GetAnswerEquation(eps, leftBorder, rightBorder);

	printf("Answer of equation: %.7f\n", answer);
	printf("Value of function (answer): %.7f\n\n", GetFuncValue(answer));
	printf("Answer of integral: %.7f\n", GetIntegral(leftBorderIntgl, rigthBorderIntgl, epsIntgl, numb, &it));
	printf("Number of iterations: %d\n", it);
}

// Первая часть программы.
double GetFuncValue(double argX)
{
	return (2 * pow(sin(argX), 2)) / 3 - 0.75 * pow(cos(argX), 2);
}

double GetAnswerEquation(double eps, double left, double right)
{
	double valueFuncLeft = 0;
	double valueFuncRight = 0;
	double pointX = 0;
	double valueFuncX = 0;

	while (1)
	{
		valueFuncLeft = GetFuncValue(left);
		valueFuncRight = GetFuncValue(right);
		pointX = (left * valueFuncRight - right * valueFuncLeft) / (valueFuncRight - valueFuncLeft);
		valueFuncX = GetFuncValue(pointX);

		if (fabs(valueFuncX) > eps)
		{
			if (valueFuncLeft != valueFuncX)
				left = pointX;
			else
				right = pointX;
		}
		else
		{
			return pointX;
		}
	}
}
/***********************************/

// Вторая часть программы (метод трапеций).
double GetIntegral(double left, double right, double eps, int numb, int *iterations)
{
	int deltaNumb = 10;

	double valueInglMoreAccurate = 0;
	double valueIngl = GetSumNumerous(left, right, numb);

	while (1)
	{
		*iterations = *iterations + 1;
		numb += deltaNumb;
		valueInglMoreAccurate = GetSumNumerous(left, right, numb);

		if (fabs(valueIngl - valueInglMoreAccurate) <= eps)
			return valueInglMoreAccurate;
		else
			valueIngl = valueInglMoreAccurate;
	}
}

double GetIntegralFuncValue(double argX)
{
	return sqrt(tan(argX));
}

double GetSumNumerous(double left, double right, int numb)
{
	double step = (right - left) / numb;
	double sumNumrs = 0;

	for (int i = 0; i < numb; i++)
		sumNumrs += GetIntegralFuncValue(left + step * i);

	sumNumrs = sumNumrs * step + (GetIntegralFuncValue(left) + GetIntegralFuncValue(right)) / 2 * step;

	return sumNumrs;
}
/*******************************************************/