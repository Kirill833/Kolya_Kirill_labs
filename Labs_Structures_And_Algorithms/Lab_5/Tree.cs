using System;
using System.Collections.Generic;

namespace Lab_5
{
	/// <summary>
	/// Класс дерева.
	/// </summary>
	class Tree : IComparable<Tree>
	{
		/// <summary>
		/// Максимальное количество дочерних узлов.
		/// </summary>
		public const int MAX_NUMBER_NODES = 2;

		/// <summary>
		/// Общее кол-во вершин.
		/// </summary>
		public static int CountNodes { get; private set; }

		private int _currentLvl;
		private List<Tree> _subTrees;
		private int _key;

		private Tree()
		{
			_subTrees = new List<Tree>();
		}

		/// <summary>
		/// Добавление узла по случайному ключу.
		/// </summary>
		/// <param name="tree">Добавляемый узел.</param>
		public string AddNode()
		{
			CountNodes++;
			string result = "Добавление случайного узла...\n";
			Tree findMatch = null;
			SearchNodeWithFreeSpace(ref findMatch);
			if (findMatch is null)
				return result + "Не удалось создать узел.";

			findMatch.CreateNewNode(this);
			return result + "Узел успешно добавлен.";
		}

		/// <summary>
		/// Добавление узла по выбранному ключу.
		/// </summary>
		/// <param name="key">Ключ.</param>
		public string AddNode(int key)
		{
			CountNodes++;
			string result = "Добавление узла по выбранному ключу...\n";
			bool isFind = false;
			Tree findNode = null;
			SearchNodeWithMatchKey(ref findNode, key, ref isFind);
			if (findNode is null)
				return result + "Не удалось добавить узел.";

			findNode._subTrees.Add(new Tree() { _key = key, _currentLvl = findNode._currentLvl + 1 });
			findNode._subTrees.Sort();

			return result + "Узел успешно добавлен.";
		}

		/// <summary>
		/// Удаление узла с одним дочерним узлом.
		/// </summary>
		public string RemoveNodeWithOneChild()
		{
			Tree findChildMatch = null;
			Tree findParentMatch = null;
			SearchParentNodeWithOneChild(ref findChildMatch, ref findParentMatch);

			if (findChildMatch is null || findParentMatch is null)
			{
				return "Удаление узла с одним дочерним узлом невозможно.";
			}
			else
			{
				findParentMatch._subTrees.Add(findChildMatch._subTrees[0]);
				findParentMatch._subTrees.Remove(findChildMatch);
				findParentMatch._subTrees.Sort();
				List<Tree> subsetTree = new List<Tree>() { findParentMatch, findParentMatch._subTrees[0], findParentMatch._subTrees[1] };
				subsetTree.Sort();

				Tree temp = findParentMatch;
				findParentMatch = subsetTree[1];
				subsetTree[1] = temp;

				subsetTree.Remove(findParentMatch);
				subsetTree.Sort();

				return $"Узел с ключом {findChildMatch._key} удалён.";
			}
		}

		/// <summary>
		/// Обход дерева.
		/// </summary>
		public void Display()
		{
			Console.WriteLine($"Уровень: {_currentLvl}, ключ: {_key}");
			foreach (Tree subTree in _subTrees)
				subTree.Display();
		}

		/// <summary>
		/// Поиск узла по ключу.
		/// </summary>
		/// <param name="key">Значение ключа.</param>
		/// <returns>Результат поиска.</returns>
		public string SearchKey(int key)
		{
			Tree findMatch = null;
			GetMatchingKey(ref findMatch, key);

			if (findMatch is null)
				return $"Ключ {key} не найден.";
			else
				return $"Ключ {key} найден.";
		}

		/// <summary>
		/// Поиск минимального ключа.
		/// </summary>
		/// <returns>Результат поиска.</returns>
		public string SearchMinKey()
		{
			int curMin = _key;
			GetMinKey(ref curMin);
			return $"Минимальный ключ = {curMin}.";
		}

		/// <summary>
		/// Создание нового дерева.
		/// </summary>
		/// <param name="numberNodes">Количество узлов.</param>
		/// <returns>Сбалансированное двоичное дерево.</returns>
		public static Tree InitializeNewTree(int numberNodes)
		{
			CountNodes = 0;
			// Максимальный уровень узлов дерева.
			int maxLvl = (int)(Math.Log(numberNodes, 2));
			int rootKey = 10000 * numberNodes;
			Tree root = new Tree() { _key = rootKey };
			List<Tree> parents = new List<Tree>();
			List<Tree> children = new List<Tree>();

			if (numberNodes > 0)
			{
				parents.Add(root);
				CountNodes++;
			}
			else
			{
				Console.WriteLine("Дерево с нулём вершин не может быть создано.");
				return null;
			}

			Console.WriteLine($"Текущий (кол-во вершин = {numberNodes}) максимальный уровень дерева: {maxLvl} (отсчёт с нуля).");
			for (int i = 0; i < maxLvl; i++)
			{
				children.AddRange(parents);
				parents.Clear();
				foreach (Tree child in children)
				{
					for (int j = 0; j < MAX_NUMBER_NODES; j++)
					{
						if (CountNodes != numberNodes)
						{
							CountNodes++;
							child.CreateNewNode(root);
							parents.Add(child._subTrees[j]);
						}
					}
				}
				children.Clear();
			}

			return root;
		}

