#include "lyos.h"
#include "type.h"
#include <stdio.h>
#include <limits.h>
#include <sys/stat.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include <dirent.h>
#if defined(LINUX)
#include <sys/mman.h>
#endif
typedef struct {
    char *name;
    int value;
}elem_t;


EXPORT int Gethostname(lua_State *l){
	char buf[512] = {0};
#if defined(WINDOW)
	WSADATA wsd;
	if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)
    {
    	lua_pushnil(l);
    	lua_pushstring(l, "call WSAStartup error");
    	return 2;
    }

#endif
	if(gethostname(buf, 512) != 0){
		lua_pushnil(l);
		lua_pushstring(l, GetError());
		goto failed;
	}
	lua_pushstring(l, buf);
	lua_pushnil(l);
failed:

#if defined(WINDOW)
	WSACleanup();
#endif
	return 2;
}

int getPageSize(){
	int pagesize;
#if defined(LINUX)
	pagesize =  getpagesize();
#elif defined(WINDOW)
    SYSTEM_INFO system_info;
    GetSystemInfo (&system_info);
    pagesize = system_info.dwPageSize;
#endif
	return pagesize;
}
EXPORT int Getpagesize(lua_State *l){
	lua_pushinteger(l, getPageSize());
	return 1;
}
EXPORT int Getlogin(lua_State *l){
    lua_pushstring(l, getlogin());
    return 1;
}
EXPORT int Getenv(lua_State *l){
	if(lua_gettop(l) == 0){//获取所有的环境变量，插入一个表中
		lua_newtable(l);
		#define ENVBUF 512
		char *buf = (char *)malloc(sizeof(char)*ENVBUF);
		if(buf == NULL){
			luaL_error(l,"malloc failed");

		}
		memset(buf, 0, ENVBUF);
#define CHECKENVMEM(n) 	if(n > ENVBUF){\
			 			free(buf);\
			 			buf = (char *)malloc(n);\
			 			if(buf == NULL){\
			 				free(buf);\
			 				luaL_error(l,"malloc failed");\
			 			}\
			 			memset(buf, 0,n);\
			 		}
		extern char **environ;
		 char **envs = environ;
		 while(*envs){
		 	char *env = *envs;
		 #if defined(WINDOW)
		 	if(*env == '#' || *env == '='){
		 		continue;
		 	}
		 #endif
		 	char *pos = strchr(env, '=');
		 	if(pos == NULL){
		 		continue;
		 	}
		 	lua_pushstring(l, pos + 1);
		 	CHECKENVMEM(pos - env);
		 	strncpy(buf, env, pos - env);
		 	buf[pos - env] = '\0';
		 	lua_setfield(l, -2, buf);
            envs++;
		#undef ENVBUF
        }
        free(buf);
        return 1;
	}else{
		if(lua_isstring(l,1)){//获取对应的值
			char *env = getenv(lua_tostring(l,1));
            lua_pushstring(l,env);
			return 1;
		}else{
			lua_pushnil(l);
			lua_pushstring(l,"string or nil need");
			return 2;
		}
	}
	return 0;
}

extern int Setenv(lua_State *l){
	const char *env_name = luaL_checkstring(l,1);
	const char *env_value = luaL_checkstring(l,2);
	#if defined(WINDOW)
		int size = strlen(env_name) + strlen(env_value) + 2;
		char *p = (char *)malloc(size);
		if(p == NULL){
			lua_pushstring(l,"malloc failed");
			return 1;
		}
		strcpy(p, env_name);
		p[strlen(env_name)] = '=';
		strcpy(p + strlen(env_name) + 1, env_value);
		p[size] = '\0';
		int res = putenv(p);
		if(res != 0){
			free(p);
			p = NULL;
			lua_pushstring(l, GetError());
			return 1;
		}
		free(p);
		lua_pushnil(l);
		return 1;
	#elif defined(LINUX)
		int res = setenv(env_name, env_value, 1);
		if(res != 0){
			lua_pushstring(l,GetError());
			return 1;
		}
		lua_pushnil(l);
		return 1;
	#endif
}

EXPORT int Cleanenv(lua_State *l){
	const char *env_name = luaL_checkstring(l,1);
#if defined(LINUX)
	int res = unsetenv(env_name);
	if(res != 0){
		lua_pushstring(l, GetError());
		return 1;
	}
#elif defined(WINDOW)
	char *p = (char *)malloc(strlen(env_name) + 2);
	memset(p, 0,strlen(env_name) + 2);
	sprintf(p,"%s=", env_name);
	int res = putenv(p);
	if(res != 0){
		free(p);
		p = NULL;
		lua_pushstring(l, GetError());
		return 1;
	}
	free(p);
	p = NULL;
#endif
	return 0;
}

