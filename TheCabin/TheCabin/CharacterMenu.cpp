#ifndef CHARACTERMENU_H
#include "CharacterMenu.h"
#endif

CharacterMenu::CharacterMenu():Menu()
{

}

void CharacterMenu::initCharacterMenu()
{
	initMenu();
	//init buttons here
}

void CharacterMenu::drawCharacterMenu()
{
		glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texID[0]);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

	glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(-mSize + x, mSize + y);
		glTexCoord2f(0,1); glVertex2f(-mSize + x, -mSize + y);
		glTexCoord2f(1,1); glVertex2f(mSize + x, -mSize + y);
		glTexCoord2f(1,0); glVertex2f(mSize + x, mSize + y);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	//drawButtons here
}

void CharacterMenu::deleteCharacterMenu()
{
	
	for(int i = 0; i < 2; ++i)
	{
		//unloads the textures from memory
		glDeleteTextures(1,&texID[i]);
	}
	//delete buttons 

	//for(int j = 0; j < 3; ++j)
	//{
	//	//removes the buffer form memory
	//	alDeleteBuffers(1,&bufferID[j]);
	//	//removes the sound from memory
	//	slDeleteSources(1,&bgmusic);
	//	//allows ALUT to perform a clean exit
	//}
	//alutExit();
}