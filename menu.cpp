
#include "flib.h"

#include "lua.h"

#include "main_menu.h"
#include "popup_menu.h"
#include "level_select_menu.h"
#include <cstring>
#include "menu.h"
#include <math.h>

TMenu::TMenu(void)
{

	m_iSelectedColor = EGfxColor_Red;
	m_iUnselectedColor = EGfxColor_White;
	
	 m_fLastChangeTime = 0.0f;
	 m_fChangeDelay = 0.2f;
	 m_bActionPressed = false;
	 m_bInteractionAllowed = false;

	#ifndef TFA_FRESH
			m_pBackgroundSprite = 0;
	#endif

}


TMenu::~TMenu(void)
{


}

void TMenu::EnableInteraction(bool bValue){


	m_bInteractionAllowed = bValue;

}

void TMenu::MakeActive(){

Show(true);
ResetSelected();

m_bActionPressed = false;
m_fActionTime = 0;
m_bInteractionAllowed = false;
if(fabs(GfxInputGetPadStickLeftY() ) < 0.5f)
{
	EnableInteraction(true);

}



}


void TMenu::Show(bool bValue){


	#ifdef TFA_FRESH
		lua_pushstring(GfxFreshLuaState(), m_cNameMenu);								
		lua_pushboolean(GfxFreshLuaState(), bValue);
		LuaCallGlobal(GfxFreshLuaState(), "ShowMenu");
	#endif
		bValue = false;
}




void TMenu::ResetSelected()
{
	for(int i = 1; i <m_iMenuCount; i++)
	{

		#ifndef TFA_FRESH		
			GfxSpriteSetColor(m_tButtonList[i].m_pTextSprite, m_iUnselectedColor);				
		#else 

			lua_pushstring(GfxFreshLuaState(), m_cNameMenu);
			lua_pushinteger(GfxFreshLuaState(), i +1);
			lua_pushboolean(GfxFreshLuaState(), false);
		
			LuaCallGlobal(GfxFreshLuaState(), "SelectMenu");
		#endif
	}

	m_iSelectedMenu = 0;

	#ifndef TFA_FRESH		
		GfxSpriteSetColor(m_tButtonList[m_iSelectedMenu].m_pTextSprite, m_iSelectedColor);	

	#else

			lua_pushstring(GfxFreshLuaState(), m_cNameMenu);
			lua_pushnumber(GfxFreshLuaState(), 1);
			lua_pushboolean(GfxFreshLuaState(), true);
		
			LuaCallGlobal(GfxFreshLuaState(), "SelectMenu");
	#endif



}


void TMenu::CreateMenu()
{
	float fTextScale = 2.5f;

	for(int i = 0 ; i< m_iMenuCount; i ++)
	{

		#ifndef TFA_FRESH

			m_tButtonList[i].m_pTextSprite =  GfxTextSpriteCreate();		
			GfxTextSpriteSetText( 	m_tButtonList[i].m_pTextSprite, m_tButtonList[i].m_cName);	
			GfxSpriteSetScale(m_tButtonList[i].m_pTextSprite, fTextScale, fTextScale);
			GfxSpriteSetFilteringEnabled(m_tButtonList[i].m_pTextSprite, false);
			GfxSpriteSetColor(m_tButtonList[i].m_pTextSprite, EGfxColor_Red);
			GfxSpriteSetPosition(m_tButtonList[i].m_pTextSprite , GfxGetDisplaySizeX()/2.0f- GfxSpriteGetSizeX(m_tButtonList[i].m_pTextSprite)*fTextScale/2.0f,  50.0f +i *35.0f);


		#else

			lua_pushstring(GfxFreshLuaState(),m_cNameMenu);
			lua_pushstring(GfxFreshLuaState(),m_tButtonList[i].m_cName);
			lua_pushinteger(GfxFreshLuaState(),i+1);
			lua_pushboolean(GfxFreshLuaState(), false);
			lua_pushnumber(GfxFreshLuaState(),0);
			lua_pushnumber(GfxFreshLuaState(),0.5);
			LuaCallGlobal(GfxFreshLuaState(), "CreateMenu");

		#endif


	}



	ResetSelected();


}

void TMenu::Update()
{

	return;

}

void TMenu::DelayAction(){
	return;
}

