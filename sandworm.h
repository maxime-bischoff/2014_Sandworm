#ifndef SANDWORM_H_INCLUDED
#define SADNWORM_H_INCLUDED

#include "transform.h"
class TScene;

struct TTail{
	

	TTransform * pTransform;
	TTransform * pBody;
	unsigned int iColor;
	float fRadius;
	float fSegmentLength;

};


enum EWormState
{
	Hunting,
	RandomWalk,
	AttackBase,
	Undergound,
	ESleep
};


class TSandWorm : public TTransform
{
public:


	bool m_bMouthClosed;

	float m_fAimedAngle;
	static const int MAX_TAILS = 50;
	TTail m_tTailList[MAX_TAILS];
	
	//	void Undergound(TGfxVec2 tPos);
	void Initialize();
	TSandWorm(TGfxVec2 tPos, float fAngle);
	~TSandWorm(void);
	void CreateArea(TScene * tScene,const TGfxVec2 &tPos);
	void AddTail();
	int GetTailCount(){return m_iTailCount;};
	bool Update(TScene * tScene);
	unsigned int GetColor(){return m_iColor;};
	float GetRadius(){return m_fRadius;}; 

	float GetCurrentRage(){return m_fCurrentRage;};
	float GetMaxRage(){return m_fMaxRage;};

	void CollideWall(const TCollideResult & tResult);
	void CollideColumn(const TCollideResult &tResult, int idColumn);
	EWormState GetState(){return m_eWormState;};
	float GetRangeMouth();
	void SetAngry(){m_eWormState = Hunting;};
	float GetCameraScale();
#ifdef TFA_FRESH
	void SendDataToFresh();
#endif

private:
	int m_iLastAngleChange;
	int m_iAngleChangeDelay;
	int m_iTailCount;	
	float m_fTailAngleMax;
	float m_fSegmentLength;

	float m_fCurrentRage;
	float m_fMaxRage;

	float m_fWalkSpeed;
	float m_fCurrentSpeed;
	float m_fHuntSpeed;
	float m_fBrakeRange;

	float m_fBrakeSpeed;
	float m_fRotationSpeed;
	float m_fBrakeRotationSpeed;


	TGfxVec2 m_tWormHole;
	TGfxVec2 m_tDigDirection;
	EWormState m_eWormState;
	float m_fRadius;
	unsigned int m_iColor;

	bool m_bIsUnderground;
	bool m_bUndergroundHead;
	bool m_bUndergroundTail[MAX_TAILS];


	int m_iAreaPerWave;
	int m_iAreaCreated;
	int m_iLastWaveCreatedTime;
	int m_iWaveCreationDelay;

	int m_iLastAreaCreatedTime;
	int m_iAreaCreationDelay;


};

#endif