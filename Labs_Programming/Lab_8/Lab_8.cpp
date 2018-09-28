/**********************************************************************
* Project Name	 :Lab_8												  *
* Project Type	 :Win32 Console Application							  *
* File Name		 :Lab_8.cpp											  *
* Language		 :C, MAVS 2010 and above		                      *
* Programmer(2)	 :Крещук Николай, Плотников Кирилл, 8 бригада		  *
* Created		 :16/04/18						                      *
* Last revision	 :28/09/18						                      *
* Comment		 :Работа с файлами			                          *
**********************************************************************/

#include "pch.h"
#include "stdio.h"
#include "Windows.h"
#define ALPHABET_N 118
#define DIGIT_N 10

const char ALPHABET[ALPHABET_N] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZабвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

int IsLetter(int alphabetCount[ALPHABET_N], char checkLetter)
{
	for (int i = 0; i < ALPHABET_N; i++)
	{
		if (checkLetter == ALPHABET[i])
		{
			alphabetCount[i]++;
			return 1;
		}
	}
	return 0;
}

int main()
{
	// Подключение русского языка.
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int eof;

	double nDigit = 0;
	double nLetter = 0;
	double nLine = 0;
	double averageLetters = 0;
	double averageDigits = 0;

	char line[256];

	// Массив для подсчёта букв.
	int alphabetOut[ALPHABET_N] = { 0 };

	// Массив для подсчёта цифр.
	int digOut[DIGIT_N] = { 0 };

	FILE *file;

	if ((file = fopen("Test.txt", "r")) == NULL)
	{
		printf("Не удалось открыть файл.\n");
		system("pause");
		return 0;
	}

	while (fgets(line, sizeof(line), file))
	{
		for (int i = 0; line[i] != '\0'; i++)
		{
			if (line[i] >= '0' && line[i] <= '9')
			{
				digOut[(int)line[i] - (int)'0']++;
				nDigit++;
				continue;
			}

			if (IsLetter(alphabetOut, line[i]))
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

	for (int i = 0; i < ALPHABET_N; i++)
		printf("Буква %c встречается %i раз.\n", ALPHABET[i], alphabetOut[i]);

	printf("\n");

	for (int i = 0; i < DIGIT_N; i++)
		printf("Цифра %i встречается %i раз.\n", i, digOut[i]);

	averageDigits = nDigit / nLine;
	averageLetters = nLetter / nLine;

	printf("Среднее количество букв в строке: %.3f.\n", averageLetters);
	printf("Среднее количество цифр в строке: %.3f.\n", averageDigits);

	return 0;
}