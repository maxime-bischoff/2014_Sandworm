#include "flib.h"
#include "flib_vec2.h"
#include <math.h>

#include "transform.h"
#include "hitbox.h"






THitBox::THitBox(void)
{
}


THitBox::~THitBox(void)
{


	m_tTransform =0;
}

TGfxVec2 THitBox::GetGlobalPos()
{
	return m_tTransform->GetPos() + m_tPos;

}



// ************ Collision depuis un cercle  *********** //


THitBoxCircle::THitBoxCircle(float fRadius, TGfxVec2 tPos,TTransform * tTransform)
{
	m_fRadius = fRadius;
	m_tPos = tPos;
	m_tTransform = tTransform;
		eCollisionType = Circle;

}

THitBoxCircle::~THitBoxCircle(void)
{
}






// ************ Collision depuis une Box  *********** //


THitBoxBox::THitBoxBox(TGfxVec2 tRadius, TGfxVec2 tPos, TTransform * tTransform)
{
	eCollisionType = Box;
	m_tRadius = tRadius;
	m_tPos = tPos;
	m_tTransform= tTransform;

}

THitBoxBox::~THitBoxBox(void)
{
}

THitBoxTriangle::THitBoxTriangle(TGfxVec2 tRadius, TGfxVec2 tPos, TTransform * tTransform, int iType)
{
	eCollisionType = Triangle;
	m_tRadius = tRadius;
	m_tPos = tPos;
	m_tTransform= tTransform;

	m_fHypo = sqrtf( tRadius.x*2 * tRadius.y*2);
	m_iType = iType;

	TGfxVec2 tTangent1 =  TGfxVec2( -sin(-1.0f), cos( 1.0f) ).Normalize();
	TGfxVec2 tTangent2 =  TGfxVec2( -sin(1.0f), cos( -1.0f) ).Normalize();
	//TGfxVec2 tNormal 1 = ;

	switch (iType)
	{
	case 1:m_tNormal = TGfxVec2(-1,1).Normalize();
		m_tTangent = tTangent1;
		break;

	case 2: m_tNormal = TGfxVec2(1,1).Normalize();
			m_tTangent = tTangent2;
		break;

	case 3: m_tNormal = TGfxVec2(1,-1).Normalize();
			m_tTangent = tTangent1;
		break;

	case 4: m_tNormal = TGfxVec2(-1,-1).Normalize();
			m_tTangent = tTangent2;
				;
		break;


	default:
		break;
	}



	
	


}