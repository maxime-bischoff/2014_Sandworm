#ifndef HITBOX_H_INCLUDED
#define HITBOX_H_INCLUDED
class TTransform;
class THitBoxBox;
class THitBoxCircle;
#include "flib_vec2.h"

enum ECollisionType{
Circle,
Box,
Triangle,


};


class THitBox
{
public:
	ECollisionType eCollisionType;

	TGfxVec2 GetGlobalPos();
	virtual float GetRadius() { float value = 0;return value;};
	virtual TGfxVec2 GetRadiusBox(){return TGfxVec2(0,0);};
	virtual TGfxVec2 GetNormal(){return TGfxVec2(0,0);}
	virtual TGfxVec2 GetTangent(){return TGfxVec2(0,0);}
	virtual float GetHypo(){return 0;};
	virtual int GetType(){return 0;};
//	virtual void  SetRadiusBox(TGfxVec2 tRadius);
//	virtual void  SetRadius(float fRadius);

	THitBox(void);
	~THitBox(void);
protected :
	TTransform * m_tTransform;
	TGfxVec2 m_tPos;

};








// ****** HitBox d'un cercle ******* //

class THitBoxCircle: public THitBox
{


public:
	THitBoxCircle(float fRadius, TGfxVec2 tPos, TTransform * tTransform);
	~THitBoxCircle(void);
	float GetRadius(){return m_fRadius;};
	// void SetRadius(float fRadius){m_fRadius = fRadius;};

	//void Collide(THitBoxCircle * tCircle);
	//void Collide(THitBoxBox * tBox);
private :
	float m_fRadius;
	
};







// ****** HitBox d'une box ******* //

class THitBoxBox: public THitBox
{
public:
	TGfxVec2 m_tRadius;

	TGfxVec2 GetRadiusBox(){return m_tRadius;};
	 void SetRadiusBox(TGfxVec2 tRadius){m_tRadius = tRadius;};
	THitBoxBox(TGfxVec2 tRadius, TGfxVec2 tPos, TTransform * tTransform);
	~THitBoxBox(void);
};




// ******* HitBox d'un triangle rectangle isocel ****** //
class THitBoxTriangle: public THitBox
{
public:
	TGfxVec2 m_tRadius;

	TGfxVec2 GetRadiusBox(){return m_tRadius;};
	TGfxVec2 GetNormal(){return m_tNormal;};
	TGfxVec2 GetTangent(){return m_tTangent;};

	int GetType(){return m_iType;};
	float GetHypo(){return m_fHypo;};

	THitBoxTriangle(TGfxVec2 tRadius, TGfxVec2 tPos, TTransform * tTransform, int iType);

	// void SetRadiusBox(TGfxVec2 tRadius){m_tRadius = tRadius;};

	TGfxVec2 m_tNormal;
	TGfxVec2 m_tTangent;
	float  m_fHypo;
	int m_iType;

	~THitBoxTriangle(void);
};













#endif