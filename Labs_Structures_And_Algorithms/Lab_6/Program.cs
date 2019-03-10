using System;
using System.Diagnostics;

namespace Lab_6
{
	class Program
	{
		static void Main(string[] args)
		{

			ISort[] sorts = new ISort[] { new BubbleSort(), new ShellSort() };
			DoAlgorithm(sorts);
			Console.ReadLine();
		}

		static void DoAlgorithm(ISort[] sorts)
		{
			Console.Write("Введите желаемое кол-во элементов: ");
			int wishCountOfElems = int.Parse(Console.ReadLine());
			Stopwatch sw = new Stopwatch();
			int[] testArr = GetTestArr(wishCountOfElems);
			int[] tempArr = new int[testArr.Length];
			int iterations = 0;

			Console.WriteLine("\nНеотсортированный массив:");
			PrintArr(testArr);

			foreach (ISort sort in sorts)
			{
				testArr.CopyTo(tempArr, 0);
				sw.Start();
				iterations = sort.Sort(tempArr);
				sw.Stop();
				Console.WriteLine($"Затраченное время на сортировку <{sort.Name}>: {sw.ElapsedMilliseconds} миллисекунд.");
				Console.WriteLine($"Кол-во итераций: {iterations}.");
			}

			Console.WriteLine("\nОтсортированный массив:");
			PrintArr(tempArr);
		}

		static int[] GetTestArr(int countOfElms)
		{
			Random rnd = new Random();
			int maxValue = countOfElms * 10000;
			int[] testArray = new int[countOfElms];
			for (int i = 0; i < countOfElms; i++)
				testArray[i] = rnd.Next(-maxValue, maxValue);

			return testArray;
		}

		static void PrintArr(int[] arr)
		{
			for (int i = 0; i < arr.Length; i++)
				Console.WriteLine(arr[i]);
		}
	}
}