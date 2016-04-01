#include "flib.h"
#include "flib_vec2.h"
#include "flib_vec3.h"
#include "transform.h"
#include "scene.h"
#include "offering.h"
#include "player.h"
#include "collision.h"
#include "collumn.h"
#include "sandworm.h"
#include "wall.h"
#include "game.h"
#include "functions.h"

#include "const.h"
#include <math.h>



TPlayer::TPlayer(TGfxVec2 tPos, float fAngle):TTransform(tPos, fAngle)
{
	m_bDirectionControl = 2;
	m_eMovingState = Walking;
	m_ePlayerState = Alive;
	m_bIsHovering = false;
	m_bThrust = false;
	m_tInertiaVector = TGfxVec2(0,0);
	m_fRadius = 0.5f;
	m_iColor = GfxColor(255,255,0,255);

	m_tSpawnPosition = tPos;
	m_fWalkSpeed = 0;
	m_fWalkAccel = 3;
	m_fWalkMaxSpeed = 15;
	m_fMaxHp = 100.0f;
	m_fHP = m_fMaxHp;

	m_iOfferingCount = 0;

	m_HoveringMaxSpeed = 20;
	m_fRotationSpeed = PI*5.0f ;
	
	m_fThrustRotationSpeed = PI;

	m_fHoveringRotationSpeed = 6.28f *3.0f ; // Rad par secondes
	m_fHoveringAccel = 1.03f;

	AddHitBox(m_fRadius, TGfxVec2(0,0));
	m_tSpeed = TGfxVec2(0,0);
	m_fThrustMaxPower = 4.0f;
	m_fThrustAccel = 0.3f;
	m_fThrustDecel = 0.4f;
	m_fThrustPower = 0.0f;
	m_fThrustMaxSpeed = 32.0f;
	m_fThrustSpeed = 0.0f;
	
	m_fIntertiaSpeed = 0.0f;

	 m_fScaleCamera =1.4f;
	 m_fScaleIncreaseSpeed = 0.005f;
	 m_fScaleDecreaseSpeed = 0.01f;

	 m_fMaxScale = 1.4f;
	 m_fMinScale = 0.8f;
	 
	 m_iReloadDelay = 3000;
	 m_iLastBoostUsed = 0;
	 m_iBoostDelay = 250;
	 m_iLastBoostRecovered =0;
	 m_iBoostAvailable = 3;
	 m_iMaxBoost = 3;

	 m_iEggCount =0;
	 m_fAngle = PI_2;
	 m_fHeightPos = 0;
	 m_fVerticalSpeed = 0; 




}


TPlayer::~TPlayer(void)
{
	
}

