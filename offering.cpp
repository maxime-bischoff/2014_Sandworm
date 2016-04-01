#include "flib.h"
#include "flib_vec2.h"
#include "transform.h"
#include "player.h"
#include "collision.h"
#include "area.h"
#include "scene.h"
#include "sandworm.h"
#include <math.h>
#include "functions.h"


#include "offering.h"


TOffering::TOffering(TGfxVec2 tPos, float fAngle, float fRadius, unsigned int iColor, bool bActive, bool bStarter):TTransform(tPos, fAngle)
{
	////m_fRadius = fRadius;
	m_fRadius = 2.0f;

	m_iColor = iColor;
	m_bActive = bActive;
	m_bPicked = false;
	m_bStarter = bStarter;
	if(bStarter) m_fRadius = 6.0f;
}


TOffering::~TOffering(void)
{
}


unsigned int TOffering::GetColor(){
	if(!m_bStarter){
		return m_iColor;
	}else{

	int iCurrentTime = GfxTimeGetMilliseconds();
	if( iCurrentTime%200 <100)
	{
		return GfxColor(255,127,0,255);
	}else {return GfxColor(255,255,0,255);
	
	}
	}

}

bool TOffering::Update(){





	if(m_bPicked)
	{
		return false;
	
	}return true;



}
