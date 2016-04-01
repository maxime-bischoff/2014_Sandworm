#include "flib.h"
#include "flib_vec2.h"

#include "lua.h"
#include "transform.h"
#include "player.h"
#include "collision.h"
#include "area.h"
#include "scene.h"
#include "game.h"
#include "collumn.h"
#include "sandworm.h"
#include "const.h"

#include <math.h>
#include "functions.h"

TSandWorm::TSandWorm(TGfxVec2 tPos, float fAngle):TTransform(tPos, fAngle)
{
	m_fCurrentRage = 0;
	m_fMaxRage = 10;
	m_eWormState = RandomWalk;
	m_fRadius = 3.0f;
	m_fSegmentLength = 6.0f;
	//m_fRadius = 4.0f;
	m_iColor = GfxColor(220,120,0,255);

	m_iLastAreaCreatedTime = GfxTimeGetMilliseconds();
	m_iAreaCreationDelay = 150;

     m_iAreaCreated =0;
	 m_iAreaPerWave = 10;
	 m_iLastWaveCreatedTime= 0;
	 m_iWaveCreationDelay = 4000;

	 m_fTailAngleMax = (PI/3.0f)*2.0f;

	m_fHuntSpeed = 30.0f;
	m_fBrakeSpeed = 20.0f;
	m_fWalkSpeed = 13.0f;
	m_fCurrentSpeed = 0;
	m_fBrakeRange = (3.14f / 3.0f) ;

	m_iLastAngleChange = GfxTimeGetMilliseconds();
	m_iAngleChangeDelay = 4000;

	m_fRotationSpeed = 3.14f / 100.0f;
	m_fBrakeRotationSpeed = 3.14f / 50.0f;

	m_bMouthClosed = true;
	m_fAngle = -PI_2;
	m_iTailCount =0;
	m_fAimedAngle = fAngle;
	AddHitBox(m_fRadius, TGfxVec2(0,0));
}

void TSandWorm::Initialize(){

	m_iTailCount = 0;

	for(int i = 0; i<4; i++)
	{
	
		AddTail();
	}



	//m_iTailCount = 2;
}



void TSandWorm::AddTail(){


	if(m_iTailCount <MAX_TAILS ){

		if(m_iTailCount ==0)
		{
			m_tTailList[0].iColor = GfxColor(220,120,0,255);
			m_tTailList[0].fRadius = m_fRadius;
			m_tTailList[0].fSegmentLength = m_fSegmentLength;

			m_tTailList[0].pTransform = new TTransform(TGfxVec2(m_tPos.x, m_tPos.y +   m_tTailList[0].fSegmentLength ),-PI_2);
			m_tTailList[0].pTransform->AddHitBox(m_tTailList[0].fRadius, TGfxVec2(0,0));	


			m_tTailList[0].pBody = new TTransform(TGfxVec2(m_tPos.x, m_tPos.y +  m_tTailList[0].fSegmentLength), 0);
			m_tTailList[0].pBody->AddHitBox(TGfxVec2(  m_tTailList[0].fSegmentLength/2.0f , m_fRadius  ), TGfxVec2(0,0) );
			m_bUndergroundTail[0] = false;
		}
		else{

		m_tTailList[m_iTailCount].iColor = GfxColor(220,120,0,255);
		m_tTailList[m_iTailCount].fRadius = m_fRadius ;
		m_tTailList[m_iTailCount].fSegmentLength = m_fSegmentLength;
		m_tTailList[m_iTailCount].pTransform = new TTransform(TGfxVec2(m_tTailList[m_iTailCount-1].pTransform->Position().x , m_tTailList[m_iTailCount-1].pTransform->Position().y +  m_tTailList[m_iTailCount-1].fSegmentLength),-PI_2);
		m_tTailList[m_iTailCount].pTransform->AddHitBox(m_tTailList[m_iTailCount].fRadius, TGfxVec2(0,0));
	
		m_tTailList[m_iTailCount].pBody = new TTransform(TGfxVec2(m_tTailList[m_iTailCount-1].pTransform->Position().x , m_tTailList[m_iTailCount-1].pTransform->Position().y +  m_tTailList[m_iTailCount-1].fSegmentLength), 0);
		m_tTailList[m_iTailCount].pBody->AddHitBox(TGfxVec2(m_tTailList[m_iTailCount].fSegmentLength/2.0f , m_fRadius ), TGfxVec2(0,0) );

		m_bUndergroundTail[m_iTailCount] = false;	

		}
		m_iTailCount++;
	}
}