void TPlayer::Move( const TGfxVec2 &tSpeed)
{

	

			 int iNbPasses=1;
			 int iMaxPasses = 3;
			 bool bCollision = false;
	


			 while ( iNbPasses <= iMaxPasses && !bCollision)
			 {
				// float fSpeed

				 TGfxVec2 tSpeedCut = (	tSpeed * ( GfxTimeFrameGetAverageDurationInSeconds()*1.0f))/(iMaxPasses*1.0f);
				  
				 Translate(tSpeedCut);

				 for(int i=0; i< TGame::m_tScene->m_iWallCount; i++)
				 {
					TCollideResult tCollideResult;
					float distance =  (Position() - TGame::m_tScene->m_pWallList[i]->Position()).SquaredLength() ;
					if   (distance <4000.0f)
					{
						tCollideResult = Collide(this, TGame::m_tScene->m_pWallList[i]);
						if(tCollideResult.fLength !=0)
						{							
							CollideWall(tCollideResult);	
							bCollision = true;
						}							
					}
				}

				 for(int i=0; i< TGame::m_tScene->m_pSandWorm->GetTailCount(); i++)
				{
					if(TGame::m_tScene->m_pSandWorm->m_tTailList[i].pTransform !=0)
					{
						float fDistance = (m_tPos - TGame::m_tScene->m_pSandWorm->m_tTailList[i].pTransform->Position()).SquaredLength();
						if(fDistance <3000.0f)
						{
							TCollideResult tResult;
							tResult = Collide(this, TGame::m_tScene->m_pSandWorm->m_tTailList[i].pTransform);

							if(tResult.fLength != 0)
								this->CollideWorm(tResult);

							if(TGame::m_tScene->m_pSandWorm->m_tTailList[i].pBody !=0)
							{

									tResult = Collide(this, TGame::m_tScene->m_pSandWorm->m_tTailList[i].pBody);

								if(tResult.fLength != 0){
									this->CollideWorm(tResult);
									bCollision = true;
								}
							}
						}		
					}
				}

				 

	for(int i = 0; i<TGame::m_tScene->m_iColumnCount;i++)
	{	
		if(TGame::m_tScene->m_pColumnList[i]!=0)
		{

			if(!TGame::m_tScene->m_pColumnList[i]->IsDestroyed())
			{
				float fDistance = (this->Position() - TGame::m_tScene->m_pColumnList[i]->Position()).SquaredLength();
				if(fDistance <8.0f)
				{
					TCollideResult tResult;
					tResult = Collide(this, TGame::m_tScene->m_pColumnList[i]);

					if(tResult.fLength != 0)
			
						this->CollideRock(tResult);			
				}
				
			}


		}
	}

	

				if(!bCollision)
				{
					iNbPasses ++;			
				}
			 
			}


}

unsigned int TPlayer::GetColor(){

	switch (m_eMovingState)
	{
	case Walking:	return  m_iColor;
					break;
	case Hovering:return GfxColor(255,110,0,255);
		break;
	case Thrust:return EGfxColor_Red;
		break;
	default:return  m_iColor;
		break;
	}



}

void TPlayer::Damage(float fDamage){


	m_fHP-=fDamage;

	if(m_fHP <0) m_fHP = 0;

}


float  TPlayer::GetScaleCameraValue(){


	return m_fScaleCamera;


}


