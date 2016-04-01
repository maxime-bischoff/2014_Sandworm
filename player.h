#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "flib_vec2.h"
#include "transform.h"
struct TCollideResult;
class TScene;
enum EPlayerState{
	Dead,
	Alive
};

enum EMovingState{
	Walking,
	Hovering,
	Thrust

};

class TPlayer:public TTransform
{
public:

	float m_fHeightPos;
	float m_fVerticalSpeed;

	TPlayer(TGfxVec2 tPos, float m_fAngle);
	~TPlayer(void);
	void CollideWall(TCollideResult &tResult);
	void CollideWorm(TCollideResult &tResult);
	void CollideRock(TCollideResult &tResult);

	void Move(const TGfxVec2 &tSpeed);

	void SetSpawnPosition(TGfxVec2 tPos);
	float GetRadius(){return m_fRadius;};

	float GetScaleCameraValue();

	float GetPower(){return m_fThrustPower;};
	float GetMaxPower(){return m_fThrustMaxPower;};
	float GetSpeed(){return m_fThrustSpeed;};
	float GetMaxSpeed(){return m_fThrustMaxSpeed;};
	void Damage(float fDamage);
	float GetHP(){return m_fHP;};
	float GetMaxHP(){return m_fMaxHp;};
	int GetAvailableBoost(){return m_iBoostAvailable;};
	EPlayerState GetState(){return m_ePlayerState;};
	int GetEggCount(){return m_iEggCount;};
	TGfxVec2 GetRotationAxe(){return m_tRotationAxe;};
	TGfxVec2 GetTSpeed(){return m_tSpeed;};
	unsigned int GetColor();

	bool Update(TScene * tScene);
	void Eat(){m_ePlayerState = Dead;};

	#ifdef TFA_FRESH
		void SendDataToFresh();
	#endif



	float m_fScaleCamera;
	float m_fScaleIncreaseSpeed;
	float m_fScaleDecreaseSpeed;

	float m_fMaxScale;
	float m_fMinScale;

private : 

	int m_bDirectionControl;

	int m_iOfferingCount;
	TGfxVec2 m_tRotationAxe;
	TGfxVec2 m_tSpawnPosition;
	EPlayerState m_ePlayerState;
	EMovingState m_eMovingState;
	float m_fRadius;
	unsigned int m_iColor;
	float m_fHP;
	float m_fMaxHp;

	int m_iEggCount;

	int m_iReloadDelay;
	int m_iLastBoostUsed;
	int m_iLastBoostRecovered;
	int m_iBoostDelay;

	int m_iBoostAvailable;
	int m_iMaxBoost;


	float m_fWalkSpeed;
	float m_fWalkAccel;
	float m_fWalkMaxSpeed;

	float m_fIntertiaSpeed;

	TGfxVec2 m_tInertiaVector; // Vecteur d'inertie
	TGfxVec2 m_tSpeed;
	float m_fRotationSpeed;

	float m_fThrustRotationSpeed;
	float m_fHoveringRotationSpeed;

	float m_fThrustMaxPower; // Puissance max quand les gaz sont a fond
	float m_fThrustAccel; // Vitesse a laquelle les gaz atteignent leur puissance max
	float m_fThrustDecel;
	float m_fThrustPower;

	float m_fThrustSpeed; // Vitesse actuelle de deplacement
	float m_fThrustMaxSpeed; // Vitesse maximun que le puisse atteindre 
	
	


	bool m_bIsHovering;
	bool m_bThrust;
	float m_HoveringMaxSpeed;
	float m_fHoveringAccel;



	
};

#endif