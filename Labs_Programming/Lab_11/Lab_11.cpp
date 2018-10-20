/**********************************************************************
* Project Name	 :Lab_11											  *
* Project Type	 :Win32 Console Application							  *
* File Name		 :Lab_11.cpp										  *
* Language		 :C, MAVS 2010 and above		                      *
* Programmer(2)	 :Крещук Николай, Плотников Кирилл, 8 бригада		  *
* Created		 :15/10/18						                      *
* Last revision	 :20/10/18						                      *
* Comment		 :Работа со строками		                          *
**********************************************************************/

#include "pch.h"
#include "stdio.h"
#include "string.h"

void PrintCodeBeforeComment(char *, char, char, FILE *);
void PrintCodeAfterMultiComment(char *, FILE *);

int main()
{
	const char *FILE_NAME = "Test.txt";
	const char *FILE_RESULT_NAME = "Result.txt";

	char line[256];
	char *lineCom;

	int iStartMultiCom = -1;
	int i = 0;
	int positionEnd = 0;

	FILE *file;
	FILE *resultFile;

	if ((file = fopen(FILE_NAME, "r")) == NULL)
	{
		printf("Error, file with comments doesn't open.\n");
		return 1;
	}

	// Смещаем курсор в конец файла.
	fseek(file, 0, SEEK_END);
	
	positionEnd = ftell(file);

	// Если позиция курсора нулевая, то файл пуст.
	if (positionEnd == 0)
	{
		printf("Файл пуст.\n");
		system("pause");
		return 1;
	}

	// Возврат курсора в начало файла.
	rewind(file);

	if ((resultFile = fopen(FILE_RESULT_NAME, "w")) == NULL)
	{
		printf("Error, resulting file doesn't open.\n");
		return 1;
	}

	while (fgets(line, 256, file) != NULL)
	{
		lineCom = strstr(line, "/*");
		if (lineCom != NULL)
		{
			PrintCodeBeforeComment(line, '/', '*', resultFile);
			fprintf(resultFile, "\n");
			iStartMultiCom = 1;
			continue;
		}

		lineCom = strstr(line, "*/");
		if (lineCom != NULL && iStartMultiCom > 0)
		{
			PrintCodeAfterMultiComment(line, resultFile);
			iStartMultiCom = 0;
			continue;
		}

		lineCom = strstr(line, "//");
		if (lineCom != NULL && iStartMultiCom <= 0)
		{
			PrintCodeBeforeComment(line, '/', '/', resultFile);
			fprintf(resultFile, "\n");
			continue;
		}

		if (iStartMultiCom > 0)
			fprintf(resultFile, "\n");
		else
			fprintf(resultFile, line);
	}

	// Если позиция конца не совпадает с текущей => не конец файла.
	if (positionEnd != ftell(file))
	{
		printf("Reading error.\n");
		return 1;
	}

	fclose(file);
	fclose(resultFile);
	return 0;
}

void PrintCodeBeforeComment(char *line, char firstSymb, char secondSymb, FILE *file)
{
	int i = 0;

	while (line[i] != firstSymb || line[i + 1] != secondSymb)
	{
		fputc(line[i], file);
		i++;
	}
}

void PrintCodeAfterMultiComment(char *line, FILE *file)
{
	int i = 0;

	while (line[i] != '*' || line[i + 1] != '/')
	{
		line[i] = ' ';
		i++;
	}

	line[i] = ' ';
	line[i + 1] = ' ';
	fputs(line, file);
}