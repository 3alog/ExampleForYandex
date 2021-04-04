#include "Printer.h"
#include <map>
#include <vector>
#include <iostream>

using namespace std;

void Printer::printVectorAndMap(std::vector<int> vecVar, std::map<int, int> mapVar)
{
	cout << "\nElements of vector: ";
	for (auto el : vecVar)
		cout << el << ' ';

	cout << "\nElements of map:\n";
	for (auto el : mapVar)
		cout << "Key: " << el.first << " Value: " << el.second << endl;
}
