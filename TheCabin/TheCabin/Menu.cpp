#ifndef MENU_H
#include <iostream>
#include <string>
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "IL\il.h"
#include "AL\al.h"
#include "AL\alut.h"
#include "Menu.h"
#include "Buttons.h"
#endif

using namespace std;

Menu::Menu()
{
	mSize = 100; //menu size for the texture to show withing bounds
	
	x = 0;
	y = 0;
}

void Menu::initMenu()
{
	//handle to file for loading images

	ILuint file[2];

	for(int i = 0; i < 2; ++i)
	{
	
	glGenTextures(1, &texID[i]);

	//just like OpenGL, you need to specify how many images you want to generate

	ilGenImages(1, &file[i]);

	//tie the current image DevIL is working with handle

	ilBindImage(file[i]);

	//safty check

	bool success = ilLoadImage(("Content\\Menu\\tex" + std::to_string(i+1) + ".png").c_str());;

		if(success)
		{
			//convert the picel data into a usable format

			success = ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE);

			if(!success)
			{
				//if an image failed to load, exit out

				cerr << "Failed to load image via DevIL" << endl;
				glutLeaveMainLoop();
				return;
			}

			glBindTexture(GL_TEXTURE_2D, texID[i]);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

			//pull th necessary information from the image DevIL loaded and bind it to an OpenGL texture

			glTexImage2D(GL_TEXTURE_2D,0,ilGetInteger(IL_IMAGE_BPP), 
						 ilGetInteger(IL_IMAGE_WIDTH),
						 ilGetInteger(IL_IMAGE_HEIGHT),
						 0, ilGetInteger(IL_IMAGE_FORMAT),
						 GL_UNSIGNED_BYTE, ilGetData());

			//since we don't need the original image anymore, remove it from memory

			ilDeleteImages(1, &file[i]);
		}

	}

	//init buttons here
}