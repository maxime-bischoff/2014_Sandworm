#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

class TPlayer;
class TWall;
#include "flib_vec2.h"

#ifndef TFA_FRESH
struct TGfxSprite;
#endif
class TColumn;
class TSandWorm;
class TArea;
class TOffering;
class TXML_TParser;


struct TCameraParam{
	float fScale;

};

class TScene & GetCurrentScene();

class TScene
{
public:
	TCameraParam m_tCameraParam;
	void ClearScene();
	void Restart();

	
	void Initialize();
	bool Update();
	void Render();
	TScene(int iIdLevel);
	~TScene(void);

	static const int MAX_WALLS = 2000;
	static const int MAX_ColumnS = 30;
	static const int MAX_OFFERING = 20;
	static const int MAX_AREAS = 30;

	 TPlayer * m_pPlayer;	
	 TSandWorm * m_pSandWorm;	
	 TXML_TParser * m_pLevelParser;
	 TOffering * m_pOfferingList[MAX_OFFERING];
	 TArea * m_pAreaList[MAX_AREAS];
	 TWall * m_pWallList[MAX_WALLS];
	 TColumn * m_pColumnList[MAX_ColumnS];

	 int m_iIdlevel;

	 int m_iOfferingCount;
	 int m_iWallCount ;	
	 int m_iAreaCount ;
	 int m_iColumnCount ;
	 bool m_bParallaxEnabled;

	 	int m_iTotalEgg;

	 bool m_bCountdown;
	 float m_iCountDownTime;
	 float m_iStartDelay;



	 void MapLoad(int iIdMap);

	 
	void MapLoadTGA();
	void MapLoadXML();

	#ifdef TFA_FRESH
		void CreateColumns();
		void CreateOfferings();
	#endif
	

	 TGfxImage  * pImage_heightmap;
	 unsigned int * pData_heightmap;
	 TGfxVec2 m_tHeightMapSize;



	TGfxVec2 m_tMapSize;

	TGfxVec2 m_tMapSizeX;
	TGfxVec2 m_tMapSizeY;





	float m_fMiniMapScale;
	TGfxVec2 m_tMiniMapPos;


#ifndef TFA_FRESH
	TGfxSprite * m_pLineSprite;
	TGfxSprite * m_pMapLineSprite;
	TGfxSprite * m_pMiniMapLineSprite;
	TGfxSprite * m_pSpriteFPS;
	TGfxSprite * pScoreSprite;
	TGfxSprite * pTimerSprite;
	TGfxSprite * pWinSprite;
	TGfxSprite * pLoseSprite;
	
#endif

bool m_bFirstUpdate ;
	bool m_bLost;
	bool m_bWin;
	bool m_bStart;

	void Start(){
		m_bStart = true;
		iTimeStart = GfxTimeGetMilliseconds();	
	}

private:


	int iTimeStart;



	

};

#endif