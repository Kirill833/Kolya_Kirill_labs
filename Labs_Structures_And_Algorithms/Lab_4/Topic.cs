using System;
using System.IO;
using System.Text;
using System.Collections.Generic;

namespace Lab_4
{
	/// <summary>
	/// Класс задания.
	/// </summary>
	class Topic
	{
		/// <summary>
		/// Общее количество вершин.
		/// </summary>
		public int NumberOfTops { get; set; }

		/// <summary>
		/// Матрица смежности графа.
		/// </summary>
		public int[,] MatrixAdjacency { get; set; }

		/// <summary>
		/// Конструктор класса задания.
		/// </summary>
		/// <param name="numb">Количество вершин графа.</param>
		public Topic(int numb)
		{
			NumberOfTops = numb;
			MatrixAdjacency = new int[numb, numb];
		}

		/// <summary>
		/// Чтение матрицы смежности из файла.
		/// </summary>
		/// <param name="filename">Имя файла.</param>
		public void ReadMatrixFromFile(string filename)
		{
			string[] rowsOfNodes = new string[NumberOfTops];
			string[] columns = new string[NumberOfTops];

			rowsOfNodes = File.ReadAllLines(filename);
			for (int i = 0; i < NumberOfTops; i++)
			{
				columns = rowsOfNodes[i].Split(new char[] { ' ', ',' }, StringSplitOptions.RemoveEmptyEntries);
				for (int j = 0; j < NumberOfTops; j++)
					MatrixAdjacency[i, j] = Convert.ToInt32(columns[j]);
			}
		}

		/// <summary>
		/// Инициализация графа.
		/// </summary>
		/// <returns>Представление графа.</returns>
		public Graph InitializeGraph()
		{
			Graph g = new Graph();
			int distance = 0;

			for (int i = 0; i < NumberOfTops; i++)
			{
				g.AddNode(i);
				for (int j = 0; j < NumberOfTops; j++)
				{
					distance = MatrixAdjacency[i, j];
					if (distance != 0)
					{
						g.AddNode(j);
						Node iNode = g.GetNode(i);
						Node jNode = g.GetNode(j);

						// Признак того, что граф ориентированный.
						if (distance != MatrixAdjacency[j, i])
							jNode.Neighbourhood.Add(iNode, -1);

						iNode.Neighbourhood.Add(jNode, distance);
					}
				}
			}

			return g;
		}

		/// <summary>
		/// Получение неориентированного графа из текущего.
		/// </summary>
		/// <returns>Неориентированный граф.</returns>
		public Graph GetNonOrientedGraph()
		{
			for (int i = 0; i < NumberOfTops; i++)
				for (int j = 0; j < NumberOfTops; j++)
					if (MatrixAdjacency[i, j] != 0)
						MatrixAdjacency[j, i] = MatrixAdjacency[i, j];
					else
						MatrixAdjacency[i, j] = MatrixAdjacency[j, i];

			return InitializeGraph();
		}

		/// <summary>
		/// Выполнение алгоритма Дейкстры.
		/// </summary>
		/// <param name="g">Граф.</param>
		/// <returns>Результат алгоритма.</returns>
		public string DoDijkstra(Graph g)
		{
			Console.WriteLine("Нумерация вершин начинается с \"0\".");
			Console.Write("Введите начальную вершину: ");
			int start = int.Parse(Console.ReadLine());
			Console.Write("Введите конечную вершину: ");
			int finish = int.Parse(Console.ReadLine());

			int[] distances = g.GetMinDistancesToOther(start);
			if (distances[finish] == -1)
				return $"Пути между вершинами {start} и {finish} не существует.";

			List<int> way = g.GetWay(distances, start, finish);
			StringBuilder result = new StringBuilder($"Крайчайший путь по алгоритму Дейкстры между вершинами" +
				$" {start} и {finish}: {distances[finish]}.\n");
			result.Append("Путь: ");
			foreach (int node in way)
				result.Append($"{node} ");

			return result.ToString();
		}

		/// <summary>
		/// Алгоритм Прима.
		/// </summary>
		/// <param name="g">Неориентированный граф.</param>
		/// <returns>Результат алгоритма.</returns>
		public string DoPrima(Graph g)
		{
			Dictionary<Node, List<Node>> spanningTree = g.GetMinSpanningTree();
			StringBuilder result = new StringBuilder($"Связи между вершинами, в \"[]\" указано расстояние до соседних вершин.\n");
			int minWeight = 0;
			int curWeight = 0;

			foreach (KeyValuePair<Node, List<Node>> node in spanningTree)
			{
				if (node.Value.Count == 0)
					continue;

				result.Append($"Вершина {node.Key.Number}: ");
				foreach (Node neighbour in node.Value)
				{
					curWeight = neighbour.Neighbourhood[node.Key];
					result.Append($"{neighbour.Number}[{curWeight}] ");
					minWeight += curWeight;
				}

				result.AppendLine();
			}

			result.Append($"Мининимальный вес основного дерева по алгоритму Прима = {minWeight}.");
			return result.ToString();
		}
	}
}