#ifndef REPELLER_H_INCLUDED
#define REPELLER_H_INCLUDED

class TTransform;
class TRepeller :
	public TTransform
{
public:
	TRepeller(TGfxVec2 tPos, float fAngle);
	~TRepeller(void);
	void Update();

private : 
	bool m_bIsEnabled;
	bool m_bPicked;

};

#endif