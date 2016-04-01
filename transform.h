#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#include "flib_vec2.h"
class THitBox;

class TTransform
{
	
public:

	TTransform(TGfxVec2 tPos, float fAngle);
	~TTransform();


	// ***** Accessor
	float Rotation(){return m_fAngle;};
	TGfxVec2 Position(){return m_tPos;};

	// ***** Mutator
	void Rotation (float fAngle);
	void Rotate (float fAngle);
	void Position(TGfxVec2 tPos){m_tPos = tPos;};
	void Translate(TGfxVec2 tVector);


	void AddHitBox(float fRadius, TGfxVec2 tPos);
	void AddHitBox(TGfxVec2 tRadius, TGfxVec2 tPos);
		void AddHitBox(TGfxVec2 tRadius, TGfxVec2 tPos, int iType);
	TGfxVec2 GetPos(){ return m_tPos; };
	float GetAngle(){ return m_fAngle; };

	THitBox * m_tHitBox;

protected :

	TGfxVec2 m_tPos;
	
	//TGfxVec2 m_tPos;
	float m_fAngle;


};


#endif