EXPORT int Getuid(lua_State *l){
    lua_pushinteger(l, getuid());
    return 1;
}

EXPORT int Geteuid(lua_State *l){
    lua_pushinteger(l, geteuid());
    return 1;
}

EXPORT int Getgid(lua_State *l){
    lua_pushinteger(l, getgid());
    return 1;
}

EXPORT int Getegid(lua_State *l){
    lua_pushinteger(l, getegid());
    return 1;
}

EXPORT int Getgroups(lua_State *l){
#if defined(WINDOW)
    lua_pushnil(l);
    lua_pushstring(l, "Windows not support");
    return 2;
#elif defined(LINUX)
    int x = getgroups(0, NULL);
    gid_t *gid_all = (gid_t*)malloc(sizeof(gid_t)*x);
    if(gid_all == NULL){
        luaL_error(l, "malloc failed");
    }
    lua_newtable(l);
    int counter = 1;
    for(int i = 0;i < x;i++){
        lua_pushinteger(l, gid_all[i]);
        lua_seti(l, -2, counter++);
    }
    return 1;
#endif
}

EXPORT int Getpid(lua_State *l){
    lua_pushinteger(l, getpid());
    return 1;
}

EXPORT int Getppid(lua_State *l){
    lua_pushinteger(l,getppid());
    return 1;
}

EXPORT int Getcwd(lua_State *l){
    char path[PATH_MAX] = {0};
    if(getcwd(path, PATH_MAX) == NULL){
        lua_pushnil(l);
        lua_pushstring(l,GetError());
        return 2;
    }
    lua_pushstring(l, path);
    return 1;
}

EXPORT int Chdir(lua_State *l){
    const char *path = luaL_checkstring(l,1);
    int ret = chdir(path);
    if(ret != 0){
        lua_pushstring(l, GetError());
        return 1;
    }
    return 0;
}

