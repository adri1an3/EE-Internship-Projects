/*
File: main.cpp
Author: Adrian Jimenez
Description: Parses file, runs menu, and take user input.
Date: December 9, 2025
*/

#include <iostream>
#include "ElementLookup.h"
#include "Menu.h"

using namespace std;
ElementLookup* gElements; //global pointer to display function options.

void lookupByName(); //prototype global functions
void lookupByNumber();

int main() {
    ElementLookup myElements;
    gElements = &myElements; 

    myElements.parseCSV("periodicTable.csv");

    Menu menu;
    menu.addMenu("1. Lookup element by atomic number", lookupByNumber);
    menu.addMenu("2. Lookup element by name", lookupByName);
    menu.runMenu();

    return 0;
}

void lookupByName() {
    string name;
    cout << "Enter element name: ";
    cin >> name;
    cout << gElements->nameLookup(name) << endl;
    system("pause"); //wait for user response
}

void lookupByNumber() {
    int number;
    cout << "Enter atomic number: ";
    cin >> number;
    cout << gElements->numberLookup(number) << endl;
    system("pause"); //wait for user response
}