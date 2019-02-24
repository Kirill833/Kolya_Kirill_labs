using System.Collections.Generic;

namespace Lab_4
{
	/// <summary>
	/// Класс вершины.
	/// </summary>
	class Node
	{
		/// <summary>
		/// Номер вершины.
		/// </summary>
		public int Number { get; }

		/// <summary>
		/// Соседние вершины и расстояние до них.
		/// </summary>
		public Dictionary<Node, int> Neighbourhood { get; set; }

		/// <summary>
		/// Конструктор класса вершины.
		/// </summary>
		/// <param name="numb">Номер вершины.</param>
		public Node(int numb)
		{
			Number = numb;
			Neighbourhood = new Dictionary<Node, int>();
		}
	}
}