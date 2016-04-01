
#include "flib.h"
#include "flib_vec2.h"


#include "transform.h"
#include "hitbox.h"

#include "functions.h"
#include "scene.h"

#include <math.h>
#include "collision.h"










TCollideResult CollideCircle(TTransform * tFirst, TTransform * tOther){


	TGfxVec2 tFirstPos = tFirst->m_tHitBox->GetGlobalPos() ;
	TGfxVec2 tOtherPos = tOther->m_tHitBox->GetGlobalPos() ;

	float fDistance = (tFirstPos - tOtherPos).Length();

	float fFirstRadius = tFirst->m_tHitBox->GetRadius();
	float fOtherRadius = tOther->m_tHitBox->GetRadius();
	float fLength = 0;
	TGfxVec2 normVec;

	if(fDistance < fFirstRadius + fOtherRadius)
	{
		fLength = (fFirstRadius + fOtherRadius) - fDistance;
		if(tFirstPos !=tOtherPos)
		{
		normVec =  (tFirstPos-tOtherPos).Normalize();
		}
		else normVec = TGfxVec2(0,0);
			
	
	}
	
	TCollideResult result;
	result.fLength = fLength;
	result.tNormal = normVec;
	return result;




}

TCollideResult CollideCircleBox(TTransform * tCircle, TTransform * tBox){

	TCollideResult tResult;
	


	const TGfxVec2 & tBoxCenter = tBox->m_tHitBox->GetGlobalPos();
	const TGfxVec2 & tBoxRadius = tBox->m_tHitBox->GetRadiusBox();	
	const float fAngle = tBox->GetAngle();

	const TGfxVec2 & tCircleCenter = tCircle->m_tHitBox->GetGlobalPos();
	const float & fCircleRadius = tCircle->m_tHitBox->GetRadius();


	const TGfxVec2 tAxisX = TGfxVec2(cosf(fAngle),sinf(fAngle));
	const TGfxVec2 tAxisY = TGfxVec2(-sinf(fAngle),cosf(fAngle));
	
	const TGfxVec2 tAxeX = tBoxCenter + tAxisX ;
	const TGfxVec2 tAxeY = tBoxCenter + tAxisY ;

	float fDotProductX = (tCircleCenter-tBoxCenter).DotProduct(tAxeX-tBoxCenter) ;
	float fDotProductY = (tCircleCenter-tBoxCenter).DotProduct(tAxeY-tBoxCenter) ;

	const TGfxVec2 tAxeX2 = tBoxCenter + tAxisX * MClamp(fDotProductX, -tBoxRadius.x, tBoxRadius.x);
	const TGfxVec2 tAxeY2 = tBoxCenter + tAxisY * MClamp(fDotProductY, -tBoxRadius.y, tBoxRadius.y);

	const TGfxVec2 tNearestPoint = tAxeX2+tAxeY2 - tBoxCenter;

	if((tCircleCenter-tNearestPoint).Length()<fCircleRadius)
	{
		TGfxVec2 normVec;


		const TGfxVec2 tNormale = TGfxVec2(1, sin(fAngle));
		float length = fCircleRadius - (tCircleCenter-tNearestPoint).Length();

		if((tCircleCenter-tNearestPoint).Length() != 0)
		{
			normVec =  (tCircleCenter-tNearestPoint).Normalize();
		}else{
			normVec =  tCircleCenter-tNearestPoint;
		}
				
		tResult.fLength = length;
		tResult.tNormal = normVec;
		return tResult;


	
	}else{

		tResult.fLength = 0;
		return tResult;


	}

}

