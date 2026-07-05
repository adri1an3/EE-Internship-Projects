/*
Adrian Jimenez
Random.cpp
Random Number Generator
03/15/2025
Description: Defines core functions of Random class
such as fillVect(),Random() constructors,
nextInt and nextDble with setRange() in both data types.
Calling shuffle() in nextInt() and nextDbl()
*/
#include "Random.h"
#include <algorithm>
#include <random>

int Random::usedCount = 0;

void Random::fillVect(double min, double max)
{
	numbers.clear(); //clear array for new array
	for (int i = 0; i < 250; i++) {
		double r = (((double)rand() / (double)RAND_MAX) * (max - min)) + min;
		numbers.push_back(r);
	}
}

void Random::shuffle() {
	static std::random_device rd;  // Generates a truly random seed
	static std::mt19937 rng(rd()); // Mersenne Twister PRNG (better than rand())

	std::shuffle(numbers.begin(), numbers.end(), rng);
}

Random::Random() {
	numbers.clear(); //clear array for new array
	usedCount = 0; //clear count
	fillVect(0, RAND_MAX); //set min/max
}

Random::Random(double min, double max) {
	numbers.clear(); //clear array for new array
	usedCount = 0; //clear count
	fillVect(min, max); //set min/max
}

Random::Random(Double min, Double max) {
	numbers.clear(); //clear array for new array
	usedCount = 0; //clear count
	fillVect(min.getValue(), max.getValue()); //set min/max
}

Random::Random(int seed) {
	numbers.clear(); //clear array for new array
	usedCount = 0; //clear count
	srand(seed); //use srand to set the seed of fillVect's rand()
	fillVect(0, RAND_MAX); //set min/max
}

int Random::nextInt()
{
	if (numbers.empty()) {
		fillVect(0, RAND_MAX); //if empty array, create random array
		int result = static_cast <int> (numbers.back()); //convert last array number into an int type
		numbers.pop_back(); //delete last number from array
		usedCount++; //add to count
		return result; //return last array number after deleting it
	}
	else if (usedCount >= numbers.size() * 0.9) {
		shuffle();
		usedCount = 0; // Reset counter
	}
	else {
		int result = static_cast <int> (numbers.back()); //convert last array number into an int type
	numbers.pop_back(); //delete last number from array
	usedCount++; //add to count
	return result; //return last array number after deleting it
	}
}

Integer Random::nextInteger() {
	return Integer(nextInt());
}

double Random::nextDbl() {
	if (numbers.empty()) {
		fillVect(0, RAND_MAX); //if empty array, create random array
		double result = static_cast <double> (numbers.back()); //convert last array number into a double type
		numbers.pop_back(); //delete last number from array
		usedCount++; //add to count
		return result; //return last array number after deleting it
	}
	else if (usedCount >= numbers.size() * 0.9) {
		shuffle();
		usedCount = 0; // Reset counter
	}
	else {
		double result = static_cast <double> (numbers.back()); //convert last array number into a double type
		numbers.pop_back(); //delete last number from array
		usedCount++; //add to count
		return result; //return last array number after deleting it
	}
}

Double Random::nextDouble()
{
	return Double(nextDbl());
}

void Random::setRange(double min, double max)
{
	if ((min < 0 || max < 0) || (max < min)) {
		std::cerr << "Error: Minimum or Maximum out of range. Cannot be less than 0 and min cannot be greater than max." << std::endl;
		waitkey();
		return;
	}
	else {
		fillVect(min, max);
	}
}

void Random::setRange(Double min, Double max) {
	if (min.getValue() < 0 || max.getValue() < 0) {
		std::cerr << "Error: Minimum or Maximum out of range. Cannot be less than 0 and min cannot be greater than max." << std::endl;
		waitkey(); //troubleshooting where maximum is less than minimum and/or negative numebrs
		return;
	}
	else {
		numbers.clear();
		fillVect(min.getValue(), max.getValue());
	}
}

void Random::waitkey() {
		std::cout << "Press Any key to continue ";
		std::cin.get(); //get user-input key
		std::cin.ignore(); //ignores buffer
		system("Cls"); //Clears screen
}