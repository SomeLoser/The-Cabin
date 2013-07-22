#ifndef MENU_H
#define MENU_H

#include "GL\freeglut.h"

class Menu
{
public:
	Menu();
	
	void drawMenu();
	void initMenu();

	int mSize;
	int x;
	int y;
	GLuint texID[2];

};
#endif