bool TPlayer::Update(TScene * tScene)
{


	if(GfxInputIsJustPressed(EGfxInputID_AnyPadShoulderL))
	{
		#ifdef TFA_FRESH
				LuaCallGlobal(GfxFreshLuaState(), "ToggleCamera");

		#endif
	
	
	
	}


	m_fVerticalSpeed -= 18.0f * GfxTimeFrameGetAverageDurationInSeconds(); 

	bool bJumping = false;
	if(m_fHeightPos >0)
	{
		bJumping = true;	
	}
	m_fHeightPos += m_fVerticalSpeed * GfxTimeFrameGetAverageDurationInSeconds();;

	if(m_fHeightPos <0) {
			m_fHeightPos = 0;
			if(bJumping){
			
				#ifdef TFA_FRESH
					LuaCallGlobal(GfxFreshLuaState(), "Land");
				#endif
				}
			}

	


	if(m_eMovingState == Walking)
	{
	
		if(GfxInputIsJustPressed(EGfxInputID_AnyPadTriangle) && m_fHeightPos == 0)
		{
		
			m_fVerticalSpeed = 10.0f;
		
		}

	
	
	}




	m_tSpeed*=0.995f;

	if(GfxInputIsJustPressed(EGfxInputID_AnyPadSelect)){
	//	if(m_bDirectionControl ==1) m_bDirectionControl = 2 ; else m_bDirectionControl = 1;
	
	
	}



	int iCurrentTime  = GfxTimeGetMilliseconds();
	if(m_iBoostAvailable< m_iMaxBoost)
	{		
			if(m_iLastBoostRecovered+  m_iReloadDelay < iCurrentTime && m_iLastBoostUsed + m_iReloadDelay < iCurrentTime)
			{
				m_iBoostAvailable++;
				m_iLastBoostRecovered = iCurrentTime;			
			}
	}




	float fDistanceWorm = ( tScene->m_pSandWorm->Position() - m_tPos).Length();

	if(tScene->m_pSandWorm->GetState() == Hunting &&  (m_eMovingState == Thrust || m_eMovingState == Hovering ) && fDistanceWorm < 25)
	{
		m_fScaleCamera-= m_fScaleDecreaseSpeed;
		if ( m_fScaleCamera <m_fMinScale) m_fScaleCamera = m_fMinScale;
	
	
	
	}else {
	
		m_fScaleCamera+= m_fScaleIncreaseSpeed;
		if ( m_fScaleCamera > m_fMaxScale) m_fScaleCamera = m_fMaxScale;
	
	}





	 float fStickLeftX = GfxInputGetPadStickLeftX();
	 float fStickLeftY = GfxInputGetPadStickLeftY();
	

	 fStickLeftX = MClamp(fStickLeftX, -1 ,1);
	 fStickLeftY = MClamp(fStickLeftY, -1 ,1);
	 bool bInputActionPressed = GfxInputIsPressed(EGfxInputID_AnyPadSquare);
	 bool bInputActionJustPressed  = GfxInputIsJustPressed(EGfxInputID_AnyPadSquare);
	 bool bInputActionJustReleased  = GfxInputIsJustReleased(EGfxInputID_AnyPadSquare);

	 bool bInputBrakePressed = GfxInputIsPressed(EGfxInputID_AnyPadCircle);

	 bool bInputBoostJustPressed  = GfxInputIsJustPressed(EGfxInputID_KeyCharB);
	


	  if(bInputBoostJustPressed)
	  {
		  m_iBoostAvailable = 0;
		  if(m_iBoostAvailable>0)
		  {
			  if(m_iLastBoostUsed + m_iBoostDelay)
			  {
				  m_iLastBoostUsed = iCurrentTime;
				  m_iBoostAvailable --;
				  m_tSpeed =  TGfxVec2( cosf(m_fAngle), sinf(m_fAngle))*(m_fThrustMaxSpeed );

				  if(m_eMovingState == Walking){m_eMovingState = Hovering;};
			  }
		  }
	  }


	 if(bInputActionJustPressed)
	 {
		 if(m_eMovingState == Walking)
		 {
			 m_fThrustSpeed = m_fWalkSpeed;
		 
		 }else{
		 
	//	  m_tSpeed  *= 0.5f;
		 
		 }

	
	 }
	


	 if(bInputBrakePressed)
	 {
		 m_fThrustSpeed -=   60.0f* GfxTimeFrameGetAverageDurationInSeconds();
		 if(m_fThrustSpeed<0) m_fThrustSpeed = 0;


		  if(m_fThrustSpeed < 10.0f ) {
			 m_bIsHovering = false;
			 m_eMovingState = Walking;
			 m_tInertiaVector = TGfxVec2(0,0);
			 m_fIntertiaSpeed = 0;
			 m_fThrustSpeed  = 0;
	 		 m_tSpeed = TGfxVec2(0,0);

		  }

	 if(m_fThrustSpeed<0) m_fThrustSpeed = 0;
	 



		// m_tSpeed -= 5.0f * GfxTimeFrameGetCurrentDurationInSeconds();
	 
	 }


	 if(bInputActionJustReleased /* || fStickLeftY <0.1f*/ )
	 {
		
		 m_eMovingState = Hovering;
		 m_tRotationAxe = TGfxVec2(cosf(m_fAngle) * 1, sinf(m_fAngle) * 1) + m_tPos;
		// m_tSpeed = TGfxVec2(sinf(m_fAngle), cosf(m_fAngle)) * m_fThrustSpeed ;
		 //m_fIntertiaSpeed =  m_fThrustSpeed;

		// m_fThrustSpeed = 0;
	 
	 }

	 


	 if(bInputActionPressed /*|| fStickLeftY > 0.1f*/)
	 {


		 m_tSpeed*=0.90f;
		float angle  = atan2f(fStickLeftY,fStickLeftX) ;

		angle = CorrectRange(angle);	

		 if(m_bDirectionControl ==1){

			  
			 m_fAngle += fStickLeftX * m_fThrustRotationSpeed * GfxTimeFrameGetAverageDurationInSeconds();
		
			 

		 }else{
		
			if (fabs( fStickLeftX )+ fabs(fStickLeftY)<0.1f ){} else		 
			 {
				if ( CorrectRange(m_fAngle -angle  ) > 0)
				{
					if(CorrectRange(m_fAngle -angle  )> m_fThrustRotationSpeed * GfxTimeFrameGetAverageDurationInSeconds()){
					angle = (m_fAngle - m_fThrustRotationSpeed * GfxTimeFrameGetAverageDurationInSeconds());			
					m_fAngle = CorrectRange(angle);
					}else {m_fAngle = CorrectRange(angle);}

				}
				 else{
					 if( fabs(CorrectRange(m_fAngle -angle  ))> m_fThrustRotationSpeed * GfxTimeFrameGetAverageDurationInSeconds()){
					angle = (m_fAngle + m_fThrustRotationSpeed * GfxTimeFrameGetAverageDurationInSeconds());
					m_fAngle = CorrectRange(angle);
					}else {m_fAngle = CorrectRange(angle);}
				}
			 }

		 }
		
	
	
		 m_eMovingState = Thrust;
	
		 m_fThrustPower += m_fThrustAccel;

		 if(m_fThrustPower > m_fThrustMaxPower)
			 m_fThrustPower = m_fThrustMaxPower;

		 m_fThrustSpeed += m_fThrustPower;

		 if(m_fThrustSpeed> m_fThrustMaxSpeed)
			 m_fThrustSpeed = m_fThrustMaxSpeed;



		 		m_tSpeed = m_tSpeed +  TGfxVec2( cosf(m_fAngle), sinf(m_fAngle))*(m_fThrustSpeed/6.0f );

			 if(m_tSpeed.Length() > m_fThrustMaxSpeed)
			 {		 
				 m_tSpeed = m_tSpeed.Normalize() * m_fThrustMaxSpeed;			 
			 }





	 }else{
		 
		 
		 m_fThrustPower -= m_fThrustDecel;
		

		 if(m_fThrustPower < 0 )
			 m_fThrustPower = 0;

		if( m_fIntertiaSpeed <0)
			 m_fIntertiaSpeed = 0;

		
	 m_fThrustSpeed -= 0.5f;

	 if(m_fThrustSpeed <0) m_fThrustSpeed = 0;


	 if(m_eMovingState == Hovering){

		 if(m_bDirectionControl ==1){
		 
			 m_fAngle += fStickLeftX * m_fHoveringRotationSpeed * GfxTimeFrameGetAverageDurationInSeconds();
		 
		//	Translate( m_tSpeed* GfxTimeFrameGetCurrentDurationInSeconds());
		
		 
		 } else{
			  float angle  = atan2f(fStickLeftY,fStickLeftX) ;

			angle = CorrectRange(angle);	

			if (fabs( fStickLeftX )+ fabs(fStickLeftY)<0.1f ){} else		 
			 {
				if ( CorrectRange(m_fAngle -angle  ) > 0)
				{
					if(CorrectRange(m_fAngle -angle  )> m_fHoveringRotationSpeed * GfxTimeFrameGetAverageDurationInSeconds() ){
					angle = (m_fAngle - m_fHoveringRotationSpeed *GfxTimeFrameGetAverageDurationInSeconds());			
					m_fAngle = CorrectRange(angle);
					}else {m_fAngle = CorrectRange(angle);}

				}
				 else{
					 if( fabs(CorrectRange(m_fAngle -angle  ))> m_fHoveringRotationSpeed *GfxTimeFrameGetAverageDurationInSeconds()){
					angle = (m_fAngle + m_fHoveringRotationSpeed *GfxTimeFrameGetAverageDurationInSeconds());
					m_fAngle = CorrectRange(angle);
					}else {m_fAngle = CorrectRange(angle);}
				}
			 }
	 
	 // Translate(m_tSpeed  * GfxTimeFrameGetCurrentDurationInSeconds());

		 }


	 		
	 }
	 
	 }


	 	




	 if(m_eMovingState == Walking && !bInputActionPressed)
	 {
	 
		 m_tSpeed *=0.9f;
		
	 
	 }




	 if(m_eMovingState == Walking){


		float fStickAngle  = atan2f(fStickLeftY,fStickLeftX) ;

		fStickAngle = CorrectRange(fStickAngle);	

		if (fabs( fStickLeftX )+ fabs(fStickLeftY)<0.01f ){} else		 
		 {
			if ( CorrectRange(m_fAngle -fStickAngle  ) > 0)
			{
				if(CorrectRange(m_fAngle -fStickAngle  )> m_fRotationSpeed * GfxTimeFrameGetAverageDurationInSeconds()){
				fStickAngle = (m_fAngle - m_fRotationSpeed * GfxTimeFrameGetAverageDurationInSeconds());			
				m_fAngle = CorrectRange(fStickAngle);
				}else {m_fAngle = CorrectRange(fStickAngle);}

			}
			 else{
				 if( fabs(CorrectRange(m_fAngle -fStickAngle  ))> m_fRotationSpeed * GfxTimeFrameGetAverageDurationInSeconds()){
				fStickAngle = (m_fAngle + m_fRotationSpeed * GfxTimeFrameGetAverageDurationInSeconds());
				m_fAngle = CorrectRange(fStickAngle);
				}else {m_fAngle = CorrectRange(fStickAngle);}
			}
		 }
		

		fStickAngle  = atan2f(fStickLeftY,fStickLeftX) ;

		fStickAngle = CorrectRange(fStickAngle);	
		
	
		float fValue =  MClamp( fabs( fStickLeftX) + fabs(fStickLeftY), 0, 1);
		


		//GfxDbgPrintf("fValue = %f \n", fValue);
		m_fWalkSpeed = MLerp(m_fWalkSpeed, m_fWalkMaxSpeed * fValue, GfxTimeFrameGetAverageDurationInSeconds() * 8.0f);
		//GfxDbgPrintf("m_fWalkSpeed = %f \n", m_fWalkSpeed);
	//	if(m_fWalkSpeed>m_fWalkMaxSpeed)m_fWalkSpeed = m_fWalkMaxSpeed;

		//if(fStickLeftX ==0 && fStickLeftY ==0) m_fWalkSpeed = 0;

		TGfxVec2 tSpeed = TGfxVec2(cosf(m_fAngle), sinf(m_fAngle));
		//m_tPos+= tSpeed * m_fWalkSpeed*GfxTimeFrameGetCurrentDurationInSeconds();


		Move(tSpeed* m_fWalkSpeed);
	
#ifdef TFA_FRESH
	//	GfxDbgPrintf("Height %f \n", m_fHeightPos);
			lua_pushnumber(GfxFreshLuaState(), m_fWalkSpeed);
			lua_pushnumber(GfxFreshLuaState(), m_fWalkMaxSpeed);
			lua_pushnumber(GfxFreshLuaState(), m_fWalkMaxSpeed);
			lua_pushnumber(GfxFreshLuaState(), m_fWalkMaxSpeed);
			lua_pushnumber(GfxFreshLuaState(), m_fHeightPos);
		
			LuaCallGlobal(GfxFreshLuaState(), "BlendAnimWalking");
#endif

				
	}else
	 {

		 #ifdef TFA_FRESH
	//	GfxDbgPrintf("Height %f \n", m_fHeightPos);
		
		 lua_pushnumber(GfxFreshLuaState(), m_tSpeed.Length());
		 lua_pushnumber(GfxFreshLuaState(), m_HoveringMaxSpeed);						
			LuaCallGlobal(GfxFreshLuaState(), "BlendAnimHovering");
		#endif

		
	
		 Move(m_tSpeed);




	
	
	
	
	}

		

	 for(int i = 0; i<tScene->MAX_OFFERING;i++)
	 {
		 if(tScene->m_pOfferingList[i] !=0)
		 {
			 if(tScene->m_pOfferingList[i]->IsActive())
			 {


				 if(   (tScene->m_pOfferingList[i]->Position()  - m_tPos).Length() <m_fRadius + tScene->m_pOfferingList[i]->GetRadius())
				 {

					 if(tScene->m_pOfferingList[i]->IsStarter()){
						tScene->m_pOfferingList[i]->Pick();
						 tScene->m_pSandWorm->SetAngry();

						#ifdef TFA_FRESH
							LuaCallGlobal(GfxFreshLuaState(), "StarterPicked");	
							
						#endif 

						
						 for(int i= 0; i<tScene->MAX_OFFERING; i++)
						 {
							  if( tScene->m_pOfferingList[i]!=0)
							  {
								  tScene->m_pOfferingList[i]->SetActive();				  
							  }
						 }

					 }else{
					 
					 tScene->m_pOfferingList[i]->Pick();	
					 
					 	 m_iEggCount++;

				#ifdef TFA_FRESH
					lua_pushinteger(GfxFreshLuaState(), i+1);
					LuaCallGlobal(GfxFreshLuaState(), "PickOffering");		

					lua_pushinteger(GfxFreshLuaState(), m_iEggCount);
					LuaCallGlobal(GfxFreshLuaState(), "SetEggCount");				 


				#endif
				

				


					 }
				 }
				 		 
			  }
		 }
	 
	 
	 }
	 

//#ifdef TFA_FRESH
		/*
	float fUnitX =  tScene->m_tHeightMapSize.x / 130.0f;
	float fUnitY =  tScene->m_tHeightMapSize.y / 90.0f;
	//fUnitX = 2.0f;
	//fUnitY = 2.0f;
	float fPosXTemp = m_tPos.x + 130.0f / 2.0f;
	float fPosYTemp = m_tPos.y - 90.0f / 2.0f;
	GfxDbgPrintf("PlayerUpdate9.051");
	if(fPosXTemp >0 && fPosYTemp < 0 )
	{

		GfxDbgPrintf("PlayerUpdate9.1");
		if( static_cast<int>( fPosXTemp * fUnitX) < tScene->m_tHeightMapSize.x-20  &&  static_cast<int>( fPosYTemp* fUnitY) > -tScene->m_tHeightMapSize.y+20 )
		{	
			float fXCoord =  fPosXTemp * (fUnitX);
			float fYCoord = ( -fPosYTemp * (fUnitY) );

			int iXCoord = static_cast<int>(fXCoord) ;
			int iYCoord = static_cast<int>(fYCoord) ;
			int iYValue = static_cast<int>(iYCoord *tScene->m_tHeightMapSize.x) ;
			int iIndex = iXCoord + iYValue;
			unsigned int iColor = tScene->pData_heightmap[ iIndex];
			TGfxVec3 tHeight = 	ColorIntToVec3(iColor);
			//GfxDbgPrintf(" Height  = %f\n", tHeight.x);		
			GfxDbgPrintf("PlayerUpdate9.2");
		//	m_fHeightPos = 17.0f*tHeight.x;
			//GfxDbgPrintf("PosX : %f PosY : %f PosZ : %f \n", fXCoord,m_fHeightPos, fYCoord);		
		}	
	}
	*/


//#endif


	

			return true;
}