TSandWorm::~TSandWorm(void)
{
	for(int i=0; i<m_iTailCount; i++)
	{
	delete m_tTailList[i].pTransform;
	 m_tTailList[i].pTransform = 0;
	delete m_tTailList[i].pBody;
	 m_tTailList[i].pBody = 0;
	
	}
}

float TSandWorm::GetRangeMouth(){

	if(m_bMouthClosed) return 6.2f; 
	else return 4.5f;
	
	


}


void TSandWorm::CollideWall(const TCollideResult &tResult){


	Translate(tResult.tNormal * (tResult.fLength  ));
	if(m_eWormState ==  RandomWalk)
	{
		if(m_iLastAngleChange + m_iAngleChangeDelay /3< GfxTimeGetMilliseconds()){

			m_fAimedAngle = 	GfxMathGetRandomFloat(0.0f, 2.0f*PI);
	
				m_fAimedAngle = CorrectRange(m_fAimedAngle);	
			m_iLastAngleChange = GfxTimeGetMilliseconds();
		}

	}


}


void TSandWorm::CollideColumn(const TCollideResult &tResult, int idColumn)
{

	m_fCurrentSpeed*=0.8f;

	m_fCurrentRage+=1.0f;

	if(m_eWormState == Hunting)
	{
	
		TGame::m_tScene->m_pColumnList[idColumn]->Destroy();	
	
	
	}else
	{
	
		
		Translate(tResult.tNormal * (tResult.fLength  ));
		if(m_eWormState ==  RandomWalk)
		{
			if(m_iLastAngleChange + m_iAngleChangeDelay /3< GfxTimeGetMilliseconds()){

				m_fAimedAngle = 	GfxMathGetRandomFloat(0.0f, 2.0f*PI);
	
					m_fAimedAngle = CorrectRange(m_fAimedAngle);	
				m_iLastAngleChange = GfxTimeGetMilliseconds();
			}

	}
	
	
	
	}

}


void TSandWorm::CreateArea(TScene * tScene,const TGfxVec2 &tPos){

	if(tScene->m_iAreaCount< TScene::MAX_AREAS)
	{
	bool bFound = false;
	int i = 0;
	while (!bFound && tScene->m_iAreaCount< tScene->MAX_AREAS)
	{	
		if(tScene->m_pAreaList[i]==0) bFound = true;
		else i++;	
	}
	
	tScene->m_pAreaList[i] = new TArea(tPos, 0, i);
	tScene->m_iAreaCount++;
	m_iLastAreaCreatedTime = GfxTimeGetMilliseconds();
	
	
	}

}


