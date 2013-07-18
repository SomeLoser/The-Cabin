#ifndef BUTTONS_H
#define BUTTONS_H

#include "GL\freeglut.h"

class Buttons
{
public:
	Buttons();
	void draw();
	bool collideWith(int x, int y);
	int x;
	int y;
	int bSize;
	bool hover;
};
#endif