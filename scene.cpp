#include "flib.h"
#include "flib_vec2.h"

#include "transform.h"
#include "collumn.h"
#include "collision.h"
#include "hitbox.h"
#include "player.h"
#include "sandworm.h"
#include "wall.h"
#include "area.h"
#include "lua.h"
#include "luafunctions.h"


#include "XML\TXML_Parser.h"
#include "XML\TSLL_Root.h"
#include "XML\TXML_Root.h"

#ifndef TFA_FRESH
#include "draw.h"
#endif
#include "game.h"

#include "offering.h"
#include "scene.h"


/*
TScene & GetCurrentScene()
{	
	static TScene tScene;
	return tScene;
}
*/

TScene::TScene(int iIdLevel)
{
	//	m_bParallaxEnabled = false;
	m_bLost = false;
	m_pLevelParser = 0;
	m_iIdlevel = iIdLevel;
	m_bFirstUpdate = true;
	
}


TScene::~TScene()
{

	ClearScene();
	if(m_pLevelParser !=0 ) delete m_pLevelParser;

	#ifndef TFA_FRESH
		if( (m_pMapLineSprite) != 0)GfxSpriteDestroy(m_pMapLineSprite);
		if( (m_pMiniMapLineSprite) != 0)GfxSpriteDestroy(m_pMiniMapLineSprite);
	#endif

}

void TScene::ClearScene()
{
	for(int i = 0; i <MAX_WALLS; i++)
	{
		if(m_pWallList[i] != 0)
		{		
			delete m_pWallList[i];
			m_pWallList[i] =0;		
		}	
	}
	m_iWallCount = 0;

	if(m_pPlayer!=0)   // Destruction du joueur
	{
		delete m_pPlayer;
		m_pPlayer = 0;
	}

	if(m_pSandWorm != 0 ) // Destruction du vers
	{
		delete m_pSandWorm;
		m_pSandWorm =0;
	}

	for(int i =0; i< MAX_ColumnS; i++)  // Destruction des obstacles
	{
		if(m_pColumnList[i] !=0)
		{
			delete m_pColumnList[i];
			m_pColumnList[i] = 0;

		}	
	}

	m_iColumnCount =0;		


	for(int i =0; i<MAX_AREAS; i++) // Destruction des zones d'effets
	{
	
		if(m_pAreaList[i] != 0)
		{
			delete m_pAreaList[i];
			m_pAreaList[i] = 0;		
		}	
	}
	m_iAreaCount = 0;


	for(int i =0; i<MAX_OFFERING; i++) // Destructions des éléments de collectes
	{	
		if(m_pOfferingList[i] != 0)
		{
			delete m_pOfferingList[i];
			m_pOfferingList[i] = 0;		
		}	
	}
	m_iOfferingCount = 0;



	m_bLost = false;
	m_bWin = false;
	m_bStart = false;



#ifndef TFA_FRESH

	//if( (pImage_heightmap) != 0) GfxImageDestroy(pImage_heightmap);
	if( (m_pLineSprite) != 0)GfxSpriteDestroy(m_pLineSprite);

	if( (m_pSpriteFPS) != 0)GfxSpriteDestroy(m_pSpriteFPS);
	if( (pScoreSprite) != 0)GfxSpriteDestroy(pScoreSprite);
	if( (pWinSprite)   != 0)GfxSpriteDestroy(pWinSprite);
	if( (pTimerSprite) != 0)GfxSpriteDestroy(pTimerSprite);
	if( (pLoseSprite) != 0)GfxSpriteDestroy(pLoseSprite);
	

#endif



}



#ifdef TFA_FRESH

void TScene::CreateColumns(){



	for(int i = 0; i<m_iColumnCount; i++)
	{
		
		lua_pushnumber(GfxFreshLuaState(), m_pColumnList[i]->Position().x);
		lua_pushnumber(GfxFreshLuaState(), -m_pColumnList[i]->Position().y);
		lua_pushnumber(GfxFreshLuaState(), m_pColumnList[i]->Rotation());
		LuaCallGlobal(GfxFreshLuaState(), "CreateColumn");	
	}
}


