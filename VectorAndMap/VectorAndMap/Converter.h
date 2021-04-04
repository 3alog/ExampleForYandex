#pragma once
#include <map>
#include <vector>
class Converter
{
public:
	void convertMapToVector(std::map<int, int>& mapVar, std::vector<std::pair<int, int>>& tempVec);
	void convertVectorToMap(std::vector<std::pair<int, int>>& tempVec, std::map<int, int>& mapVar);
};

