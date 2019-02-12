using System;
using System.Collections.Generic;

namespace Lab_4
{
	/// <summary>
	/// Класс графа.
	/// </summary>
	class Graph
	{
		/// <summary>
		/// Словарь вершин графа.
		/// </summary>
		private Dictionary<int, Element> _elements { get; set; } = new Dictionary<int, Element>();

		/// <summary>
		/// Добавление вершины в граф.
		/// </summary>
		/// <param name="numb">Номер вершины.</param>
		public void AddElement(int numb)
		{
			if (!_elements.ContainsKey(numb))
				_elements.Add(numb, new Element(numb));
		}

		/// <summary>
		/// Получение вершины графа.
		/// </summary>
		/// <param name="numb">Номер вершины.</param>
		/// <returns>Вершина графа.</returns>
		public Element GetElement(int numb)
		{
			return _elements[numb];
		}

		/// <summary>
		/// Получение минимального расстояния между двумя вершинами.
		/// </summary>
		/// <param name="start">Начальная вершина.</param>
		/// <param name="finish">Конечная вершина.</param>
		public void GetMinDistance(int start, int finish)
		{
			bool[] isCheck = new bool[_elements.Count];
			int[] distances = new int[_elements.Count];
			int neighbour = 0;
			int minCurDistance = 0;
			int minIndexElem = 0;
			int iCur = start - 1;

			distances[iCur] = 0;
			for (int i = 0; i < _elements.Count; i++)
			{
				if (i == iCur)
					continue;
				distances[i] = -1;
			}

			for (int i = 0; i < _elements.Count; i++)
			{
				if (isCheck[iCur])
					continue;

				foreach (KeyValuePair<Element, int> neighb in _elements[iCur].Neighbourhood)
				{
					neighbour = neighb.Key.Number;
					if (distances[neighbour] > distances[iCur] + neighb.Value || distances[neighbour] == -1)
						distances[neighbour] = distances[iCur] + neighb.Value;
				}

				isCheck[iCur] = true;
				for (int j = 0; j < _elements.Count; j++)
				{
					if (distances[j] != -1 && (distances[j] < minCurDistance || minCurDistance == 0)
						&& !isCheck[j])
					{
						minCurDistance = distances[j];
						minIndexElem = j;
					}
				}

				iCur = minIndexElem;
				minCurDistance = 0;
			}

			Console.WriteLine($"Крайчайший путь между вершинами {start} и {finish}: {distances[finish - 1]}.");
			PrintWay(distances, start, finish);
		}

		private void PrintWay(int[] distces, int start, int finish)
		{
			List<int> ascendingWay = new List<int>();
			int iCur = finish - 1;
			ascendingWay.Add(iCur);
			while (iCur != start - 1)
			{
				foreach (KeyValuePair<Element, int> elem in _elements[iCur].Neighbourhood)
				{
					if (elem.Value == -1 && elem.Key.Neighbourhood.ContainsKey(GetElement(iCur))
						&& distces[elem.Key.Number] == distces[iCur] - elem.Key.Neighbourhood[GetElement(iCur)])
					{
						iCur = elem.Key.Number;
						ascendingWay.Add(iCur);
					}
				}
			}

			Console.Write("Путь: ");

			ascendingWay.Reverse();
			foreach (int point in ascendingWay)
				Console.Write($"{point + 1} ");

			Console.WriteLine();
		}
	}
}