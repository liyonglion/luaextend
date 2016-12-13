#include "cstring.h"
#include <stdio.h>
#include <stdlib.h>

long long GetMaxRecentofTwo(int size){

	int i = 0, n = size;
	while(n != 0){
		i++;
		n = n>>1;
	}
	return (size >> (i-1))<<(i+1);
}
int InitString(string *str, int size){
	if(str == NULL){
		return -1;
	}

	str->size = size;
	str->len = 0;
	str->buf = (char *)malloc(sizeof(char)*str->size);
	if(str->buf == NULL){
		return -1;
	}
	return 0;
}

string * String(long long size){
	string *res = (string *)malloc(sizeof(string));
	if(res == NULL){
		return NULL;
	}
	if(InitString(res, size) != 0){
		free(res);
		return NULL;
	}
	return res;
}
int Resize(string *str, long long size){
    if(str->size &(str->size -1 ) != 0){
        str->size = GetMaxRecentofTwo(str->size);
    }else{
	    str->size *= 2;
    }
    if(str->size == 0){
        str->size = size + 1;
    }
	str->buf = realloc(str->buf, str->size);
	if(str->buf == NULL){
		return -1;
	}
	return 0;
}
void StringAppendN(string *str, const char *ctx, long long n){
	n = min(n, strlen(ctx));

	while(str->len + n > str->size){
		Resize(str,n);
	}
	memcpy(str->buf + str->len, ctx, n);
	str->len += n;
}

void StringAppend(string *str, const char *ctx){
	StringAppendN(str, ctx, strlen(ctx));
}

void StringAppendc(string *str, char c){
	StringAppendN(str, &c, 1);
}

long long StringLen(string *str){
    return str->len;
}
long long StringCap(string *str){
    return str->size;
}
char StringIndex(string *str, long long pos){
    return str->buf[pos];
}
long long  StringSeek(string *str, long long pos){
    long long cur_pos = str->len;
    pos = str->len + pos > 0? pos: -(str->len);
    str->len += pos;
    return cur_pos;
}
char * GetCString(string *str){
    str->buf[str->len] = '\0';
    return str->buf;
}
void DestroyString(string *str){
	if(str->buf != NULL){
		free(str->buf);
	}
}

#if 0
int main(int argc, char *argv[]){
    string str;
    InitString(&str, 5);
    StringAppendN(&str, "this is a test", 4);
    StringAppend(&str, " is ");
    StringAppendc(&str, 'a');
    StringAppend(&str, " test");
    StringAppend(&str, ". you");
    StringSeek(&str, -4);
    printf("%s\n", GetString(&str));
    DestroyString(&str);
}
#endif
