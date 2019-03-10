namespace Lab_6
{
	/// <summary>
	/// Интерфейс сортировки.
	/// </summary>
	interface ISort
	{
		/// <summary>
		/// Имя сортировки.
		/// </summary>
		string Name { get; }

		/// <summary>
		/// Сортировка массива.
		/// </summary>
		/// <param name="arr">Массив для сортировки.</param>
		/// <returns>Кол-во интераций.</returns>
		int Sort(int[] arr);
	}
}