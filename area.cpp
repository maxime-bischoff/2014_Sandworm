
#include "flib.h"
#include "flib_vec2.h"
#include "lua.h"
#include "transform.h"
#include "area.h"


TArea::TArea(TGfxVec2 tPos,float fAngle, int iId):TTransform(tPos, fAngle)
{
	m_iId = iId;
	m_fRadius  = 2.0f;
	m_iColor = GfxColor(255,255,0,255);
	m_iComeOutDelay = 450;
	m_iOutDuration = 250;
	m_iTimeCreated = GfxTimeGetMilliseconds();
	m_bPreparing = true;
	m_iTimeDisplayed = 1000;
	m_bGrowing = false;
	AddHitBox(m_fRadius-0.1f, TGfxVec2(0,0));


#ifdef TFA_FRESH

	lua_pushnumber( GfxFreshLuaState(), m_tPos.x);
	lua_pushnumber( GfxFreshLuaState(), -m_tPos.y);
	lua_pushinteger( GfxFreshLuaState(), m_iId+1);
	LuaCallGlobal(GfxFreshLuaState(), "PlaceArea");

#endif
}


TArea::~TArea(void)
{
		#ifdef TFA_FRESH
				lua_pushinteger(GfxFreshLuaState(), m_iId+1);
				LuaCallGlobal(GfxFreshLuaState(), "HideArea");
			#endif

}

unsigned int TArea::GetColor(){	

	if(m_bPreparing){
		return m_iColor;
	}else return EGfxColor_Red;


}

float TArea::GetRadius(){
	if(m_bPreparing){
		return m_fRadius;
	
	}else{
		if(m_bGrowing){

		float fValue =    ( GfxTimeGetMilliseconds()*1.0f - (m_iTimeCreated+m_iComeOutDelay) *1.0f) /(m_iOutDuration*1.0f) ;
			

		return m_fRadius * fValue;


	
		}else{return m_fRadius;}
	
	
	}



}

bool TArea::Update()
{
	if(m_iTimeCreated+ m_iComeOutDelay + m_iOutDuration  + m_iTimeDisplayed> GfxTimeGetMilliseconds())
	{

		#ifdef TFA_FRESH		
				lua_pushinteger( GfxFreshLuaState(), m_iId+1);
				LuaCallGlobal(GfxFreshLuaState(), "PlaceAreaLogo");
		#endif


		if(m_bPreparing){



			if(m_iTimeCreated + m_iComeOutDelay <GfxTimeGetMilliseconds())
			{		
				m_bPreparing = false;
				m_bGrowing = true;

				#ifdef TFA_FRESH
					lua_pushinteger(GfxFreshLuaState(), m_iId+1);
					LuaCallGlobal(GfxFreshLuaState(), "SpawnArea");
				#endif
			}
		}

		if(m_bGrowing){
			if(m_iTimeCreated + m_iComeOutDelay +m_iOutDuration <GfxTimeGetMilliseconds())
			{		
				


		
				m_bGrowing = false;		
			}
		}



	return true;
	}
	else {


		
		return false;
		}



}
