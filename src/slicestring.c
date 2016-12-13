#include "slicestring.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "errdef.h"

stringSlice_t *NewStringSlice(int cap){
    stringSlice_t *res = (stringSlice_t *)malloc(sizeof(stringSlice_t));
    if(res == NULL){
        exit(ENOENOUGHMEMERY);
    }
    memset(res, 0, sizeof(stringSlice_t));
    res->len = 0;
    res->cap = cap;
    res->slice = (char **)(void*)malloc(sizeof(char *)*cap);
    if(res->slice == NULL){
        free(res);
        exit(ENOENOUGHMEMERY);
    }
    return res;
}

void AppendStrN(stringSlice_t *slice,const char *data,int len){
    if(slice->len >= slice->cap){
        slice->cap = slice->cap ? 2*slice->cap:1;
        char **p = (char **)malloc(sizeof(char *)*slice->cap);
        if(p == NULL){
            exit(ENOENOUGHMEMERY);
        }
        memcpy(p, slice->slice, sizeof(char *)*slice->len);
        if(slice->slice != NULL){
            free(slice->slice);
        }
        slice->slice = p;
    }
    char *p = (char *)malloc(sizeof(char)*(len+1));
    if(p == NULL){
        exit(ENOENOUGHMEMERY);
    }
    memcpy(p,data, len);
    p[len] = '\0';
    slice->slice[slice->len] = p;
    slice->len++;
}

void AppendStr(stringSlice_t *slice,const char *data){
    AppendStrN(slice, data, strlen(data));
}

int StringSliceLen(stringSlice_t *slice){
    return slice->len ;
}

char *GetString(stringSlice_t *slice, int pos){
    if(pos > slice->len){
        return NULL;
    }
    return slice->slice[pos];
}
void DestroyStringSlice(void *s){
    stringSlice_t *slice = (stringSlice_t *)s;
    int len = StringSliceLen(slice);
    for(int i = 0; i < len; i++){
        free(slice->slice[i]);
        slice->slice[i] = NULL;
    }
    free(slice);
}
#if 0
int main(int argc ,char *argv[]){
   stringSlice_t *slice =  makeStringSlice();
   appendstr(slice, "liyong");
   appendstrN(slice, "yyyyyyy",3);
   int len = stringSliceLen(slice);
   for(int i = 0; i < len; i++){
        printf("%s\n", GetString(slice, i));
   }
   destroyStringSlice(slice);
}
#endif