TCollideResult CollideCircleTriangle(TTransform * tCircle, TTransform * tBox){

	TCollideResult tResult;
	
	tResult.self = tCircle;
	tResult.other = tBox;


	
	const TGfxVec2 & tBoxCenter = tBox->m_tHitBox->GetGlobalPos();
	const TGfxVec2 & tBoxRadius = tBox->m_tHitBox->GetRadiusBox();	
	const float fAngle = tBox->GetAngle();

	const TGfxVec2 & tCircleCenter = tCircle->m_tHitBox->GetGlobalPos();
	const float & fCircleRadius = tCircle->m_tHitBox->GetRadius();


	const TGfxVec2 tAxisX = TGfxVec2(cosf(fAngle),sinf(fAngle));
	const TGfxVec2 tAxisY = TGfxVec2(-sinf(fAngle),cosf(fAngle));
	
	TGfxVec2 tCircleToBox = tCircleCenter - tBoxCenter;
	float fAngleNormal =  CorrectRange(  atan2f(tBox->m_tHitBox->GetNormal().y, tBox->m_tHitBox->GetNormal().x)  );

	float fAngleObjects = CorrectRange( atan2f(tCircleToBox.y, tCircleToBox.x)    );

	

		if(  CorrectRange(   fAngleNormal -fAngleObjects ) >  M_PI_2   || CorrectRange( fAngleNormal - fAngleObjects  ) < -M_PI_2   ){
		


				const TGfxVec2 tAxeX = tBoxCenter + tAxisX ;
	const TGfxVec2 tAxeY = tBoxCenter + tAxisY ;

	float fDotProductX = (tCircleCenter-tBoxCenter).DotProduct(tAxeX-tBoxCenter) ;
	float fDotProductY = (tCircleCenter-tBoxCenter).DotProduct(tAxeY-tBoxCenter) ;

	const TGfxVec2 tAxeX2 = tBoxCenter + tAxisX * MClamp(fDotProductX, -tBoxRadius.x, tBoxRadius.x);
	const TGfxVec2 tAxeY2 = tBoxCenter + tAxisY * MClamp(fDotProductY, -tBoxRadius.y, tBoxRadius.y);

	const TGfxVec2 tNearestPoint = tAxeX2+tAxeY2 - tBoxCenter;

	if((tCircleCenter-tNearestPoint).Length()<fCircleRadius)
	{
		TGfxVec2 normVec;


		const TGfxVec2 tNormale = TGfxVec2(1, sin(fAngle));
		float length = fCircleRadius - (tCircleCenter-tNearestPoint).Length();

		if((tCircleCenter-tNearestPoint).Length() != 0)
		{
			normVec =  (tCircleCenter-tNearestPoint).Normalize();
		}else{
			normVec =  tCircleCenter-tNearestPoint;
		}
				
		tResult.fLength = length;
		tResult.tNormal = normVec;
		return tResult;




	}

	}else{

		float length = tCircleToBox.DotProduct(tBox->m_tHitBox->GetNormal());
		if(length<fCircleRadius)
		{
			float distance = fabs(tCircleToBox.DotProduct(-tBox->m_tHitBox->GetTangent()));
			if(distance - fCircleRadius  < tBox->m_tHitBox->GetHypo()/2 )
			{
			tResult.fLength = length - fCircleRadius;
			tResult.tNormal = - tBox->m_tHitBox->GetNormal();
			return tResult;
			}
		}

	}
	tResult.fLength  = 0;
	return tResult;
	

}


TCollideResult Collide(TTransform * tFirst, TTransform * tOther){
	
	if(	tFirst->m_tHitBox->eCollisionType == Circle &&
		tOther->m_tHitBox->eCollisionType == Circle)
	{
		return CollideCircle(tFirst, tOther);

	}else if(	tFirst->m_tHitBox->eCollisionType == Circle && 
				tOther->m_tHitBox->eCollisionType == Box)
	{
		return CollideCircleBox(tFirst, tOther);

	}else if(	tFirst->m_tHitBox->eCollisionType == Box &&
				tOther->m_tHitBox->eCollisionType == Circle)
	{
		return CollideCircleBox(tOther, tFirst);
	}else if(	tFirst->m_tHitBox->eCollisionType == Circle &&
				tOther->m_tHitBox->eCollisionType == Triangle)
	{

		return CollideCircleTriangle(tFirst, tOther);


	}else{

		TCollideResult result;
		result.fLength = 0;

		return result;
	}


}


