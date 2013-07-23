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
	string name;
	float BOUND;
	GLuint faceID[5];

	void draw();
	void loadTexture();
	void update(int value);
	void saveToFile();
	void loadFromFile();
	void destroy();
	void getName();



};

#endif