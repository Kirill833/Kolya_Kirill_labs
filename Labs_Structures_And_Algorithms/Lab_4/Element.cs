using System.Collections.Generic;

namespace Lab_4
{
	/// <summary>
	/// Класс вершины.
	/// </summary>
	class Element
	{
		/// <summary>
		/// Номер вершины.
		/// </summary>
		public int Number { get; set; }

		/// <summary>
		/// Соседние вершины и расстояние до них.
		/// </summary>
		public Dictionary<Element, int> Neighbourhood { get; set; } = new Dictionary<Element, int>();

		/// <summary>
		/// Конструктор класса вершины.
		/// </summary>
		/// <param name="numb">Номер вершины.</param>
		public Element(int numb)
		{
			Number = numb;
		}
	}
}