void TScene::CreateOfferings(){



	for(int i = 0; i<m_iOfferingCount; i++)
	{
		
		lua_pushnumber(GfxFreshLuaState(), m_pOfferingList[i]->Position().x);
		lua_pushnumber(GfxFreshLuaState(), -m_pOfferingList[i]->Position().y);
		lua_pushnumber(GfxFreshLuaState(), m_pOfferingList[i]->Rotation());
		lua_pushboolean(GfxFreshLuaState(), m_pOfferingList[i]->IsStarter());
		LuaCallGlobal(GfxFreshLuaState(), "CreateOffering");	
	}
}

#endif


void TScene::Restart(){
	ClearScene();

	m_pPlayer = new TPlayer(TGfxVec2(0,0), 0);

	m_pSandWorm = new  TSandWorm(TGfxVec2 (0,0), 0);

	m_iTotalEgg = -1;

	m_pLevelParser->ExtractXML();	




	m_bCountdown = true;
	m_iCountDownTime = 0;

	#ifndef TFA_FRESH
		m_pLineSprite = GfxLineSpriteCreate();
	
		m_pSpriteFPS =  GfxTextSpriteCreate();
		pWinSprite = GfxTextSpriteCreate();
		pLoseSprite = GfxTextSpriteCreate();
		pTimerSprite = GfxTextSpriteCreate();
		pScoreSprite = GfxTextSpriteCreate();	
	#endif

	m_pSandWorm->Initialize();

		
	m_bLost = false;
	m_bWin = false;
	m_bStart = false;


	#ifdef TFA_FRESH
		LuaCallGlobal(GfxFreshLuaState(), "Restart");
	#endif

}



void  TScene::Initialize()
{	
	m_iStartDelay = 0.5f;
	m_iCountDownTime = 0;
	m_bCountdown = true;

	m_tCameraParam.fScale = 1.4f;
	m_iWallCount = 0;
	m_iAreaCount = 0;
	m_iColumnCount = 0;
	m_iOfferingCount = 0;

	m_fMiniMapScale = 0.5f;
	m_tMiniMapPos = TGfxVec2(65,225);

	for (int i = 0; i< MAX_WALLS; i++)
	{
		m_pWallList[i] = 0;	
	}

	for (int i = 0; i< MAX_AREAS; i++)
	{
		m_pAreaList[i] = 0;	
	}

	for (int i = 0; i< MAX_ColumnS; i++)
	{
		m_pColumnList[i] = 0;	
	}

	for (int i = 0; i< MAX_OFFERING; i++)
	{
		m_pOfferingList[i] = 0;	
	}
	
	m_pPlayer = 0;
	m_pSandWorm = 0;


	

	m_iTotalEgg = -1;



	m_pPlayer = new TPlayer(TGfxVec2(0,0),0);
	m_pSandWorm = new  TSandWorm(TGfxVec2 (0,0), 0);

	
	
	m_pSandWorm->Initialize();
		

	
	m_bLost = false;
	m_bWin = false;
	m_bStart = false;



		#ifndef TFA_FRESH
			m_pSpriteFPS =  GfxTextSpriteCreate();
			m_pLineSprite = GfxLineSpriteCreate();
			m_pMapLineSprite = GfxLineSpriteCreate();
			m_pMiniMapLineSprite = GfxLineSpriteCreate();

			pWinSprite = GfxTextSpriteCreate();
			GfxTextSpritePrintf(pWinSprite, "Victory");

			GfxSpriteSetFilteringEnabled(pWinSprite, false);
			GfxSpriteSetScale(pWinSprite, 2.0f,2.0f);
			GfxSpriteSetPosition(pWinSprite,GfxGetDisplaySizeX()/2.0f - GfxSpriteGetSizeX(pWinSprite)/2.0f , GfxGetDisplaySizeY() /2.0f);

			pLoseSprite = GfxTextSpriteCreate();
			GfxTextSpritePrintf(pLoseSprite, "You have been eaten by \n       Vernando");

			GfxSpriteSetFilteringEnabled(pLoseSprite, false);
			GfxSpriteSetScale(pLoseSprite, 2.0f,2.0f);
			GfxSpriteSetPosition(pLoseSprite,GfxGetDisplaySizeX()/2 - GfxSpriteGetSizeX(pLoseSprite) +10.0f, GfxGetDisplaySizeY()/2.0f);
			pScoreSprite = GfxTextSpriteCreate();	
			GfxSpriteSetPosition(pScoreSprite,GfxGetDisplaySizeX()/2.0f -50.0f , GfxGetDisplaySizeY() - 15.0f);

			pTimerSprite = GfxTextSpriteCreate();		
			GfxSpriteSetPosition(pTimerSprite,20.0f , 20.0f);
		#endif


			if(m_pLevelParser == 0) m_pLevelParser = new TXML_TParser();

			MapLoad(m_iIdlevel);

			m_pLevelParser->ExtractXML();

			#ifdef TFA_FRESH
			//	CreateColumns();
				//CreateOfferings();
				
					
			#endif

		#ifndef TFA_FRESH
		DrawMap(m_pMapLineSprite, this);
		DrawMiniMap(m_pMiniMapLineSprite, this);
		GfxSpriteSetPosition( m_pMiniMapLineSprite,  m_tMiniMapPos.x,m_tMiniMapPos.y);
	//	GfxSpriteSetScale(m_pMapLineSprite, tCameraParam.fScale, tCameraParam.fScale);
		#endif



	
		#ifdef TFA_FRESH
		InitLuaFunctions();
		#endif

}









