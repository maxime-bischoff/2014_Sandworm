#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED


#include "flib.h"
#include "flib_vec2.h"
#include "transform.h"
#include "collumn.h"
#include "game.h"
#include "scene.h"
#include "player.h"
#include "functions.h"
#include "offering.h"
#include "const.h"
#include <math.h>


float gfScale = 1.4f; // Scale de la scene
float gfSize = 10.0f; // Nombre de pixels par metre
float gfSizeModifier = gfScale * gfSize;
TGfxVec2 gCamera;




void DrawOrientedCircle(TGfxSprite * pLineSprite, float fRadius,float fAngle,const TGfxVec2 & tPos, unsigned int iColor)
{
	//tPos.y *=-1;
	GfxLineSpriteSetDrawingColor(pLineSprite, iColor);

	GfxLineSpriteJumpTo(pLineSprite, tPos.x,tPos.y);	
	//float lvlDetail = ( (2*PI)  /  (2*PI*fRadius ) ) * 20.0f  ;	
	float detail = (1.0f/fRadius  );

	for(float angle= fAngle; angle<2.0f*PI +fAngle; angle+=detail)
	{		
		float iPosX =  cosf(angle) * fRadius+tPos.x ;	
		float iPosY =  - sinf(angle)* fRadius + tPos.y;		
		GfxLineSpriteLineTo(pLineSprite,iPosX,iPosY);
	
	}

	float iPosX =  cosf(fAngle) * fRadius+tPos.x ;	
		float iPosY =  - sinf(fAngle)* fRadius + tPos.y;		
		GfxLineSpriteLineTo(pLineSprite,iPosX,iPosY);


}

void DrawCircle(TGfxSprite * pLineSprite, float fRadius,  TGfxVec2  tPos, unsigned int iColor)
{
	

	GfxLineSpriteSetDrawingColor(pLineSprite, iColor);
	
	float iPosX =  1.0f * fRadius + tPos.x ;	
	float iPosY =  0.0f* fRadius + tPos.y;
	//float fAngle = 0.0f;
	GfxLineSpriteJumpTo(pLineSprite, iPosX,iPosY);	
	//float lvlDetail = (2*M_PI)  /  (2*M_PI*fRadius )  ;	

	//for(float angle= 0; angle<2*M_PI ; angle+=lvlDetail*10.0f)
	float detail = 1.0f/fRadius;
	for(float theta=0.0f; theta<6.28f; theta+=detail) 
	{		
		float iPosX =  cosf(theta) * fRadius +tPos.x ;	
		float iPosY =   sinf(theta)* fRadius + tPos.y;		
		GfxLineSpriteLineTo(pLineSprite,iPosX,iPosY);
	
	}

	//	GfxLineSpriteLineTo(pLineSprite,iPosX,iPosY);
}

void DrawScreenCircle(TGfxSprite * pLineSprite, float fRadius,  const TGfxVec2  & tPos, unsigned int iColor)
{
	
	

	GfxLineSpriteSetDrawingColor(pLineSprite, iColor);
	
	float iPosX =  1.0f * fRadius + tPos.x ;	
	float iPosY =  0.0f* fRadius + tPos.y;
	//float fAngle = 0.0f;
	GfxLineSpriteJumpTo(pLineSprite, iPosX,iPosY);	
	//float lvlDetail = (2*M_PI)  /  (2*M_PI*fRadius )  ;	

	//for(float angle= 0; angle<2*M_PI ; angle+=lvlDetail*10.0f)
	float detail = 1.0f/fRadius;
	for(float theta=0.0f; theta<6.28f; theta+=detail) 
	{		
		float iPosX =  cosf(theta) * fRadius +tPos.x ;	
		float iPosY =   sinf(theta)* fRadius + tPos.y;		
		GfxLineSpriteLineTo(pLineSprite,iPosX,iPosY);
	
	}

		GfxLineSpriteLineTo(pLineSprite,iPosX,iPosY);
}


void DrawPartialCircle(TGfxSprite * pLineSprite, float fRadius,float fAngle,float fRange,  const TGfxVec2 & tPos, unsigned int iColor)
{
	
	//tPos.y *= -1;
	GfxLineSpriteSetDrawingColor(pLineSprite, iColor);
	/*
	float iPosX =  sinf(0) * fRadius +tPos.x ;	
	float iPosY =   cosf(0)* fRadius + tPos.y;
	*/
	GfxLineSpriteJumpTo(pLineSprite, tPos.x,tPos.y);	
	float lvlDetail = (2*PI)  /  (2*PI*fRadius )  ;	

	for(float angle= fAngle - fRange/2; angle < fAngle+ fRange/2 ; angle+=lvlDetail)
	{		
		float iPosX =  cosf(angle) * fRadius+tPos.x ;	
		float iPosY =  - sinf(angle)* fRadius + tPos.y;		
		GfxLineSpriteLineTo(pLineSprite,iPosX,iPosY);
	
	}
	GfxLineSpriteLineTo(pLineSprite, tPos.x,tPos.y);


}


void DrawWeaponArea(TGfxSprite * pLineSprite, float fRadius,float fAngle,float fRange, const   TGfxVec2 & tPos, unsigned int iColor)
{
	
	fRadius *= gfSizeModifier;

	GfxLineSpriteSetDrawingColor(pLineSprite, iColor);
	
	float iPosX =  cosf(fAngle- fRange/2) * fRadius +tPos.x ;	
	float iPosY =   sinf(fAngle- fRange/2)* fRadius + tPos.y;
	
	GfxLineSpriteJumpTo(pLineSprite, iPosX,iPosY);	
	float lvlDetail = (2.0f*PI)  /  (2.0f*PI*fRadius )  ;	

	for(float angle= fAngle - fRange/2.0f; angle < fAngle+ fRange/2.0f ; angle+=lvlDetail)
	{		
		float iPosX =  cosf(angle) * fRadius+tPos.x ;	
		float iPosY =   sinf(angle)* fRadius + tPos.y;		
		GfxLineSpriteLineTo(pLineSprite,iPosX,iPosY);
	
	}
	//GfxLineSpriteLineTo(pLineSprite, tPos.x,tPos.y);


}

