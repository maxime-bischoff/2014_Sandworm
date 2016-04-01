#ifndef Column_H_INCLUDED
#define Column_H_INCLUDED
#include "transform.h"
class TTransform;
struct TGfxVec2;

class TColumn: public TTransform
{
public :


	TColumn(TGfxVec2 tPos, float fAngle, float fRadius, unsigned int iColor, int iId);
	~TColumn();


	unsigned int GetColor(){ return m_iColor;};
	float GetRadius(){return m_fRadius;};
	bool IsDestroyed(){return m_bDestroyed;};
	void Destroy();
	void Update();
private :

	int m_iId;
	bool m_bDestroyed;
	unsigned int m_iColor;
	float m_fRadius;
	int m_iTimeDestroyed;
	int m_iDestroyedDelay;

};


#endif