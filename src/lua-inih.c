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

static int callback(
    void * user,
    const char * section,
    const char * name,
    const char * value
  )
{
  lua_State * L = (lua_State *) user;
  int base = lua_gettop(L);

  /* TODO: Hack. Fix inih to stop at first error and remove this check */
  if (!lua_isfunction(L, -1))
  {
    /* Assuming we have an error message on stack */
    return 0;
  }

  lua_pushvalue(L, base); /* the function itself */
  lua_pushstring(L, section);
  lua_pushstring(L, name);
  lua_pushstring(L, value);

  if (lua_pcall(L, 3, 2, 0) != 0)
  {
    /* TODO: provide better error reporting */
    const char * error_message = lua_tostring(L, -1);

    lua_pop(L, 1);

    lua_pushnil(L);
    lua_pushfstring(
        L, "callback error: %s",
        (error_message != NULL)
          ? error_message
          : "(non-string error message)"
      );

    return 0; /* We've encountered an error */
  }

  if (!lua_toboolean(L, base + 1))
  {
    const char * error_message = lua_tostring(L, base + 2);
    lua_pop(L, 2);

    lua_pushnil(L);
    lua_pushstring(
        L,
        (error_message != NULL)
          ? error_message
          : "(unintelligible error from callback)"
      );

    return 0; /* We've encountered an error */
  }

  lua_pop(L, 2); /* Pop results */

  return 1; /* Continue parsing. */
}

/*
* inih.parse(filename : string, callback : function) : true / nil, error_message
*/
static int l_parse(lua_State * L)
{
  int base = lua_gettop(L);
  int error_line = 0;

  const char * filename = luaL_checkstring(L, 1);
  luaL_checktype(L, 2, LUA_TFUNCTION);

  error_line = ini_parse(filename, callback, L);
  if (error_line != 0)
  {
    const char * error_message = NULL;

    int new_base = lua_gettop(L);
    if (new_base == base)
    {
      lua_pushnil(L);
      lua_pushstring(
          L,
          (error_line == -1)
            ? "failed to open file"
            : "bad file format" /* TODO: Pick a better error message */
        );
    }
    else if (new_base != base + 2)
    {
      lua_settop(L, base);
      return luaL_error(
          L, "lua-inih: bad implementation, garbage on stack on error"
        );
    }

    error_message = lua_tostring(L, -1);
    lua_pop(L, 1);

    /* TODO: Trim filename */

    if (error_line == -1)
    {
      lua_pushfstring(
          L, "%s: %s",
          filename,
          (error_message != NULL)
            ? error_message
            : "unintelligible error message"
        );
    }
    else
    {
      lua_pushfstring(
          L, "%s:%d: %s",
          filename,
          error_line,
          (error_message != NULL)
            ? error_message
            : "unintelligible error message"
        );
    }

    return 2; /* nil and error message are already on stack */
  }

  lua_pushboolean(L, 1);

  return 1;
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
