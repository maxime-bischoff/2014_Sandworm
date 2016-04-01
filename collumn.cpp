#include "flib.h"
#include "flib_vec2.h"
#include "lua.h"
#include "transform.h"

#include "collumn.h"


TColumn::TColumn(TGfxVec2 tPos, float fAngle, float fRadius, unsigned int iColor, int iId):TTransform(tPos, fAngle)
{
	m_iId = iId;
	m_fRadius = fRadius;
	m_iColor = iColor;
	AddHitBox(fRadius,TGfxVec2(0,0));
	m_bDestroyed = false;
	m_iDestroyedDelay = 20000;
}

TColumn::~TColumn(){};

void TColumn::Update()
{

	if(m_bDestroyed)
	{
		if (m_iTimeDestroyed + m_iDestroyedDelay< GfxTimeGetMilliseconds())
		{
		
			m_bDestroyed = false;
			
			#ifdef TFA_FRESH
				lua_pushinteger(GfxFreshLuaState(), m_iId + 1 );
				LuaCallGlobal(GfxFreshLuaState(), "ColumnOut");
			#endif

		
		}
	
	
	}






}

void TColumn::Destroy(){
	
	
	m_bDestroyed = true;
	m_iTimeDestroyed = GfxTimeGetMilliseconds();


	#ifdef TFA_FRESH
		lua_pushinteger(GfxFreshLuaState(), m_iId + 1 );
		LuaCallGlobal(GfxFreshLuaState(), "ColumnIn");
	#endif
};