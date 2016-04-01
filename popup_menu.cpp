#include "flib.h"
#include "flib_vec2.h"
#include "menu.h"
#include "luafunctions.h"
#include "lua.h"
#include "scene.h"

#include "game.h"
#include "main_menu.h"
#include "level_select_menu.h"


#include <cstring>
#include <cstdio>
#include "popup_menu.h"







// --------------------------------------------------------
// PAUSE MENU
// -------------------------------------------------------




TPauseMenu::TPauseMenu(void)
{


}
TPauseMenu::~TPauseMenu(void)
{


}




void TPauseMenu::Initialize()
{
	sprintf(m_cNameMenu, "PauseMenu");
	m_iSelectedMenu = 0;


	sprintf(m_tButtonList[0].m_cName, "Resume");
	m_tButtonList[0].m_eButtonType = EButtonType_Resume;
	m_tButtonList[0].m_iNextButton = 1;
	m_tButtonList[0].m_iPreviousButton = 3;


	sprintf(m_tButtonList[1].m_cName, "Restart");
	m_tButtonList[1].m_eButtonType = EButtonType_Restart;
	m_tButtonList[1].m_iNextButton = 2;
	m_tButtonList[1].m_iPreviousButton = 0;


	sprintf(m_tButtonList[2].m_cName, "Level Select");
	m_tButtonList[2].m_eButtonType = EButtonType_LevelSelect;
	m_tButtonList[2].m_iNextButton = 3;
	m_tButtonList[2].m_iPreviousButton = 1;


	sprintf(m_tButtonList[3].m_cName, "Quit");
	m_tButtonList[3].m_eButtonType = EButtonType_Quit;
	m_tButtonList[3].m_iNextButton = 0;
	m_tButtonList[3].m_iPreviousButton = 2;



	m_iMenuCount = 4;


	#ifndef TFA_FRESH
		m_pBackgroundTexture = GfxTextureLoad("menu_background.tga");
		m_pBackgroundSprite =  GfxSpriteCreate(m_pBackgroundTexture);
		GfxSpriteSetPosition(m_pBackgroundSprite, GfxGetDisplaySizeX()/2.0f- GfxSpriteGetSizeX(m_pBackgroundSprite)/2.0f, 0);
		

	#endif

	CreateMenu();

Show(false);
}

void TPauseMenu::Update()
{
	
	if( m_bActionPressed)DelayAction();
	CheckControls();

}


void TPauseMenu::BackButton()
{


}


void TPauseMenu::DelayAction(){


	if(m_fActionTime< m_fActionDelay)
	{
		m_fActionTime+= GfxTimeFrameGetCurrentDurationInSeconds();	
	}
	else{


		switch (m_tButtonList[m_iSelectedMenu].m_eButtonType   )
		{
		case EButtonType_Resume :  break;

		case EButtonType_Restart : 	TGame::m_eGameState = GameState_Game;   
									TGame::m_tScene->Restart();
									this->Show(false);	
									break;
					
		
		case EButtonType_LevelSelect : 
										TGame::m_eGameState = GameState_LevelSelect;
										TGame::m_pLevelSelectMenu->MakeActive();	
										TGame::ExitScene();
										this->Show(false);

										#ifdef TFA_FRESH
											LuaCallGlobal(GfxFreshLuaState(), "ClearScene");
											LuaCallGlobal(GfxFreshLuaState(), "LoadMenuMap");
										#endif



			break;

		case EButtonType_Quit : 	TGame::m_eGameState = GameState_MainMenu;
									TGame::m_pMainMenu->MakeActive();
									TGame::ExitScene();
									this->Show(false);

									#ifdef TFA_FRESH
										LuaCallGlobal(GfxFreshLuaState(), "ClearScene");
										LuaCallGlobal(GfxFreshLuaState(), "LoadMenuMap");
									#endif

			break;
		}	


}
}


void TPauseMenu::ActionButton()
{

	switch (m_tButtonList[m_iSelectedMenu].m_eButtonType   )
		{
		case EButtonType_Resume :  TGame::m_eGameState = GameState_Game;   
								this->Show(false);	

								#ifdef TFA_FRESH
										LuaCallGlobal(GfxFreshLuaState(), "Resume");
								#endif

								break;

		case EButtonType_Restart :		m_fActionDelay = 1.0f;
									    TGame::StartFadeIn(m_fActionDelay);
										EnableInteraction(false);
										m_bActionPressed = true;

										break;
					
		
		case EButtonType_LevelSelect :  m_fActionDelay = 1.0f;
									    TGame::StartFadeIn(m_fActionDelay);
										EnableInteraction(false);
										m_bActionPressed = true;
										break;

		case EButtonType_Quit : 	
									m_fActionDelay = 1.0f;
									TGame::StartFadeIn(m_fActionDelay);
									EnableInteraction(false);
									m_bActionPressed = true;
									break;
		}	
	}


	


