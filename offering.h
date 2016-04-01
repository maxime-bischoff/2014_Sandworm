#ifndef OFFERING_H_INCLUDED
#define OFFERING_H_INCLUDED

#include "transform.h"

class TOffering :public TTransform
{
public:
	TOffering(TGfxVec2 tPos, float fAngle, float fRadius, unsigned int iColor, bool bActive, bool bStarter);
	~TOffering(void);
	unsigned int GetColor();
	float GetRadius(){return m_fRadius;}; 
	void SetActive(){m_bActive =true;};
	bool Update();
	void Pick(){m_bPicked = true;
	m_bActive = false;};
	bool IsActive(){return m_bActive;};
	bool IsStarter(){return  m_bStarter;};

private:

	bool m_bStarter;
	bool m_bActive;
	bool m_bPicked;
		float m_fRadius ;
	unsigned int m_iColor ;

};


#endif