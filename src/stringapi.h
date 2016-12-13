#ifndef __LION_STRING_API__H
#define __LION_STRING_API__H
#include "type.h"
#include "slicestring.h"

#define STRING_FOUND 1
#define STRING_NOTFOUND 0

#define STRING_INVALID_POS -1
#define STRING_INVALID -1

long long  HashString(const char *str,int len);
int SundayBackward(const char *src, const char *des);
int SundayForward(const char *src, const char *des);
int S_Hasprefix(const char *str, const char *sub);
int S_HasSuffix(const char *str, const char *sub);
int S_Contains(const char *str, const char *sub);
int S_IndexAny(const char *str, const char *sub);
int S_LastIndexAny(const char *str, const char *sub);
int S_ContainsAny(const char *str, const char *sub);
int S_Count(const char *s, const char *sep);
int S_Fields(const char *str, stringSlice_t *slice);
int S_Index(const char *str, const char *sub);
int S_LastIndex(const char *str, const char *sub);
int S_Replace(const char *str, const char *old,const char* newstr, int n, stringSlice_t *slice);
char *S_TrimLeft(const char *s, const char *cutset);
char * S_TrimRight(const char *s, const char *cutset);
int S_SplitString(const char *str, const char *sep, stringSlice_t *slice);
char * S_TrimSpace(const char *str);
#endif

