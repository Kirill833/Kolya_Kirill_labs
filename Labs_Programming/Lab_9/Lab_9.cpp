/**********************************************************************
* Project Name	 :Lab_9												  *
* Project Type	 :Win32 Console Application							  *
* File Name		 :Lab_9.cpp											  *
* Language		 :C, MAVS 2010 and above		                      *
* Programmer(2)	 :Крещук Николай, Плотников Кирилл, 8 бригада		  *
* Created		 :20/04/18						                      *
* Last revision	 :28/09/18						                      *
* Comment		 :Работа с файлами			                          *
**********************************************************************/

#include "pch.h"
#include "stdio.h"
#include <Windows.h>

// Запись данных в двоичный файл.
void WriteBinaryData(double nLine, int maxLength, char *lines)
{
	FILE *textFile;
	FILE *binaryFile;

	textFile = fopen("Test.txt", "r");
	binaryFile = fopen("BinaryFile.bin", "wb");

	// Запись в файл количества строк.
	fwrite(&nLine, sizeof(double), 1, binaryFile);

	// Счётчик.
	int j = 0;

	for (int i = 0; i < nLine; i++)
	{
		fgets(lines, maxLength + 1, textFile);
		
		// Удаление знаков новой строки ('\n').
		while (j < maxLength && lines[j] != '\n')
			j++;

		lines[j] = '\0';
		j = 0;
		fwrite(lines, sizeof(char), maxLength, binaryFile);
	}

	fclose(textFile);
	fclose(binaryFile);
}

// Чтение данных из двоичного файла.
void ReadBinaryData(char *lines, int nLine, int maxLength)
{
	FILE *binaryFile;
	binaryFile = fopen("BinaryFile.bin", "rb");

	double numbLines = 0;
	fread(&numbLines, sizeof(double), 1, binaryFile);

	if (numbLines < 0)
	{
		printf("Ошибка: количество элементов не может быть меньше 0.");
		return;
	}
	else if (numbLines == 0 && fread(lines, sizeof(char), maxLength, binaryFile))
	{
		printf("Ошибка: количество элементов 0, и далее следуют элементы.");
	}

	printf("Количество элементов: %.3f.\n", numbLines);

	for (int i = 0; i < nLine; i++)
	{
		fread(lines, sizeof(char), maxLength, binaryFile);
		printf("%s\n", lines);
	}

	double size = ftell(binaryFile);
	fclose(binaryFile);
	printf("Размер файла: %.3f байт.", size);
}

// Чтение данных из файла.
int ReadData(double *nLine, int *maxLength)
{
	FILE *file;
	
	char line[256];
	int countSymbols = 0;
	int i = 0;

	if ((file = fopen("Test.txt", "r")) == NULL)
	{
		printf("Ошибка: не удалось открыть файл.\n");
		return 2;
	}

	while (fgets(line, sizeof(line), file))
	{
		// Подсчёт длины строки.
		while (line[i] != '\0')
		{
			countSymbols++;
			i++;
		}

		if (countSymbols > *maxLength)
			*maxLength = countSymbols;

		*nLine = *nLine + 1;
		countSymbols = 0;
		i = 0;
	}

	if (!feof(file))
	{
		printf("Ошибка: неудачное чтение из файла.\n");
		return 3;
	}

	if (*nLine == 0)
	{
		printf("Ошибка: файл пуст.");
		return 4;
	}

	fclose(file);

	return 0;
}

int main()
{
	// Подключение русского языка.
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	// Максимальная длина строки.
	int maxLength = 0;

	double nLine = 0;
	int error = ReadData(&nLine, &maxLength);

	if (error != 0)
		return 1;

	// Объявление динамического массива.
	char *lines = (char*)malloc(maxLength + 1 * sizeof(char));
	lines[maxLength] = '\0';

	WriteBinaryData(nLine, maxLength, lines);
	ReadBinaryData(lines, nLine, maxLength);

	return 0;
}