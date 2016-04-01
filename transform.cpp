#include "flib.h"
#include "flib_vec2.h"



#include "hitbox.h"
#include "transform.h"




TTransform::TTransform(TGfxVec2 tPos, float fAngle):
	m_tPos (tPos),
	m_fAngle (fAngle)
{
	m_tHitBox = 0;
}

TTransform::~TTransform()
{
	if(m_tHitBox!=0)delete m_tHitBox;
	m_tHitBox=0;

}




void TTransform::Rotation(float fAngle)
{
	this->m_fAngle = fAngle;

}
void TTransform::Rotate(float fAngle)
{
	this->m_fAngle += fAngle;

}


void TTransform::Translate(TGfxVec2 tVector)
{
	m_tPos+= tVector;

}

void TTransform::AddHitBox(float fRadius, TGfxVec2 tPos)
{
	m_tHitBox =new THitBoxCircle(fRadius, tPos, this);


}

void TTransform::AddHitBox(TGfxVec2 tRadius, TGfxVec2 tPos)
{

	m_tHitBox =new THitBoxBox(tRadius, tPos, this);
	//m_tHitBox =new THitBoxBox();


}


void TTransform::AddHitBox(TGfxVec2 tRadius, TGfxVec2 tPos, int iType)
{

	m_tHitBox =new THitBoxTriangle(tRadius, tPos, this, iType);
	//m_tHitBox =new THitBoxBox();


}