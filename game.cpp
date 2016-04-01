#include "flib.h"
#include "flib_vec2.h"
#include "scene.h"
#include "main_menu.h"
#include "level_select_menu.h"
#include "popup_menu.h"


#include "game.h"

TScene *TGame::m_tScene  = new TScene(1); 
TMainMenu *TGame::m_pMainMenu  = new TMainMenu(); 
TLevelSelectMenu *TGame::m_pLevelSelectMenu  = new TLevelSelectMenu(); 
TPauseMenu * TGame::m_pPauseMenu = new TPauseMenu();
TGameOverMenu * TGame::m_pGameOverMenu = new TGameOverMenu();
TWinMenu * TGame::m_pWinMenu = new TWinMenu();
EGameState TGame::m_eGameState = GameState_MainMenu;
EGameState TGame::m_eGameStatePreparing = GameState_MainMenu;
bool TGame::m_bPause = false;
float TGame::m_fFadeValue = 1;
enum EFadeState TGame::m_eFadeState = EFadeState_FadingOut;
float TGame::m_fFadeDelay = 0.2f;

TGame::TGame(void)
{
	m_eGameState = GameState_MainMenu;
	

	//m_fFadeDelay = 2.0f;
	//m_fFadeValue = 0;
	//m_tMainMenu = new TMainMenu();
	//m_tScene = new TScene();
	//m_tScene = 0;
	//TScene tScene;

}




TGame::~TGame(void)
{
}

void TGame::GamePause()
{
//	m_bPause = true;
	m_eGameState =GameState_Pause;

	
#ifdef TFA_FRESH

	LuaCallGlobal(GfxFreshLuaState(), "Pause");

#endif
	m_pPauseMenu->MakeActive();

}

void TGame::SetGameOver()
{
	m_eGameState = GameState_GameOver;

	#ifdef TFA_FRESH
	LuaCallGlobal(GfxFreshLuaState(), "GameOver");
	#endif


	m_pGameOverMenu->MakeActive();

}

void TGame::GameWin(){

	m_eGameState = GameState_Win;
	m_pWinMenu->MakeActive();

	#ifdef TFA_FRESH
		LuaCallGlobal(GfxFreshLuaState(), "Succeed");

	#endif

}



 void  TGame::StartFadeIn(float fDelay){

	 m_eFadeState = EFadeState_FadingIn;
	 m_fFadeDelay = fDelay;
}
 void  TGame::StartFadeOut(float fDelay){
	 m_eFadeState = EFadeState_FadingOut;
	 m_fFadeDelay = fDelay; 
}

 void TGame::ToggleFade(float fDelay){

	 if(m_eFadeState ==  EFadeState_Black || m_eFadeState == EFadeState_FadingIn)
		 StartFadeOut(fDelay);
	 else StartFadeIn(fDelay);


}


void TGame::ExitScene(){

	if(m_tScene!=0)
	{
		delete m_tScene;
		m_tScene = 0;
	
	}
}



void TGame::Initialize(){

	#ifdef TFA_FRESH
		LuaCallGlobal(GfxFreshLuaState(), "LoadMenuMap");

	#endif


	m_pMainMenu->Initialize();
	m_pPauseMenu->Initialize();
	m_pGameOverMenu->Initialize();
	m_pWinMenu->Initialize();
	m_pLevelSelectMenu->Initialize();



//	m_tScene->Initialize();
}

void TGame::FadeUpdate()
{
	switch(m_eFadeState)
	{
		case EFadeState_FadingIn:

			m_fFadeValue +=   GfxTimeFrameGetCurrentDurationInSeconds() /m_fFadeDelay   ;

				if(m_fFadeValue >= 1)
				{
					m_fFadeValue = 1;
					m_eFadeState = EFadeState_Black;
				

			




				
				}

				#ifdef TFA_FRESH
					lua_pushnumber(GfxFreshLuaState(), m_fFadeValue);
					LuaCallGlobal(GfxFreshLuaState(), "FadePlane");
				#endif


			
			break;

		case EFadeState_FadingOut: 

				m_fFadeValue -=  GfxTimeFrameGetCurrentDurationInSeconds() /m_fFadeDelay  ;
			
				if(m_fFadeValue<=0)
				{
					m_fFadeValue = 0;
					m_eFadeState = EFadeState_Transluscent;
				
				
				}
				#ifdef TFA_FRESH
					lua_pushnumber(GfxFreshLuaState(), m_fFadeValue);
					LuaCallGlobal(GfxFreshLuaState(), "FadePlane");
				#endif
			break;

		case EFadeState_Black : 
		
			break;

		case EFadeState_Transluscent : 
			
			break;
	
	
	}

	
		
	




}


void TGame::Update()
{
	FadeUpdate();




		switch (m_eGameState)
		{	
		case GameState_Game:		m_tScene->Update();




									break;
	
		case GameState_MainMenu:	
									#ifdef TFA_FRESH
										LuaCallGlobal(GfxFreshLuaState(), "UpdateCameraMenu");
									#endif
									m_pMainMenu->Update();

									

									break;

		case GameState_Pause:		m_pPauseMenu->Update();
									break;

		case GameState_GameOver:	m_pGameOverMenu->Update();
									break;

		case GameState_Win :		m_pWinMenu->Update();
									break;

		case GameState_LevelSelect : 
									#ifdef TFA_FRESH
										LuaCallGlobal(GfxFreshLuaState(), "UpdateCameraMenu");
									#endif
										m_pLevelSelectMenu->Update();
									 break;

		default:		 			break;
		}


	


}

void TGame::Render(){

	switch (m_eGameState)
	{
	case GameState_Game:		m_tScene->Render();
								break;

	case GameState_MainMenu:	m_pMainMenu->Render();
								break;

	case GameState_Pause:		m_tScene->Render();
								m_pPauseMenu->Render();
								break;

	case GameState_GameOver:	m_tScene->Render();
								m_pGameOverMenu->Render();
								break;

	case GameState_Win :		m_tScene->Render();
								m_pWinMenu->Render();
								break;

	case GameState_LevelSelect : m_pLevelSelectMenu->Render();
								 break;

	default: 					break;

	}
	

}