#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED
class TTransform;
struct TGfxVec2;


struct TCollideResult
{
	TTransform * self;
	TTransform * other;
	TGfxVec2 tNormal;
	float fLength;
};



TCollideResult Collide(TTransform * tFirst, TTransform * tOher);


#endif