/*
Adrian Jimenez
main.cpp
Bernstein Hash Function
05/18/2025
Description: Use a for loop to display the
hashed contents of the name.txt file.
*/

#include "HashNames.h"
#include <iostream>

using namespace std;

int main() {
	HashNames hn("names.txt");

	for (int i = 0; i < 53; i++) {
		hn.printNames(i);
		cout << endl;
	} //display names, ordered 0-52

}