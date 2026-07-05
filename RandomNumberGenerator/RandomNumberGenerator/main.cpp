/*
Adrian Jimenez
main.cpp
Random Number Generator
03/15/2025
Description: Create Menu and test code with user-input
with options of integers or doubles, w or w/o a seed
*/
#include "Random.h"
#include <iostream>

using namespace std;

int main() {
	Random rand1; //Random class object to Generate Numbers
	int min, max; //declare user-input int variables
	double doubleMin, doubleMax;//declare user-input double variables
	int seed; //declare user-input seed
	char genKey; //declare generator menu option
	
	//Generator Menu
	do {
			cout << "1. Integer Generator" << endl;
		cout << "2. Integer(seed) Generator" << endl;
		cout << "3. Double Generator" << endl;
		cout << "4. Double(seed) Generator" << endl;
		cout << "5. Exit" << endl;
		cin >> genKey; //menu key

		
		switch (genKey) {
		case '1':
			cout << "Integer Generator: " << endl;
			cout << "Enter Int Minimum: " << endl;
			cin >> min;
			cout << "Enter Int Maximum: " << endl;
			cin >> max;
			rand1.setRange(min, max); //set user-inputted minimum and maximum
			if (!(min < 0 || max < 0 || max < min)) {
				cout << "Generated Integer: " << rand1.nextInteger().getValue() << endl;
			} //make sure numbers out of range aren't printed
			rand1.waitkey();
			break;

		case '2':
			cout << "Integer(seed) Generator: " << endl;
			cout << "Enter seed integer number: " << endl;
			cin >> seed;
			{

				Random rand2(seed); //Random object rand2 for seeds
				cout << "Enter Int Minimum: " << endl;
				cin >> min;
				cout << "Enter Int Maximum: " << endl;
				cin >> max;
				rand2.setRange(min, max); //set user-inputted minimum and maximum
				if (!(min < 0 || max < 0 || max < min)) {
					cout << "Generated Integer: " << rand2.nextInteger().getValue() << endl;
				} //make sure numbers out of range aren't printed
				rand2.waitkey();
			}
			break;

		case '3':
			cout << "Double Generator: " << endl;
			cout << "Enter Double Minimum: " << endl;
			cin >> doubleMin;
			cout << "Enter Double Maximum: " << endl;
			cin >> doubleMax;
			rand1.setRange(doubleMin, doubleMax); //set user-inputted minimum and maximum
			if (!(doubleMin < 0 || doubleMax < 0 || doubleMax < doubleMin)) {
				cout << "Generated Double: " << rand1.nextDouble().getValue() << endl;
			} //make sure numbers out of range aren't printed
			rand1.waitkey();
			break;

		case '4':
			cout << "Double(seed) Generator: " << endl;
			cout << "Enter seed integer number: " << endl;
			cin >> seed;
			{
				Random rand4(seed);
				cout << "Enter Double Minimum: " << endl;
				cin >> doubleMin;
				cout << "Enter Double Maximum: " << endl;
				cin >> doubleMax;
				rand4.setRange(doubleMin, doubleMax); //set user-inputted minimum and maximum
				if (!(doubleMin < 0 || doubleMax < 0 || doubleMax < doubleMin)) {
					cout << "Generated Double: " << rand4.nextDouble().getValue() << endl;
				} //make sure numbers out of range aren't printed
				rand4.waitkey();
			}
			break;

		case '5':
			cout << "Exit Successfully." << endl;
			break;

		default: 
			cout << "Invalid Option. Try Again." << endl;
			break;
		};

	} while (genKey != '5'); //stop loop when 5 is picked

	return 0;
}