void TPlayer::CollideWall(TCollideResult &tResult){


	Translate(  tResult.tNormal * tResult.fLength);

//	Translate(  -m_tSpeed*GfxTimeFrameGetAverageDurationInSeconds()/3.0f);
//	Translate( ( m_tSpeed*GfxTimeFrameGetAverageDurationInSeconds()/3.0f + tResult.tNormal * tResult.fLength ).Normalize() * (m_tSpeed*GfxTimeFrameGetAverageDurationInSeconds()/3.0f).Length()  );
	//Translate( ( m_tSpeed*GfxTimeFrameGetAverageDurationInSeconds()/3.0f + tResult.tNormal * tResult.fLength ).Normalize() * (m_tSpeed*GfxTimeFrameGetAverageDurationInSeconds()/3.0f).Length()  );
	

	//m_bIsHovering = false;
	//m_tSpeed = TGfxVec2(0,0);
	//m_tSpeed *= 0.98f;

	if(m_eMovingState != Walking)
	{
		return;
	//	float fBounceCoeff = 1-  tResult.tNormal.DotProduct(-m_tSpeed.Normalize());
	
	//	m_tSpeed += ( ( (tResult.tNormal)  *  -m_tSpeed.DotProduct(tResult.tNormal) ) * 2.0f )  ;
	//	m_tSpeed *= fBounceCoeff;

	

	//	m_fAngle = atan2f(m_tSpeed.y, m_tSpeed.x);
	}
	//m_eMovingState = Walking;
	//m_fThrustSpeed *= 0.20f;
	//m_fThrustPower = 0;
	

}

