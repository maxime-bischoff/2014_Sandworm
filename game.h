#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

enum EGameState{
	GameState_Game,
	GameState_MainMenu,
	GameState_LevelSelect,
	GameState_Pause,
	GameState_GameOver,
	GameState_Win
};

enum EFadeState{
	EFadeState_FadingIn,
	EFadeState_FadingOut,
	EFadeState_Black,
	EFadeState_Transluscent,
	EFadeState

};


class TScene;
class TMainMenu;
class TPauseMenu;
class TGameOverMenu;
class TWinMenu;
class TLevelSelectMenu;

class TGame
{
public:
	void Initialize();
	void Update();
	void Render();
	static void GamePause();
	static void GameWin();
	static void SetGameOver();
	static void ExitScene();
	void FadeUpdate();
	static enum EFadeState   GetStateFade(){return m_eFadeState;};
	static void  StartFadeIn(float fDelay);
	static void  StartFadeOut(float fDelay);
	static void  ToggleFade(float fDelay);



	TGame(void);
	~TGame(void);
	/*
	static TGame& Instance() {
		static TGame game;
		return game;
	  }
	  */

	 static TMainMenu * m_pMainMenu;
	 static TLevelSelectMenu * m_pLevelSelectMenu;
	 static TPauseMenu * m_pPauseMenu;
	 static TGameOverMenu * m_pGameOverMenu;
	 static TWinMenu * m_pWinMenu;
	 static TScene * m_tScene;
	 static EGameState m_eGameState;
	 static EGameState m_eGameStatePreparing;
private:


 static float m_fFadeValue;
 static float m_fFadeDelay;


 static enum EFadeState m_eFadeState;



	static bool m_bPause;

};

#endif