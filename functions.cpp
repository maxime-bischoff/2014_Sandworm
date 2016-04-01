#include "flib.h"
#include "flib_vec2.h"
#include "flib_vec3.h"
#include "functions.h"
#include <math.h>
#include "const.h"
#include "luafunctions.h"



float CorrectRange(float fAngle)
{
	
	if(fAngle > PI) return 2.0f*-PI + fAngle;
	else if(fAngle< - PI) return  2.0f* PI +fAngle;
	else return fAngle;


}

float Min(float fValue1,float fValue2)
{
	if(fValue1 > fValue2) return fValue2; else return fValue1;
	

}


float Max(float fValue1,float fValue2)
{
	if(fValue1 < fValue2) return fValue2; else return fValue1;


}

float MLerp( float fValA, float fValB, float fWeight )
{
	return fValA + ( fValB - fValA ) * fWeight;
}

float MClamp(float fValue, float fLimite1, float fLimite2)
{
	if(fValue < fLimite1)
	{
		return fLimite1;
	}
	else {
		if(fValue>fLimite2)
		{
			return fLimite2;
		} else return fValue;
	}
}


unsigned int ColorVec3ToInt(const TGfxVec3 &tColor)
{
	/*if(tColor.x> 1) tColor.x = 1;
	if(tColor.y> 1) tColor.y = 1;
	if(tColor.z> 1) tColor.z = 1;*/


	return (GfxColor(tColor.x * 255 , tColor.y * 255, tColor.z * 255, 255));
}

TGfxVec3 ColorIntToVec3(unsigned int iColor)
{
	unsigned char * pColor = reinterpret_cast<unsigned char *>(&iColor);
	TGfxVec3 tColor;
	tColor.x = pColor[ 0 ] / 255.0f;
	tColor.y = pColor[ 1 ] / 255.0f;
	tColor.z = pColor[ 2 ] / 255.0f;
	return tColor;

}




/*
float CorrectRange(float fAngle)
{
	if(fAngle> M_PI) return 2*-M_PI + fAngle;
	else if(fAngle< - M_PI) return  2* M_PI +fAngle;
	else return fAngle;


}*/