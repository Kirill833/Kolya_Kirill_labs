using System;
using System.Collections.Generic;
using System.IO;

namespace Lab_4
{
	class Program
	{
		static void Main(string[] args)
		{
			int n = 6;
			string fileName = @"D:\GitHub\Labs_Struct_Prog\Labs_Structures_And_Algorithms\Lab_4\Test.txt";
			Task t = new Task(n, fileName);
			t.ReadMatrixFromFile();
			Graph graph = t.Initialize();
			graph.GetMinDistance(1, 3);

			Console.ReadLine();
		}
	}
}