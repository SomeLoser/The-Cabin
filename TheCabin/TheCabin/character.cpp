#ifndef CHARACTER_H
#include "character.h"
#endif

Character::Character()
{
	name = "    ";
	BOUND = 100;
}

Character::~Character()
{

}

void Character::loadTexture()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-BOUND, BOUND, -BOUND, BOUND, -BOUND, BOUND);

	//enable access to the alpha channel
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//handle to file for loading images
	ILuint file[5];
	for(int i = 0; i < 5; ++i)
	{
		glGenTextures(1, &faceID[i]);
		//just like OpenGL, you need to specify how mnay images
		//you want to generate
		ilGenImages(1, &file[i]);
		//tie the current image DevIL is working with to a handle
		ilBindImage(file[i]);

		//safety check
		bool success = ilLoadImage(("Content\\Face\\face" + std::to_string(i+1) + ".png").c_str());
		
			if(success)
			{
				//convert the pixel data into a usable format
				success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

				if(!success)
				{
					//if an image failed to load, exit out
					cerr << "Failed to load image via DevIL" << endl;
					glutLeaveMainLoop();
					return;
				}

				glBindTexture(GL_TEXTURE_2D, faceID[i]);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
				//pull th necessary information from the image DevIL loaded
				//and bind it to an OpenGL texture
				glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP),
						 ilGetInteger(IL_IMAGE_WIDTH),
						 ilGetInteger(IL_IMAGE_HEIGHT),
						 0, ilGetInteger(IL_IMAGE_FORMAT),
						 GL_UNSIGNED_BYTE, ilGetData());
				//since we dont need the original image
				//anymore, remove from memory
				ilDeleteImages(1,&file[i]);
			}
	}
}

void Character::getName()
{
	cerr << "Enter you name: " << endl;
	name = cin.get();
	cerr << "Good luck, " << name << endl;
}

void Character::draw()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int x = -36;
	int y = -8;
	float w = 28;
	float h = 30;

	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, faceID[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor3f(0,1,0);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(-w + x, h + y);
		glTexCoord2f(0,1); glVertex2f(-w + x, -h + y);
		glTexCoord2f(1,1); glVertex2f(w + x, -h + y);
		glTexCoord2f(1,0); glVertex2f(w + x, h + y);
	glEnd();
	
	
	glDisable(GL_TEXTURE_2D);
}

void Character::destroy()
{
	for(int i = 0; i < 5; ++i)
	{
	//unload the texture from memory
	glDeleteTextures(1, &faceID[i]);
	}
}