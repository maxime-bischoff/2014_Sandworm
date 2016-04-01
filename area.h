#ifndef AREA_H_INCLUDED
#define AREA_H_INCLUDED
#include "transform.h"
class TArea :
	public TTransform
{
public:
	TArea(TGfxVec2 tPos, float fAngle, int iId);
	~TArea(void);
	unsigned int GetColor();
	float GetRadius();
	bool IsPreparing(){return m_bPreparing;};

	bool Update();
private:

	int m_iId;
	bool m_bPreparing;
	bool m_bGrowing;
	float m_fRadius;
	unsigned int m_iColor;
	int m_iTimeCreated;
	int m_iComeOutDelay;
	int m_iOutDuration;
	int m_iTimeDisplayed;
};

#endif