/*
Adrian Jimenez
HashNames.cpp
Bernstein Hash Function
05/18/2025
Description: Define HashName class functions, using 
D.J. Bernstein's function and incursion to avoid 
looping. Also using getline to read each file from 
the ifstream (reading) file methods of the fstream 
library.
*/

#include "HashNames.h"
#include <fstream>

int HashNames::djbHash(std::string data, int tableIndex, int index, int hashVal) {
    if (index >= data.length()) {
        return abs(hashVal % tableIndex); //if index greater than 53 slots, take absolute modulus
    }

    hashVal = (hashVal * 33) + static_cast<int>(data[index]); //data acts as a key
    return djbHash(data, tableIndex, index + 1, hashVal);
}

HashNames::HashNames(const std::string& filename) //overloaded constructor with file parameter
{
    std::ifstream filein(filename); //open file for Name File reading
    if (!filein) {
        std::cerr << "ERROR: Unable to open for writing" << std::endl;
        return;
    }

    hash(filein); //call hash function from hash constructor
}

int HashNames::hash(std::ifstream& file) {
    std::string name;
    while (std::getline(file, name)) { //get each name on line
        int index = djbHash(name, 53); // hash the name and create an index for it
        table[index].push_back(name);  // store hashed name at the hashed index
    }

    return 0;
}

void HashNames::printNames(int tableIndex, int index)
{
    if (tableIndex < 0 || tableIndex >= 53) {
        std::cout << "TableIndex out of range.\n";
        return;
    } //out of range error

    //index stores one or more names

    if (index == 0) {
        std::cout << tableIndex << ": ";
    }  //print first vector value

    if (index >= table[tableIndex].size()) {
        return; } // base case at end of vector

    std::cout << table[tableIndex][index] << ", "; //table[between0&53][amtofnames@index]
    printNames(tableIndex, index + 1); // reach hashed tableIndex and print each element in same hash tableIndex
}