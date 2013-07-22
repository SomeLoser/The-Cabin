#ifndef CHARACTERMENU_H
#define CHARACTERMENU_H


#include "Menu.h"

class CharacterMenu : public Menu
{
public:
	CharacterMenu();

	void initCharacterMenu();
	void drawCharacterMenu();
	void deleteCharacterMenu();
};
#endif