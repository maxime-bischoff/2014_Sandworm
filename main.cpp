#include "flib.h"
#include "game.h"
TGame gGame;

void Initialize()
{
	gGame.Initialize();
}

void Update()
{
	gGame.Update();

}

void Render()
{
#ifndef TFA_FRESH
		GfxClear(EGfxColor_Black);
#endif
	gGame.Render();
}



void GfxMain( int, char * [] )
{
	

	GfxCallbacks(Initialize, Update, Render);
}