EXPORT int Mkdir(lua_State *l){
    const char *path = luaL_checkstring(l,1);
    int mode = luaL_checkinteger(l,2);
#if defined(WINDOW)
    if(mkdir(path) != 0){
#elif defined(LINUX)
    if(mkdir(path,mode) != 0){
#endif
       lua_pushstring(l, GetError());
       return 1;
    }
    return 0;
}

static elem_t accessmode[] = {
    REGISTER(F_OK),
    REGISTER(R_OK),
    REGISTER(W_OK),
    REGISTER(X_OK),
    {NULL, 0}
};
//成功返回0。返回-1，有可能是文件不存在，或者没有对应mode权限，返回-1
EXPORT int Access(lua_State *l){
    const char *path = luaL_checkstring(l, 1);
    int mode = luaL_checkinteger(l,2);
    if(access(path, mode) == 0){
        lua_pushboolean(l,1);
        lua_pushnil(l);
        return 2;
    }
    if(errno == EACCES){
        lua_pushboolean(l,0);
        lua_pushnil(l);
        return 2;
    }
    lua_pushnil(l);
    lua_pushstring(l, GetError());
    return 2;
}
//返回一个布尔值说明该错误是否表示一个文件或目录不存在。一些系统调用错误会使它返回真。
EXPORT int Isnotexist(lua_State *l){
    const char *path = luaL_checkstring(l,1);
    if(access(path, F_OK) != 0){
        lua_pushboolean(l,1);
        return 1;
    }
    lua_pushboolean(l, 0);
    return 1;
}

////返回一个布尔值说明该错误是否表示一个文件或目录不存在。一些系统调用错误会使它返回假
EXPORT int Isexist(lua_State *l){
    const char *path = luaL_checkstring(l,1);
    if(access(path, F_OK) == 0){
        lua_pushboolean(l,1);
        return 1;
    }
    lua_pushboolean(l, 0);
    return 1;
}

EXPORT int Rmdir(lua_State *l){
    const char *path = luaL_checkstring(l,1);
    if(rmdir(path) != 0){
        lua_pushstring(l, GetError());
        return 1;
    }
    return 0;
}

EXPORT int Chmod(lua_State *l){
    const char *path = luaL_checkstring(l,1);
    int mode = luaL_checkinteger(l,2);
    if(chmod(path, mode) != 0){
        THROW_ERR(l);
        return 1;
    }
    return 0;
}
int isDir(const char *path){
    struct stat st;
    if(stat(path, &st) != 0){
        return errno;
    }
    if(S_ISDIR(st.st_mode))
        return 1;
    return 0;
}
EXPORT int Stat(lua_State *l){
   const char *path = luaL_checkstring(l,1);

   struct stat *st =  (struct stat*)lua_newuserdata(l, sizeof(struct stat));
   
    if(stat(path, st) != 0){
        THROW_ERR(l);
    }
   luaL_getmetatable(l, STATSTRING);
   lua_setmetatable(l, -2);
   return 1;
}

EXPORT int Abspath(lua_State *l){
    const char *path = luaL_checkstring(l,1);
    char buf[PATH_MAX] = {0};
    if(GetFullPath(path, buf, PATH_MAX) != 0){
        lua_pushnil(l);
        lua_pushstring(l,GetError());
        return 2;
    }
    lua_pushstring(l, buf);
    return 1;
}

EXPORT int Samefile(lua_State *l){
    const char *src = luaL_checkstring(l, 1);
    const char *dst = luaL_checkstring(l,2);
#if defined(LINUX)
    //比较linux的inode节点号和dev号是否相同
    struct stat st,dt;
    if(stat(src,&st) != 0){
       goto failed; 
    }
    if(stat(src, &dt) != 0){
        goto failed;
    }
    if(st.st_ino == dt.st_ino && st.st_dev == dt.st_dev){
        lua_pushboolean(l,1);
        return 1;
    }
failed:
    lua_pushboolean(l,0);
    return 1;
#elif defined(WINDOW)
    lua_pushboolean(l, !strcmp(src,dst));
    return 1;
#endif
}
EXPORT int Readdir(lua_State *l){
    const char *path = luaL_checkstring(l,1);
    DIR *dir = opendir(path);
    if(dir == NULL){
        lua_pushnil(l);
        lua_pushstring(l, GetError());
        return 2;
    }
    struct dirent *dt = NULL;
    lua_newtable(l);
    int count = 1;
    while((dt = readdir(dir)) != NULL){
        if(strcmp(dt->d_name,".") == 0 || strcmp(dt->d_name, "..") == 0){
            continue;
        }
        lua_pushstring(l, dt->d_name);
        lua_seti(l,-2, count++);
    }
    closedir(dir);
    return 1;
}

EXPORT int Rename(lua_State *l){
    const char *spath = luaL_checkstring(l,1);
    const char *dpath = luaL_checkstring(l,2);
    if(rename(spath, dpath) != 0){
        lua_pushstring(l, GetError());
        return 1;
    }
    return 0;
}

EXPORT int Remove(lua_State *l){
    const char *path = luaL_checkstring(l,1);
    if(remove(path) != 0){
        lua_pushstring(l, GetError());
        return 1;
    }
    return 0;
}

EXPORT int Unlink(lua_State *l){
    const char *path = luaL_checkstring(l,1);
    if(unlink(path) != 0){
        lua_pushstring(l,GetError());
        return 1;
    }
    return 0;
}
EXPORT int Copyfile(lua_State *l){
    const char *inpath = luaL_checkstring(l,1);
    const char *outpath = luaL_checkstring(l,2);
    if(!lua_isboolean(l,3)){
        luaL_error(l, "arg 3 except boolean");
        return 1;
    }
    int flag = lua_toboolean(l,3);
    char errmsg[128] = {0};
#if defined(LINUX)
    void *src,*dst;
    int fin = open(inpath, O_RDONLY);
    if(fin < 0){
        lua_pushstring(l, GetError());
        return 1;
    }
    struct stat st;
    if(fstat(fin, &st) < 0){
        lua_pushstring(l, GetError());
        close(fin);
        return 1;
    }
    if(S_ISDIR(st.st_mode)){
        sprintf(errmsg, "%s is dir", inpath);
        lua_pushstring(l, errmsg);
        close(fin);
        return 1;
    }
    int mode = O_RDWR | O_CREAT;
    if(flag == 1){
        mode |= O_TRUNC;
    }
    int fout = open(outpath,mode, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if(fout < 0){
        lua_pushstring(l, GetError());
        close(fin);
        return 1;
    }
    if(flag == 0){
        sprintf(errmsg, "%s is already exist", outpath);
        lua_pushstring(l,errmsg);
        return 1;
    }
    if(lseek(fout, st.st_size -1, SEEK_SET) == -1){
        close(fin);
        close(fout);
        lua_pushstring(l, GetError());
        return 1;
    }
    if(write(fout, "",1) != 1){
        close(fin);
        close(fout);
        lua_pushstring(l, GetError());
        return 1;        
    }
    if((src = mmap(0, st.st_size, PROT_READ, MAP_SHARED,fin, 0)) == MAP_FAILED){
        close(fin);
        close(fout);
        lua_pushstring(l,GetError());
        return 1;
    }
    if((dst = mmap(0, st.st_size, PROT_WRITE, MAP_SHARED, fout, 0)) == MAP_FAILED){
        close(fin);
        close(fout);
        munmap(src, st.st_size);
        lua_pushstring(l, GetError());
        return 1;
    }
    memcpy(dst, src, st.st_size);
    msync(dst, st.st_size, MS_SYNC);
    close(fin);
    close(fout);
    munmap(src, st.st_size);
    munmap(dst, st.st_size);
    return 0;
#elif defined(WINDOW)
    if(isdir(inpath)){
        sprintf(errmsg, "%s is dir", inpath);
        lua_pushstring(l, errmsg);
        return 1;
    }
    if(CopyFile(inpath, outpath, !flag) == 0){
        lua_pushstring(l, GetError());
        return 1;
    }
    return 0;
#endif
}
#if defined(LINUX)

EXPORT int Link(lua_State *l){
    const char *spath = luaL_checkstring(l,1);
    const char *dpath = luaL_checkstring(l,2);
    if(link(spath, dpath) != 0){
        lua_pushstring(l,GetError());
        return 1;
    }
    return 0;
}

EXPORT int Symlink(lua_State *l){
    const char *spath = luaL_checkstring(l,1);
    const char *dpath = luaL_checkstring(l,2);
    if(symlink(spath, dpath) != 0){
        lua_pushstring(l,GetError());
        return 1;
    }
    return 0;    
}
EXPORT int Readlink(lua_State *l){
    const char *path = luaL_checkstring(l,1);
    char buf[PATH_MAX] = {0};
    if(readlink(path, buf, PATH_MAX -1) == -1){
        lua_pushnil(l);
        lua_pushstring(l, GetError());
        return 2;
    }
    lua_pushstring(l, buf);
    return 1;
}
#endif

typedef struct {
    int fd;
    char path[PATH_MAX];
}fd_t;

EXPORT int Create(lua_State *l){
    const char *path = luaL_checkstring(l,1);

    fd_t *ud = (fd_t*)lua_newuserdata(l, sizeof(fd_t));
    //设置metatable
    luaL_getmetatable(l, FDSTRING);
    lua_setmetatable(l, -2);
    int flag = S_IRUSR | S_IWUSR;
#if defined(LINUX)
    flag |= S_IRGRP;
    flag |= S_IWGRP;
    flag |= S_IROTH;
    flag |= S_IWOTH;
#endif
    int fd = open(path, O_RDWR | O_TRUNC | O_CREAT, flag);
    if(fd < 0 ){
        lua_settop(l, 0);
        lua_pushnil(l);
        lua_pushstring(l, GetError());
        return 2;
    }
    ud->fd = fd;
    //获得绝对路径
    if(GetFullPath(path, ud->path, PATH_MAX) != 0){
        close(fd);
        lua_pushnil(l);
        lua_pushstring(l,GetError());
        return 2;
    }
    return 1;
}

EXPORT int Open(lua_State *l){
    const char *path = luaL_checkstring(l,1);
    fd_t *ud = (fd_t*)lua_newuserdata(l, sizeof(fd_t));
    //设置metatable
    luaL_getmetatable(l, FDSTRING);
    lua_setmetatable(l, -2);
    
    int fd = open(path, O_RDONLY);
    if(fd < 0 ){
        lua_settop(l, 0);
        lua_pushnil(l);
        lua_pushstring(l, GetError());
        return 2;
    }
    ud->fd = fd;
    //获得绝对路径
    if(GetFullPath(path, ud->path, PATH_MAX) != 0){
        close(fd);
        lua_pushnil(l);
        lua_pushstring(l,GetError());
        return 2;
    }
    return 1;
}

EXPORT int Openfile(lua_State *l){
    const char *path = luaL_checkstring(l,1);
    int mode = luaL_checkinteger(l,2);
    int perm = luaL_checkinteger(l,3);
    fd_t *ud = (fd_t*)lua_newuserdata(l, sizeof(fd_t));
    //设置metatable
    luaL_getmetatable(l, FDSTRING);
    lua_setmetatable(l, -2);
    
    int fd = open(path, mode, perm);
    if(fd < 0 ){
        lua_settop(l, 0);
        lua_pushnil(l);
        lua_pushstring(l, GetError());
        return 2;
    }
    ud->fd = fd;
    //获得绝对路径
    if(GetFullPath(path, ud->path, PATH_MAX) != 0){
        close(fd);
        lua_pushnil(l);
        lua_pushstring(l,GetError());
        return 2;
    }
    return 1;    
}

EXPORT int Name(lua_State *l){
   fd_t *fd = (fd_t*)luaL_checkudata(l, 1,FDSTRING);
   lua_pushstring(l,fd->path);
   return 1;
}

EXPORT int Fdstat(lua_State *l){
   fd_t *fd = (fd_t*)luaL_checkudata(l, 1,FDSTRING);
   struct stat *st =  (struct stat*)lua_newuserdata(l, sizeof(struct stat));

    if(fstat(fd->fd, st) != 0){
        THROW_ERR(l);
    }
   luaL_getmetatable(l, STATSTRING);
   lua_setmetatable(l, -2);
    return 1;
}

EXPORT int Fd(lua_State *l){
    fd_t *fd = (fd_t*)luaL_checkudata(l, 1,FDSTRING);
    lua_pushinteger(l, fd->fd);
    return 1;
}

EXPORT int Fdchdir(lua_State *l){
    int ret = 0;
    fd_t *fd = (fd_t*)luaL_checkudata(l, 1,FDSTRING);
#if defined(LINUX)
    ret = fchdir(fd->fd);
#elif defined(WINDOW)
    ret = chdir(fd->path);
#endif
    if(ret != 0){
        lua_pushstring(l,GetError());
        return 1;
    }
    return 0;
}

EXPORT int Fdchmod(lua_State *l){
    fd_t *fd = (fd_t*)luaL_checkudata(l,1, FDSTRING);
    int mode = luaL_checkinteger(l, 2);
    if(chmod(fd->path, mode) != 0){
        lua_pushstring(l, GetError());
        return 1;
    }
    return 0;
}

#if defined(LINUX)
EXPORT int Chown(lua_State *l){
    fd_t *fd = (fd_t*)luaL_checkudata(l, 1,FDSTRING);
    int uid,gid;
    uid = luaL_checkinteger(l,2);
    gid = luaL_checkinteger(l,3);
    if(fchown(fd->fd, uid, gid) != 0){
        lua_pushstring(l, GetError());
        return 1;
    }
    return 0;
}
#endif

EXPORT int Fdreaddir(lua_State *l){
    return 0;
}

EXPORT int Truncate(lua_State *l){
    fd_t *fd = (fd_t*)luaL_checkudata(l, 1,FDSTRING);
    long long size = luaL_checkinteger(l,2);
    if(ftruncate(fd->fd, size) != 0){
        lua_pushstring(l, GetError());
        return 1;
    }
    long long offset = lseek(fd->fd, size, SEEK_SET);
    if(offset == -1){
        lua_pushstring(l, GetError());
        return 1;
    }
    return 0;
}

EXPORT int Read(lua_State *l){
    fd_t *fd = (fd_t*)luaL_checkudata(l, 1,FDSTRING);
    const char *arg = luaL_checkstring(l,2);
    if(arg[0] != '*'){
        luaL_argerror(l,1,"must be *all *n *line");
    }
    luaL_Buffer buf;
    luaL_buffinit(l, &buf);
    int size = getPageSize();
    char *tmp = (char *)malloc(size*sizeof(char));
    if(tmp == NULL){
        luaL_error(l,"malloc failed");
    }

    if(strcmp(arg+1, "all") == 0){//读取所有
        while(1){
            int ret = read(fd->fd, tmp, size);
            if(ret < 0){
                lua_pushnil(l);
                lua_pushstring(l, GetError());
                free(tmp);
                return 2;
            }else if(ret == 0){
                luaL_pushresult(&buf);
                lua_pushinteger(l, EOF);
                free(tmp);
                return 2;
            }
            luaL_addlstring(&buf, tmp, ret);
        }
    }else if(strcmp(arg + 1, "line") == 0){//读取一行
        while(1){
            memset(tmp,0,size);
            int ret = read(fd->fd,tmp, size);
            if(ret < 0){
                lua_pushnil(l);
                lua_pushstring(l, GetError());
                free(tmp);
                return 2;
            }else if(ret == 0){
                luaL_pushresult(&buf);
                lua_pushinteger(l, EOF);
                free(tmp);
                return 2;
            }
            //查找\n
            int i = 0;
            for(i = 0; i < ret;i++){
                if(tmp[i] == '\n'){
                    luaL_addlstring(&buf, tmp, i);
                    //把多余设置回来
                    lseek(fd->fd, SEEK_CUR, -(ret - i - 1));
                    luaL_pushresult(&buf);
                    lua_pushnil(l);
                    free(tmp);
                    return 2;
                }
            }
            luaL_addlstring(&buf,tmp, ret);
        }
    }else{//读取n个字节
       int len =  atoi(arg + 1);
       if(len == 0){
            free(tmp);
            luaL_argerror(l,1,"not a number");
       }
       if(len <= 0){
            free(tmp);
            lua_pushnil(l);
            lua_pushstring(l, "must bigger then 0");
            return 2;
       }
       int total = 0;
       int readbyte = 0;
       while(total < len){
            if((len - total)/size != 0){
                readbyte = size;
            }else{
                readbyte = (len - total)%size;
            }
            int ret =  read(fd->fd, tmp, readbyte);
            if(ret < 0){
                lua_pushnil(l);
                lua_pushstring(l, GetError());
                free(tmp);
                return 2;                   
            }else if(ret == 0){
                luaL_pushresult(&buf);
                lua_pushinteger(l, EOF);
                free(tmp);
                return 2;                    
            }

            luaL_addlstring(&buf, tmp, ret);
            total += ret;
       }
       luaL_pushresult(&buf);
       lua_pushnil(l);
       free(tmp);
       return 2;
    }
    return 0;
}

EXPORT int Readat(lua_State *l){
    fd_t *fd = (fd_t*)luaL_checkudata(l, 1,FDSTRING);
    const char *arg = luaL_checkstring(l,2);
    int offset = luaL_checkinteger(l,3);
    int whence = luaL_checkinteger(l,4);
    //检查有消息
    if(arg[0] != '*'){

        luaL_argerror(l,1,"must be *all *n *line");
    }
    if(strcmp(arg+1, "all") == 0 || strcmp(arg+1, "line") == 0){
        if(lseek(fd->fd, offset, whence) == -1){
            lua_pushnil(l);
            lua_pushstring(l, GetError());
            return 2;
        }
        return Read(l);
    }
    if(atoi(arg+1) > 0){
        if(lseek(fd->fd, offset, whence) == -1){
            lua_pushnil(l);
            lua_pushstring(l, GetError());
            return 2;
        }
        return Read(l);        
    }
    lua_pushnil(l);
    luaL_argerror(l,1,"wrong format");
    return 2;
}

EXPORT int Write(lua_State *l){
    fd_t *fd = (fd_t*)luaL_checkudata(l, 1,FDSTRING);
    const char *data = luaL_checkstring(l,2);
    int len = luaL_checkinteger(l,3);

    if(len > strlen(data)){
        len = strlen(data);
    }
    int ret = write(fd->fd, data, len);
    if(ret < 0){
        lua_pushnil(l);
        lua_pushstring(l, GetError());
        return 2;
    }
    lua_pushinteger(l, ret);
    lua_pushnil(l);
    return 2;
}

EXPORT int Writeat(lua_State *l){
    fd_t *fd = (fd_t*)luaL_checkudata(l, 1,FDSTRING);
    const char *data = luaL_checkstring(l,2);
    int len = luaL_checkinteger(l,3);
    int offset = luaL_checkinteger(l,4);
    int whence = luaL_checkinteger(l,5);
    if(lseek(fd->fd, offset, whence) == -1){
        lua_pushnil(l);
        lua_pushstring(l, GetError());
        return 2;
    }

    return Write(l);
}

EXPORT int Writestring(lua_State *l){
    const char *data = luaL_checkstring(l,2);
    lua_pushinteger(l, strlen(data));
    return Write(l);
}

EXPORT int Writestringat(lua_State *l){
    const char *data = luaL_checkstring(l,2);
    lua_pushinteger(l, strlen(data));
    lua_insert(l, 3);
    return Writeat(l);
}
EXPORT int Seek(lua_State *l){
    fd_t *fd = (fd_t*)luaL_checkudata(l, 1,FDSTRING);
    long long offset = luaL_checkinteger(l,2);
    int where = luaL_checkinteger(l,3);
    offset = lseek(fd->fd, offset, where);
    if(offset == -1){
        lua_pushnil(l);
        lua_pushstring(l, GetError());
        return 2;
    }
    lua_pushinteger(l, offset);
    return 1;
}
#if defined(LINUX)
EXPORT int Sync(lua_State *l){
    fd_t *fd = (fd_t*)luaL_checkudata(l, 1,FDSTRING);
    if(fsync(fd->fd)!= 0){
        lua_pushstring(l, GetError());
        return 1;
    }
    return 0;
}
#endif

EXPORT int Fdclose(lua_State *l){
    fd_t *fd = (fd_t*)luaL_checkudata(l, 1,FDSTRING);
    if(fd->fd > 0){
        close(fd->fd);
        fd->fd = -1;
    }
    return 0;
}
static luaL_Reg fdfuncs[] = {
    REGISTERFUNC(Name),
    {"Stat",Fdstat},
    REGISTERFUNC(Fd),
    {"Chdir",Fdchdir},
    {"Chmod",Fdchmod},
#if defined(LINUX)
    REGISTERFUNC(Chown),
    REGISTERFUNC(Sync),
#endif
    {"Readdir",Fdreaddir},
    REGISTERFUNC(Truncate),
    REGISTERFUNC(Read),
    REGISTERFUNC(Readat),
    REGISTERFUNC(Write),
    REGISTERFUNC(Writeat),
    REGISTERFUNC(Writestring),
    REGISTERFUNC(Writestringat),
    REGISTERFUNC(Seek),
    {"Close",Fdclose},
    {NULL,NULL}
};

static luaL_Reg funs[] = {
    REGISTERFUNC(Gethostname),
    REGISTERFUNC(Getpagesize),
    REGISTERFUNC(Getenv),
    REGISTERFUNC(Setenv),
    REGISTERFUNC(Cleanenv),
    REGISTERFUNC(Getuid),
    REGISTERFUNC(Geteuid),
    REGISTERFUNC(Getgid),
    REGISTERFUNC(Getegid),
    REGISTERFUNC(Getgroups),
    REGISTERFUNC(Getpid),
    REGISTERFUNC(Getppid),
    REGISTERFUNC(Getcwd),
    REGISTERFUNC(Chdir),
    REGISTERFUNC(Mkdir),
    REGISTERFUNC(Rmdir),
    REGISTERFUNC(Chmod),
    REGISTERFUNC(Stat),
    REGISTERFUNC(Abspath),
    REGISTERFUNC(Create),
    REGISTERFUNC(Open),
    REGISTERFUNC(Openfile),
    REGISTERFUNC(Readdir),
    REGISTERFUNC(Access),
    REGISTERFUNC(Isnotexist),
    REGISTERFUNC(Isexist),
    REGISTERFUNC(Remove),
    REGISTERFUNC(Rename),
    REGISTERFUNC(Getlogin),
    REGISTERFUNC(Copyfile),
    REGISTERFUNC(Samefile),
#if defined(LINUX)
    REGISTERFUNC(Link),
    REGISTERFUNC(Symlink),
    REGISTERFUNC(Readlink),
    REGISTERFUNC(Unlink),
#endif
	{NULL,NULL}
};

EXPORT int Isregular(lua_State *l){
    struct stat *st = (struct stat*)luaL_checkudata(l,1,STATSTRING);
    lua_pushboolean(l, S_ISREG(st->st_mode));
    return 1;    
}

static elem_t perms[] = {
    REGISTER(S_IRWXU),
    REGISTER(S_IRUSR),
    REGISTER(S_IWUSR),
    REGISTER(S_IXUSR),
#if defined(LINUX)
    REGISTER(S_IRWXG),
    REGISTER(S_IRGRP),
    REGISTER(S_IWGRP),
    REGISTER(S_IXGRP),
    
    REGISTER(S_IRWXO),
    REGISTER(S_IROTH),
    REGISTER(S_IWOTH),
    REGISTER(S_IXOTH),
#endif
    {NULL,0}
};
EXPORT int Perm(lua_State *l){
    struct stat *st = (struct stat*)luaL_checkudata(l,1,STATSTRING);
    int perm = 0;
    //user perm
    perm = st->st_mode & S_IRWXU;
#if defined(LINUX) 
    //group perm
    perm |= st->st_mode & S_IRWXG;
    //other perm
    perm |= st->st_mode & S_IRWXO;
#endif
    lua_pushinteger(l, perm);
    return 1;
}

EXPORT int Isdir(lua_State *l){
    struct stat *st = (struct stat*)luaL_checkudata(l,1,STATSTRING);
    lua_pushboolean(l, S_ISDIR(st->st_mode));
    return 1;
}

EXPORT int Size(lua_State *l){
    struct stat *st = (struct stat*)luaL_checkudata(l,1,STATSTRING);
    lua_pushinteger(l, st->st_size);
    return 1;
}

EXPORT int Getmodtime(lua_State *l){
    struct stat *st = (struct stat*)luaL_checkudata(l,1,STATSTRING);
    lua_pushinteger(l, st->st_mtime);
    return 1;
}

EXPORT int Getcreatetime(lua_State *l){
    struct stat *st = (struct stat*)luaL_checkudata(l,1,STATSTRING);
    lua_pushinteger(l, st->st_ctime);
    return 1;
}

EXPORT int Getlastaccesstime(lua_State *l){
    struct stat *st = (struct stat*)luaL_checkudata(l,1,STATSTRING);
    lua_pushinteger(l, st->st_atime);
    return 1;
}

static elem_t filetypes[] = {
   REGISTER(S_IFIFO),
   REGISTER(S_IFCHR),
   REGISTER(S_IFDIR),
   REGISTER(S_IFBLK),
   REGISTER(S_IFREG),
#if defined(LINUX)
   REGISTER(S_IFLNK),
   REGISTER(S_IFSOCK),
#endif
   {NULL, 0}
};

EXPORT int Gettype(lua_State *l){
    struct stat *st = (struct stat*)luaL_checkudata(l,1,STATSTRING);
    int flag = 0;
    if(S_ISDIR(st->st_mode)){
        flag = S_IFDIR;
    }else if(S_ISFIFO(st->st_mode)){
        flag = S_IFIFO;
    }else if(S_ISCHR(st->st_mode)){
        flag = S_IFCHR;
    }else if(S_ISBLK(st->st_mode)){
        flag = S_IFBLK;
    }else if(S_ISREG(st->st_mode)){
        flag = S_IFREG;
    }
#if defined(LINUX)
    else if(S_ISSOCK(st->st_mode)){
        flag = S_IFSOCK;
    }else if(S_ISLNK(st->st_mode)){
        flag = S_IFLNK;
    }
#endif
    else{
        flag = -1;
    }
    lua_pushinteger(l, flag);
    return 1;
}

static luaL_Reg statfuncs[] = {
    REGISTERFUNC(Isdir),
    REGISTERFUNC(Isregular),
    REGISTERFUNC(Perm),
    REGISTERFUNC(Size),
    REGISTERFUNC(Getmodtime),
    REGISTERFUNC(Getcreatetime),
    REGISTERFUNC(Getlastaccesstime),
    REGISTERFUNC(Gettype),
    {NULL, NULL}
};

static elem_t modes[] = {
    REGISTER(O_RDONLY),
    REGISTER(O_WRONLY),
    REGISTER(O_RDWR),
    REGISTER(O_APPEND),
    REGISTER(O_CREAT),
    REGISTER(O_TRUNC),
#if defined(LINUX)
    REGISTER(O_NONBLOCK),
#endif
    REGISTER(O_EXCL),
    {NULL,0}
};

static elem_t whence[] = {
    REGISTER(SEEK_SET),
    REGISTER(SEEK_CUR),
    REGISTER(SEEK_END),
    {NULL,0}
};

static elem_t others[] = {
    REGISTER(EOF),
    {NULL, 0}
};
EXPORT int luaopen_lionos(lua_State *l){
    //stat 函数组
    luaL_newmetatable(l, STATSTRING);
    lua_pushvalue(l, -1);
    lua_setfield(l, -2, "__index");
    //向元表中注册函数
    luaL_setfuncs(l, statfuncs, 0);

    //fd 函数组
    luaL_newmetatable(l,FDSTRING);
    lua_pushvalue(l, -1);
    lua_setfield(l, -2, "__index");
    lua_pushcfunction(l, Fdclose);
    lua_setfield(l, -2, "__gc");
    
    luaL_setfuncs(l, fdfuncs, 0);
    int i = 0;
	luaL_newlib(l, funs);
#define REGISTERCONST(elem) \
    i = 0;\
    while(elem[i].name != NULL){\
        lua_pushinteger(l, elem[i].value);\
        lua_setfield(l, -2 ,elem[i].name);\
        i++;\
    }
    
    //注册file type
    REGISTERCONST(filetypes)
    //注册perm
    REGISTERCONST(perms)
    //注册文件 mode
    REGISTERCONST(modes)
    //注册whence
    REGISTERCONST(whence)

    //注册访问模式
    REGISTERCONST(accessmode)
    //注册其他
    REGISTERCONST(others)
#undef REGISTERCONST
    
	return 1;
}
