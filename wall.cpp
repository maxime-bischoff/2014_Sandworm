
#include "flib_vec2.h"
#include "transform.h"
#include "wall.h"

TWall::TWall(TGfxVec2 tRadius, TGfxVec2 tPos,float fAngle, unsigned int iColor, int iType):TTransform(tPos, fAngle)
{

	this->m_iColor = iColor;

	m_tRadius = tRadius;
	m_fRadius = tRadius.x * 2.0f;
	m_iType = iType;


	
}

TWall::~TWall()
{
}