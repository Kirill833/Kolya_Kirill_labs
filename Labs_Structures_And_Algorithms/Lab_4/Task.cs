using System;
using System.IO;

namespace Lab_4
{
	/// <summary>
	/// Класс задания.
	/// </summary>
	class Task
	{
		/// <summary>
		/// Общее количество вершин.
		/// </summary>
		public int NumberOfTops { get; set; }

		/// <summary>
		/// Имя файла.
		/// </summary>
		public string FileName { get; set; }

		/// <summary>
		/// Матрица смежности графа.
		/// </summary>
		public int[,] MatrixAdjacency { get; set; }

		/// <summary>
		/// Конструктор класса задания.
		/// </summary>
		/// <param name="numb">Количество вершин графа.</param>
		/// <param name="fileName">Имя текстового файла.</param>
		public Task(int numb, string fileName)
		{
			NumberOfTops = numb;
			FileName = fileName;
			MatrixAdjacency = new int[numb, numb];
		}

		/// <summary>
		/// Чтение матрицы смежности из файла.
		/// </summary>
		public void ReadMatrixFromFile()
		{
			string[] rowsOfElemts = new string[NumberOfTops];
			string[] columns = new string[NumberOfTops];

			using (StreamReader sr = File.OpenText(FileName))
			{
				for (int i = 0; i < NumberOfTops; i++)
				{
					rowsOfElemts[i] = sr.ReadLine();
					columns = rowsOfElemts[i].Split(" ", StringSplitOptions.RemoveEmptyEntries);
					for (int j = 0; j < NumberOfTops; j++)
						MatrixAdjacency[i, j] = Convert.ToInt32(columns[j]);
				}
			}
		}

		/// <summary>
		/// Инициализация графа.
		/// </summary>
		/// <returns>Представление графа.</returns>
		public Graph Initialize()
		{
			Graph g = new Graph();
			int distance = 0;

			for (int i = 0; i < NumberOfTops; i++)
			{
				g.AddElement(i);
				for (int j = 0; j < NumberOfTops; j++)
				{
					distance = MatrixAdjacency[i, j];
					if (distance != 0)
					{
						g.AddElement(j);

						// Признак того, что граф ориентированный.
						g.GetElement(j).Neighbourhood.Add(g.GetElement(i), -1);
						g.GetElement(i).Neighbourhood.Add(g.GetElement(j), distance);
					}
				}
			}

			return g;
		}
	}
}