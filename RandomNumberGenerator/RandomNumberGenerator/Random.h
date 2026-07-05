/*
Adrian Jimenez
Random.h
Random Number Generator
03/15/2025
Description: Define member functions that the Random 
class will be using to generate numbers
*/
#pragma once
#ifndef RANDOM
#define RANDOM

#include <iostream>
#include <string>
#include <vector>
#include "Integer.h"
#include "Double.h"

class Random {
private:
	void fillVect(double min, double max); //Populates numbers with random doubles within the specified range.
	void shuffle(); //Shuffles the elements in numbers to ensure randomness.

public:
	//Data Members:
	std::vector<double> numbers; //Stores the generated random double values.
		
	//Constructors:
	Random(); //Default constructor.Fills numbers with random values in the range[0, RAND_MAX].
	Random(double min, double max); //Generates random numbers within the specified range of min and max.
	Random(Double min, Double max); //using the Double class for the range.Double refers to a user - defined class or a type alias for double.
	Random(int seed); // Seeds the random number generator and fills numbers in the range[0, RAND_MAX].
	
	//Member Functions:
	int nextInt(); //Returns the next number in the vector as an int.
	Integer nextInteger(); //Returns the next number as an Integer, a user - defined class or a type alias representing integer values.
	double nextDbl(); //Returns the next number as a primitive double.
	Double nextDouble(); //Returns the next number as a Double.Ensure that this method properly converts the primitive double value to a Double object or equivalent.
	void setRange(double min, double max); //Sets the range for random number generation, accepting either primitive doubles or Double objects.
	void setRange(Double min, Double max); //Sets the range for random number generation, accepting either primitive doubles or Double objects.
	
	static int usedCount; //track count of numbers popped

	static void waitkey();


};

#endif