#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <algorithm>
#include "Printer.h"
#include "Converter.h"
#include "Synchronizer.h"

#define RAND 1 + rand() % 9
#define MAX_ERASE_ITEM 15

using namespace std;

void pushRandomElements(vector<int>& vectorInt, map<int, int>& mapInt, int i)
{
	for (int it = 0; it < i; it++)
	{
		vectorInt.push_back(RAND);
		mapInt.emplace(it, RAND);
	}
}

int setMaxEraseIterator(int i)
{
	if (i <= MAX_ERASE_ITEM)
		return 1 + rand() % i;
	return 1 + rand() % MAX_ERASE_ITEM;
}

void eraseRandomElements(vector<int>& vectorInt, map<int, int>& mapInt, int maxEraseIterator)
{
	for (int it = 0; it < maxEraseIterator; it++)
	{
		auto vecIt = vectorInt.begin();
		vecIt += rand() % vectorInt.size();
		vectorInt.erase(vecIt);

		auto mapIt = mapInt.begin();
		for (int j = 0; j < rand() % mapInt.size(); j++)
			mapIt++;
		mapInt.erase(mapIt);
	}
}

void sortVectorAndMap(vector<int>& vectorInt, vector<pair<int, int>>& tempVector)
{
	sort(vectorInt.begin(), vectorInt.end());
	sort(tempVector.begin(), tempVector.end(), [](
		pair<int, int>& vec1,
		pair<int, int>& vec2
		)
		{
			return vec1.second < vec2.second;
		});
}

int inputNumber()
{
	string inputString;
	bool flag = true;
	while (flag)
	{
		flag = false;
		cout << "The number should be greater than 0\nType a size of vector and map > ";
		getline(cin, inputString);
		for (size_t i = 0; i < inputString.size(); ++i)
		{
			if (ispunct(inputString[i]) || !isdigit(inputString[i]))
			{
				cout << "The input is wrong\nTry again\n";
				flag = true;
				break;
			}
		}
	}
	return stoul(inputString);
}

int main()
{
	srand(time(0));

	Printer printer;
	Converter converter;
	Synchronizer synchronizer;
	vector<int> vectorInt;
	map<int, int> mapInt;
	vector<pair<int, int>> tempVector;
	int i = 0;

	i = inputNumber();

	pushRandomElements(vectorInt, mapInt, i);
	printer.printVectorAndMap(vectorInt, mapInt);
	eraseRandomElements(vectorInt, mapInt, setMaxEraseIterator(i));
	cout << "\nSome elemets were erased" << endl;
	printer.printVectorAndMap(vectorInt, mapInt);
	converter.convertMapToVector(mapInt, tempVector);
	sortVectorAndMap(vectorInt, tempVector);
	synchronizer.synchronizeVectorAndMap(vectorInt, tempVector);
	converter.convertVectorToMap(tempVector, mapInt);
	cout << "\nVector and Map were synchronized" << endl;
	printer.printVectorAndMap(vectorInt, mapInt);
	return 0;
}