void DrawSword1(TGfxSprite * pLineSprite, float fRadius,float fAngle,float fRange, const  TGfxVec2 & tPos, unsigned int iColor)
{	
	
	fRadius *= gfSizeModifier;

	GfxLineSpriteSetDrawingColor(pLineSprite, iColor);
	
	float iPosX =  cosf(fAngle+ fRange/2.0f) * fRadius +tPos.x ;	
	float iPosY =   sinf(fAngle+ fRange/2.0f)* fRadius + tPos.y;
	


	
	GfxLineSpriteJumpTo(pLineSprite, iPosX,iPosY);	
	float lvlDetail = (2.0f*PI)  /  (2.0f*PI*fRadius )  ;	

	for(float angle =   fAngle+ fRange/2.0f ; angle > fAngle - fRange/2.0f ; angle-=lvlDetail)
	{		
	
		float iPosX =  cosf(angle) * fRadius+tPos.x ;	
		float iPosY =   sinf(angle)* fRadius + tPos.y;		
		GfxLineSpriteLineTo(pLineSprite,iPosX,iPosY);	
	}


	for(float angle= fAngle - fRange/2.0f; angle < fAngle+ fRange/2.0f ; angle+=lvlDetail)
	{		

			fRadius -=0.4f;
		float iPosX =  cosf(angle) * fRadius+tPos.x ;	
		float iPosY =   sinf(angle)* fRadius + tPos.y;		
		GfxLineSpriteLineTo(pLineSprite,iPosX,iPosY);	
	}

	

	GfxLineSpriteLineTo(pLineSprite,  iPosX, iPosY);

}

void DrawSword2(TGfxSprite * pLineSprite, float fRadius,float fAngle,float fRange, const  TGfxVec2 & tPos, unsigned int iColor)
{
	fRadius *= gfSizeModifier;

	GfxLineSpriteSetDrawingColor(pLineSprite, iColor);
	
	float iPosX =  cosf(fAngle- fRange/2.0f) * fRadius +tPos.x ;	
	float iPosY =   sinf(fAngle- fRange/2.0f)* fRadius + tPos.y;
	
	GfxLineSpriteJumpTo(pLineSprite, iPosX,iPosY);	
	float lvlDetail = (2.0f*PI)  /  (2.0f*PI*fRadius )  ;	

	for(float angle= fAngle - fRange/2.0f; angle < fAngle+ fRange/2.0f ; angle+=lvlDetail)
	{		
		float iPosX =  cosf(angle) * fRadius+tPos.x ;	
		float iPosY =   sinf(angle)* fRadius + tPos.y;		
		GfxLineSpriteLineTo(pLineSprite,iPosX,iPosY);	
	}

	for(float angle=   fAngle+ fRange/2.0f ; angle > fAngle - fRange/2.0f ; angle-=lvlDetail)
	{		
		fRadius -=0.4f;
		float iPosX =  cosf(angle) * fRadius+tPos.x ;	
		float iPosY =   sinf(angle)* fRadius + tPos.y;		
		GfxLineSpriteLineTo(pLineSprite,iPosX,iPosY);	
	}

	GfxLineSpriteLineTo(pLineSprite,  iPosX, iPosY);

}

void DrawPowerUp(TGfxSprite * pLineSprite, float fSize,float fAngle, const TGfxVec2  & tPos, unsigned int iColor)
{
	fSize *= gfSizeModifier;	

	
	const TGfxVec2 & tCenter = tPos;
	//const TGfxVec2 & tRadius = tRadius;

	GfxLineSpriteSetDrawingColor(pLineSprite, iColor);	

	//TGfxVec2 tCornerUR, tCornerDR, tCornerDL, tCornerUL;
	
	const TGfxVec2 tAxisX = TGfxVec2(cosf(fAngle),sinf(fAngle));
	const TGfxVec2 tAxisY = TGfxVec2(-sinf(fAngle),cosf(fAngle));


	GfxLineSpriteSetDrawingColor(pLineSprite, iColor);
	const TGfxVec2 tCornerU = tCenter + tAxisX + tAxisY * fSize;
	const TGfxVec2 tCornerR = tCenter + tAxisX * fSize - tAxisY ;
	const TGfxVec2 tCornerD = tCenter - tAxisX  - tAxisY * fSize;
	const TGfxVec2 tCornerL = tCenter - tAxisX * fSize + tAxisY ;
	
	GfxLineSpriteJumpTo(pLineSprite, tCornerU.x,	tCornerU.y);
	GfxLineSpriteLineTo(pLineSprite, tCornerR.x,	tCornerR.y);	
	GfxLineSpriteLineTo(pLineSprite, tCornerD.x,	tCornerD.y);	
	GfxLineSpriteLineTo(pLineSprite, tCornerL.x,	tCornerL.y);		
	GfxLineSpriteLineTo(pLineSprite, tCornerU.x,	tCornerU.y);	


}


void DrawReward(TGfxSprite * pLineSprite, float fSize,float fAngle, const  TGfxVec2 & tPos, unsigned int iColor)
{
	fSize *= gfSizeModifier;
	



	
	const TGfxVec2 & tCenter = tPos;
	//const TGfxVec2 & tRadius = tRadius;

	GfxLineSpriteSetDrawingColor(pLineSprite, iColor);
	

	//TGfxVec2 tCornerUR, tCornerDR, tCornerDL, tCornerUL;
	
	const TGfxVec2 tAxisX = TGfxVec2(cosf(fAngle),sinf(fAngle));
	const TGfxVec2 tAxisY = TGfxVec2(-sinf(fAngle),cosf(fAngle));


	GfxLineSpriteSetDrawingColor(pLineSprite, iColor);
	const TGfxVec2 tCornerU = tCenter + tAxisX + tAxisY * fSize;
	const TGfxVec2 tCornerR = tCenter + tAxisX * fSize/2.0f - tAxisY ;
	const TGfxVec2 tCornerD = tCenter - tAxisX  - tAxisY * fSize;
	const TGfxVec2 tCornerL = tCenter - tAxisX * fSize/2.0f + tAxisY ;
	
	GfxLineSpriteJumpTo(pLineSprite, tCornerU.x,	tCornerU.y);
	GfxLineSpriteLineTo(pLineSprite, tCornerR.x,	tCornerR.y);	
	GfxLineSpriteLineTo(pLineSprite, tCornerD.x,	tCornerD.y);	
	GfxLineSpriteLineTo(pLineSprite, tCornerL.x,	tCornerL.y);		
	GfxLineSpriteLineTo(pLineSprite, tCornerU.x,	tCornerU.y);	


}


void DrawShatteredCircle(TGfxSprite * pLineSprite, float fRadius,float fAngle,const  TGfxVec2 & tPos, unsigned int iColor)
{
	

	GfxLineSpriteSetDrawingColor(pLineSprite, iColor);

	GfxLineSpriteJumpTo(pLineSprite, tPos.x,tPos.y);	
	float lvlDetail = (2.0f*PI)  /  (2.0f*PI*fRadius )  ;	
	fAngle = 0;
	for(float angle= fAngle; angle<2.0f*PI +fAngle; angle+=lvlDetail)
	{		
		if(fmod(angle , 6.28f/7.0f) > 0.5)
		{
			
			float iPosX =  cosf(angle) * fRadius+tPos.x ;	
			float iPosY =   sinf(angle)* fRadius + tPos.y;		
			GfxLineSpriteLineTo(pLineSprite,iPosX,iPosY);
		}else{
			float iPosX =  cosf(angle) * fRadius+tPos.x ;	
			float iPosY =   sinf(angle)* fRadius + tPos.y;		
			GfxLineSpriteJumpTo(pLineSprite,iPosX,iPosY);



		}
	
	}


}