// --------------------------------------------------------
// WIN MENU
// -------------------------------------------------------


TWinMenu::TWinMenu(void)
{
}

TWinMenu::~TWinMenu(void)
{
}




void TWinMenu::Initialize()
{
	
	sprintf(m_cNameMenu, "WinMenu");
	m_iSelectedMenu = 0;


	sprintf(m_tButtonList[0].m_cName, "Continue");
	m_tButtonList[0].m_eButtonType = EButtonType_Continue;
	m_tButtonList[0].m_iNextButton = 1;
	m_tButtonList[0].m_iPreviousButton = 3;


	sprintf(m_tButtonList[1].m_cName, "Restart");
	m_tButtonList[1].m_eButtonType = EButtonType_Restart;
	m_tButtonList[1].m_iNextButton = 2;
	m_tButtonList[1].m_iPreviousButton = 0;


	sprintf(m_tButtonList[2].m_cName, "Level Select");
	m_tButtonList[2].m_eButtonType = EButtonType_LevelSelect;
	m_tButtonList[2].m_iNextButton = 3;
	m_tButtonList[2].m_iPreviousButton = 1;


	sprintf(m_tButtonList[3].m_cName, "Quit");
	m_tButtonList[3].m_eButtonType = EButtonType_Quit;
	m_tButtonList[3].m_iNextButton = 0;
	m_tButtonList[3].m_iPreviousButton = 2;



	m_iMenuCount = 4;

	#ifndef TFA_FRESH
		m_pBackgroundTexture = GfxTextureLoad("menu_background.tga");
		m_pBackgroundSprite =  GfxSpriteCreate(m_pBackgroundTexture);
		GfxSpriteSetPosition(m_pBackgroundSprite, GfxGetDisplaySizeX()/2.0f- GfxSpriteGetSizeX(m_pBackgroundSprite)/2.0f, 0);


	#endif
		CreateMenu();

		Show(false);
}



void TWinMenu::Update()
{
	
	if( m_bActionPressed)DelayAction();


	

	CheckControls();

}






void TWinMenu::BackButton()
{


}


void TWinMenu::DelayAction(){


	if(m_fActionTime< m_fActionDelay)
	{
		m_fActionTime+= GfxTimeFrameGetCurrentDurationInSeconds();
	
	}
	else{


		switch (m_tButtonList[m_iSelectedMenu].m_eButtonType   )
		{
		case EButtonType_Continue :  break;

		case EButtonType_Restart : 	     TGame::m_tScene->Restart();
										 TGame::m_eGameState = GameState_Game;   
										 Show(false);
										break;
					
		
		case EButtonType_LevelSelect : 
										TGame::m_eGameState = GameState_LevelSelect;
										TGame::m_pLevelSelectMenu->MakeActive();									
										this->Show(false);

										#ifdef TFA_FRESH
											LuaCallGlobal(GfxFreshLuaState(), "ClearScene");
											LuaCallGlobal(GfxFreshLuaState(), "LoadMenuMap");
										#endif



			break;

		case EButtonType_Quit : 	TGame::m_eGameState = GameState_MainMenu;
									TGame::m_pMainMenu->MakeActive();
									TGame::ExitScene();
									this->Show(false);
									#ifdef TFA_FRESH
										LuaCallGlobal(GfxFreshLuaState(), "ClearScene");
										LuaCallGlobal(GfxFreshLuaState(), "LoadMenuMap");
									#endif

			break;
		}	

	
	}


}


void TWinMenu::ActionButton()
{
		switch (m_tButtonList[m_iSelectedMenu].m_eButtonType   )
		{
		case EButtonType_Continue : 
			TGame::m_tScene->Restart();
			 TGame::m_eGameState = GameState_Game;  
			 Show(false);
			break;

		case EButtonType_Restart:		m_fActionDelay = 1.0f;
									    TGame::StartFadeIn(m_fActionDelay);
										EnableInteraction(false);
										m_bActionPressed = true;

		case EButtonType_LevelSelect :  m_fActionDelay = 1.0f;
									    TGame::StartFadeIn(m_fActionDelay);
										EnableInteraction(false);
										m_bActionPressed = true;



			break;

		case EButtonType_Quit :			m_fActionDelay = 1.0f;
									    TGame::StartFadeIn(m_fActionDelay);
										EnableInteraction(false);
										m_bActionPressed = true;


			break;
		}	
}


	






