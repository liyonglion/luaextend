#include <stdio.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "stringapi.h"
#include "md5.h"
#include <ctype.h>
#include <stdlib.h>
#include "defer.h"
#include "base64.h"
#include "type.h"

EXPORT int Hasprefix(lua_State *l){
    const char *str = luaL_checkstring(l, 1);
    
    const char *sub = luaL_checkstring(l, 2);
    
    lua_pushboolean(l,S_Hasprefix(str, sub));
    return 1;
}

EXPORT int Hassuffix(lua_State *l){
    const char *str = luaL_checkstring(l, 1);
    const char *sub = luaL_checkstring(l,2);
    lua_pushboolean(l, S_HasSuffix(str, sub));
    return 1;
}

EXPORT int Contains(lua_State *l){
    const char *s = luaL_checkstring(l, 1);
    const char *sub = luaL_checkstring(l,2);
    lua_pushboolean(l, S_Contains(s,sub));
    return 1;
}

EXPORT int Containsany(lua_State *l){
    const char *s = luaL_checkstring(l, 1);
    const char *sub = luaL_checkstring(l,2);
    lua_pushboolean(l, S_ContainsAny(s, sub));
    return 1;
}

EXPORT int Count(lua_State *l){
    const char *s = luaL_checkstring(l, 1);
    const char *sep = luaL_checkstring(l,2);
    lua_pushinteger(l, S_Count(s,sep));
    return 1;
}

EXPORT int Fields(lua_State *l){
    deferBegin();
    const char *str = luaL_checkstring(l, 1);
    lua_newtable(l);
    stringSlice_t *slice = MakeStringSlice();
    defer(DestroyStringSlice, slice);
    if(S_Fields(str, slice) != OK){
        lua_pushnil(l);
        lua_pushstring(l, GetErrMsg(errNo));
        deferReturn(2);
    }
    int count = 1;
    int i = 0;
    for(;i < StringSliceLen(slice);i++){
        lua_pushstring(l,GetString(slice, i));
        lua_seti(l, -2, count++);
    }
    deferReturn(1);
}

EXPORT int Index(lua_State *l){
    const char *str = luaL_checkstring(l, 1);
    const char *sub = luaL_checkstring(l,2);
    int pos = S_Index(str, sub);
    if(pos != STRING_INVALID_POS){
        pos += 1;
    }
    lua_pushinteger(l, pos);
    return 1;
}

EXPORT int Indexany(lua_State *l){
    const char *str = luaL_checkstring(l, 1);
    const char *sub = luaL_checkstring(l,2);
    int pos = S_IndexAny(str, sub);
    if(pos != STRING_INVALID){
        pos += 1;
    }
    lua_pushinteger(l, pos);
    return 1;    
}

EXPORT int Lastindex(lua_State *l){
    const char *str = luaL_checkstring(l, 1);
    const char *sub = luaL_checkstring(l,2);
    int pos = SundayForward(str, sub);
    if(pos != STRING_INVALID_POS){
        pos += 1;
    }
    lua_pushinteger(l, pos);
    return 1;
}


EXPORT int Lastindexany(lua_State *l){
    const char *str = luaL_checkstring(l, 1);
    const char *sub = luaL_checkstring(l,2);
    int pos = S_LastIndexAny(str, sub);
    if(pos != STRING_INVALID){
        pos += 1;
    }
    lua_pushinteger(l,pos);
    return 1;
}

EXPORT int Repeat(lua_State *l){
    const char *str = luaL_checkstring(l, 1);
    int count = luaL_checkinteger(l,2);
    char *p = (char *)malloc(strlen(str)*count + 1);
    if(p == NULL){
        luaL_error(l, "%s","malloc failed");
        return 0;
    }
    int i = 0;
    for(; i < count;i++){
        memcpy(p+ i*strlen(str), str, strlen(str));
    }
    p[strlen(str)*count] = '\0';
    lua_pushstring(l, p);
    free(p);
    return 1;
}
//Replace returns a copy of the string s with the first n non-overlapping instances of old replaced by new. If n < 0, there is no limit on the number of replacements. 
EXPORT int Replace(lua_State *l){
    const char *str = luaL_checkstring(l, 1);
    const char *old = luaL_checkstring(l, 2);
    const char *newstr = luaL_checkstring(l,3);
    int n = luaL_checkinteger(l,4);
    const char *s = str;
    if(n == 0){
        lua_pushnil(l);
        return 1;
    }
    int size = strlen(str);
    luaL_Buffer b;
    luaL_buffinitsize(l, &b, size);
    stringSlice_t *slice = MakeStringSlice();
    S_Replace(str, old, newstr, n, slice);
    for(int i =  0; i < StringSliceLen(slice);i++){
        luaL_addstring(&b, GetString(slice, i));
    }
    DestroyStringSlice(slice); 
    luaL_pushresult(&b);
    return 1;
}

