/**********************************************************************
* Project Name	 :Lab_8												  *
* Project Type	 :Win32 Console Application							  *
* File Name		 :Lab_8.cpp											  *
* Language		 :C, MAVS 2010 and above		                      *
* Programmer(2)	 :Крещук Николай, Плотников Кирилл, 8 бригада		  *
* Created		 :16/09/18						                      *
* Last revision	 :26/10/18						                      *
* Comment		 :Работа с файлами			                          *
**********************************************************************/

#include "pch.h"
#include "stdio.h"
#include "Windows.h"
#define DIGIT_N 10

int IsLetter(int *, char, char *);

int main()
{
	// Подключение русского языка.
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZабвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

	double nDigit = 0;
	double nLetter = 0;
	double nLine = 0;
	double averageLetters = 0;
	double averageDigits = 0;

	char line[256];

	// Массив для подсчёта букв.
	int alphabetOut[sizeof(ALPHABET) / sizeof(char)] = { 0 };

	// Массив для подсчёта цифр.
	int digOut[DIGIT_N] = { 0 };

	FILE *file;

	if ((file = fopen("Test.txt", "r")) == NULL)
	{
		printf("Не удалось открыть файл.\n");
		system("pause");
		return 0;
	}

	while (fgets(line, sizeof(line), file) != NULL)
	{
		for (int i = 0; line[i] != '\0'; i++)
		{
			if (line[i] >= '0' && line[i] <= '9')
			{
				digOut[(int)line[i] - (int)'0']++;
				nDigit++;
				continue;
			}

			if (IsLetter(alphabetOut, line[i], ALPHABET))
				nLetter++;
		}
		nLine++;
	}

	if (!feof(file))
	{
		printf("Произошла ошибка чтения из файла.\n");
		return 1;
	}
	
	fclose(file);

	if (nLine == 0)
	{
		printf("Файл пуст.");
		return 2;
	}

	for (int i = 0; i < sizeof(ALPHABET) / sizeof(char); i++)
		if (alphabetOut[i] != 0)
			printf("Буква %c встречается %i раз.\n", ALPHABET[i], alphabetOut[i]);

	for (int i = 0; i < DIGIT_N; i++)
		if (digOut[i] != 0)
			printf("Цифра %i встречается %i раз.\n", i, digOut[i]);

	averageDigits = nDigit / nLine;
	averageLetters = nLetter / nLine;

	printf("\nСреднее количество букв в строке: %.3f.\n", averageLetters);
	printf("Среднее количество цифр в строке: %.3f.\n", averageDigits);

	return 0;
}

int IsLetter(int *alphabetCount, char checkLetter, char *alphabet)
{
	for (int i = 0; i < sizeof(alphabet) / sizeof(char); i++)
	{
		if (checkLetter == alphabet[i])
		{
			alphabetCount[i]++;
			return 1;
		}
	}

	return 0;
}