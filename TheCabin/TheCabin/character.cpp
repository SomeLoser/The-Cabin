//#ifndef CHARACTER_H
//#include "character.h"
//#endif
//
//Character::Character()
//{
//	name = cin.get();
//	BOUND = 100;
//}
//
//void Character::loadTexture()
//{
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(-BOUND, BOUND, -BOUND, BOUND, -BOUND, BOUND);
//
//	//enable access to the alpha channel
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	//handle to file for loading images
//	ILuint file;
//	glGenTextures(1, &faceOne);
//	//just like OpenGL, you need to specify how mnay images
//	//you want to generate
//	ilGenImages(1, &file);
//	//tie the current image DevIL is working with to a handle
//	ilBindImage(file);
//
//	//safety check
//	bool success = ilLoadImage("Content\\nullflag.png");
//	if(success)
//	{
//		//conver the pixel data into a usable format
//		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
//
//		if(!success)
//		{
//			//if an image failed to load, exit out
//			cerr << "Failed to load image via DevIL" << endl;
//			glutLeaveMainLoop();
//			return;
//		}
//
//		glBindTexture(GL_TEXTURE_2D, faceOne);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//		//pull th necessary information from the image DevIL loaded
//		//and bind it to an OpenGL texture
//		glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP),
//					 ilGetInteger(IL_IMAGE_WIDTH),
//					 ilGetInteger(IL_IMAGE_HEIGHT),
//					 0, ilGetInteger(IL_IMAGE_FORMAT),
//					 GL_UNSIGNED_BYTE, ilGetData());
//		//since we dont need the original image
//		//anymore, remove from memory
//		ilDeleteImages(1,&file);
//	}
//}