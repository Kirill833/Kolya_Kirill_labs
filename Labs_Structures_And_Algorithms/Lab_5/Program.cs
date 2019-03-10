using System;

namespace Lab_5
{
	class Program
	{
		static void Main(string[] args)
		{
			StartProgram();
			Console.ReadLine();
		}

		private static void StartProgram()
		{
			Console.Write("Введите кол-во желаемых вершин: ");
			int numberOfNodes = int.Parse(Console.ReadLine());
			Tree t = Tree.InitializeNewTree(numberOfNodes);
			ShowMenu();
			string command;
			int searchingKey;
			do
			{
				command = Console.ReadLine();
				switch (command)
				{
					case "1":
						Console.Write("Введите значение ключа: ");
						searchingKey = int.Parse(Console.ReadLine());
						Console.WriteLine(t.SearchKey(searchingKey));
						break;
					case "2":
						Console.WriteLine("Как вы хотите добавить узел? (0 - случайный ключ, 1 - выбранный ключ).");
						string choice = Console.ReadLine();
						if (choice == "0")
						{
							Console.WriteLine(t.AddNode());
						}
						else if (choice == "1")
						{
							Console.WriteLine("Введите ключ.");
							int key = int.Parse(Console.ReadLine());
							Console.WriteLine(t.AddNode(key));
						}
						else
						{
							Console.WriteLine("Неправильный номер выбора!");
							Console.WriteLine("Выберите команду снова.");
						}

						break;
					case "3":
						t.Display();
						break;
					case "4":
						Console.WriteLine(t.SearchMinKey());
						break;
					case "5":
						Console.WriteLine(t.RemoveNodeWithOneChild());
						break;
					default:
						Console.WriteLine("Повторите попытку...");
						break;
				}
			} while (command.ToUpper() != "Q");
		}

		private static void ShowMenu()
		{
			Console.WriteLine("КОМАНДЫ:");
			Console.WriteLine("Введите q/Q для выхода.");
			Console.WriteLine("Введите 1 для поиска с заданным значением ключа.");
			Console.WriteLine("Введите 2 для вставки нового узла.");
			Console.WriteLine("Введите 3 для обхода дерева.");
			Console.WriteLine("Введите 4 для поиска узла с минимальным ключом.");
			Console.WriteLine("Введите 5 для удаления узла с одной дочерней вершиной.");
		}
	}
}