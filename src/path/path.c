#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "pathapi.h"
//IsAbs返回路径是否是一个绝对路径。
EXPORT int Isabs(lua_State *l){
	const char *path = luaL_checkstring(l,1);
    lua_pushboolean(l,isabs(path));
	return 1;
}

//Split函数将路径从最后一个路径分隔符后面位置分隔为两个部分
//（dir和file）并返回。如果路径中没有路径分隔符，函数返回值dir会设为空字符串，
//file会设为path。两个返回值满足path == dir+file。
EXPORT int Splitpath(lua_State *l){
	const char *path = luaL_checkstring(l,1);
    string dir,file;
    InitString(&dir, 0);
    InitString(&file, 0);
	splitpath(path,&dir, &file);
	lua_pushstring(l, GetCString(&dir));//DIR
	lua_pushstring(l,GetCString(&file));
    DestroyString(&dir);
    DestroyString(&file);
	return 2;
}

//Join函数可以将任意数量的路径元素放入一个单一路径里，会根据需要添加路径分隔符。结果是经过简化的
//，所有的空字符串元素会被忽略。

EXPORT int Join(lua_State *l){
	if(!lua_istable(l, 1)){
		const char *type = lua_typename(l, lua_type(l,1));
		lua_pushnil(l);
		luaL_error(l, "except table, but %s",type);
		return 2;
	}
	lua_len(l,1);
	int len = lua_tointeger(l,-1);
	lua_pop(l,1);
	int i = 1;
	char m[PATH_MAX] = {0};
	int used = 0;
	for(;i <= len;i++){
		lua_geti(l, 1, i);
		if(!lua_isstring(l,2)){
			lua_pushnil(l);
		    luaL_error(l,"%d of table is not string",i);
			return 2;
		}
		const char *e = lua_tostring(l,2);
		if((used + strlen(e) + 1) > PATH_MAX){
			lua_pushnil(l);
			luaL_error(l,"the path is too long");
			return 2;
		}
        if(strlen(e) == 0){
            continue;
        }
		memcpy(m + used,e ,strlen(e));
		used += strlen(e);
        if(m[used - 1] != sep){
		    m[used] = sep;
		    used += 1;
        }
		lua_pop(l,1);
	}
	lua_pushstring(l, m);
	return 1;
}
//Dir返回路径除去最后一个路径元素的部分，即该路径最后一个元素所在的目录。在使用Split去掉最后一个元素后，
//会简化路径并去掉末尾的斜杠。如果路径是空字符串，会返回"."；末尾带有路径分隔符
EXPORT int Dir(lua_State *l){
	const char *path = luaL_checkstring(l,1);
    string str;
    InitString(&str, strlen(path));
    pathdir(path, &str);
    lua_pushstring(l, GetCString(&str));
    DestroyString(&str);
	return 1;
}
//Base函数返回路径的最后一个元素。在提取元素前会求掉末尾的路径分隔符。如果路径是""，会返回"."；
//如果路径是只有一个斜杆构成，会返回单个路径分隔符。
EXPORT int Base(lua_State *l){
	const char *path = luaL_checkstring(l,1);
    string str;
    InitString(&str, strlen(path));
    pathbase(path, &str);
    lua_pushstring(l, GetCString(&str));
    DestroyString(&str);
	return 1;
}

//Ext函数返回path文件扩展名。返回值是路径最后一个路径元素的最后一个'.'起始的后缀（不包括'.'）。
//如果该元素没有'.'会返回空字符串。
EXPORT int Ext(lua_State *l){
	const char *path = luaL_checkstring(l,1);
    string str;
    InitString(&str,0);
    pathext(path, &str);
    lua_pushstring(l, GetCString(&str));
    DestroyString(&str);
	return 1;
}

//Clean函数清理路径中多余的项。例如剔除.(代表当前目录) ..等
EXPORT int Abs(lua_State *l){
	const char *path = luaL_checkstring(l,1);
    string str;
    InitString(&str, 0);
    if(pathabs(path, &str) != OK){
        DestroyString(&str);
        lua_pushnil(l);
        luaL_error(l, "%s: %s",path, GetError());
        return 2;
    }
    lua_pushstring(l, GetCString(&str));
    DestroyString(&str);
    return 1;
}

EXPORT int Clean(lua_State *l){
    const char *path = luaL_checkstring(l,1);
    string str;
    InitString(&str,strlen(path));
    pathclean(path, &str);
    lua_pushstring(l, GetCString(&str));
    DestroyString(&str);
    return 1;
}

EXPORT int Fromslash(lua_State *l){
    const char *path = luaL_checkstring(l,1);
    char *slash = (char*)malloc((strlen(path) + 1)*sizeof(char));
    if(slash == NULL){
        lua_pushnil(l);
        return 1;
    }
    memset(slash, 0, (strlen(path) + 1)*sizeof(char));
    fromSlash(path, slash);
    lua_pushstring(l, slash);
    free(slash);
    return 1;
}

EXPORT int Toslash(lua_State *l){
    const char *path = luaL_checkstring(l,1);
    char *slash = (char*)malloc((strlen(path) + 1)*sizeof(char));
    if(slash == NULL){
        lua_pushnil(l);
        return 1;
    }
    memset(slash, 0, (strlen(path) + 1)*sizeof(char));
    toSlash(path, slash);
    lua_pushstring(l, slash);
    free(slash);
    return 1;
    
}

EXPORT int Volumename(lua_State *l){
    const char *path = luaL_checkstring(l,1);
    int vollen = volumeNameLen(path);
    lua_pushlstring(l, path, vollen);
    return 1;
}

static luaL_Reg funs[] = {
    REGISTERFUNC(Isabs),
    REGISTERFUNC(Splitpath),
    REGISTERFUNC(Join),
    REGISTERFUNC(Dir),
    REGISTERFUNC(Base),
    REGISTERFUNC(Ext),
    REGISTERFUNC(Clean),
    REGISTERFUNC(Abs),
    REGISTERFUNC(Fromslash),
    REGISTERFUNC(Toslash),
    REGISTERFUNC(Volumename),
	{NULL,NULL}
};

EXPORT int luaopen_path(lua_State *l){
	luaL_newlib(l, funs);
	return 1;
}
