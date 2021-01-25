#pragma once
#include "Messanges.h"

struct bin_tree
{
	int numOfTop;
	bin_tree* left = nullptr;
	bin_tree* right = nullptr;
};

void catchTheTop(bin_tree* tree, int num, void (*func)(bin_tree* tree, int num));
void catchTheTop(bin_tree* tree, void (*func)(bin_tree* tree));
void deleteTree(bin_tree* tree);
void findSumOfParentsTops(bin_tree* tree, int sum);
void showTree(bin_tree* tree, int level);
void createNewTree(bin_tree*& tree, int num);
void putNumOnTop(bin_tree*& tree, int num);

void putNumOnTop(bin_tree*& tree, int num)
{
	tree = new bin_tree;
	tree->numOfTop = num;
};
void catchTheTop(bin_tree*& tree, int num, void (*func)(bin_tree*& tree, int num))
{
	if (tree != nullptr)
		func(tree, num);
}
void catchTheTop(bin_tree * tree, int num, void (*func)(bin_tree * tree, int num))
{
	if (tree != nullptr)
		func(tree, num);
}
void catchTheTop(bin_tree * tree, void (*func)(bin_tree * tree))
{
	if (tree != nullptr)
		func(tree);
}

void findSumOfParentsTops(bin_tree * tree, int sum)
{
	if (tree->left == nullptr && tree->right == nullptr)
	{
		cout << "Top, where number = " << tree->numOfTop << ", sum of parents = " << sum << endl;
		return;
	}
	sum += tree->numOfTop;
	catchTheTop(tree->left, sum, findSumOfParentsTops);
	catchTheTop(tree->right, sum, findSumOfParentsTops);
}

void findAmountOfParents(bin_tree* tree, int num, int amount)
{
	if (tree == nullptr) { return; }
	if (num == tree->numOfTop)
	{
		cout << "Amount of knots, before your number is " << amount << endl;
		return;
	}
	findAmountOfParents(tree->left, num, amount + 1);
	findAmountOfParents(tree->right, num, amount + 1);
}

void tempTop(bin_tree * &tree, bin_tree * treeSide)
{
	bin_tree* temp = treeSide;
	delete tree;
	tree = temp;
}

void connectTops(bin_tree * &tree)
{
	if (tree->left == nullptr && tree->right == nullptr)
	{
		delete tree;
		tree = nullptr;
		return;
	}
	else if (tree->left != nullptr)
	{
		bin_tree* ptr = nullptr;
		if (tree->right != nullptr)
		{
			ptr = tree->right;
		}
		tempTop(tree, tree->left);
		if (ptr)
		{
			tree->right = ptr;
		}
		return;
	}
	tempTop(tree, tree->right);
}

void equalTop(bin_tree * &tree, int num, void (*func)(bin_tree * &tree))
{
	if (num == tree->numOfTop)
	{
		func(tree);
	}
}

void deleteTopInTree(bin_tree * &tree, int num)
{
	equalTop(tree, num, connectTops);
	if (tree != nullptr)
	{
		catchTheTop(tree->left, num, deleteTopInTree);
		catchTheTop(tree->right, num, deleteTopInTree);
	}
}

void deleteTree(bin_tree * tree)
{
	catchTheTop(tree->left, deleteTree);
	catchTheTop(tree->right, deleteTree);
	delete tree;

}

void createNewTree(bin_tree * &tree, int num)
{
	if (tree == nullptr)
	{
		putNumOnTop(tree, num);
	}
	else if (tree->numOfTop > num)
	{
		createNewTree(tree->left, num);
	}
	else if (tree->numOfTop < num)
	{
		createNewTree(tree->right, num);
	}
}

int typeNum(void (*func)())
{
	int num;
	func();
	cin >> num;
	return num;
}

void createBinTree(bin_tree * &tree)
{
	tree = nullptr;
	while (true)
	{
		int num = typeNum(messageCreateTree);
		if (!num)
		{
			break;
		}
		createNewTree(tree, num);
	}
	return;
}

void showTree(bin_tree * tree, int level)
{
	if (tree)
	{
		showTree(tree->left, level + 1);
		for (int i = 0; i < level; i++) cout << "   ";
		cout << tree->numOfTop << endl;
		showTree(tree->right, level + 1);
	}
}