void DrawBox(TGfxSprite * pLineSprite, const TGfxVec2  & tRadius,float fAngle,const  TGfxVec2 & tPos, unsigned int iColor)
{

	if(fAngle ==0)
	{
	const TGfxVec2 & tCenter = tPos;
	//tPos.y *=-1;
	//const TGfxVec2 & tRadius = tRadius;

	GfxLineSpriteSetDrawingColor(pLineSprite, iColor);
	

	//TGfxVec2 tCornerUR, tCornerDR, tCornerDL, tCornerUL;
	
	//const TGfxVec2 tAxisX = TGfxVec2(cosf(fAngle),-sinf(fAngle));
	//const TGfxVec2 tAxisY = TGfxVec2(sinf(fAngle),cosf(fAngle));


	GfxLineSpriteSetDrawingColor(pLineSprite, iColor);
	const TGfxVec2 tCornerUR =TGfxVec2( tCenter.x  + tRadius.x ,tCenter.y + tRadius.y);
	const TGfxVec2 tCornerDR =TGfxVec2( tCenter.x  + tRadius.x ,tCenter.y - tRadius.y);
	const TGfxVec2 tCornerDL =TGfxVec2( tCenter.x  - tRadius.x ,tCenter.y - tRadius.y);
	const TGfxVec2 tCornerUL =TGfxVec2( tCenter.x  - tRadius.x, tCenter.y + tRadius.y);
	
	GfxLineSpriteJumpTo(pLineSprite, tCornerUR.x,	tCornerUR.y);
	GfxLineSpriteLineTo(pLineSprite, tCornerDR.x,	tCornerDR.y);	
	GfxLineSpriteLineTo(pLineSprite, tCornerDL.x,	tCornerDL.y);	
	GfxLineSpriteLineTo(pLineSprite, tCornerUL.x,	tCornerUL.y);		
	GfxLineSpriteLineTo(pLineSprite, tCornerUR.x,	tCornerUR.y);	
	
	
	}else{
	
	const TGfxVec2 & tCenter = tPos;
	//tPos.y *=-1;
	//const TGfxVec2 & tRadius = tRadius;

	GfxLineSpriteSetDrawingColor(pLineSprite, iColor);
	

	//TGfxVec2 tCornerUR, tCornerDR, tCornerDL, tCornerUL;
	
	const TGfxVec2 tAxisX = TGfxVec2(cosf(fAngle),-sinf(fAngle));
	const TGfxVec2 tAxisY = TGfxVec2(sinf(fAngle),cosf(fAngle));


	GfxLineSpriteSetDrawingColor(pLineSprite, iColor);
	const TGfxVec2 tCornerUR = tCenter + tAxisX * tRadius.x - tAxisY * tRadius.y;
	const TGfxVec2 tCornerDR = tCenter + tAxisX * tRadius.x + tAxisY * tRadius.y;
	const TGfxVec2 tCornerDL = tCenter - tAxisX * tRadius.x + tAxisY * tRadius.y;
	const TGfxVec2 tCornerUL = tCenter - tAxisX * tRadius.x - tAxisY * tRadius.y;
	
	GfxLineSpriteJumpTo(pLineSprite, tCornerUR.x,	tCornerUR.y);
	GfxLineSpriteLineTo(pLineSprite, tCornerDR.x,	tCornerDR.y);	
	GfxLineSpriteLineTo(pLineSprite, tCornerDL.x,	tCornerDL.y);	
	GfxLineSpriteLineTo(pLineSprite, tCornerUL.x,	tCornerUL.y);		
	GfxLineSpriteLineTo(pLineSprite, tCornerUR.x,	tCornerUR.y);	
	}


}

void DrawTriangle(TGfxSprite * pLineSprite, const TGfxVec2 & tRadius,float fAngle, const  TGfxVec2 & tPos, unsigned int iColor, int iType)
{

	//tPos.y *=-1;
	
	const TGfxVec2 & tCenter = tPos;
	//const TGfxVec2 & tRadius = tRadius;

	GfxLineSpriteSetDrawingColor(pLineSprite, iColor);
	//TGfxVec2 tCornerUR, tCornerDR, tCornerDL, tCornerUL;
	

	const TGfxVec2 tAxisX = TGfxVec2(cosf(fAngle),-sinf(fAngle));
	const TGfxVec2 tAxisY = TGfxVec2(sinf(fAngle),cosf(fAngle));


	GfxLineSpriteSetDrawingColor(pLineSprite, iColor);

	const TGfxVec2 tCornerUR = tCenter + tAxisX * tRadius.x - tAxisY * tRadius.y;
	const TGfxVec2 tCornerDR = tCenter + tAxisX * tRadius.x + tAxisY * tRadius.y;
	const TGfxVec2 tCornerDL = tCenter - tAxisX * tRadius.x + tAxisY * tRadius.y;
	const TGfxVec2 tCornerUL = tCenter - tAxisX * tRadius.x - tAxisY * tRadius.y;
	

	switch(iType)
	{
	case 1:	GfxLineSpriteJumpTo(pLineSprite, tCornerUR.x,	tCornerUR.y);
			GfxLineSpriteLineTo(pLineSprite, tCornerDR.x,	tCornerDR.y);	
			GfxLineSpriteLineTo(pLineSprite, tCornerDL.x,	tCornerDL.y);	
			
			GfxLineSpriteLineTo(pLineSprite, tCornerUR.x,	tCornerUR.y);	


		break;
	case 2:	GfxLineSpriteJumpTo(pLineSprite, tCornerDR.x,	tCornerDR.y);
			
			GfxLineSpriteLineTo(pLineSprite, tCornerDL.x,	tCornerDL.y);	
			GfxLineSpriteLineTo(pLineSprite, tCornerUL.x,	tCornerUL.y);		
			GfxLineSpriteLineTo(pLineSprite, tCornerDR.x,	tCornerDR.y);	

		break;
	case 3 :GfxLineSpriteJumpTo(pLineSprite, tCornerUR.x,	tCornerUR.y);

			GfxLineSpriteLineTo(pLineSprite, tCornerDL.x,	tCornerDL.y);	
			GfxLineSpriteLineTo(pLineSprite, tCornerUL.x,	tCornerUL.y);		
			GfxLineSpriteLineTo(pLineSprite, tCornerUR.x,	tCornerUR.y);	

		break;

	case 4 :GfxLineSpriteJumpTo(pLineSprite, tCornerUR.x,	tCornerUR.y);
			GfxLineSpriteLineTo(pLineSprite, tCornerDR.x,	tCornerDR.y);	
		
			GfxLineSpriteLineTo(pLineSprite, tCornerUL.x,	tCornerUL.y);		
			GfxLineSpriteLineTo(pLineSprite, tCornerUR.x,	tCornerUR.y);	

	break;
	
	
	}
	/*
	GfxLineSpriteJumpTo(pLineSprite, tCornerUR.x,	tCornerUR.y);
	GfxLineSpriteLineTo(pLineSprite, tCornerDR.x,	tCornerDR.y);	
	GfxLineSpriteLineTo(pLineSprite, tCornerDL.x,	tCornerDL.y);	
	GfxLineSpriteLineTo(pLineSprite, tCornerUL.x,	tCornerUL.y);		
	GfxLineSpriteLineTo(pLineSprite, tCornerUR.x,	tCornerUR.y);	

	*/
}