bool TScene::Update()
{
	


	if(m_bFirstUpdate == true)
	{
	
#ifdef TFA_FRESH

			CreateColumns();
			CreateOfferings();

#endif

			m_bFirstUpdate = false;
	}

	if (TGame::GetStateFade() ==  EFadeState_Black )
	{
		TGame::StartFadeOut(0.5f);
		return true;
	}else if (	TGame::GetStateFade() == EFadeState_FadingOut)
		return true;


	if(m_bCountdown)
	{
		m_iCountDownTime+= GfxTimeFrameGetCurrentDurationInSeconds();

		if(m_iCountDownTime <m_iStartDelay){
			#ifndef TFA_FRESH
				GfxLineSpriteReset(m_pLineSprite);
				DrawScene(this);
			#endif


			#ifdef TFA_FRESH

				LuaCallGlobal(GfxFreshLuaState(), "UpdateCamera");
				m_pPlayer->SendDataToFresh();
				m_pSandWorm->SendDataToFresh();
			#endif



		
		return true;
		}else{
			m_bCountdown = false;		
		}	
	}



	if(GfxInputIsJustPressed(EGfxInputID_AnyPadStart) ||  GfxInputIsJustPressed( EGfxInputID_KeyCharP)){
	
		TGame::GamePause();
	
	}

	



	if(m_pPlayer->GetState() == Dead) m_bLost = true;
	

	if(m_bLost){
	
		TGame::SetGameOver();
	
	return true;
	}



	if(m_pPlayer->GetEggCount()>=m_iTotalEgg){m_bWin =true;}
	

	if(m_bWin){
		TGame::GameWin();
	}




	m_pPlayer->Update(this);
	m_pSandWorm->Update(this);
		



	#ifndef TFA_FRESH
		GfxTextSpritePrintf(m_pSpriteFPS, "FPS : %f", GfxTimeFrameGetCurrentFPS());;
	#endif


	m_tCameraParam.fScale = m_pPlayer->GetScaleCameraValue();



	// *************************************************************************************************** //
	// --------------- UPDATE DES ELEMENTS DE LA SCENE --------------------------------------------------//
	// *************************************************************************************************** //
	


	for(int i=0; i<MAX_AREAS; i++)
	{	
		if(m_pAreaList[i] != 0 )
		{	
			if(!m_pAreaList[i]->Update())
			{
				delete m_pAreaList[i];
				m_pAreaList[i] = 0;
				m_iAreaCount --;			
			}		
		}
	}

	for(int i=0; i<MAX_ColumnS; i++)
	{	
		if(m_pColumnList[i] != 0 )
		{	
			m_pColumnList[i]->Update();
			
		}
	}

	for(int i=0; i<MAX_OFFERING; i++)
	{	
		if(m_pOfferingList[i] != 0 )
		{	
			if(!m_pOfferingList[i]->Update())
			{

				if(m_pOfferingList[i]->IsStarter())Start();

				delete m_pOfferingList[i];
				m_pOfferingList[i] = 0;
				m_iOfferingCount --;			
			}		
		}
	}


	// *************************************************************************************************** //
	// --------------- COLLISIONS -----------------------------------------------------------------------//
	// *************************************************************************************************** //
	
	
	for(int i=0; i< m_pSandWorm->GetTailCount(); i++)
	{
		if(m_pSandWorm->m_tTailList[i].pTransform !=0)
		{
			float fDistance = (m_pPlayer->Position() - m_pSandWorm->m_tTailList[i].pTransform->Position()).SquaredLength();
			if(fDistance <40.0f)
			{
				TCollideResult tResult;
				tResult = Collide(m_pPlayer, m_pSandWorm->m_tTailList[i].pTransform);

				if(tResult.fLength != 0)
					m_pPlayer->CollideWorm(tResult);

				if(m_pSandWorm->m_tTailList[i].pBody !=0)
				{

						tResult = Collide(m_pPlayer, m_pSandWorm->m_tTailList[i].pBody);

					if(tResult.fLength != 0)
						m_pPlayer->CollideWorm(tResult);
				}
			}		
		}
	}


	for (int i = 0; i< MAX_AREAS; i++)
	{
		if(m_pAreaList[i] !=0)
		{
			if(!m_pAreaList[i]->IsPreparing())
			{

				float fDistance = (m_pPlayer->Position() - m_pAreaList[i]->Position()).SquaredLength();
				if(fDistance <7.0f)
				{
					TCollideResult tResult;
					tResult = Collide(m_pPlayer, m_pAreaList[i]);

					if(tResult.fLength != 0)
			
						m_pPlayer->CollideRock(tResult);			
				}
			}
		}
	}



	for(int i = 0; i<m_iColumnCount;i++)
	{	
		if(m_pColumnList[i]!=0)
		{

			if(!m_pColumnList[i]->IsDestroyed())
			{
				float fDistance = (m_pPlayer->Position() - m_pColumnList[i]->Position()).SquaredLength();
				if(fDistance <8.0f)
				{
					TCollideResult tResult;
					tResult = Collide(m_pPlayer, m_pColumnList[i]);

					if(tResult.fLength != 0)
			
						m_pPlayer->CollideRock(tResult);			
				}


				fDistance = (m_pSandWorm->Position() - m_pColumnList[i]->Position()).SquaredLength();
				if(fDistance <60.0f)
				{
					TCollideResult tResult;
					tResult = Collide(m_pSandWorm, m_pColumnList[i]);

					if(tResult.fLength != 0){

						m_pSandWorm->CollideColumn(tResult, i);

							
					}
				}



			}


		}
	}

	for(int i = 0; i<m_iWallCount;i++)	{
	
		if(m_pWallList[i]!=0)
		{
			float	 fDistance = (m_pSandWorm->Position() - m_pWallList[i]->Position()).SquaredLength();
			if(fDistance <4000.0f)
			{
				TCollideResult tResult;
				tResult = Collide(m_pSandWorm, m_pWallList[i]);

				if(tResult.fLength != 0)
					m_pSandWorm->CollideWall(tResult);
			}


		
		}
	}


	#ifdef TFA_FRESH

		LuaCallGlobal(GfxFreshLuaState(), "UpdateCamera");
		m_pPlayer->SendDataToFresh();
		m_pSandWorm->SendDataToFresh();
	#endif


	if(m_bStart){

	#ifndef TFA_FRESH

	GfxTextSpritePrintf(pScoreSprite, "Score : %d  / %d",m_pPlayer->GetEggCount(), m_iTotalEgg);
	GfxTextSpritePrintf(pTimerSprite, " %d:%d:%d  ",  ((GfxTimeGetMilliseconds() - iTimeStart)/1000) / 60,((GfxTimeGetMilliseconds() - iTimeStart)/1000) % 60 ,((GfxTimeGetMilliseconds() - iTimeStart )/10)%100 );

	#endif
	}
	#ifndef TFA_FRESH
	GfxLineSpriteReset(m_pLineSprite);
	DrawScene(this);
	#endif

	return true;
}