EXPORT int Splitstring(lua_State *l){
    const char *str = luaL_checkstring(l, 1);
    const char *sep = luaL_checkstring(l, 2);
    const char *s = str;
    int count = 1;
    lua_newtable(l);
    stringSlice_t *slice = MakeStringSlice();
    S_SplitString(str, sep, slice);
    for(int i = 0;i < StringSliceLen(slice);i++){
        lua_pushstring(l, GetString(slice, i));
        lua_seti(l, -2, count++);
    }
    DestroyStringSlice(slice);
    return 1;
}

EXPORT int Trim(lua_State *l){
    const char *str = luaL_checkstring(l, 1);
    const char *cutset  = luaL_checkstring(l, 2);
    deferBegin();
    char *s = NULL;
    s = S_TrimLeft(str, cutset);
    defer(free, s);
    s = S_TrimRight(s, cutset);
    lua_pushstring(l,s);
    defer(free,s);
    
    deferReturn(1);
}

EXPORT int Trimleft(lua_State *l){
    const char *str = luaL_checkstring(l, 1);
    const char *cutset  = luaL_checkstring(l, 2);
    char *s = NULL;
    s = S_TrimLeft(str, cutset);
    lua_pushstring(l,s);
    free(s);
    return 1;
}

EXPORT int Trimprefix(lua_State *l){
    const char *str = luaL_checkstring(l, 1);
    const char *prefix  = luaL_checkstring(l, 2);
    const char *p = str;
    if(prefix == NULL || strlen(prefix) == 0 || strlen(prefix) > strlen(str)){
        lua_pushstring(l, str);
        return 1;
    }
    if(memcmp(str, prefix, strlen(prefix)) == 0){
        p += strlen(prefix);
    }
    lua_pushstring(l, p);
    return 1;
}
EXPORT int Trimright(lua_State *l){
    const char *str = luaL_checkstring(l, 1);
    const char *cutset  = luaL_checkstring(l, 2);
    char *s = NULL;
    s = S_TrimRight(str, cutset);
    lua_pushstring(l,s);
    free(s);
    return 1;
}

EXPORT int Trimsuffix(lua_State *l){
    const char *str = luaL_checkstring(l, 1);
    const char *prefix  = luaL_checkstring(l, 2);
    char *p = NULL;
    if(prefix == NULL || strlen(prefix) == 0 || (strlen(prefix) > strlen(str))){
        lua_pushstring(l, str);
        return 1;
    }
    char *s = (char *)malloc(strlen(str) * sizeof(char) + 1);
    if(s == NULL){
        luaL_error(l, "%s","malloc failed");
        return 0;
    }
    strcpy(s, str);
    s[strlen(str)] = '\0';
    if(memcmp(s+ strlen(s) - strlen(prefix), prefix, strlen(prefix)) == 0){
        s[strlen(s) - strlen(prefix)] = '\0';
    }
    lua_pushstring(l, s);
    free(s);
    return 1;
}
EXPORT int Trimspace(lua_State *l){
    const char *str = luaL_checkstring(l, 1);
    char *s = S_TrimSpace(str);
    lua_pushstring(l,s);
    free(s);
    return 1;
}

EXPORT int md5(lua_State *l){
    const char*str = luaL_checkstring(l, 1);
    char * p = GetMd5String(str, strlen(str));
    lua_pushstring(l,p);
    free(p);
    return 1;
}

EXPORT int base64(lua_State *l){
    const char*str = luaL_checkstring(l, 1);
    int len = 0;
    char *res = Getbase64(str, strlen(str), &len);
    if(res == NULL){
        luaL_error(l, "%d","malloc failed");
        return 0;
    }
    lua_pushlstring(l, res, len);
    free(res);
    return 1;
}

EXPORT int unbase64(lua_State *l){
    const char*str = luaL_checkstring(l, 1);
    int len = 0;
    char *res = (char *)Getunbase64(str, strlen(str), &len);
    if(res == NULL){
        luaL_error(l, "%d","malloc failed");
        return 0;
    }
    lua_pushlstring(l, res, len);
    free(res);
    return 1;
}

static luaL_Reg mainfuns[] = {
    REGISTERFUNC(md5),
    REGISTERFUNC(base64),
    REGISTERFUNC(unbase64),
    REGISTERFUNC(Hasprefix),
    REGISTERFUNC(Hassuffix),
    REGISTERFUNC(Contains),
    REGISTERFUNC(Containsany),
    REGISTERFUNC(Count),
    REGISTERFUNC(Fields),
    REGISTERFUNC(Index),
    REGISTERFUNC(Indexany),
    REGISTERFUNC(Lastindex),
    REGISTERFUNC(Lastindexany),
    REGISTERFUNC(Repeat),
    REGISTERFUNC(Replace),
    REGISTERFUNC(Splitstring),
    REGISTERFUNC(Trim),
    REGISTERFUNC(Trimleft),
    REGISTERFUNC(Trimprefix),
    REGISTERFUNC(Trimright),
    REGISTERFUNC(Trimsuffix),
    REGISTERFUNC(Trimspace),

    {NULL,NULL}
};

EXPORT int luaopen_strings(lua_State *l){
    luaL_newlib(l, mainfuns);
    return 1;
}