TGfxVec2 GameSizeToScreen(TGfxVec2 tSize)
{
	return tSize *= gfSizeModifier;
}

float GameSizeToScreen(float fSize)
{
	return fSize *= gfSizeModifier;
}

TGfxVec2  GamePosToScreen(  TGfxVec2  tPos )
{
	//TGfxVec2 &tPosition = tPos;
	tPos	*= gfSizeModifier;	
	//	tPos.y *=-1;
	tPos += gCamera; 
	tPos.y *=-1;
	//tPos.x -=gCamera.x;
	//tPos.y +=gCamera.y;
	return tPos;


}



float ClampScreen(float fValue, float fLimite1, float fLimite2)
{
	if(fValue < fLimite1)
	{
		return fLimite1;
	}
	else {
		if(fValue>fLimite2)
		{
			return fLimite2;
		} else return fValue;
	}
}


void DrawHud(TScene * tScene)
{
	float fPower = tScene->m_pPlayer->GetPower();
	float fMaxPower = tScene->m_pPlayer->GetMaxPower();
	float fSpeed = tScene->m_pPlayer->GetSpeed();
	float fMaxSpeed = tScene->m_pPlayer->GetMaxSpeed();

	TGfxSprite * pLineSprite =  tScene->m_pLineSprite;
	/*

	int iLineThickness = 10;
	float fLengthLine = 30.0f;
	for(int i = 0; i<iLineThickness; i++)
	{
		GfxLineSpriteSetDrawingColor(pLineSprite , EGfxColor_Red);
		GfxLineSpriteJumpTo(pLineSprite, 10  ,10 +i);
		GfxLineSpriteLineTo(pLineSprite, 10 + fLengthLine ,10+i);

		GfxLineSpriteSetDrawingColor(pLineSprite , EGfxColor_Green);
		GfxLineSpriteJumpTo(pLineSprite, 10  ,10 +i);
		GfxLineSpriteLineTo(pLineSprite, 10 + fLengthLine *(fHP / fMaxLife) ,10+i);
	}
	*/

	

	/*

		int iLineThickness = 5;
	float fLengthLine = 50.0f;
	for(int i = 0; i<iLineThickness; i++)
	{
		GfxLineSpriteSetDrawingColor(pLineSprite , EGfxColor_Red);
		GfxLineSpriteJumpTo(pLineSprite, 10.0f  ,10.0f +i);
		GfxLineSpriteLineTo(pLineSprite, 10.0f + fLengthLine ,10.0f+i);

		GfxLineSpriteSetDrawingColor(pLineSprite , EGfxColor_Green);
		GfxLineSpriteJumpTo(pLineSprite, 10.0f  ,10.0f +i);
		GfxLineSpriteLineTo(pLineSprite, 10.0f + fLengthLine * (tScene->m_pSandWorm->GetCurrentRage() / tScene->m_pSandWorm->GetMaxRage()) ,10.0f+i);
	}
	
	*/


	//DrawCircle(pLineSprite, 1,(2*-M_PI) * tGame->m_pPowerUpList[i]->GetTimePercent()   + M_PI, ( TGfxVec2(GfxGetDisplaySizeX() / 2,50)+ gCamera )/gfSizeModifier, GfxColor(255,255,0,255));


	// *** Dessin des jauges *** //

	DrawOrientedCircle(pLineSprite,10.0f,(2.0f *PI - PI_2) *  -(  fPower /fMaxPower ) - PI_4 , (TGfxVec2( GfxGetDisplaySizeX() -100.0f,GfxGetDisplaySizeY()- 30.0f )   )  , GfxColor(120,120,120,255));
	DrawOrientedCircle(pLineSprite,15.0f,(2.0f *PI - PI_2) *  -(  fSpeed /fMaxSpeed ) - PI_4 , (TGfxVec2( GfxGetDisplaySizeX() -50.0f,GfxGetDisplaySizeY()- 30.0f) ), GfxColor(120,120,120,255));


	// *** Dessin du player sur la minimap *** //
	TGfxVec2 tPlayerPos =  tScene->m_pPlayer->GetPos();
	tPlayerPos.y *= -1;
	DrawCircle(pLineSprite, tScene->m_pPlayer->GetRadius()*3 , tPlayerPos * tScene->m_fMiniMapScale + tScene->m_tMiniMapPos , tScene->m_pPlayer->GetColor() );



	// **** dessin de la representaiton du vers   **** //
	

	TGfxVec2 tWormPos = tScene->m_pSandWorm->Position();
	float fRadius  = tScene->m_pSandWorm->GetRadius() * gfSizeModifier;
	
	//float fValueX = (tWormPos * gfSizeModifier - gCamera).x  + fRadius;
	//float fValueY =( tWormPos * gfSizeModifier + gCamera).y  + fRadius;


	if(   ((tWormPos * gfSizeModifier + gCamera).x  + fRadius <0    ||   (tWormPos * gfSizeModifier + gCamera).x -  fRadius>GfxGetDisplaySizeX() )  ||
		  ((-tWormPos * gfSizeModifier - gCamera).y  + fRadius <0    ||   (-tWormPos * gfSizeModifier - gCamera).y -  fRadius >GfxGetDisplaySizeY() )
		
		)
		{
		
		

			unsigned int iColor;
			int iCurrentTime = GfxTimeGetMilliseconds();
			if( iCurrentTime%200 <100)
			{
				iColor= GfxColor(255,127,0,255);
			}else {iColor= GfxColor(255,255,0,255);
	
			}
			
			DrawCircle(pLineSprite, 8.0f,TGfxVec2(ClampScreen( (tWormPos * gfSizeModifier + gCamera).x , 10.0f, GfxGetDisplaySizeX()-10.0f ),ClampScreen( (-tWormPos * gfSizeModifier - gCamera).y , 10.0f, GfxGetDisplaySizeY()-10.0f )), iColor);

			if((tWormPos-tScene->m_pPlayer->Position()).Length()<30)
			{
				DrawCircle(pLineSprite, 14.0f,TGfxVec2(ClampScreen( (tWormPos * gfSizeModifier + gCamera).x , 10.0f, GfxGetDisplaySizeX()-10.0f ),ClampScreen( (-tWormPos * gfSizeModifier - gCamera).y , 10.0f, GfxGetDisplaySizeY()-10.0f )), EGfxColor_Red);

			
			}



		
		}
	


	// ****** Dessin des boost ***** //
	/*
	for(int i =0; i<tScene->m_pPlayer->GetAvailableBoost(); i++)
	{
	
		DrawBox(pLineSprite,TGfxVec2(7.0f,7.0f),0.0f , TGfxVec2( GfxGetDisplaySizeX() -20.0f,GfxGetDisplaySizeY()- 30.0f - 30.0f*i ) , GfxColor(255,255,0,255));

	
	
	}
	*/

}