// --------------------------------------------------------
// GAME OVER MENU
// -------------------------------------------------------




TGameOverMenu::TGameOverMenu(void)
{
}

TGameOverMenu::~TGameOverMenu(void)
{
}




void TGameOverMenu::Initialize()
{
	sprintf(m_cNameMenu, "GameOverMenu");
	m_iSelectedMenu = 0;


	sprintf(m_tButtonList[0].m_cName, "Restart");
	m_tButtonList[0].m_eButtonType = EButtonType_Restart;
	m_tButtonList[0].m_iNextButton = 1;
	m_tButtonList[0].m_iPreviousButton = 2;



	sprintf(m_tButtonList[1].m_cName, "Level Select");
	m_tButtonList[1].m_eButtonType = EButtonType_LevelSelect;
	m_tButtonList[1].m_iNextButton = 2;
	m_tButtonList[1].m_iPreviousButton = 0;


	sprintf(m_tButtonList[2].m_cName, "Quit");
	m_tButtonList[2].m_eButtonType = EButtonType_Quit;
	m_tButtonList[2].m_iNextButton = 0;
	m_tButtonList[2].m_iPreviousButton = 1;

	m_iMenuCount = 3;

	#ifndef TFA_FRESH
	//	m_pBackgroundTexture = GfxTextureLoad("menu_background.tga");
	//	m_pBackgroundSprite =  GfxSpriteCreate(m_pBackgroundTexture);
	//	GfxSpriteSetPosition(m_pBackgroundSprite, GfxGetDisplaySizeX()/2.0f- GfxSpriteGetSizeX(m_pBackgroundSprite)/2.0f, 0);	
	#endif

		CreateMenu();

		Show(false);
}



void TGameOverMenu::Update()
{



	if( m_bActionPressed)DelayAction();


	CheckControls();

}






void TGameOverMenu::BackButton()
{



}


void TGameOverMenu::DelayAction(){


	if(m_fActionTime< m_fActionDelay)
	{
		m_fActionTime+= GfxTimeFrameGetCurrentDurationInSeconds();
	
	}
	else{

		switch (m_tButtonList[m_iSelectedMenu].m_eButtonType   )
		{	

		case EButtonType_Restart :				TGame::m_eGameState = GameState_Game;   
												TGame::m_tScene->Restart();
												this->Show(false);	
											
										break;
					
		
		case EButtonType_LevelSelect : 
										TGame::m_eGameState = GameState_LevelSelect;
										TGame::m_pLevelSelectMenu->MakeActive();									
										this->Show(false);

										#ifdef TFA_FRESH
											LuaCallGlobal(GfxFreshLuaState(), "ClearScene");
											LuaCallGlobal(GfxFreshLuaState(), "LoadMenuMap");
										#endif



			break;

		case EButtonType_Quit : 	TGame::m_eGameState = GameState_MainMenu;
									TGame::m_pMainMenu->MakeActive();
									TGame::ExitScene();
									this->Show(false);
									#ifdef TFA_FRESH
										LuaCallGlobal(GfxFreshLuaState(), "ClearScene");
										LuaCallGlobal(GfxFreshLuaState(), "LoadMenuMap");
									#endif

			break;
		}	

	
	}


}



void TGameOverMenu::ActionButton()
{
		switch (m_tButtonList[m_iSelectedMenu].m_eButtonType   )
		{



		case EButtonType_Restart : 		m_fActionDelay = 1.0f;
									    TGame::StartFadeIn(m_fActionDelay);
										EnableInteraction(false);
										m_bActionPressed = true;
										break;

		case EButtonType_LevelSelect :	m_fActionDelay = 1.0f;
									    TGame::StartFadeIn(m_fActionDelay);
										EnableInteraction(false);
										m_bActionPressed = true;								
										break;

		case EButtonType_Quit :			m_fActionDelay = 1.0f;
									    TGame::StartFadeIn(m_fActionDelay);
										EnableInteraction(false);
										m_bActionPressed = true;								
										break;
		}	
}
	

