#ifndef LEVEL_SELECT_MENU_H_INCLUDED
#define LEVEL_SELECT_MENU_H_INCLUDED

	
#include "menu.h"


class TLevelSelectMenu : public TMenu{

private:

public:


	
	TLevelSelectMenu();
	~TLevelSelectMenu();
	void ActionButton();
	void BackButton();
	void Initialize();
	void DelayAction();
	void Update();



};


#endif