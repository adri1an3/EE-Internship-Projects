/*
File: periodicTable.h
Author: Adrian Jimenez
Description: Declares and defines all of periodicTable struct members.
Date: December 9, 2025
*/

#include <string>

#pragma once
#ifndef PERIODICTABLE
#define PERIODICTABLE

struct periodicTable {
	std::string name;
	std::string symbol;
	int atomicNumber;
	double atomicWeight;

	periodicTable() : name(""), symbol(""), atomicNumber(0), atomicWeight(0.0) {}

	periodicTable(std::string n, std::string s, int num, double weight)
		: name(n), symbol(s), atomicNumber(num), atomicWeight(weight) {
	}

	bool operator<(const periodicTable& other) const {
		return name < other.name;
	}

	bool operator>(const periodicTable& other) const {
		return name > other.name;
	}

	bool operator==(const periodicTable& other) const {
		return name == other.name;
	}
};



#endif