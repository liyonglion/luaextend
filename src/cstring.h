#ifndef __LION__STRING__H
#define __LION__STRING__H
#include "type.h"

typedef struct {
	long long size;
	long long len;
	char *buf;
}string;

int InitString(string *str, int size);
string * String(long long size);
void StringAppendN(string *str,const char *ctx, long long n);
void StringAppend(string *str,const char *ctx);
void StringAppendc(string *str, char c);
long long  StringSeek(string *str, long long pos);
char * GetCString(string *str);
void DestroyString(string *str);
long long StringLen(string *str);
long long StringCap(string *str);
char StringIndex(string *str,long long c);
#endif
