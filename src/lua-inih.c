/*
* lua-inih.c: bindings for inih, simple .INI file parser
*/

#define LUAINIH_VERSION     "lua-inih 0.1"
#define LUAINIH_COPYRIGHT   "Copyright (C) 2010, lua-inih authors"
#define LUAINIH_DESCRIPTION "Bindings for inih r7, simple .INI file parser"

#if defined (__cplusplus) && !defined (LUABINS_LUABUILTASCPP)
extern "C" {
#endif

#include <lua.h>
#include <lauxlib.h>

#if defined (__cplusplus) && !defined (LUABINS_LUABUILTASCPP)
}
#endif

#include "ini.h"

/*
* inih.parse(filename : string, callback : function) : true / nil, error_message
*/
static int l_parse(lua_State * L)
{
  size_t len = 0;
  const char * filename = luaL_checklstring(L, 1, &len);
  luaL_checktype(L, 2, LUA_TFUNCTION);

  return luaL_error(L, "TODO: Implement");
}

/* luabins Lua module API */
static const struct luaL_reg R[] =
{
  { "parse", l_parse },
  { NULL, NULL }
};

#ifdef __cplusplus
extern "C" {
#endif

LUALIB_API int luaopen_inih(lua_State * L)
{
  /*
  * Register module
  */
  luaL_register(L, "inih", R);

  /*
  * Register module information
  */
  lua_pushliteral(L, LUAINIH_VERSION);
  lua_setfield(L, -2, "_VERSION");

  lua_pushliteral(L, LUAINIH_COPYRIGHT);
  lua_setfield(L, -2, "_COPYRIGHT");

  lua_pushliteral(L, LUAINIH_DESCRIPTION);
  lua_setfield(L, -2, "_DESCRIPTION");

  return 1;
}

#ifdef __cplusplus
}
#endif
