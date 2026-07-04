/*
File: ElementLookup.h
Author: Adrian Jimenez
Description: Declares all of ElementLookup class members.
Date: December 9, 2025
*/

#include "periodicTable.h"
#include "AVLTree.h"

class ElementLookup {
private: 
	AVLTree<periodicTable> PTtree;

public:
	void parseCSV(const std::string& filename);
	void trim(std::string s);
	std::string numberLookup(const int number);
	std::string nameLookup(const std::string name);
};