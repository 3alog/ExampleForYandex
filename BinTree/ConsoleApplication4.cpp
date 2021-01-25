#include <iostream>
#include <vector>
#include <ctime>
#include "Algorithms.h"
using namespace std;



int main()
{
	bool isCycleTrue = true;
	bool isTreeExist = false;
	bin_tree* tree = nullptr;

	while (isCycleTrue)
	{
		int choice;
		cout << "What do you want to do?\n" <<
			"(1) Create Tree\n" <<
			"(2) Find summary parents of tops\n" <<
			"(3) Show Map of Tree\n" <<
			"(4) Delete Top in Tree\n" <<
			"(5) Find Amount of knots befor number\n" <<
			"(0) To stop the programm\n> ";
		cin >> choice;
		switch (choice)
		{
		case(1):
			if (isTreeExist)
				deleteTree(tree);
			createBinTree(tree);
			if (tree == nullptr)
				isTreeExist = false;
			else
				isTreeExist = true;
			break;
		case(2):
			if (isTreeExist)
			{
				findSumOfParentsTops(tree, 0);
			}
			else
				cout << "Your Tree isn't existing\n";
			break;
		case(3):
			if (isTreeExist)
			{
				showTree(tree, 1);
			}
			else
				cout << "Your Tree isn't existing\n";
			break;
		case(4):
			if (isTreeExist)
			{
				deleteTopInTree(tree, typeNum(messageDeleteTop));
				if (tree == nullptr)
				{
					isTreeExist = false;
				}
			}
			else
				cout << "Your Tree isn't existing\n";
			break;
		case(5):
			if (isTreeExist)
			{
				findAmountOfParents(tree, typeNum(messageFindAmountOfKnots), -1);
			}
			else
				cout << "Your Tree isn't existing\n";
			break;
		case(0):
			isCycleTrue = false;
			break;
		default:
			cout << "You've typed a wrong number\n"; break;
		}
	}
		if (isTreeExist)
			deleteTree(tree);
	return EXIT_SUCCESS;
}