#ifndef __TYPE__H__LION
#define __TYPE__H__LION
#include "lua.h"
#include "lauxlib.h"
#include "errdef.h"
#include <errno.h>
#include <string.h>
#if defined(LINUX)
	#ifndef EXPORT
    	#define EXPORT extern
	#endif
#elif defined(WINDOW)
	#ifndef EXPORT
		#define EXPORT __declspec(dllexport)
	#endif
#endif


#ifndef CHECKNULL
	#define CHECKNULL(p,ret) if(p == NULL){return ret;}
#endif

#ifndef CHECKSTRING
#define CHECKSTRING(l, n) if(!lua_isstring(l,n)){luaL_error(l, "arg %d must be string",n);}

#endif

#ifndef CHECKINTEGER
#define CHECKINTEGER(l,n) if(!lua_isinteger(l,n)){luaL_error(l, "arg %d must be interger", n);}
#endif

#if defined(LINUX)
#define GetError() strerror(errno)
#elif defined(WINDOW)
#define GetError() strerror(errno)
#endif

#define THROW_ERR(l) luaL_error(l, "%s",GetError())

#ifndef REGISTERFUNC
    #define REGISTERFUNC(fun) {#fun, fun}
#endif

#ifndef REGISTER
    #define REGISTER(e) {#e,e}
#endif

#ifndef min
#define min(i,j) (i) >(j)?(j):(i)
#endif
#ifndef max
#define max(i,j) (i) >(j)?(i):(j)
#endif

#endif


