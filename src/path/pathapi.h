#ifndef __PATH__API__H__
#define __PATH__API__H__

#include <stdio.h>
#include <string.h>
#include "stringapi.h"
#include "type.h"
#include "errdef.h"
#include "cstring.h"
#include <stdlib.h>
#if defined(LINUX)
	#include <limits.h>
	char sep = '/';
#elif defined(WINDOW)
	#include <windows.h>
	char sep = '\\'; 
#endif

int IsPathSeparator(char c){
#if defined(LINUX)
    return c == '/';
#elif defined(WINDOW)
    return c == '\\' || c == '/'
#endif
}

void pathclean(const char *path, string *str);

int volumeNameLen(const char *path){
#if defined(LINUX)
    return 0;
#elif defined(WINDOW)
    if(strlen(path) < 2){
        return 0;
    }
    //判断是否是磁盘
    char c = path[0];
    if(path[1] == ':' && ('a' <= c && c<= 'z' || 'A' <= c && c <= 'Z')){
        return 2;
    }
    //是否是UNC目录 \\servername\sharename\filename
    int l = strlen(path);
    int n = 0;
    if(l >= 5) && IsPathSeparator(path[0] && IsPathSeparator(path[1]) && !IsPathSeparator(path[2]) && path[2] != '.'){
        //server name
        for(n = 3; n <= l -1;n++){
            //不能重复“\”
            if(IsPathSeparator(path[n])){
                n++;
                //share name
                if(!IsPathSeparator(path[n])){
                    if(path[n] == '.'){
                        break;
                    }
                    for(;n < l;n++){
                        if(IsPathSeparator(path[n])){
                            break
                        }
                    }
                    return n;
                }
                break;
            }
        }
    }
    return 0;
#endif
}

int fromSlash(const char *src, char *dst){
    if(sep == '/'){
        memcpy(dst, src, strlen(src) + 1);
        return OK;
    }
    for(int i = 0;i < strlen(src);i++){
        if(src[i] == '/'){
            dst[i] = sep;
            continue;
        }
        dst[i] = src[i];
    }
    return OK;
}
int toSlash(const char *src, char *dst){
    if(sep == '/'){
        memcpy(dst, src, strlen(src) + 1);
        return OK;
    }
    for(int i = 0;i < strlen(src);i++){
        if(src[i] == sep){
            dst[i] = '/';
            continue;
        }
        dst[i] = src[i];
    }
    return OK;
}

void pathbase(const char *path , string *str){
    if(strlen(path) == 0){
        StringAppendc(str, '.');
        return;
    }
    //strip traliling slashes.
    string strpath;
    InitString(&strpath, strlen(path));
    StringAppend(&strpath, path);
    while(StringLen(&strpath) > 0 && IsPathSeparator(StringIndex(&strpath, StringLen(&strpath) - 1))){
        StringSeek(&strpath, -1);
    }
    char *rpath = GetCString(&strpath);
    int vollen = volumeNameLen(path);
    //Find the last element
    int i = strlen(rpath) - 1;
    while(i >= 0 && !IsPathSeparator(rpath[i])){
        i--;
    }
    if(i >= 0){
        rpath = rpath + i + 1; 
    }
    if(strlen(rpath) == 0){
        StringAppendc(str, sep);
        DestroyString(&strpath);
        return;
    }
    StringAppend(str, rpath);
    DestroyString(&strpath);
    return;
}

void pathdir(const char *path, string *str){
    int vollen = volumeNameLen(path);
    int i = strlen(path) - 1;
    while(i >= vollen && !IsPathSeparator(path[i])){
        i--;
    }
    char *clean_path = (char *)malloc(sizeof(char)*(i+1 - vollen + 1));
    if(clean_path ==NULL){
        exit(ENOENOUGHMEMERY);
    }
    memset(clean_path, 0, i+1 - vollen + 1);
    memcpy(clean_path, path + vollen, i+1 - vollen);
    pathclean(clean_path, str);
    free(clean_path);
    return;
}
void pathclean(const char *path, string *str){
    const char *originalPath = path;
    int vollen = volumeNameLen(path);
    path = path + vollen;
    
    if(strlen(path) == 0){
        if(vollen > 1 && originalPath[1] != ':'){
            //should be UNC
            StringAppend(str, path);
            fromSlash(path, GetCString(str));
            return;
        }
        StringAppend(str, originalPath);
        StringAppend(str, ".");
        return;
    }
    int rooted = IsPathSeparator(path[0]);
    int n = strlen(path);
    int r = 0, dotdot = 0;
    if(rooted){
        StringAppendc(str, sep);
        r = dotdot = 1;
    }
    while(r < n){
        if(IsPathSeparator(path[r])){
            r++;
        }else if(path[r] == '.' &&(r+1 == n || IsPathSeparator(path[r+1]))){
            //. element
            r++;
        }else if(path[r] == '.' && path[r+ 1] == '.' && (r + 2 == n || IsPathSeparator(path[r+2]))){
            //..element: remove to last separator
            r += 2;
            if(StringLen(str) > dotdot){
                StringSeek(str, -1);
                while(StringLen(str) > dotdot && !IsPathSeparator(StringIndex(str, StringLen(str) - 1))){
                    StringSeek(str, -1);
                }
            }else if(!rooted){
                //cannot backtrack, but not rooted, so append ..element.
                if(StringLen(str) > 0){
                    StringAppendc(str, sep);
                }
                StringAppendc(str, '.');
                StringAppendc(str, '.');
                dotdot = StringLen(str);
            }
        }else{
            //real path element
            //add slash if needed
            if(rooted && StringLen(str) != 1 || !rooted && StringLen(str) != 0){
                StringAppendc(str,sep);
            }
            //copy element
            for(;r < n && !IsPathSeparator(path[r]);r++){
                StringAppendc(str, path[r]);
            }
        }
    }
    if(StringLen(str) == 0){
        StringAppendc(str, '.');
    }
    fromSlash(GetCString(str),GetCString(str));
    return;
}
void pathext(const char *path,string *str){
    int i = 0;
    for(i = strlen(path) -1; i >= 0&& !IsPathSeparator(path[i]);i--){
        if(path[i] == '.'){
            StringAppend(str, path + i + 1);
            return;
        }
    }
    return;
}

int isabs(const char *path){
    int vollen = volumeNameLen(path);
#if defined(LINUX)
    return S_Hasprefix(path, "/");
#elif defined(WINDOW)
    return vollen?1:0;
#endif
}

void splitpath(const char *path, string *dir, string *file){
    int vollen = volumeNameLen(path);
    int i = strlen(path) - 1;
    while(i >=vollen && !IsPathSeparator(path[i])){
        i--;
    }
    StringAppendN(dir, path, i+1);
    StringAppend(file, path + i+ 1);
    return;
}

int pathabs(const char *path, string *str){
	char abspath[PATH_MAX] = {0};
#if defined(LINUX)
	if(realpath(path, abspath) == NULL){
		return BAD;
	}

#elif defined(WINDOW)
	char *ppart = NULL;
	size_t len = GetFullPathName(path, MAX_PATH, abspath, &ppart);
    if(len == 0){
        return BAD;
    }
#endif
    StringAppend(str, abspath);
    return OK;    
}
#endif
