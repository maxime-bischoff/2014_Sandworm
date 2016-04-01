#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED



class TMenu
{

	


public:

	enum EButtonType{
		EButtonType_Resume,
		EButtonType_Restart,	
		EButtonType_MainMenu,	
		EButtonType_NewGame,
		EButtonType_Continue,
		EButtonType_Back,
		EButtonType_Level,
		EButtonType_LevelSelect,
		EButtonType_Options,	
		EButtonType_Quit,	
	};



	struct TButton{
		char m_cName[32];
		EButtonType m_eButtonType;
		int m_iId;
		int m_iPreviousButton;
		int m_iNextButton;	
	


		#ifndef TFA_FRESH
				TGfxSprite * m_pTextSprite;
		#endif

	};


	char m_cNameMenu[32];

	unsigned int m_iSelectedColor;
	unsigned int m_iUnselectedColor;


	bool m_bUpAllowedToPressed;
	bool m_bDownAllowedToPressed;
	bool m_bUpJustPressed;
	bool m_bDownJustPressed;
	float m_fLastChangeTime;
	float m_fChangeDelay;

	bool m_bInteractionAllowed;

	int m_iSelectedMenu;


	bool m_bActionPressed;
	float m_fActionDelay;
	float m_fActionTime;


	int m_iMenuCount;
	TButton  m_tButtonList[10];
	

	#ifndef TFA_FRESH
		TGfxTexture * m_pBackgroundTexture;
		TGfxSprite * m_pBackgroundSprite;
	#endif


	TMenu(void);
	~TMenu(void);

	virtual void ActionButton(){ return; };
	virtual void BackButton(){ return; };


	void CreateMenu();
	void ResetSelected();
	virtual void Update();
	void CheckControls();
	void MakeActive();
	void Render();
	void DelayAction();



	void EnableInteraction(bool bValue);
	void Show(bool bValue);


private : 








};

#endif
