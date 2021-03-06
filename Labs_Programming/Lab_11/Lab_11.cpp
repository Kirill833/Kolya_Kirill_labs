/**********************************************************************
* Project Name	 :Lab_11											  *
* Project Type	 :Win32 Console Application							  *
* File Name		 :Lab_11.cpp										  *
* Language		 :C, MAVS 2010 and above		                      *
* Programmer(2)	 :Крещук Николай, Плотников Кирилл, 8 бригада		  *
* Created		 :15/10/18						                      *
* Last revision	 :26/10/18						                      *
* Comment		 :Работа со строками		                          *
**********************************************************************/

#include "pch.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"

void DeleteAllComments(char *, int *);
void EndLine(char *);

int main()
{
	const char *FILE_NAME = "Test.txt";
	const char *FILE_RESULT_NAME = "Result.txt";

	char line[256] = { 0 };

	// Флаг наличия многострочного комментария.
	int multiCom = 0;

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
		printf("Error: file is empty.\n");
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
		DeleteAllComments(line, &multiCom);

		if ((fwrite(line, sizeof(char), strlen(line), resultFile)) < 0)
		{
			printf("Writing error.\n");
			return 1;
		}
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

void DeleteAllComments(char *line, int *multiCom)
{
	int iFindMultiCom = 0;
	int j = 0;

	char *lineCom;

	lineCom = strstr(line, "/*");
	if (lineCom != NULL)
	{
		iFindMultiCom = strcspn(line, "/*");
		*multiCom = 1;
	}

	// Если в строке встретился конец многострочного комментария,
	// Удалить всё, что идёт до него.
	if ((strstr(line, "*/")) != NULL && *multiCom > 0)
	{
		int i = 0;
		j = iFindMultiCom;

		while (line[i] != '*' || line[i + 1] != '/')
			i++;

		i = i + 2;

		while (line[i] != '\0')
			line[j++] = line[i++];

		line[j] = '\0';
		*multiCom = 0;
	}

	lineCom = strstr(line, "//");
	if (lineCom != NULL && *multiCom == 0)
	{
		if (line[0] == '/' && line[1] == '/')
			lineCom[0] = '\0';
		else
			EndLine(lineCom);
	}

	if (*multiCom > 0)
		line[iFindMultiCom] = '\0';
}

void EndLine(char *line)
{
	if (strstr(line, "\n") != NULL)
	{
		line[0] = '\n';
		line[1] = '\0';
	}
	else
	{
		line[0] = '\0';
	}
}