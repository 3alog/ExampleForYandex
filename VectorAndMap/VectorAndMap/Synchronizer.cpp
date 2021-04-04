#include "Synchronizer.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

void Synchronizer::synchronizeVectorAndMap(std::vector<int>& vectorInt, std::vector<std::pair<int, int>>& tempVector)
{
	int vectorIterator = 0;
	int mapIterator = 0;

	while (vectorIterator < vectorInt.size() && mapIterator < tempVector.size())
	{
		if (vectorInt[vectorIterator] == tempVector[mapIterator].second)
		{
			++mapIterator;
			++vectorIterator;
			continue;
		}
		if (vectorInt[vectorIterator] > tempVector[mapIterator].second)
		{
			tempVector.erase(tempVector.begin() + mapIterator);
			continue;
		}
		vectorInt.erase(vectorInt.begin() + vectorIterator);
	}

	int sizeDifference = 0;
	sizeDifference = vectorInt.size() - tempVector.size();
	if (sizeDifference < 0)
		sizeDifference *= -1;

	if (vectorInt.size() > tempVector.size())
	{
		vectorInt.erase(vectorInt.end() - sizeDifference, vectorInt.end());
		return;
	}
	tempVector.erase(tempVector.end() - sizeDifference, tempVector.end());
}