void TScene::Render()
{


	#ifndef TFA_FRESH



	
	GfxSpriteRender(m_pMapLineSprite);

	GfxSpriteRender(m_pLineSprite);
	GfxSpriteRender(m_pMiniMapLineSprite);
	//GfxSpriteRender(m_pSpriteFPS);
	if(m_bStart){
	GfxSpriteRender(pTimerSprite);
	GfxSpriteRender(pScoreSprite);
	}

	if(m_bWin)GfxSpriteRender(pWinSprite);
	if(m_bLost)GfxSpriteRender(pLoseSprite);

	#endif
}


void TScene::MapLoad(int iIdMap)
{
	

	switch (iIdMap)
	{

	case 1 :		{
							m_pLevelParser->DoXML("maps/level1.xml");
					

					#ifdef TFA_FRESH	
					lua_pushfstring(GfxFreshLuaState(), "Resources/level1.pak");

					#ifdef PSP
					lua_pushfstring(GfxFreshLuaState(), "PSP");
					#else 
					lua_pushfstring(GfxFreshLuaState(), "PC");
					#endif

					LuaCallGlobal(GfxFreshLuaState(), "LoadLevel");
					#endif
				
					break;
					}
	
	default: break;
	}




}


void TScene::MapLoadXML(){

		//MapLoadTGA();
	//return;


	m_pLevelParser->DoXML("maps/level1.xml");
	
	#ifdef TFA_FRESH
		lua_pushfstring(GfxFreshLuaState(), "Resources/level1.pak");
		LuaCallGlobal(GfxFreshLuaState(), "LoadLevel");

	#endif


	
//#ifdef TFA_FRESH
	pImage_heightmap = GfxImageLoad("maps/map1_heightmap.tga");
	  pData_heightmap = GfxImageGetData(pImage_heightmap);
	  m_tHeightMapSize.x = static_cast<float>(GfxImageGetSizeX(pImage_heightmap)) ;
	  m_tHeightMapSize.y = static_cast<float>( GfxImageGetSizeY(pImage_heightmap)) ;

	  if(pImage_heightmap !=0){
	//	  GfxImageDestroy(pImageHeightmap);
		//  pImageHeightmap = 0;
	  
	  }

	







}


