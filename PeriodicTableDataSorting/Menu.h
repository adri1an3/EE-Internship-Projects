/*
Adrian Jimenez
Menu.h
01/24/25
*/

#ifndef MENU
#define MENU

const int MAXCOUNT = 20;

struct menuItem {
	void (*func)();
	char description[50];
};

class Menu {
private:
	menuItem mi[MAXCOUNT];
	int count = 0;
	void runSelection();
public:
	Menu();
	void addMenu(const char* description, void(*f)());
	void runMenu();
};

#endif