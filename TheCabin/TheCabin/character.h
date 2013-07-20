#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <string>
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "IL\il.h"
#include "AL\al.h"
#include "AL\alut.h"

using namespace std;

class Character
{
public:
	Character();
	~Character();
	string hair[3];
	string eyes[3];
	string face[3];
	string mouth[3];
	string name;
	float BOUND;
	GLuint faceOne;
	GLuint faceTwo;

	void draw();
	void loadTexture();
	void update(int value);
	void saveToFile();
	void loadFromFile();


};

#endif