void TMenu::CheckControls()
{
	if(m_bActionPressed) return;


	if(!m_bInteractionAllowed){
	
		if(fabs( GfxInputGetPadStickLeftY() ) < 0.5f)
		{
			m_bInteractionAllowed = true;
		
		}else return;
	
	};

	m_fLastChangeTime+= GfxTimeFrameGetCurrentDurationInSeconds();

	if(m_fLastChangeTime >=m_fChangeDelay){
		m_bUpAllowedToPressed = true;
		m_bDownAllowedToPressed = true;
	
	}

	float fLeftStickValueY =  GfxInputGetPadStickLeftY();
	
	if(m_bUpJustPressed) m_bUpJustPressed = false;
	if(m_bDownJustPressed) m_bDownJustPressed = false;

	
	if(fLeftStickValueY>= 0.65f && m_bUpAllowedToPressed)
	{
		m_bUpJustPressed = true;
		m_bUpAllowedToPressed = false;
		m_fLastChangeTime = 0;			
	}	
		
	
	if(fLeftStickValueY<= 0.1f)
	{
		m_bUpAllowedToPressed = true;			
	}
			
	if(fLeftStickValueY<= - 0.65f  && m_bDownAllowedToPressed)
	{
		m_bDownJustPressed = true;
		m_bDownAllowedToPressed = false;
		m_fLastChangeTime = 0;
			
	}	
		
	
	if(fLeftStickValueY>= - 0.1f)
	{
		m_bDownAllowedToPressed = true;
			
	}
		



	
		if(GfxInputIsJustPressed(EGfxInputID_KeyArrowDown)  || GfxInputIsJustPressed(EGfxInputID_AnyPadDown)||m_bDownJustPressed )
		{
					#ifndef TFA_FRESH
						GfxSpriteSetColor(m_tButtonList[m_tButtonList[m_iSelectedMenu].m_iNextButton].m_pTextSprite, m_iSelectedColor);	
						GfxSpriteSetColor(m_tButtonList[m_iSelectedMenu].m_pTextSprite, m_iUnselectedColor);			
					#else 
						lua_pushstring(GfxFreshLuaState(), m_cNameMenu);
						lua_pushinteger(GfxFreshLuaState(), m_iSelectedMenu+1);
						lua_pushboolean(GfxFreshLuaState(), false);
						LuaCallGlobal(GfxFreshLuaState(), "SelectMenu");

						lua_pushstring(GfxFreshLuaState(), m_cNameMenu);
						lua_pushinteger(GfxFreshLuaState(), m_tButtonList[m_iSelectedMenu].m_iNextButton + 1);
						lua_pushboolean(GfxFreshLuaState(), true);
						LuaCallGlobal(GfxFreshLuaState(), "SelectMenu");
					#endif		
						m_iSelectedMenu = m_tButtonList[m_iSelectedMenu].m_iNextButton;
		}else	if(GfxInputIsJustPressed(EGfxInputID_KeyArrowUp) || GfxInputIsJustPressed(EGfxInputID_AnyPadUp)||m_bUpJustPressed )
		{

			
					#ifndef TFA_FRESH
						GfxSpriteSetColor(m_tButtonList[m_tButtonList[m_iSelectedMenu].m_iPreviousButton].m_pTextSprite, m_iSelectedColor);	
						GfxSpriteSetColor(m_tButtonList[m_iSelectedMenu].m_pTextSprite, m_iUnselectedColor);	
						

			
		
					#else 			
							
						lua_pushstring(GfxFreshLuaState(), m_cNameMenu);
						lua_pushinteger(GfxFreshLuaState(), m_iSelectedMenu+1);
						lua_pushboolean(GfxFreshLuaState(), false);
						LuaCallGlobal(GfxFreshLuaState(), "SelectMenu");

						lua_pushstring(GfxFreshLuaState(), m_cNameMenu);
						lua_pushinteger(GfxFreshLuaState(), m_tButtonList[m_iSelectedMenu].m_iPreviousButton + 1);
						lua_pushboolean(GfxFreshLuaState(), true);
						LuaCallGlobal(GfxFreshLuaState(), "SelectMenu");
					#endif

						m_iSelectedMenu = m_tButtonList[m_iSelectedMenu].m_iPreviousButton;
		}


		
		if( GfxInputIsJustPressed(EGfxInputID_KeyReturn)    || GfxInputIsJustPressed(EGfxInputID_KeySpace) || 
			GfxInputIsJustPressed(EGfxInputID_AnyPadStart)  || GfxInputIsJustPressed(EGfxInputID_AnyPadCross) )
		{
			ActionButton();
		}

		if( GfxInputIsJustPressed(EGfxInputID_KeyBackspace)  || GfxInputIsJustPressed(EGfxInputID_KeyEscape) || 
			GfxInputIsJustPressed(EGfxInputID_AnyPadCircle)  || GfxInputIsJustPressed(EGfxInputID_AnyPadTriangle) )
		{
			BackButton();
		}






}

void TMenu::Render()
{

#ifndef TFA_FRESH
	if(m_pBackgroundSprite != 0 )
	{
		GfxSpriteRender(m_pBackgroundSprite);
	
	
	}


	for(int i = 0 ;i< m_iMenuCount; i++)
	{
		if( m_tButtonList[i].m_pTextSprite !=0)
		{
		
			GfxSpriteRender(m_tButtonList[i].m_pTextSprite);

		
		}
	
	
	}

#endif




}