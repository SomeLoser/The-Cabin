#ifndef BUTTONS_H
#include "Buttons.h"
#endif

Buttons::Buttons()
{
	hover = false;
	x = 0;
	y = 0;
	bSize = 15;
}

void Buttons::draw()
{
	glPushMatrix();

	if(hover = true)
	{
		glColor3f(1,0,1);
	}

	glColor3f(0,1,1);
	glBegin(GL_QUADS);			   
		glVertex2f(x - bSize, y + bSize);
		glVertex2f(x - bSize, y - bSize);
		glVertex2f(x + bSize, y - bSize);
		glVertex2f(x + bSize, y + bSize);
	glEnd();

	glPopMatrix();
}

bool Buttons::collideWith(int x, int y)
{
	float left = this -> x - bSize;
	float right = this -> x + bSize;
	float top = this -> y + bSize;
	float bottom = this -> y - bSize;

	return(x >= left && x <= right &&
		   y >= bottom && y <= top);
}