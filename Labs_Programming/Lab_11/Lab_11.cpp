/**********************************************************************
* Project Name	 :Lab_11											  *
* Project Type	 :Win32 Console Application							  *
* File Name		 :Lab_11.cpp										  *
* Language		 :C, MAVS 2010 and above		                      *
* Programmer(2)	 :Крещук Николай, Плотников Кирилл, 8 бригада		  *
* Created		 :15/10/18						                      *
* Last revision	 :21/10/18						                      *
* Comment		 :Работа со строками		                          *
**********************************************************************/

#include "pch.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"

void DeleteAllComments(char *, int *);

int main()
{
	const char *FILE_NAME = "Test.txt";
	const char *FILE_RESULT_NAME = "Result.txt";

	char line[256];

	// Флаг наличия многострочного комментария.
	int multiCom = 0;

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

		if ((fprintf(resultFile, line)) < 0)
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

	char *lineCom;

	lineCom = strstr(line, "/*");
	if (lineCom != NULL)
	{
		iFindMultiCom = strcspn(line, "/*");
		lineCom[0] = ' ';
		lineCom[1] = ' ';
		*multiCom = 1;
	}

	// Если в строке встретился конец многострочного комментария,
	// Удалить всё, что идёт до него.
	if ((strstr(line, "*/")) != NULL && *multiCom > 0)
	{
		int i = iFindMultiCom;
		while (line[i] != '*' || line[i + 1] != '/')
		{
			if (!iscntrl(line[i]))
				line[i] = ' ';
			i++;
		}

		line[i] = ' ';
		line[i + 1] = ' ';
		*multiCom = 0;
	}

	lineCom = strstr(line, "//");
	if (lineCom != NULL && *multiCom <= 0)
	{
		if (strstr(line, "\n") != NULL)
			lineCom[0] = '\n';
		else
			lineCom[0] = '\0';
		lineCom[1] = '\0';
	}

	if (*multiCom > 0)
	{
		line[iFindMultiCom] = '\n';
		line[iFindMultiCom + 1] = '\0';
	}
}