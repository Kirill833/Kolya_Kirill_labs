/**********************************************************************
* Project Name	 :Lab_9												  *
* Project Type	 :Win32 Console Application							  *
* File Name		 :Lab_9.cpp											  *
* Language		 :C, MAVS 2010 and above		                      *
* Programmer(2)	 :Крещук Николай, Плотников Кирилл, 8 бригада		  *
* Created		 :20/04/18						                      *
* Last revision	 :28/09/18						                      *
* Comment		 :Работа с двоичными файлами			              *
**********************************************************************/

#include "pch.h"
#include "stdio.h"
#include <Windows.h>
	
// Подсчёт количества символов в строке.
int CountSymbols(char *line)
{
	int nSymb = 0;

	// Пока не конец строки.
	while (line[nSymb] != '\0')
		nSymb++;

	return nSymb;
}

char* DeleteSymbolNewLine(int maxLength, char *line)
{
	int j = 0;

	// Удаление знаков новой строки ('\n').
	while (j < maxLength && line[j] != '\n')
		j++;

	line[j] = '\0';
	return line;
}

int main()
{
	// Подключение русского языка.
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	// Максимальная длина строки.
	int maxLength = 0;
	int countSymb = 0;
	int i = 0;

	double nLine = 0;

	FILE *file;
	FILE *binaryFile;

	char line[256];

	if ((file = fopen("Test.txt", "r")) == NULL)
	{
		printf("Ошибка: не удалось открыть файл.\n");
		return 2;
	}

	while (fgets(line, sizeof(line), file))
	{
		countSymb = CountSymbols(line);

		if (countSymb > maxLength)
			maxLength = countSymb;

		nLine++;
		countSymb = 0;
		i = 0;
	}

	if (!feof(file))
	{
		printf("Ошибка: неудачное чтение из файла.\n");
		return 3;
	}

	if (nLine == 0)
	{
		printf("Ошибка: файл пуст.");
		return 4;
	}

	binaryFile = fopen("BinaryFile.bin", "wb");
	fwrite(&nLine, sizeof(double), 1, binaryFile);

	int j = 0;
	rewind(file);

	while (fgets(line, maxLength + 1, file)
	{
		DeleteSymbolNewLine(maxLength, line);
		fwrite(line, sizeof(char), maxLength, binaryFile);
	}
	
	fclose(file);
	fclose(binaryFile);
	binaryFile = fopen("BinaryFile.bin", "rb");

	fread(&nLine, sizeof(double), 1, binaryFile);

	if (nLine < 0)
	{
		printf("Ошибка: количество элементов не может быть меньше 0.");
		return;
	}
	else if (nLine == 0 && fread(line, sizeof(char), maxLength, binaryFile))
	{
		printf("Ошибка: количество элементов 0, и далее следуют элементы.");
	}

	printf("Количество элементов: %.3f.\n", nLine);

	for (int i = 0; i < nLine; i++)
	{
		fread(line, sizeof(char), maxLength, binaryFile);
		printf("%s\n", line);
	}

	double size = ftell(binaryFile);
	
	fclose(binaryFile);
	printf("Размер файла: %.3f байт.", size);

	return 0;
}