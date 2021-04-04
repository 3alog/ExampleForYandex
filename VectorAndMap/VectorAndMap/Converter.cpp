#include "Converter.h"
#include <map>
#include <vector>


void Converter::convertMapToVector(std::map<int, int>& mapVar, std::vector<std::pair<int, int>>& tempVec)
{
	for (auto el : mapVar)
		tempVec.push_back(std::make_pair(el.first, el.second));
	mapVar.clear();
}

void Converter::convertVectorToMap(std::vector<std::pair<int, int>>& tempVec, std::map<int, int>& mapVar)
{
	for (auto el : tempVec)
		mapVar.emplace(el.first, el.second);
	tempVec.clear();
}