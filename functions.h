#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

float CorrectRange(float fAngle);
float Min(float fValue1, float fValue2);
float Max(float fValue1, float fValue2);
float MClamp(float fValue, float fLimite1, float fLimite2);
float MLerp( float fValA, float fValB, float fWeight );
unsigned int ColorVec3ToInt(const struct TGfxVec3 &tColor);
struct TGfxVec3 ColorIntToVec3(unsigned int iColor);
#endif