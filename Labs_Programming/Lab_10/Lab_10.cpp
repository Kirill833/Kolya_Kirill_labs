/*********************************************************************
* Project Name	 :Lab_10											 *
* Project Type	 :Win32 Console Application							 *
* File Name		 :Lab_10.cpp										 *
* Language		 :C, MAVS 2010 and above		                     *
* Programmer(2)	 :Крещук Николай, Плотников Кирилл, 8 бригада		 *
* Created		 :09/10/18						                     *
* Last revision	 :13/10/18						                     *
* Comment		 :Шифр Цезаря				                         *
*********************************************************************/

#include "pch.h"
#include "Windows.h"
#include "stdio.h"
#include "string.h"

void ChangeSymbols(char *line, int offset, int encrypt);

int main()
{
	// Подключение русского языка.
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	const char *TEST_FILE = "Test.txt";
	const char *ENCRYPT_FILE = "Encrypt.txt";
	const int offset = -150;

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
	if (ftell(testFile) == 0)
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

	while (fgets(buffer, 256, testFile) != NULL)
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

	while (fgets(buffer, 256, encryptFile) != NULL)
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

void ChangeSymbols(char *line, int offset, int encrypt)
{
	const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZабвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

	int i = 0;
	int j = 0;

	if (offset < 0)
		offset = -offset;

	while (line[i] != '\0')
	{
		if (strchr(ALPHABET, line[i]) == NULL)
		{
			i++;
			continue;
		}

		j = strchr(ALPHABET, line[i]) - ALPHABET;

		// Замена буквы.
		if (encrypt)
			line[i] = ALPHABET[(j + offset) % strlen(ALPHABET)];
		else
			line[i] = ALPHABET[((j - offset) + strlen(ALPHABET)) % strlen(ALPHABET)];

		i++;
	}
}