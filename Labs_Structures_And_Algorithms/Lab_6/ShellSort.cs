namespace Lab_6
{
	/// <summary>
	/// Класс сортировки Шелла.
	/// </summary>
	class ShellSort : ISort
	{
		/// <summary>
		/// Имя сортировки.
		/// </summary>
		public string Name { get; }

		/// <summary>
		/// Конструктор по умолчанию класса сортировки Шелла.
		/// </summary>
		public ShellSort()
		{
			Name = "Сортировка Шелла";
		}

		/// <summary>
		/// Сортировка массива методов Шелла.
		/// </summary>
		/// <param name="arr">Массив для сортировки.</param>
		/// <returns>Кол-во итераций.</returns>
		public int Sort(int[] arr)
		{
			int iterations = 0;
			int j;
			int step = arr.Length / 2;
			while (step > 0)
			{
				for (int i = 0; i < (arr.Length - step); i++)
				{
					j = i;
					while ((j >= 0) && (arr[j] > arr[j + step]))
					{
						int tmp = arr[j];
						arr[j] = arr[j + step];
						arr[j + step] = tmp;
						j -= step;
						iterations++;
					}
				}
				step = step / 2;
			}
			return iterations;
		}
	}
}