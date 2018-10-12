/*********************************************************************
* Project Name	 :Lab_10											 *
* Project Type	 :Win32 Console Application							 *
* File Name		 :Lab_8.cpp											 *
* Language		 :C, MAVS 2010 and above		                     *
* Programmer(2)	 :Крещук Николай, Плотников Кирилл, 8 бригада		 *
* Created		 :09/10/18						                     *
* Last revision	 :12/10/18						                     *
* Comment		 :Шифр Цезаря				                         *
*********************************************************************/

#include "pch.h"
#include "Windows.h"
#include "stdio.h"
#define ALPHABET_N 118

const char ALPHABET[ALPHABET_N] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZабвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

void ChangeSymbols(char *line, int offset, int encrypt)
{
	int j = 0;
	int i = 0;

	while (line[i] != '\0')
	{
		// Нахождение индекса данной буквы.
		while (j < ALPHABET_N)
		{
			if (line[i] == ALPHABET[j])
				break;
			j++;
		}

		// Если символ не буква, переходим к следующему символу.
		if (j == ALPHABET_N)
		{
			i++;
			j = 0;
			continue;
		}

		// Смещение алфавита.
		if (encrypt)
			line[i] = ALPHABET[(j + offset) % ALPHABET_N];
		else
			line[i] = ALPHABET[(j - offset + ALPHABET_N) % ALPHABET_N];

		j = 0;
		i++;
	}
}

int main()
{
	// Подключение русского языка.
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	const char *TEST_FILE = "Test.txt";
	const char *ENCRYPT_FILE = "Encrypt.txt";
	const int offset = 1;

	char *buffer[256];

	FILE *encryptFile;
	FILE *testFile;

	if ((testFile = fopen(TEST_FILE, "r")) == NULL)
	{
		printf("Не удалось открыть файл.\n");
		system("pause");
		return 0;
	}

	// Смещаем курсор в конец файла.
	fseek(testFile, 0, SEEK_END);

	// Если позиция курсора нулевая, то файл пуст.
	if (!ftell(testFile))
	{
		printf("Файл пуст.\n");
		system("pause");
		return 1;
	}

	rewind(testFile);

	if ((encryptFile = fopen(ENCRYPT_FILE, "w")) == NULL)
	{
		printf("Не удалось создать файл для записи.\n");
		system("pause");
		return 0;
	}

	while (fgets(buffer, 256, testFile))
	{
		ChangeSymbols(buffer, offset, 1);
		if ((fputs(buffer, encryptFile)) == EOF)
		{
			printf("Произошла ошибка записи данных в файл.");
			system("pause");
			return 1;
		}
	}

	if (!feof(testFile))
	{
		printf("Произошла ошибка чтения из файла.\n");
		system("pause");
		return 1;
	}
	
	fclose(encryptFile);
	encryptFile = fopen(ENCRYPT_FILE, "r");

	while (fgets(buffer, 256, encryptFile))
	{
		ChangeSymbols(buffer, offset, 0);
		printf("%s", buffer);
	}

	if (!feof(encryptFile))
	{
		printf("Произошла ошибка чтения из файла.\n");
		system("pause");
		return 1;
	}

	printf("\n");
	system("pause");
	return 0;
}