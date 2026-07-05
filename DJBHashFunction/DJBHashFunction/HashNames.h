/*
Adrian Jimenez
HashNames.h
Bernstein Hash Function
05/18/2025
Description: Declare HashName class functions and use a 
private vector from the STL to store each hashed elements.
Utilize D.J. Bernstein's slash function, without looping
through data, taking the hashcode, and using modulus to 
store in the hashtable.
*/

#pragma once
#ifndef HASHNAMES
#define HASHNAMES

#include <string>
#include <vector>
#include <iostream>

class HashNames {

private:
	std::vector<std::string> table[53];
	int djbHash(std::string data, int tablesize, int index = 0, int hashVal = 5381); //private hash function

public:
	HashNames(const std::string& filename); //overloaded constructor, calls hash(), takes an argument the name of the file to open. 
	int hash(std::ifstream &file); //takes file and hashes it
	void printNames(int tableIndex, int index = 0); //print names hashed by ordered index
};



#endif