		private void SearchNodeWithMatchKey(ref Tree matchingTree, int key, ref bool isFind)
		{
			if (_key <= key)
			{
				if (_subTrees.Count > 0)
				{
					if (_subTrees.Count == 2)
					{
						_subTrees[1].SearchNodeWithMatchKey(ref matchingTree, key, ref isFind);
					}
					else if (_subTrees[0]._key >= _key)
					{
						_subTrees[0].SearchNodeWithMatchKey(ref matchingTree, key, ref isFind);
					}
					else
					{
						if (!isFind)
						{
							matchingTree = this;
							isFind = true;
							return;
						}
					}
				}
				else
				{
					if (!isFind)
					{
						matchingTree = this;
						isFind = true;
						return;
					}
				}
			}
			else
			{
				if (_subTrees.Count == 2 || (_subTrees.Count == 1 && _subTrees[0]._key < _key))
				{
					_subTrees[0].SearchNodeWithMatchKey(ref matchingTree, key, ref isFind);
				}
				else
				{
					if (!isFind)
					{
						matchingTree = this;
						isFind = true;
						return;
					}
				}
			}

			return;
		}

		private void CreateNewNode(Tree root)
		{
			Random rnd = new Random();
			int newKey = 0;
			int maxDelta = 500;
			int minDelta = 100;
			int maxOnLvl = (int)(Math.Pow(2, _currentLvl + 1));
			double countPrevCurNodes = 0.0;

			for (int i = _currentLvl; i >= 0; i--)
				countPrevCurNodes += Math.Pow(2, i);

			int numberNodeOnLvl = CountNodes - (int)countPrevCurNodes;
			if (_subTrees.Count == 0)
			{
				if (numberNodeOnLvl <= maxOnLvl / 2)
				{
					do
					{
						maxDelta -= 1;
						minDelta += 1;
						newKey = rnd.Next(_key - maxDelta, _key - minDelta);
					} while (!(newKey < _key && newKey < root._key));
				}
				else
				{
					do
					{
						minDelta -= 1;
						maxDelta += 1;
						newKey = rnd.Next(_key - maxDelta, _key - minDelta);
					} while (!(newKey < _key && newKey >= root._key));
				}

				_subTrees.Add(new Tree() { _key = newKey, _currentLvl = _currentLvl + 1 });
			}
			else
			{
				if (numberNodeOnLvl <= maxOnLvl / 2)
				{
					do
					{
						maxDelta -= 1;
						newKey = rnd.Next(_key, _key + maxDelta);
					} while (!(newKey >= _key && newKey < root._key));
				}
				else
				{
					do
					{
						maxDelta += 1;
						newKey = rnd.Next(_key, _key + maxDelta);
					} while (!(newKey >= _key && newKey >= root._key));
				}

				_subTrees.Add(new Tree() { _key = newKey, _currentLvl = _currentLvl + 1 });
			}
		}

		private void SearchNodeWithFreeSpace(ref Tree matchingNode)
		{
			List<Tree> parents = new List<Tree>() { this };
			List<Tree> children = new List<Tree>();

			while (true)
			{
				for (int i = 0; i < parents.Count; i++)
				{
					if (parents[i]._subTrees.Count < MAX_NUMBER_NODES)
					{
						matchingNode = parents[i];
						return;
					}
					else
					{
						children.Add(parents[i]._subTrees[0]);
						children.Add(parents[i]._subTrees[1]);
					}
				}

				parents.Clear();
				parents.AddRange(children);
				children.Clear();
			}
		}

		private void GetMatchingKey(ref Tree matchingNode, int key)
		{
			if (_key == key)
			{
				matchingNode = this;
				return;
			}

			if (_key < key)
			{
				if (_subTrees.Count == 2)
					_subTrees[1].GetMatchingKey(ref matchingNode, key);
			}

			if (_subTrees.Count > 0)
				_subTrees[0].GetMatchingKey(ref matchingNode, key);
		}

		private void GetMinKey(ref int min)
		{
			foreach (Tree subTree in _subTrees)
			{
				if (subTree._key < min)
					min = subTree._key;

				subTree.GetMinKey(ref min);
			}
		}

		private void SearchParentNodeWithOneChild(ref Tree matchingNode, ref Tree matchingParentTree)
		{
			foreach (Tree subTree in _subTrees)
			{
				if (subTree._subTrees.Count == 1)
				{
					matchingNode = subTree;
					matchingParentTree = this;
					return;
				}

				subTree.SearchParentNodeWithOneChild(ref matchingNode, ref matchingParentTree);
			}
		}

		int IComparable<Tree>.CompareTo(Tree other)
		{
			return _key.CompareTo(other._key);
		}
	}
}