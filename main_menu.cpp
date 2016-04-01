


#include "flib.h"
#include "flib_vec2.h"
#include "lua.h"
#include "luafunctions.h"
#include "game.h"
#include "scene.h"
#include "menu.h"
#include "level_select_menu.h"
#include "main_menu.h"

TMainMenu::TMainMenu()
{

}


TMainMenu::~TMainMenu()
{

}

void TMainMenu::BackButton()
{




}



void TMainMenu::ActionButton()
{
	switch (m_tButtonList[m_iSelectedMenu].m_eButtonType)
	{	
		case  EButtonType_NewGame : 

								TGame::m_eGameState = GameState_LevelSelect;
								TGame::m_pLevelSelectMenu->MakeActive();									
								Show(false);
							


			break;

		case  EButtonType_Options :

			break;

		case  EButtonType_Quit :  GfxExitRequest();
			
			break;


	default:
		break;
	}

	


}




void TMainMenu::Initialize()
{
	sprintf(m_cNameMenu, "MainMenu");
	m_iSelectedMenu = 0;


	sprintf(m_tButtonList[0].m_cName, "New Game");
	m_tButtonList[0].m_eButtonType = EButtonType_NewGame;
	m_tButtonList[0].m_iNextButton = 1;
	m_tButtonList[0].m_iPreviousButton = 1;



	sprintf(m_tButtonList[1].m_cName, "Controls");
	m_tButtonList[1].m_eButtonType = EButtonType_Options;
	m_tButtonList[1].m_iNextButton = 0;
	m_tButtonList[1].m_iPreviousButton = 0;
	/*
	sprintf(m_tButtonList[2].m_cName, "Quit");
	m_tButtonList[2].m_eButtonType = EButtonType_Quit;
	m_tButtonList[2].m_iNextButton = 0;
	m_tButtonList[2].m_iPreviousButton = 1;
	*/

	m_iMenuCount = 2;


	CreateMenu();
}

void TMainMenu::Update()
{
	if(TGame::GetStateFade() == EFadeState_Black && !m_bActionPressed)
	{
		TGame::StartFadeOut(1);		
	}

	CheckControls();

}