void TScene::MapLoadTGA(){
	
	



	TGfxImage *pMap = GfxImageLoad("maps/map3.tga");

	int iSizeX = GfxImageGetSizeX(pMap);
	int iSizeY = GfxImageGetSizeY(pMap);	
	unsigned int *pData = GfxImageGetData(pMap);
	if(pMap !=0){

	}



//#ifdef TFA_FRESH
	pImage_heightmap = GfxImageLoad("maps/map1_heightmap.tga");
	  pData_heightmap = GfxImageGetData(pImage_heightmap);
	  m_tHeightMapSize.x = static_cast<float>(GfxImageGetSizeX(pImage_heightmap)) ;
	  m_tHeightMapSize.y = static_cast<float>( GfxImageGetSizeY(pImage_heightmap)) ;

	  if(pImage_heightmap !=0){
	//	  GfxImageDestroy(pImageHeightmap);
		//  pImageHeightmap = 0;
	  
	  }

	

//#endif

	float fSizeBox = 1.5f;

	float fMaxSizeX = 0;
	float fMaxSizeY = -300;
	float fPosX =0;
	float fPosY = 0;

	const unsigned int WALL = EGfxColor_Black;
	const unsigned int WALL_UR = EGfxColor_Green;
	const unsigned int WALL_DR = GfxColor(255,0,255,255);		
	const unsigned int WALL_DL = GfxColor(255,255,0,255);
	const unsigned int WALL_UL = GfxColor(0,255,255,255);
	const unsigned int Column = GfxColor(255,120,0,255);
	const unsigned int PLAYER = EGfxColor_Blue;
	const unsigned int SANDWORM = EGfxColor_Red;
	const unsigned int OFFERING = GfxColor(127,127,127,255);
	const unsigned int START = GfxColor(50,50,50,255);


	int iBoucle  = iSizeX * iSizeY;
	for(int i = 0; i< iBoucle ; i++)
	{

		switch (pData[i])
		{
		case PLAYER : 
						this->m_pPlayer->Position(TGfxVec2 (i%iSizeX * (fSizeBox + fSizeBox) ,-( i/iSizeX * (fSizeBox + fSizeBox) ) ) );
						m_pPlayer->SetSpawnPosition(m_pPlayer->Position());
					break;
		case SANDWORM : 
					this->m_pSandWorm->Position(TGfxVec2 (i%iSizeX * (fSizeBox + fSizeBox) ,-( i/iSizeX * (fSizeBox + fSizeBox)  ) ));
					
					break;

		case WALL			: 
					fPosX = ( i%iSizeX) * (fSizeBox + fSizeBox) ;
					fPosY = ( i/iSizeX ) * (fSizeBox + fSizeBox);

					if(fPosX> fMaxSizeX) fMaxSizeX = fPosX;
					if(fPosY> fMaxSizeY) fMaxSizeY = fPosY;
					//break;
					m_pWallList[m_iWallCount] =  new TWall( TGfxVec2(fSizeBox, fSizeBox), TGfxVec2(fPosX , -fPosY),0, EGfxColor_White, 0);
					m_pWallList[m_iWallCount]->AddHitBox(TGfxVec2(fSizeBox,fSizeBox),TGfxVec2(0,0));


					m_iWallCount++;

						#ifdef TFA_FRESH
					
						lua_pushnumber(GfxFreshLuaState(), fPosX);
						lua_pushnumber(GfxFreshLuaState(), fPosY);
						lua_pushnumber(GfxFreshLuaState(), fSizeBox);
						lua_pushnumber(GfxFreshLuaState(), fSizeBox);
						lua_pushnumber(GfxFreshLuaState(), 0);
						LuaCallGlobal(GfxFreshLuaState(), "CreateWall");
						#endif
					

					break;

		case WALL_UL : 	fPosX = ( i%iSizeX) * (fSizeBox + fSizeBox) ;
						fPosY = -( i/iSizeX ) * (fSizeBox + fSizeBox);

						if(fPosX> fMaxSizeX) fMaxSizeX = fPosX;
						if(fPosY> fMaxSizeY) fMaxSizeY = fPosY;

						m_pWallList[m_iWallCount] =  new TWall( TGfxVec2(fSizeBox, fSizeBox), TGfxVec2(fPosX , fPosY),0, EGfxColor_Green,1);
						m_pWallList[m_iWallCount]->AddHitBox(TGfxVec2(fSizeBox,fSizeBox),TGfxVec2(0,0), 1);
						m_iWallCount++;
						break;


		case WALL_UR : 	fPosX = ( i%iSizeX) * (fSizeBox + fSizeBox) ;
						fPosY = -( i/iSizeX ) * (fSizeBox + fSizeBox);

						if(fPosX> fMaxSizeX) fMaxSizeX = fPosX;
						if(fPosY> fMaxSizeY) fMaxSizeY = fPosY;

						m_pWallList[m_iWallCount] =  new TWall( TGfxVec2(fSizeBox, fSizeBox), TGfxVec2(fPosX , fPosY),0, EGfxColor_Green,2);
						m_pWallList[m_iWallCount]->AddHitBox(TGfxVec2(fSizeBox,fSizeBox),TGfxVec2(0,0), 2);
						m_iWallCount++;
						break;

		case WALL_DR : 	fPosX = ( i%iSizeX) * (fSizeBox + fSizeBox) ;
						fPosY =- ( i/iSizeX ) * (fSizeBox + fSizeBox);

						if(fPosX> fMaxSizeX) fMaxSizeX = fPosX;
						if(fPosY> fMaxSizeY) fMaxSizeY = fPosY;

						m_pWallList[m_iWallCount] =  new TWall( TGfxVec2(fSizeBox, fSizeBox), TGfxVec2(fPosX , fPosY),0, EGfxColor_Green,3);
						m_pWallList[m_iWallCount]->AddHitBox(TGfxVec2(fSizeBox,fSizeBox),TGfxVec2(0,0), 3);
						m_iWallCount++;
						break;
		case WALL_DL : 	fPosX = ( i%iSizeX) * (fSizeBox + fSizeBox) ;
						fPosY = -( i/iSizeX ) * (fSizeBox + fSizeBox);

						if(fPosX> fMaxSizeX) fMaxSizeX = fPosX;
						if(fPosY> fMaxSizeY) fMaxSizeY = fPosY;

						m_pWallList[m_iWallCount] =  new TWall( TGfxVec2(fSizeBox, fSizeBox), TGfxVec2(fPosX , fPosY),0, EGfxColor_Green,4);
						m_pWallList[m_iWallCount]->AddHitBox(TGfxVec2(fSizeBox,fSizeBox),TGfxVec2(0,0), 4);
						m_iWallCount++;
						break;
	
		case Column:	if(m_iColumnCount <MAX_ColumnS)
						{			
							fPosX = ( i%iSizeX) * (fSizeBox + fSizeBox) ;
							fPosY =- ( i/iSizeX ) * (fSizeBox + fSizeBox);

							if(fPosX> fMaxSizeX) fMaxSizeX = fPosX;
							if(fPosY> fMaxSizeY) fMaxSizeY = fPosY;

							m_pColumnList[m_iColumnCount] =  new TColumn(  TGfxVec2(fPosX , fPosY),0.0f, 0.8f,  GfxColor(150,70,0,255) , m_iColumnCount);

							#ifdef TFA_FRESH
					
								lua_pushnumber(GfxFreshLuaState(), fPosX);
								lua_pushnumber(GfxFreshLuaState(), -fPosY);								
								LuaCallGlobal(GfxFreshLuaState(), "CreateColumn");

							#endif

							
							m_iColumnCount++;
						}

						break;
			
		case OFFERING:	if(m_iOfferingCount <MAX_OFFERING)
						{			
							fPosX = ( i%iSizeX) * (fSizeBox + fSizeBox) ;
							fPosY = -( i/iSizeX ) * (fSizeBox + fSizeBox);

							if(fPosX> fMaxSizeX) fMaxSizeX = fPosX;
							if(fPosY> fMaxSizeY) fMaxSizeY = fPosY;

							m_pOfferingList[m_iOfferingCount] =  new TOffering(  TGfxVec2(fPosX , fPosY),0, 1.0f,  GfxColor(255,70,198,255), false, false);
							
							m_iOfferingCount++;
							m_iTotalEgg++;
						}

						break;

		case START:	if(m_iOfferingCount <MAX_OFFERING)
						{			
							fPosX = ( i%iSizeX) * (fSizeBox + fSizeBox) ;
							fPosY =- ( i/iSizeX ) * (fSizeBox + fSizeBox);

							if(fPosX> fMaxSizeX) fMaxSizeX = fPosX;
							if(fPosY> fMaxSizeY) fMaxSizeY = fPosY;

							m_pOfferingList[m_iOfferingCount] =  new TOffering(  TGfxVec2(fPosX , fPosY),0, 1.0f,  GfxColor(255,70,198,255), true, true);
							
							m_iOfferingCount++;
						}

						break;
		



		default : break;
		}
	
	
	
	}

	GfxImageDestroy(pMap);

	m_tMapSize.x = fMaxSizeX;
	m_tMapSize.y = fMaxSizeY;
#ifndef TFA_FRESH
	DrawMap(m_pMapLineSprite, this);
	DrawMiniMap(m_pMiniMapLineSprite, this);
	GfxSpriteSetPosition( m_pMiniMapLineSprite,  m_tMiniMapPos.x,m_tMiniMapPos.y);
//	GfxSpriteSetScale(m_pMapLineSprite, tCameraParam.fScale, tCameraParam.fScale);
#endif

}
