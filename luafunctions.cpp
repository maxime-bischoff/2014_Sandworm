#include "flib.h"



#include "flib_vec2.h"

#include "transform.h"

#include "collision.h"
#include "hitbox.h"
#include "player.h"
#include "sandworm.h"
#include "wall.h"

#include "area.h"

#include "offering.h"
//#include "functions.h"
#include "scene.h"
#include "game.h"
#include "lua.h"
#include "const.h"
#include "luafunctions.h"

int LuaGetPlayerParams(lua_State * L){
	

	TGfxVec2 tPosition = 	TGame::m_tScene->m_pPlayer->Position();
	float fAngle = TGame::m_tScene->m_pPlayer->Rotation()+PI_2;
	lua_pushnumber(L, tPosition.x);
	lua_pushnumber(L, TGame::m_tScene->m_pPlayer->m_fHeightPos);
	lua_pushnumber(L, tPosition.y);
	lua_pushnumber(L, fAngle);

return 4;
}



int LuaGetTailCount(lua_State * L){
	lua_pushinteger(L, TGame::m_tScene->m_pSandWorm->GetTailCount());
	return 1;
}

int LuaGetWall(lua_State * L){

	int iIndex  = lua_tointeger(L,1) - 1;
	lua_pushnumber(L, TGame::m_tScene->m_pWallList[iIndex]->Position().x);
	lua_pushnumber(L, TGame::m_tScene->m_pWallList[iIndex]->Position().y);
	lua_pushnumber(L, TGame::m_tScene->m_pWallList[iIndex]->GetSize().x);
	lua_pushnumber(L, TGame::m_tScene->m_pWallList[iIndex]->GetSize().y);
	return 4;
}

int LuaGetWallCount( lua_State * L){



	lua_pushinteger(L, TGame::m_tScene->m_iWallCount);
	return 1;


}

int LuaGetWormRadius(lua_State * L){


	lua_pushnumber(L, TGame::m_tScene->m_pSandWorm->GetRadius());


	return 1;


}


int LuaGetWormHeadParams(lua_State * L){

	lua_pushnumber(L, TGame::m_tScene->m_pSandWorm->Position().x);
	lua_pushnumber(L, TGame::m_tScene->m_pSandWorm->Position().y);
	lua_pushnumber(L, TGame::m_tScene->m_pSandWorm->Rotation());
	return 3;
}

int LuaGetWormTailParams(lua_State * L){

	int iIndex  = lua_tointeger(L,1) - 1;
	lua_pushnumber(L, TGame::m_tScene->m_pSandWorm->m_tTailList[iIndex].pTransform->Position().x);
	lua_pushnumber(L, TGame::m_tScene->m_pSandWorm->m_tTailList[iIndex].pTransform->Position().y);
	lua_pushnumber(L, TGame::m_tScene->m_pSandWorm->m_tTailList[iIndex].pTransform->Rotation());
	


	return 3;
}




void InitLuaFunctions(){

#ifdef TFA_FRESH
	lua_pushcfunction( GfxFreshLuaState(), LuaGetPlayerParams );
	lua_setglobal(GfxFreshLuaState(), "LuaGetPlayerParams");

	lua_pushcfunction( GfxFreshLuaState(), LuaGetTailCount);
	lua_setglobal(GfxFreshLuaState(), "LuaGetTailCount");

	lua_pushcfunction( GfxFreshLuaState(), LuaGetWormRadius);
	lua_setglobal(GfxFreshLuaState(), "LuaGetWormRadius");

	lua_pushcfunction( GfxFreshLuaState(), LuaGetWormHeadParams );
	lua_setglobal(GfxFreshLuaState(), "LuaGetWormHeadParams");

	lua_pushcfunction( GfxFreshLuaState(), LuaGetWormTailParams);
	lua_setglobal(GfxFreshLuaState(), "LuaGetWormTailParams");

	lua_pushcfunction( GfxFreshLuaState(), LuaGetWall );
	lua_setglobal(GfxFreshLuaState(), "LuaGetWall");

	lua_pushcfunction( GfxFreshLuaState(), LuaGetWallCount);
	lua_setglobal(GfxFreshLuaState(), "LuaGetWallCount");

	

#endif



	

}