bool TSandWorm::Update(TScene * tScene)
{


	if(GfxInputIsPressed(EGfxInputID_AnyPadUp) && GfxInputIsJustPressed(EGfxInputID_AnyPadShoulderR) && GfxInputIsPressed(EGfxInputID_AnyPadSelect) ){
	
		if(m_eWormState == RandomWalk) m_eWormState = Hunting; else m_eWormState = RandomWalk;
	
	
	}

	if(GfxInputIsJustPressed(EGfxInputID_KeyCharP))
	{
		AddTail();	
	}

	if(GfxInputIsPressed(EGfxInputID_KeyCharM  ))
	{
		for(int i = 0; i<m_iTailCount; i++)
		{
			m_tTailList[i].fRadius +=0.05f;
			
			//m_fRadius +=0.05f/2.0f;
		}
	
	}

	if(GfxInputIsPressed(EGfxInputID_KeyCharL  ))
	{
	for(int i = 0; i<m_iTailCount; i++)
		{
			m_tTailList[i].fRadius -=0.05f;
			//m_fRadius -= 0.05f/2.0f;
		}
	
	}

	if(GfxInputIsPressed(EGfxInputID_KeyCharJ  ))
	{
		for(int i = 0; i<m_iTailCount; i++)
		{
			m_tTailList[i].fSegmentLength -=0.05f;
			
		}
	
	}

		if(GfxInputIsPressed(EGfxInputID_KeyCharK  ))
	{
		for(int i = 0; i<m_iTailCount; i++)
		{
			m_tTailList[i].fSegmentLength +=0.05f;
			
		}
	
	}



int iCurrentTime = GfxTimeGetMilliseconds();

float fDistance = (tScene->m_pPlayer->Position() - m_tPos).Length();

if(fDistance >15.0f) {
		
		m_bMouthClosed = true;

		#ifdef TFA_FRESH
			LuaCallGlobal(GfxFreshLuaState(), "WormIdlePlay");
		
		#endif
	


}
else if(fDistance >4.0f ){

	if(m_bMouthClosed)
	{
		m_bMouthClosed = false;

		#ifdef TFA_FRESH
			LuaCallGlobal(GfxFreshLuaState(), "WormOpenJaw");
		#endif
	}

}else { 
if(fDistance <3.8f){
	TGfxVec2 tPlayerToEnemy =  tScene->m_pPlayer->Position() - m_tPos ;
		float angle =CorrectRange( atan2(tPlayerToEnemy.y, tPlayerToEnemy.x) );
		
	if(     ( CorrectRange(  m_fAngle - angle    ) < 1.0f) &&
			( CorrectRange(  m_fAngle  -angle  ) > - (1.0f) ) )

		{



	tScene->m_pPlayer->Eat();
	m_bMouthClosed = true;

	#ifdef TFA_FRESH
			LuaCallGlobal(GfxFreshLuaState(), "WormCloseJaw");
		#endif



		}
	}
}







if(m_eWormState == Hunting){

	m_fCurrentSpeed  =  MLerp(m_fCurrentSpeed, m_fHuntSpeed,  GfxTimeFrameGetAverageDurationInSeconds() /0.65f);
	
		TGfxVec2  tPlayerToWorm =    tScene->m_pPlayer->Position() - this->m_tPos ;
		m_fAimedAngle =atan2f(tPlayerToWorm.y, tPlayerToWorm.x) ;

		
		float angle = m_fAimedAngle;
		

			
					
			if(     ( CorrectRange(  m_fAimedAngle - m_fAngle   ) < - m_fBrakeRange) ||
						( CorrectRange(  m_fAimedAngle - m_fAngle   ) >  (m_fBrakeRange) ) )
			{

				
					if ( CorrectRange(m_fAngle -angle  ) > 0)
					{
						if(CorrectRange(m_fAngle -angle  )> m_fBrakeRotationSpeed){
						angle = (m_fAngle - m_fBrakeRotationSpeed);			
						m_fAngle = CorrectRange(angle);
						}else {m_fAngle = CorrectRange(angle);}

					}
					 else{
						 if( fabs(CorrectRange(m_fAngle -angle  ))> m_fBrakeRotationSpeed){
						angle = (m_fAngle + m_fBrakeRotationSpeed);
						m_fAngle = CorrectRange(angle);
						}else {m_fAngle = CorrectRange(angle);}
					}
			
			


				Translate( TGfxVec2( cosf(m_fAngle), sinf(m_fAngle)) * m_fBrakeSpeed * (1.0f/60.0f));
			
			}else{

					if ( CorrectRange(m_fAngle -angle  ) > 0)
					{
						if(CorrectRange(m_fAngle -angle  )> m_fRotationSpeed){
						angle = (m_fAngle - m_fRotationSpeed);			
						m_fAngle = CorrectRange(angle);
						}else {m_fAngle = CorrectRange(angle);}

					}
					 else{
						 if( fabs(CorrectRange(m_fAngle -angle  ))> m_fRotationSpeed){
						angle = (m_fAngle + m_fRotationSpeed);
						m_fAngle = CorrectRange(angle);
						}else {m_fAngle = CorrectRange(angle);}
					}

					 Translate( TGfxVec2( cosf(m_fAngle), sinf(m_fAngle)) * m_fCurrentSpeed * (1.0f/60.0f));


			}





		float fDistance = (m_tPos -tScene->m_pPlayer->Position()).Length();



		

		if(fDistance <16.0f || m_iAreaCreated< m_iAreaPerWave)
		{
			if(m_iLastWaveCreatedTime + m_iWaveCreationDelay<iCurrentTime)
			{
		
				if(m_iLastAreaCreatedTime + m_iAreaCreationDelay< GfxTimeGetMilliseconds()  )
				{

					TGfxVec2 tWormToPlayer = tScene->m_pPlayer->Position() - m_tPos;
					float fAngle = CorrectRange( atan2f(tWormToPlayer.y, tWormToPlayer.x) );
					float fRange = PI / 6.0f;

					float fRandRange = GfxMathGetRandomFloat(0.0f, 2.0f* fRange);
					float fRandomAngle = CorrectRange( fAngle+  (fRange -fRandRange));

					float fRandomDistance = GfxMathGetRandomFloat(0.0f,10.0f);

					CreateArea( tScene, m_tPos+ TGfxVec2(cosf(fRandomAngle), sinf(fRandomAngle)) * (30.0f + fRandomDistance));	
					m_iAreaCreated++;

					if(m_iAreaCreated >= m_iAreaPerWave)
					{
						m_iLastWaveCreatedTime = iCurrentTime;
						m_iAreaCreated = 0;
				
					}


				}
			}
		}

	}




	if(m_eWormState == RandomWalk)
	{
		if(m_iLastAngleChange + m_iAngleChangeDelay< iCurrentTime)
		{
			m_fAimedAngle = 	GfxMathGetRandomFloat(0, 6.28f);
			m_iLastAngleChange = iCurrentTime;
			m_fAimedAngle = CorrectRange(m_fAimedAngle);	
		
		}


		float angle = m_fAimedAngle;

			 
			if ( CorrectRange(m_fAngle -angle  ) > 0)
			{
				if(CorrectRange(m_fAngle -angle  )> m_fRotationSpeed){
				angle = (m_fAngle - m_fRotationSpeed);			
				m_fAngle = CorrectRange(angle);
				}else {m_fAngle = CorrectRange(angle);}

			}
			 else{
				 if( fabs(CorrectRange(m_fAngle -angle  ))> m_fRotationSpeed){
				angle = (m_fAngle + m_fRotationSpeed);
				m_fAngle = CorrectRange(angle);
				}else {m_fAngle = CorrectRange(angle);}
			}
			
			 Translate( TGfxVec2( cosf(m_fAngle), sinf(m_fAngle)) * m_fWalkSpeed *(1.0f/60.0f));

	
	
	
	}
	TGfxVec2 tHeadToTail;
	TGfxVec2 tTailToTail;
	TGfxVec2 tTailToHead;
	float fAngle2;

	// ************************************************ Placement des segments ************** //

	for(int i =0; i<m_iTailCount ; i++)
	{

		if(i ==0)
		{
			tHeadToTail =   m_tTailList[0].pTransform->Position()  - m_tPos  ;
	
			fAngle2 = CorrectRange( atan2f(tHeadToTail.y, tHeadToTail.x)  );


			 if(      CorrectRange(   m_fAngle   - fAngle2  ) > -m_fTailAngleMax  &&  CorrectRange(   m_fAngle   - fAngle2  ) <0) 
			 {					 
				TGfxVec2 tAngleVector =  TGfxVec2(cosf (CorrectRange( m_fAngle +m_fTailAngleMax)), sinf(CorrectRange( m_fAngle + m_fTailAngleMax )));
				m_tTailList[0].pTransform->Position( m_tPos + tAngleVector * ( m_tTailList[0].fSegmentLength));	 
				tTailToHead =   m_tPos  - m_tTailList[0].pTransform->Position()  ;	
				fAngle2 = CorrectRange( atan2f(tTailToHead.y, tTailToHead.x)  );
				m_tTailList[0].pTransform->Rotation( fAngle2 );

			 } else if	( CorrectRange(   m_fAngle -fAngle2    ) <  (m_fTailAngleMax) && CorrectRange(   m_fAngle   - fAngle2  ) >0 )				{
		 		TGfxVec2 tAngleVector = TGfxVec2(cosf (CorrectRange( m_fAngle - m_fTailAngleMax)), sinf(CorrectRange( m_fAngle -m_fTailAngleMax)));				
				m_tTailList[0].pTransform->Position( m_tPos + tAngleVector* ( m_tTailList[0].fSegmentLength));
				tTailToHead =   m_tPos  - m_tTailList[0].pTransform->Position()  ;	
				fAngle2 = CorrectRange( atan2f(tTailToHead.y, tTailToHead.x)  );
				m_tTailList[0].pTransform->Rotation( fAngle2 );
			
				}else{
				tTailToHead =   m_tPos  - m_tTailList[0].pTransform->Position()  ;	
				fAngle2 = CorrectRange( atan2f(tTailToHead.y, tTailToHead.x)  );
				m_tTailList[0].pTransform->Rotation( fAngle2 );
				m_tTailList[0].pTransform->Position( m_tPos + tHeadToTail.Normalize() * ( m_tTailList[0].fSegmentLength));
					}

			 m_tTailList[0].pBody->Position( m_tPos+ tHeadToTail.Normalize() * 	 m_tTailList[m_iTailCount-1].fSegmentLength/2.0f );
			 	fAngle2 = CorrectRange( atan2f(tHeadToTail.y, tHeadToTail.x)  );
			 m_tTailList[0].pBody->Rotation(fAngle2);



			 }else{
	 
/*
	 tTailToTail = m_tTailList[i-1].pTransform->Position() - m_tTailList[i].pTransform->Position() ;

	fAngle2 = CorrectRange(atan2f(tTailToTail.y, tTailToTail.x) );
	*/


		tHeadToTail =   m_tTailList[i].pTransform->Position()  - m_tTailList[i-1].pTransform->Position()  ;
	
			fAngle2 = CorrectRange( atan2f(tHeadToTail.y, tHeadToTail.x)  );


			 if(      CorrectRange(   m_tTailList[i-1].pTransform->Rotation()   - fAngle2  ) > -m_fTailAngleMax  &&  CorrectRange(   m_tTailList[i-1].pTransform->Rotation()   - fAngle2  ) <0) 
			 {					 
				TGfxVec2 tAngleVector =  TGfxVec2(cosf (CorrectRange( m_tTailList[i-1].pTransform->Rotation() +m_fTailAngleMax)), sinf(CorrectRange( m_tTailList[i-1].pTransform->Rotation() + m_fTailAngleMax )));
				m_tTailList[i].pTransform->Position( m_tTailList[i-1].pTransform->Position() + tAngleVector * ( m_tTailList[m_iTailCount-1].fSegmentLength));	 
				tTailToHead =   m_tTailList[i-1].pTransform->Position()  - m_tTailList[i].pTransform->Position()  ;	
				fAngle2 = CorrectRange( atan2f(tTailToHead.y, tTailToHead.x)  );
				m_tTailList[i].pTransform->Rotation( fAngle2 );

			 } else if	( CorrectRange(   m_tTailList[i-1].pTransform->Rotation() -fAngle2    ) <  (m_fTailAngleMax) && CorrectRange(   m_tTailList[i-1].pTransform->Rotation()   - fAngle2  ) >0 )				{
		 		TGfxVec2 tAngleVector = TGfxVec2(cosf (CorrectRange( m_tTailList[i-1].pTransform->Rotation() - m_fTailAngleMax)), sinf(CorrectRange( m_tTailList[i-1].pTransform->Rotation() -m_fTailAngleMax)));				
				m_tTailList[i].pTransform->Position( m_tTailList[i-1].pTransform->Position() + tAngleVector* ( m_tTailList[m_iTailCount-1].fSegmentLength));
				tTailToHead =   m_tTailList[i-1].pTransform->Position()  - m_tTailList[i].pTransform->Position()  ;	
				fAngle2 = CorrectRange( atan2f(tTailToHead.y, tTailToHead.x)  );
				m_tTailList[i].pTransform->Rotation( fAngle2 );
			
				}else{
				tTailToHead =   m_tTailList[i-1].pTransform->Position()  - m_tTailList[i].pTransform->Position()  ;	
				fAngle2 = CorrectRange( atan2f(tTailToHead.y, tTailToHead.x)  );
			 	m_tTailList[i].pTransform->Rotation( fAngle2 );
				m_tTailList[i].pTransform->Position( m_tTailList[i-1].pTransform->Position() - tTailToHead.Normalize() * ( m_tTailList[m_iTailCount-1].fSegmentLength));
			 
					}

			 	 m_tTailList[i].pBody->Position(  m_tTailList[i-1].pTransform->Position()+ tHeadToTail.Normalize() * 	 m_tTailList[m_iTailCount-1].fSegmentLength/2.0f);
				 	fAngle2 = CorrectRange( atan2f(tHeadToTail.y, tHeadToTail.x)  );
			 m_tTailList[i].pBody->Rotation(fAngle2);

			 

	//	m_tTailList[i-1].pTransform->Rotation()
	/*
	 if(      CorrectRange(   m_fAngle   - fAngle2  ) > -m_fTailAngleMax) 
	 {
		 
		m_tTailList[i].pTransform->Rotation( CorrectRange(m_fAngle + m_fTailAngleMax ) );
		m_tTailList[i].pTransform->Position( m_tTailList[i-1].pTransform->Position() - tTailToTail.Normalize() * ( m_tTailList[i].fRadius *2.0f +0.3f) ) ;
		
	 } else if	( CorrectRange(   m_fAngle -fAngle2    ) < (m_fTailAngleMax) ) 				{
			m_tTailList[i].pTransform->Rotation( CorrectRange(m_fAngle - m_fTailAngleMax ) );
		m_tTailList[i].pTransform->Position( m_tTailList[i-1].pTransform->Position() - tTailToTail.Normalize() * ( m_tTailList[i].fRadius *2.0f +0.3f) ) ;
		
		 }else{
		m_tTailList[i].pTransform->Rotation( fAngle2 );
		m_tTailList[i].pTransform->Position( m_tTailList[i-1].pTransform->Position() - tTailToTail.Normalize() * ( m_tTailList[i].fRadius *2.0f +0.3f) ) ;
			}


		*/	

		/*
	m_tTailList[i].pTransform->Rotation( fAngle2 );
	m_tTailList[i].pTransform->Position( m_tTailList[i-1].pTransform->Position() - tTailToTail.Normalize() * ( m_tTailList[i].fRadius *2.0f +0.3f) ) ;*/
		}
	}
	


	for(int i =0; i<m_iTailCount ; i++)
	{
		if(i == 0)
		{

			TGfxVec2 tailvector =  m_tPos -m_tTailList[i+1].pTransform->Position() ;
			m_tTailList[i].pTransform->Rotation( CorrectRange( atan2f( tailvector.y, tailvector.x ))) ;
			
		
		} else if (i != m_iTailCount-1)
		{
			TGfxVec2 tailvector = m_tTailList[i-1].pTransform->Position() - m_tTailList[i+1].pTransform->Position();
			m_tTailList[i].pTransform->Rotation( CorrectRange( atan2f( tailvector.y, tailvector.x ))) ;
			
		
		
		}

		


	}



	



return true;


}
#ifdef TFA_FRESH





void TSandWorm::SendDataToFresh(){


						#ifdef TFA_FRESH
					
						lua_pushnumber(GfxFreshLuaState(), m_tPos.x);
						lua_pushnumber(GfxFreshLuaState(), 0);
						lua_pushnumber(GfxFreshLuaState(), -m_tPos.y);
						
						lua_pushnumber(GfxFreshLuaState(), m_fAngle+PI_2);
						LuaCallGlobal(GfxFreshLuaState(), "WormHeadPosition");
						#endif
						
						#ifdef TFA_FRESH

						
						for(int i= 0; i<m_iTailCount; i++)
						{
							lua_pushinteger(GfxFreshLuaState(), i);
							lua_pushnumber(GfxFreshLuaState(), m_tTailList[i].pTransform->Position().x);
							lua_pushnumber(GfxFreshLuaState(), 0);
							lua_pushnumber(GfxFreshLuaState(), -m_tTailList[i].pTransform->Position().y);
						
							lua_pushnumber(GfxFreshLuaState(), m_tTailList[i].pTransform->Rotation()+PI_2);
							LuaCallGlobal(GfxFreshLuaState(), "WormTailPosition");
				
						
						}
						#endif

}
	#endif 