void DrawMap (TGfxSprite * pLineSprite, TScene * tScene)
{

	gfScale = tScene->m_tCameraParam.fScale;
	gfSizeModifier = gfScale * gfSize;


	GfxLineSpriteSetDrawingColor(pLineSprite, GfxColor(70,70,70,255));

	float fCellSize = 6.0f; // Size in meter
	float fGgridSize = fCellSize * gfSizeModifier;

	//Dessin des lignes horizontales
	int iLineCount =static_cast<int>( ( tScene->m_tMapSizeY.y -  tScene->m_tMapSizeY.x)/ fCellSize +2.0f );

	for(int i = -2; i<iLineCount; i++){	
		
		GfxLineSpriteJumpTo(pLineSprite, tScene->m_tMapSizeX.x * gfSizeModifier -150.0f,( i * fGgridSize +  tScene->m_tMapSizeY.x* gfSizeModifier  ) );
		GfxLineSpriteLineTo(pLineSprite, tScene->m_tMapSizeX.y * gfSizeModifier  +150.0f  ,(  i * fGgridSize +  tScene->m_tMapSizeY.x *gfSizeModifier)  );	
	}


	//Dessin des lignes verticales
	 iLineCount =static_cast<int>( ( tScene->m_tMapSizeX.y -  tScene->m_tMapSizeX.x)/ fCellSize + 2.0f);

	for(int i = -2; i<iLineCount; i++){	
		
		GfxLineSpriteJumpTo(pLineSprite,(i * fGgridSize +  tScene->m_tMapSizeX.x  * gfSizeModifier),( tScene->m_tMapSizeY.x  *gfSizeModifier ) -150.0f );
			GfxLineSpriteLineTo(pLineSprite, (i * fGgridSize + tScene->m_tMapSizeX.x *gfSizeModifier) ,( tScene->m_tMapSizeY.y  *gfSizeModifier) +150.0f );	
	}






	for(int i = 0; i<tScene->m_iWallCount; i++)
	{
	
		// ****************************  Dessin du niveau *********************** //

		TGfxVec2 tWallPos = tScene->m_pWallList[i]->Position();
		tWallPos.y *=-1;
		

	
		if(tScene->m_pWallList[i]->GetType() ==0){
			DrawBox(pLineSprite, GameSizeToScreen( tScene->m_pWallList[i]->GetSize() ),tScene->m_pWallList[i]->Rotation(), tWallPos * gfSizeModifier, tScene->m_pWallList[i]->GetColor() );
		
		}else if(tScene->m_pWallList[i]->GetType() ==360){
		
			DrawCircle(pLineSprite, GameSizeToScreen( tScene->m_pWallList[i]->GetRadius() ), tWallPos * gfSizeModifier, tScene->m_pWallList[i]->GetColor() );
		
		}else	{
			DrawTriangle(pLineSprite, GameSizeToScreen(  tScene->m_pWallList[i]->GetSize()),tScene->m_pWallList[i]->Rotation(),tWallPos * gfSizeModifier , tScene->m_pWallList[i]->GetColor(),tScene->m_pWallList[i]->GetType() );
		}
		
	
	}

	



}

void DrawMiniMap (TGfxSprite * pLineSprite, TScene * tScene)
{
	for(int i = 0; i<tScene->m_iWallCount; i++)
	{	
		// ****************************  Dessin du niveau *********************** //

		TGfxVec2 tWallPos = tScene->m_pWallList[i]->Position();
		tWallPos.y *=-1;
		
		unsigned int iMiniMapColor = GfxColor(100,100,100,255);
	
		if(tScene->m_pWallList[i]->GetType() ==0){
			DrawBox(pLineSprite, tScene->m_pWallList[i]->GetSize() * tScene->m_fMiniMapScale ,tScene->m_pWallList[i]->Rotation(), tWallPos * tScene->m_fMiniMapScale , iMiniMapColor);
		
		}else{
			DrawTriangle(pLineSprite,  tScene->m_pWallList[i]->GetSize() * tScene->m_fMiniMapScale,tScene->m_pWallList[i]->Rotation(),tWallPos * tScene->m_fMiniMapScale , iMiniMapColor,tScene->m_pWallList[i]->GetType() );
		}
		
	
	}

	



}







