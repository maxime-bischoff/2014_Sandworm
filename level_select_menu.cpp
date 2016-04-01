


#include "flib.h"
#include "flib_vec2.h"
#include "main_menu.h"
#include "scene.h"
#include "lua.h"

#include "game.h"
#include "menu.h"
#include "level_select_menu.h"



TLevelSelectMenu::TLevelSelectMenu(void)
{
}

TLevelSelectMenu::~TLevelSelectMenu(void)
{
}

void TLevelSelectMenu::Update()
{

	if(TGame::GetStateFade() == EFadeState_Black && !m_bActionPressed)
	{
		TGame::StartFadeOut(1);	
	
	}

	if( m_bActionPressed)DelayAction();


	CheckControls();

}


void TLevelSelectMenu::DelayAction(){


	if(m_fActionTime< m_fActionDelay)
	{
		m_fActionTime+= GfxTimeFrameGetCurrentDurationInSeconds();
	
	}
	else{


		switch (m_tButtonList[m_iSelectedMenu].m_eButtonType)
		{	
			case  EButtonType_Level : 	   TGame::m_eGameState = GameState_Game;
											TGame::m_tScene = new TScene(1);
											TGame::m_tScene ->Initialize();											


											this->Show(false);
											#ifdef TFA_FRESH
															
															LuaCallGlobal(GfxFreshLuaState(), "UnloadMenuMap");
											#endif 

	
	
			case  EButtonType_Back : break;
		}
	
	}


}


void TLevelSelectMenu::ActionButton()
{


	switch (m_tButtonList[m_iSelectedMenu].m_eButtonType)
	{	
		case  EButtonType_Level : 
									switch (m_iSelectedMenu)
									{
			
									case 0 : 		  
													
														TGame::StartFadeIn(0.5f);
														EnableInteraction(false);
														m_bActionPressed = true;
														m_fActionDelay = 0.5f;

									case 2 :  break;
									
									break;
			
			
									}
						


			break;

		case  EButtonType_Back : BackButton();
			break;

		

	default:
		break;
	}

	


}

void TLevelSelectMenu::BackButton()
{
	TGame::m_eGameState = GameState_MainMenu;

	TGame::m_pMainMenu->MakeActive();
	
	Show(false);
}


void TLevelSelectMenu::Initialize()
{
	sprintf(m_cNameMenu, "LevelSelectMenu");
	m_iSelectedMenu = 0;

	/*
	sprintf(m_tButtonList[0].m_cName, "Tutorial");
	m_tButtonList[0].m_eButtonType = EButtonType_Level;
	m_tButtonList[0].m_iNextButton = 1;
	m_tButtonList[0].m_iPreviousButton = 3;
	*/

	sprintf(m_tButtonList[0].m_cName, "Level 1 ");
	m_tButtonList[0].m_eButtonType = EButtonType_Level;
	m_tButtonList[0].m_iNextButton = 1;
	m_tButtonList[0].m_iPreviousButton = 2;


	sprintf(m_tButtonList[1].m_cName, "Level 2 ");
	m_tButtonList[1].m_eButtonType = EButtonType_Level;
	m_tButtonList[1].m_iNextButton = 2;
	m_tButtonList[1].m_iPreviousButton = 0;


	sprintf(m_tButtonList[2].m_cName, "Back");
	m_tButtonList[2].m_eButtonType = EButtonType_Back;
	m_tButtonList[2].m_iNextButton = 0;
	m_tButtonList[2].m_iPreviousButton = 1;



	m_iMenuCount = 3;


	CreateMenu();
	Show(false);

}