void TPlayer::CollideRock(TCollideResult &tResult){


	Translate(tResult.tNormal * tResult.fLength);
	m_bIsHovering = false;
	//m_tSpeed  *=0.8f;
	m_tSpeed += (tResult.tNormal * tResult.fLength);

	//m_fThrustPower = 0;
	//m_fThrustSpeed *= 0.97f;
	m_fIntertiaSpeed =0;


}

void TPlayer::CollideWorm(TCollideResult &tResult){


	Translate(tResult.tNormal * tResult.fLength);
	//m_bIsHovering = false;
	//m_tSpeed = TGfxVec2(0,0);
	//m_eMovingState = Walking;
	//m_fThrustSpeed *= 0.97f;


}

void TPlayer::SetSpawnPosition(TGfxVec2 tPos)
{
	m_tSpawnPosition = tPos;

}

#ifdef TFA_FRESH
void TPlayer::SendDataToFresh(){



	#ifdef TFA_FRESH
	
	lua_pushnumber(GfxFreshLuaState(), m_tPos.x);
	lua_pushnumber(GfxFreshLuaState(), m_fHeightPos);
	lua_pushnumber(GfxFreshLuaState(), -m_tPos.y);						
	lua_pushnumber(GfxFreshLuaState(), m_fAngle+PI_2);
	LuaCallGlobal(GfxFreshLuaState(), "PlayerSetPosition");
	



	if(m_eMovingState == Walking){
	
		lua_pushstring(GfxFreshLuaState(), "Walking");
	}else if (m_eMovingState ==  Hovering  || m_eMovingState == Thrust)
	{
		lua_pushstring(GfxFreshLuaState(), "Hovering");	
	}

	
	
	lua_pushnumber(GfxFreshLuaState(),m_fThrustSpeed );
	lua_pushnumber(GfxFreshLuaState(),m_fThrustMaxSpeed );
	lua_pushnumber(GfxFreshLuaState(),m_tSpeed.Length() );
	float fAngle = atan2(m_tSpeed.y, m_tSpeed.x);
	
	lua_pushnumber(GfxFreshLuaState(), fAngle  );
	LuaCallGlobal(GfxFreshLuaState(), "UpdateParticles");
#endif




}
#endif