bool bParallaxEnabled = false;
int iParallaxLevel = 2;
float fParallaxPower = 0.1f;
int iTest =0;
void DrawScene(TScene * tScene)
{

	gCamera = TGfxVec2(0,0);
	gfScale = tScene->m_tCameraParam.fScale;
	//gfScale = 4.0f;


	GfxSpriteSetScale(tScene->m_pMapLineSprite, tScene->m_tCameraParam.fScale/1.4f, tScene->m_tCameraParam.fScale/1.4f);
	gfSizeModifier = gfScale * gfSize;

	TGfxVec2 tMiniMapPosition = TGfxVec2(150.0f,  GfxGetDisplaySizeY() - tScene->m_tMapSize.y /2.0f - 150.0f)  ;
	TGfxSprite * pLineSprite = tScene->m_pLineSprite;

	TGfxVec2 pos  = TGfxVec2(GfxGetDisplaySizeX() / 2.0f / gfSizeModifier, GfxGetDisplaySizeY() / 2.0f / gfSizeModifier);

	
//	TGfxVec2 tCameraTarget = tScene->m_pPlayer->GetPos() - pos   + tScene->m_pPlayer->GetTSpeed() /5.0f;
	TGfxVec2 tPlayerPos =  tScene->m_pPlayer->GetPos();
	tPlayerPos.y *=-1;
	TGfxVec2 tCameraTarget;
	 tCameraTarget.x = tPlayerPos.x- pos.x ;
	 tCameraTarget.y = tPlayerPos.y- pos.y ;
	tCameraTarget.x*=-1;
	gCamera = tCameraTarget;
	
	//TGfxVec2	tCameraTarget = tScene->m_pPlayer->GetPos() - pos   +TGfxVec2(cosf( tScene->m_pPlayer->Rotation()) * 3, sinf(tScene->m_pPlayer->Rotation())*3);
	//TGfxVec2	tCameraTarget = tScene->m_pPlayer->GetRotationAxe() - pos   +TGfxVec2(cosf( tScene->m_pPlayer->Rotation()) * 3, sinf(tScene->m_pPlayer->Rotation())*3);
/*
	if(iTest == 0)
	{
			
		gCamera = tCameraTarget;
		iTest = 1;
	
	}else{
	 float Scaled_Lerp_Value = GfxTimeFrameGetCurrentDurationInSeconds() / 0.15f ;
	 gCamera/= gfSizeModifier;
	gCamera.x = Lerp(gCamera.x, tCameraTarget.x, Scaled_Lerp_Value);
	gCamera.y = Lerp(gCamera.y, tCameraTarget.y, Scaled_Lerp_Value);
	//gCamera = tCameraTarget;
	}
	
	*/

//		GfxDbgPrintf("Pos X : %f  -  ", gCamera.x); 
//	GfxDbgPrintf("Pos Y : %f \n ", gCamera.y); 


	/*
	if(gCamera.x> 0.0f) gCamera.x = 0.0f;
	if(gCamera.y< 0.0f) gCamera.y = 0.0f;
	if(gCamera.x< -( tScene->m_tMapSize.x - pos.x*2 +1.5f )) gCamera.x = -( tScene->m_tMapSize.x - pos.x*2  +1.5f) ;
	if(gCamera.y> tScene->m_tMapSize.y - pos.y*2 +1.5f  ) gCamera.y = tScene->m_tMapSize.y - pos.y*2  +1.5f;
	*/
	if(gCamera.x> -tScene->m_tMapSizeX.x + pos.x/2.0f - 1.5f )   gCamera.x = -tScene->m_tMapSizeX.x + pos.x/2.0f -1.5f;
	if(gCamera.y< tScene->m_tMapSizeY.x + pos.y/ 2.0f ) gCamera.y = tScene->m_tMapSizeY.x + pos.y /2.0f;
	if(gCamera.x< -( tScene->m_tMapSizeX.y - pos.x * 2 + 1.5f )) gCamera.x = -(  tScene->m_tMapSizeX.y - pos.x * 2 + 1.5f) ;
	if(gCamera.y> tScene->m_tMapSizeY.y - pos.y * 2 + 1.5f  ) gCamera.y = tScene->m_tMapSizeY.y - pos.y * 2  + 1.5f;

	GfxSpriteSetPosition(tScene->m_pMapLineSprite, gCamera.x * gfSizeModifier, -gCamera.y*gfSizeModifier);
	




	/*
	if(gCamera.x< -1.5f) gCamera.x = -1.5f;
	if(gCamera.y< -1.5f) gCamera.y = -1.5f;
	if(gCamera.x> tScene->m_tMapSize.x - pos.x*2 +1.5f ) gCamera.x = tScene->m_tMapSize.x - pos.x*2  +1.5f ;
	if(gCamera.y> tScene->m_tMapSize.y - pos.y*2 +1.5f  ) gCamera.y = tScene->m_tMapSize.y - pos.y*2  +1.5f;
	*/
	gCamera *= gfSizeModifier;

	//gCamera.y *= -1; 
//	GfxDbgPrintf("sixe X %f \n", tScene->tMapSize.x);



	// *********************************************************** Dessin de la grille ************* //

	/*
	GfxLineSpriteSetDrawingColor(pLineSprite, GfxColor(70,70,70,255));
	float fGgridSize = 6.01f;
	for(int i = -1; i<35; i++){	
		
			GfxLineSpriteJumpTo(pLineSprite,( i * fGgridSize + fGgridSize/4.0f  )* gfSizeModifier + gCamera.x,( -1.0f  *fGgridSize ) * gfSizeModifier - gCamera.y);
			GfxLineSpriteLineTo(pLineSprite, (i *fGgridSize+ fGgridSize/4.0f) * gfSizeModifier + gCamera.x,( 30.0f * fGgridSize) *gfSizeModifier - gCamera.y);
	
	}

		for(int i = -1; i<28; i++){	
		
			GfxLineSpriteJumpTo(pLineSprite,( -1.0f  *fGgridSize) * gfSizeModifier + gCamera.x,( i * fGgridSize +fGgridSize/4.0f)* gfSizeModifier - gCamera.y);
			GfxLineSpriteLineTo(pLineSprite,( 60.0f * fGgridSize) *gfSizeModifier + gCamera.x, (i *fGgridSize +fGgridSize/4.0f) * gfSizeModifier - gCamera.y);
	
	}
	*/


	// ************************************************************* Dessin des zones d'effets *******//

	for(int i = 0; i <tScene->MAX_AREAS; i++)
	{
		if(tScene->m_pAreaList[i] !=0)
		{
			if(tScene->m_pAreaList[i]->IsPreparing())

				DrawShatteredCircle(  pLineSprite,GameSizeToScreen( tScene->m_pAreaList[i]->GetRadius()),0.0f, GamePosToScreen( tScene->m_pAreaList[i]->Position()), tScene->m_pAreaList[i]->GetColor());
			else {
				
			//	float fParalaxValue = 0.05f;
				//TGfxVec2 tDist = gCamera / gfSizeModifier -tScene->m_pAreaList[i]->Position() + pos; 

				DrawCircle(  pLineSprite,GameSizeToScreen( tScene->m_pAreaList[i]->GetRadius()), GamePosToScreen( tScene->m_pAreaList[i]->Position() ), tScene->m_pAreaList[i]->GetColor() );

				/*for(int j =0; j<2; j++)
				{
				DrawCircle(  pLineSprite, tScene->m_pAreaList[i]->GetRadius() *(1.0f - (fParalaxValue*3.0f) *(j*1.0f)) , tScene->m_pAreaList[i]->Position() - (tDist* fParalaxValue*(j*1.0f)), GfxColor(255.0f  * (1.0f - 0.2f*j) ,255.0f  * (1.0f - 0.2f*j),0.0f  ,255.0f) );
				}*/
			}
		}
	}





	// *** Dessin du joueur
	DrawOrientedCircle(pLineSprite, GameSizeToScreen( tScene->m_pPlayer->GetRadius()), tScene->m_pPlayer->Rotation(), GamePosToScreen( tScene->m_pPlayer->GetPos()), tScene->m_pPlayer->GetColor() );
	//DrawCircle(pLineSprite, 0.2f , tScene->m_pPlayer->GetRotationAxe()  , EGfxColor_Red );


	//Dessin du vers

	if(tScene->m_pSandWorm != 0)
	{	
	//	DrawOrientedCircle(pLineSprite, tScene->m_pSandWorm->GetRadius(),tScene->m_pSandWorm->Rotation(), tScene->m_pSandWorm->Position(), tScene->m_pSandWorm->GetColor());
		DrawPartialCircle(pLineSprite,GameSizeToScreen( tScene->m_pSandWorm->GetRadius()), CorrectRange( tScene->m_pSandWorm->Rotation()+ PI ), tScene->m_pSandWorm->GetRangeMouth(),GamePosToScreen( tScene->m_pSandWorm->Position()), tScene->m_pSandWorm->GetColor());

			//DrawOrientedCircle(pLineSprite, tScene->m_pSandWorm->m_tTailList[0].fRadius,tScene->m_pSandWorm->m_tTailList[0].pTransform->Rotation(), tScene->m_pSandWorm->m_tTailList[0].pTransform->Position(), tScene->m_pSandWorm->m_tTailList[0].iColor);
			//DrawOrientedCircle(pLineSprite, tScene->m_pSandWorm->m_tTailList[1].fRadius,tScene->m_pSandWorm->m_tTailList[1].pTransform->Rotation(), tScene->m_pSandWorm->m_tTailList[1].pTransform->Position(), tScene->m_pSandWorm->m_tTailList[1].iColor);
			
		for(int i=0; i < tScene->m_pSandWorm->GetTailCount(); i++)
		{
			DrawBox(pLineSprite, GameSizeToScreen( tScene->m_pSandWorm->m_tTailList[i].pBody->m_tHitBox->GetRadiusBox()), tScene->m_pSandWorm->m_tTailList[i].pBody->Rotation(), GamePosToScreen( tScene->m_pSandWorm->m_tTailList[i].pBody->Position()), EGfxColor_Red);

			DrawOrientedCircle(pLineSprite, GameSizeToScreen( tScene->m_pSandWorm->m_tTailList[i].fRadius),tScene->m_pSandWorm->m_tTailList[i].pTransform->Rotation(),GamePosToScreen( tScene->m_pSandWorm->m_tTailList[i].pTransform->Position()), tScene->m_pSandWorm->m_tTailList[i].iColor);
			//		DrawCircle(pLineSprite, GameSizeToScreen( tScene->m_pSandWorm->m_tTailList[i].fRadius),GamePosToScreen( tScene->m_pSandWorm->m_tTailList[i].pTransform->Position()), tScene->m_pSandWorm->m_tTailList[i].iColor);

		}
		
	
			float fAngle =0;
				float fRadius = 0;

				float fPosX = 0;
				float fPosY = 0;

				float tTailLength = 0;
				TGfxVec2 tPos;
				TGfxVec2 tTailVector;
				TGfxVec2 tTempVec;

			for(int i = tScene->m_pSandWorm->GetTailCount()-1; i>=0; --i)
			{

				

				if(i ==0)
				{
				

				fAngle = tScene->m_pSandWorm->m_tTailList[0].pTransform->Rotation();
				fRadius = GameSizeToScreen( tScene->m_pSandWorm->m_tTailList[0].fRadius );
				tPos = GamePosToScreen( tScene->m_pSandWorm->m_tTailList[0].pTransform->Position()) ;
				fPosX =  cosf(fAngle +3.14f/2.0f) * fRadius+tPos.x ;	
				fPosY =-  sinf(fAngle+3.14f/2.0f)* fRadius + tPos.y;		
				GfxLineSpriteJumpTo(pLineSprite,fPosX,fPosY);


				tTailVector =GameSizeToScreen( (tScene->m_pSandWorm->Position() -tScene->m_pSandWorm->m_tTailList[0].pTransform->Position()) );

				tTempVec =  TGfxVec2( tTailVector.x + fPosX, tTailVector.y *-1+ fPosY);

				GfxLineSpriteLineTo(pLineSprite,   tTempVec.x,tTempVec.y);



				fAngle = tScene->m_pSandWorm->m_tTailList[0].pTransform->Rotation();
				 fRadius = GameSizeToScreen(tScene->m_pSandWorm->m_tTailList[0].fRadius);
				 tPos = GamePosToScreen( tScene->m_pSandWorm->m_tTailList[0].pTransform->Position());

				 fPosX =  cosf(fAngle -3.14f/2.0f) * fRadius+tPos.x ;	
				 fPosY = - sinf(fAngle-3.14f/2.0f)* fRadius + tPos.y;	

			 	GfxLineSpriteJumpTo(pLineSprite,fPosX,fPosY);

				 tTempVec = TGfxVec2( tTailVector.x + fPosX, tTailVector.y*-1 + fPosY);

				GfxLineSpriteLineTo(pLineSprite,   tTempVec.x,tTempVec.y);
				
				
				
				}else{



				 fAngle =   tScene->m_pSandWorm->m_tTailList[i].pTransform->Rotation() ;
				 fRadius = GameSizeToScreen( tScene->m_pSandWorm->m_tTailList[i].fRadius);
				 TGfxVec2 tPos = GamePosToScreen( tScene->m_pSandWorm->m_tTailList[i].pTransform->Position() );
				 fPosX =  cosf(fAngle +3.14f /2.0f) * fRadius+tPos.x ;	
				 fPosY =  - sinf(fAngle+3.14f/2.0f)* fRadius + tPos.y;		
				GfxLineSpriteJumpTo(pLineSprite,fPosX,fPosY);


				TGfxVec2 tTailVector = GameSizeToScreen (tScene->m_pSandWorm->m_tTailList[i-1].pTransform->Position() -tScene->m_pSandWorm->m_tTailList[i].pTransform->Position() );
			 tTailLength = tTailVector.Length();

				TGfxVec2 tTempVec = TGfxVec2( tTailVector.x + fPosX, tTailVector.y*-1 + fPosY);

				GfxLineSpriteLineTo(pLineSprite,   tTempVec.x,tTempVec.y);

			
				fAngle = tScene->m_pSandWorm->m_tTailList[i].pTransform->Rotation();
				 fRadius =GameSizeToScreen( tScene->m_pSandWorm->m_tTailList[i].fRadius );
				 tPos = GamePosToScreen( tScene->m_pSandWorm->m_tTailList[i].pTransform->Position() );
				 fPosX =  cosf(fAngle -3.14f /2.0f) * fRadius+tPos.x ;	
				 fPosY =  - sinf(fAngle-3.14f/2.0f)* fRadius + tPos.y;		
				GfxLineSpriteJumpTo(pLineSprite,fPosX,fPosY);


		
				 tTempVec = TGfxVec2( tTailVector.x + fPosX, tTailVector.y *-1+ fPosY);

				GfxLineSpriteLineTo(pLineSprite,   tTempVec.x,tTempVec.y);



			

				}
			}

			
	}



	//DrawBox(tScene->m_pBoxSprite, GameSizeToScreen( tScene->m_pWallList[0]->GetSize()), 0, TGfxVec2(0,0), tScene->m_pWallList[0]->GetColor());

	// *** Dessin du decors
	/*
	for(int i = 0; i<tScene->m_iWallCount; i++)
	{
		// ***************************** Dessin de la minimap ******************** //		
		if(tScene->m_pWallList[i]->GetType() ==0){
			DrawBox(pLineSprite,  tScene->m_pWallList[i]->GetSize() /4 ,tScene->m_pWallList[i]->Rotation(),(tScene->m_pWallList[i]->GetPos() /4 +tMiniMapPosition ) ,GfxColor(100,100,100,125) );
		
		}else{
			DrawTriangle(pLineSprite,  tScene->m_pWallList[i]->GetSize() /4,tScene->m_pWallList[i]->Rotation(),tScene->m_pWallList[i]->GetPos()/ 4+ tMiniMapPosition , GfxColor(100,100,100,125),tScene->m_pWallList[i]->GetType() );
		}

		// ****************************  Dessin du niveau *********************** //

		TGfxVec2 tWallPos = tScene->m_pWallList[i]->Position();
		tWallPos.y *=-1;
		
		TGfxVec2 tCamTemp = gCamera / gfSizeModifier;
		//tCamTemp.y *=-1;
		tCamTemp.x*=-1;
		//float distance = (tCamTemp - pos -tWallPos ).SquaredLength();
		float distance = (tCamTemp + pos -tWallPos ).SquaredLength();

		
		if(distance<1000){

			if(tScene->m_pWallList[i]->GetType() ==0){
				DrawBox(pLineSprite, GameSizeToScreen( tScene->m_pWallList[i]->GetSize() ),tScene->m_pWallList[i]->Rotation(),GamePosToScreen( tScene->m_pWallList[i]->GetPos()), tScene->m_pWallList[i]->GetColor() );
		
			}else{
				DrawTriangle(pLineSprite, GameSizeToScreen(  tScene->m_pWallList[i]->GetSize()),tScene->m_pWallList[i]->Rotation(), GamePosToScreen( tScene->m_pWallList[i]->GetPos()), tScene->m_pWallList[i]->GetColor(),tScene->m_pWallList[i]->GetType() );
			}
		
			TGfxVec2 tDist = gCamera / gfSizeModifier -tScene->m_pWallList[i]->GetPos() + pos; 
	
			float fParalaxValue = 0.1f;
			bParallaxEnabled = true;
			int iParallaxLevel = 2;
	
		}

	}
	*/

	// **************************************************** Dessin des elements a recuperer ********************* //

	for(int i=0; i< tScene->MAX_OFFERING; i++)
	{
		if(tScene->m_pOfferingList[i] !=0)
		{
			if(tScene->m_pOfferingList[i]->IsActive()){
				DrawCircle(pLineSprite, GameSizeToScreen( tScene->m_pOfferingList[i]->GetRadius()),GamePosToScreen( tScene->m_pOfferingList[i]->Position()), tScene->m_pOfferingList[i]->GetColor());
			}
		
		}
	
	
	
	
	}


		for(int i = 0; i< tScene->MAX_ColumnS; i++)
		{
			if(tScene->m_pColumnList[i] !=0)
			{		

			
				//float distance = (gCamera / gfSizeModifier+ pos - tScene->m_pColumnList[i]->Position()).SquaredLength();
			//	if(distance<800){


					
				TGfxVec2 tCollPos = tScene->m_pColumnList[i]->Position();
				tCollPos.y *=-1;
		
				TGfxVec2 tCamTemp = gCamera / gfSizeModifier;
			//	tCamTemp.y *=-1;
				tCamTemp.x*=-1;
				//float distance = (tCamTemp - pos -tWallPos ).SquaredLength();
				float distance = (tCamTemp + pos -tCollPos ).SquaredLength();




				if(distance<1000){



				TGfxVec2 tDist =  tCamTemp + pos -tCollPos ;
				tDist.y *=-1;

	

					if(!tScene->m_pColumnList[i]->IsDestroyed()){
					//	float fParalaxValue = 0.05f;
					//	TGfxVec2 tDist = gCamera / gfSizeModifier -tScene->m_pColumnList[i]->Position() - pos; 

						DrawCircle(pLineSprite, GameSizeToScreen( tScene->m_pColumnList[i]->GetRadius()),  GamePosToScreen( tScene->m_pColumnList[i]->Position()),  tScene->m_pColumnList[i]->GetColor()  );		
			
	/*
						for(int j = 1; j < 4; j++)
						{
				
							DrawCircle(pLineSprite,GameSizeToScreen( tScene->m_pColumnList[i]->GetRadius()*(1.0f + fParalaxValue *(j*1.0f)) ), GamePosToScreen(  tScene->m_pColumnList[i]->Position() - (tDist* fParalaxValue*(j*1.0f))),  GfxColor(150.0f  * (1.0f - 0.2f*j) ,70.0f  * (1.0f - 0.2f*j),0  ,255)   );		

						//	DrawBox(pLineSprite,  tScene->m_pWallList[i]->GetSize()*(1.0f + fParalaxValue *j),tScene->m_pWallList[i]->Rotation(),tScene->m_pWallList[i]->GetPos()  - (tDist* fParalaxValue*j) , EGfxColor_White );}
						}

						DrawCircle(pLineSprite,GameSizeToScreen( 2.0f), GamePosToScreen(  tScene->m_pColumnList[i]->Position() - (tDist* fParalaxValue*4)), GfxColor(0,150,0,255 ) )	;	
						DrawCircle(pLineSprite,GameSizeToScreen (1.7f), GamePosToScreen(   tScene->m_pColumnList[i]->Position() - (tDist* fParalaxValue*5)),  GfxColor(0,150,0,255 )  );		
						DrawCircle(pLineSprite,GameSizeToScreen( 1.4f), GamePosToScreen(   tScene->m_pColumnList[i]->Position() - (tDist* fParalaxValue*6)),  GfxColor(0,150,0,255 ) );		
						DrawCircle(pLineSprite,GameSizeToScreen( 1.1f), GamePosToScreen(   tScene->m_pColumnList[i]->Position() - (tDist* fParalaxValue*7)), GfxColor(0,150,0,255 )  );		
						DrawCircle(pLineSprite,GameSizeToScreen (0.5f), GamePosToScreen(   tScene->m_pColumnList[i]->Position() - (tDist* fParalaxValue*8)),  GfxColor(0,150,0,255 )  );		
						//	DrawCircle(pLineSprite, tScene->m_pColumnList[i]->GetRadius() *(1.0f - fParalaxValue *j*5) ,  tScene->m_pColumnList[i]->Position() - (tDist* fParalaxValue*j),  tScene->m_pColumnList[i]->GetColor()  );		

*/
					}else {	DrawCircle(pLineSprite, GameSizeToScreen( tScene->m_pColumnList[i]->GetRadius()),  GamePosToScreen( tScene->m_pColumnList[i]->Position()),  tScene->m_pColumnList[i]->GetColor()  );		
					}
				}

			}
		
		

		}

		

		DrawHud(tScene);



}



#endif

