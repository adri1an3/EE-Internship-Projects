/*
File: ElementLookup.cpp
Author: Adrian Jimenez
Description: Defines all of ElementLookup class members. Uses a breadth-first search
in numberLookup method
Date: December 9, 2025
*/

#include "ElementLookup.h"
#include "Queue.h"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>

void ElementLookup::parseCSV(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {

        std::stringstream ss(line);
        std::string name, symbol, weightStr, numberStr;

       
        if (std::getline(ss, name, ',') &&
            std::getline(ss, symbol, ',') &&
            std::getline(ss, numberStr, ',') &&
            std::getline(ss, weightStr, ','))
			//get all of Element's attributes
        {

            trim(name);
            trim(symbol);
            trim(weightStr);
            trim(numberStr);
			//trim strings of whitespaces

            if (!name.empty() && !symbol.empty() && !weightStr.empty() && !numberStr.empty())
            {
                try {
                    int atomicNum = std::stoi(numberStr); //convert atomic number strings to int
                    double atomicWeight = std::stod(weightStr); //convert atomic weight strings into double

                    periodicTable PT(name, symbol, atomicNum, atomicWeight); //store all of struct members
                    PTtree.insert(PT); //place periodic element onto tree.
                }
                catch (...) {
					//error handling
                }
            }
        }
    }
}

void ElementLookup::trim(std::string s)
{
	while (!s.empty() && (s.front() == ' ' || s.front() == '\t')) {
		s.erase(s.begin()); //Remove unwanted space or tab characters before and after reading each string (name, number)
	}
	while (!s.empty() && (s.back() == ' ' || s.back() == '\t')) {
		s.pop_back(); //remove spaces or tab chars
	}
}

std::string ElementLookup::numberLookup(const int number)
{
	if (!PTtree.getRoot()) return "Element not found.";

	Queue<AvlNode<periodicTable>*> q;
	q.enqueue(PTtree.getRoot()); //add tree Root onto quueue

	while (!q.isEmpty()) {
		AvlNode<periodicTable>* node = q.dequeue(); 

		if (node->Data.atomicNumber == number) {
			return "Atomic Number: " + std::to_string(node->Data.atomicNumber) +
				", Symbol: " + node->Data.symbol +
				", Name: " + node->Data.name +
				", Atomic Weight: " + std::to_string(node->Data.atomicWeight);
		} //if atomic number matches, display details

		if (node->left) q.enqueue(node->left); //if value of node doesn't match, add it's children
		if (node->right) q.enqueue(node->right); //keep iterating while queue not empty
	}

	return "Element not found.";
}

std::string ElementLookup::nameLookup(const std::string name)
{
	periodicTable temp;
	temp.name = name;

	AvlNode<periodicTable>* node = PTtree.getNode(temp); //find node that matches temp and set it to AvlNode object
	if (node != nullptr)
	{
		return "Atomic Number: " + std::to_string(node->Data.atomicNumber) +
			", Symbol: " + node->Data.symbol +
			", Name: " + node->Data.name +
			", Atomic Weight: " + std::to_string(node->Data.atomicWeight);
	} //return details

	return "Element not found.";
}