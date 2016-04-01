#ifndef LUAFUNCTIONS_H_INCLUDED
#define LUAFUNCTIONS_H_INCLUDED

struct lua_state;
int LuaGetPlayerParams(lua_State * L);

int LuaGetWormHeadParams(lua_State * L);
int LuaGetWormTailParams(lua_State * L);
int LuaGetColumnParams(lua_State * L);
int LuaGetTailCount(lua_State * L);

int LuaGetWallCount( lua_State * L);

int LuaGetWormRadius(lua_State * L);

void InitLuaFunctions();



#endif