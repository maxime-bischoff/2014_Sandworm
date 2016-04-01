#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED
class TTransform;

#include "transform.h"


class TWall:public TTransform
	
{
public:
	TWall(TGfxVec2 tRadius, TGfxVec2 tPos,float fAngle, unsigned int iColor, int iType);
	~TWall();
	TGfxVec2 GetSize(){return m_tRadius;};
	float GetRadius(){return m_fRadius;};
	unsigned int GetColor( ){return m_iColor ;};
	int GetType(){return m_iType;};
private:

	bool m_bBox;
	int m_iType;
	TGfxVec2 m_tRadius;
	float m_fRadius;
	unsigned int m_iColor;




};


#endif