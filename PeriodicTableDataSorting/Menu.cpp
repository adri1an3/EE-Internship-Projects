/*
Menu.cpp
*/
#include <iostream>
#include <cstdlib>

using namespace std;

#include "Menu.h"

Menu::Menu()
	: count(0)
{

}

void Menu::addMenu(const char* Description, void(*f)(void)) {
	if (count < MAXCOUNT) {
		this->mi[count].func = f;
		strcpy_s(this->mi[count].description, Description);
		count++;
	}
}

void Menu::runMenu() {
	for (;;) {
		system("CLS");
		for (int i = 0; i < count; i++) {
			cout << this->mi[i].description << endl;
		}
		runSelection();
	}
}

void Menu::runSelection() {
	int select;
	cin >> select;
	if (select <= count) {
		this->mi[select - 1].func();

	}
}