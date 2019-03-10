namespace Lab_6
{
	/// <summary>
	/// Класс пузырьковой сортировки.
	/// </summary>
	class BubbleSort : ISort
	{ 
		/// <summary>
		/// Имя сортировки.
		/// </summary>
		public string Name { get; }

		/// <summary>
		/// Конструктор по умолчанию класса пузьковой сортировки.
		/// </summary>
		public BubbleSort()
		{
			Name = "Сортировка пузьрьковая (прямого обмена)";
		}

		/// <summary>
		/// Сортировка массива метод пузырька.
		/// </summary>
		/// <param name="arr">Массив для сортировки.</param>
		public int Sort(int[] arr)
		{
			int iterations = 0;
			for (int i = 0; i < arr.Length - 1; i++)
			{
				for (int j = i + 1; j < arr.Length; j++)
				{
					if (arr[i] > arr[j])
					{
						int temp = arr[i];
						arr[i] = arr[j];
						arr[j] = temp;
						iterations++;
					}
				}
			}
			return iterations;
		}
	}
}