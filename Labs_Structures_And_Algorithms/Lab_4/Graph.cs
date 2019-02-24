using System.Collections.Generic;
using System.Linq;

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
		private Dictionary<int, Node> _nodes { get; set; }

		/// <summary>
		/// Стандартный конструктор класса графа.
		/// </summary>
		public Graph()
		{
			_nodes = new Dictionary<int, Node>();
		}

		/// <summary>
		/// Добавление вершины в граф.
		/// </summary>
		/// <param name="number">Номер вершины.</param>
		public void AddNode(int number)
		{
			if (!_nodes.ContainsKey(number))
				_nodes.Add(number, new Node(number));
		}

		/// <summary>
		/// Получение вершины графа.
		/// </summary>
		/// <param name="number">Номер вершины.</param>
		/// <returns>Вершина графа.</returns>
		public Node GetNode(int number)
		{
			return _nodes[number];
		}

		/// <summary>
		/// Получение минимального расстояния между данной вершиной и остальными.
		/// </summary>
		/// <param name="start">Номер начальной вершины.</param>
		public int[] GetMinDistancesToOther(int start)
		{
			bool[] isCheck = new bool[_nodes.Count];
			int[] distances = new int[_nodes.Count];
			int NumberNeighbour = 0;
			int minCurDistance = 0;
			int minIndexElem = -1;
			int iCur = start;

			distances[iCur] = 0;
			for (int i = 0; i < _nodes.Count; i++)
			{
				if (i == iCur)
					continue;

				// -1 означает, что путь из начальной вершины не найден/не существует.
				distances[i] = -1;
			}

			for (int i = 0; i < _nodes.Count; i++)
			{
				if (isCheck[iCur])
					 break;

				var reachableNeighbors = _nodes[iCur].Neighbourhood.Where((n) => n.Value != -1).Select((n) => n);
				foreach (var neighb in reachableNeighbors)
				{
					NumberNeighbour = neighb.Key.Number;
					if (distances[NumberNeighbour] > distances[iCur] + neighb.Value || distances[NumberNeighbour] == -1)
						distances[NumberNeighbour] = distances[iCur] + neighb.Value;
				}

				isCheck[iCur] = true;
				for (int j = 0; j < _nodes.Count; j++)
				{
					if (distances[j] != -1 && (distances[j] < minCurDistance || minCurDistance == 0) && !isCheck[j])
					{
						minCurDistance = distances[j];
						minIndexElem = j;
					}
				}

				if (minIndexElem == -1)
					break;

				iCur = minIndexElem;
				minCurDistance = 0;
			}

			return distances;
		}
		
		/// <summary>
		/// Получение пути от начальной вершины до конечной.
		/// </summary>
		/// <param name="distances">Минимальное расстояние между начальной вершиной и остальными.</param>
		/// <param name="start">Номер начальной вершины.</param>
		/// <param name="finish">Номер конечной вершины.</param>
		/// <returns>Путь в виде списка вершин.</returns>
		public List<int> GetWay(int[] distances, int start, int finish)
		{
			List<int> ascendingWay = new List<int>();
			int iCur = finish;
			ascendingWay.Add(iCur);
			while (iCur != start)
			{
				foreach (KeyValuePair<Node, int> node in _nodes[iCur].Neighbourhood)
				{
					Node neighbourNode = node.Key;
					Node curNode = GetNode(iCur);
					if (neighbourNode.Neighbourhood.ContainsKey(curNode) && neighbourNode.Neighbourhood[curNode] != -1 &&
						 distances[neighbourNode.Number] == distances[iCur] - neighbourNode.Neighbourhood[curNode])
					{
						iCur = neighbourNode.Number;
						ascendingWay.Add(iCur);
						break;
					}
				}
			}
			
			ascendingWay.Reverse();
			return ascendingWay;
		}

		/// <summary>
		/// Получение минимального остовного дерева.
		/// </summary>
		/// <returns>Минимальное остовное дерево.</returns>
		public Dictionary<Node, List<Node>> GetMinSpanningTree()
		{
			int minDistance;
			int iMinNeibour = 0;
			int iCur = 0;
			bool[] isChecked = new bool[_nodes.Count];
			Dictionary<Node, List<Node>> spanningTree = new Dictionary<Node, List<Node>>();

			for (int i = 0; i < _nodes.Count; i++)
				spanningTree.Add(_nodes[i], new List<Node>());

			for (int i = 0; i < _nodes.Count - 1; i++)
			{
				minDistance = -1;
				isChecked[iMinNeibour] = true;
				for (int j = 0; j < _nodes.Count; j++)
				{
					if (isChecked[j])
					{
						foreach (KeyValuePair<Node, int> neighbour in _nodes[j].Neighbourhood)
						{
							if (!isChecked[neighbour.Key.Number] && (neighbour.Value < minDistance || minDistance == -1))
							{
								minDistance = neighbour.Value;
								iMinNeibour = neighbour.Key.Number;
								iCur = j;
							}
						}
					}
				}

				spanningTree[GetNode(iCur)].Add(GetNode(iMinNeibour));
			}

			return spanningTree;
		}
	}
}