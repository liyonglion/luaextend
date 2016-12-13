#include <stdio.h>
#include <string.h>
#include "md5.h"
#include <ctype.h>
#include <stdlib.h>
#include "defer.h"
#include "slicestring.h"
#include "errdef.h"
#include "stringapi.h"
/*
 * @brief 算法由于在Brian Kernighan与Dennis Ritchie的《The C Programming Language》一书被展示而得 名，是一种简单快捷的hash算法，也是Java目前采用的字符串的Hash算法（累乘因子为31）。
 *
 * @param str 待hash字符串
 * @param len hash字符串长度
 *
 * @return  hash后的结果
 */
long long  HashString(const char *str,int len){
    long long hash = 0;
    int ch = 0;
    long long i = 0;
    while (i < len){
        ch = (int)*str;
        str++;
        hash = hash * 31 + ch;// 也可以乘以31、131、1313、13131、131313..
        i++;
    }
    return hash;
}

/**
 * @brief sunday 算法，从字符串开头开始查找，返回匹配字符串的位置
 *
 * @param src 待匹配字符串
 * @param des 匹配字符串
 *
 * @return 匹配字符串的位置
 */
int SundayBackward(const char *src, const char *des){
    int len_s = strlen(src);
    int len_d = strlen(des);
    char next[256];
    int i = 0;
    memset(next, 1, sizeof(char)*256);
    //记录模式串每个字符出现的最后位置到开头的偏移量
    for(i = 0;i < len_d;i++){
        next[des[i]] = len_d - i;
    }
    int pos = 0;
    while(pos <(len_s - len_d +1)){
        i = pos;
        int j = 0;
        for(j = 0;j < len_d;++j,++i){
            if(src[i] != des[j]){
                pos += next[src[pos + len_d]];
                break;
            }
        }
        if(j == len_d){
            return pos;
        }
    }
    return STRING_INVALID_POS;
}
/**
 * @brief sunday 算法，从字符串末尾开始查找，返回匹配字符串的位置
 *
 * @param src 待匹配字符串
 * @param des 匹配字符串
 *
 * @return 匹配字符串的位置
 */
int SundayForward(const char *src, const char *des){
    int len_s = strlen(src);
    int len_d = strlen(des);
    char next[256];
    int i = 0;
    memset(next, 1, sizeof(char)*256);
    if(len_s < len_d){
        return -1;
    }
    //记录模式串每个字符出现的最后位置到开头的偏移量
    for(i = 0;i < len_d;i++){
        next[des[i]] = i + 1;
    }
    int pos = len_s - len_d;
    while(pos >= 0){
        i = pos;
        int j = 0;
        for(j = 0;j < len_d;++i,++j){
            if(src[i] != des[j]){
                pos -= next[src[pos+1]];
                break;
            }
        }
        if(j == len_d){
            return pos;
        }
    }
    return STRING_INVALID_POS;
}


/**
 * @brief 是否有sub前缀
 *
 * @param str 源字符串
 * @param sub 前缀
 *
 * @return 
 *      STRING_NOTFOUND:没有找到
 *      STRING_FOUND：找到
 */
int S_Hasprefix(const char *str, const char *sub){
    if(str == NULL || sub == NULL){
        return STRING_NOTFOUND;
    }
    if(strlen(sub) > strlen(str)){
        return STRING_NOTFOUND;
    }
    if(memcmp(str, sub, strlen(sub)) == 0){
        return STRING_FOUND;
    }
    return STRING_NOTFOUND;
}

/**
 * @brief 是否有sub后缀
 *
 * @param str 源字符串
 * @param sub 后缀字符串
 *
 * @return 
 *      STRING_NOTFOUND:没有找到
 *      STRING_FOUND：找到
 */
int S_HasSuffix(const char *str, const char *sub){
    if(str ==NULL|| sub ==NULL){
        return STRING_NOTFOUND;
    }
    if(strlen(sub) > strlen(str)){
        return STRING_NOTFOUND;
    }
    if(memcmp(str + strlen(str) - strlen(sub), sub,strlen(sub)) == 0){
        return STRING_FOUND;
    }
    return STRING_NOTFOUND;
}

/**
 * @brief 是否包含sub字符串
 *
 * @param str 源字符串
 * @param sub 子串
 *      STRING_NOTFOUND:没有找到
 *      STRING_FOUND：找到
 * @return 
 */
int S_Contains(const char *str, const char *sub){
    if(str == NULL || sub == NULL){
        return STRING_INVALID;
    }
    if(strlen(sub) > strlen(str)){
        return STRING_NOTFOUND;
    }
    if(SundayBackward(str, sub) != STRING_INVALID_POS){
        return STRING_FOUND;
    }
    return STRING_NOTFOUND;
}

/**
 * @brief 字符串sub中的任一值在str中第一次出现的位置，如果不存在或者sub为空字符串则返回-1。
 *
 * @param str 源字符串
 * @param sub 子字符串
 *
 * @return 第一次出现位置信息；不存在返回-1
 */
int S_IndexAny(const char *str, const char *sub){
    CHECKNULL(str, STRING_INVALID);
    CHECKNULL(sub, STRING_INVALID);
    int i= 0,j = 0;
    for(;i < strlen(sub);i++){
        for(j = 0;j < strlen(str);j++){
            if(str[j] == sub[i]){
                return j;
            }
        }
    }
    return STRING_INVALID;
}


/**
 * @brief 字符串sub中的任一值在str中最后一次出现的位置，如不存在或者chars为空字符串则返回-1。
 *
 * @param str 
 * @param sub
 *
 * @return 
 */
int S_LastIndexAny(const char *str, const char *sub){
    int i = strlen(str),j = 0;
    const char *s = str;
    for(;i >= 0;i--){
        for(j = 0;j < strlen(sub);j++){
            if(s[i] == sub[j]){
                return i+1;
            }
        }
    }
    return STRING_INVALID;
}

/**
 * ContainsAny returns true if any Unicode code points in sub are within str.
 * @brief 判断字符串str 是否包含字符串sub中的任一字符。
 *
 * @param str
 * @param sub
 *
 * @return 
 *      STRING_NOTFOUND:没有找到
 *      STRING_FOUND：找到
 */
int S_ContainsAny(const char *str, const char *sub){
    CHECKNULL(str, STRING_INVALID);
    CHECKNULL(sub,STRING_INVALID);
    if(S_IndexAny(str, sub) != STRING_INVALID){
        return STRING_FOUND;
    }
    return STRING_NOTFOUND;
}

/**
 * @brief 返回字符串s中有几个重复的sep子串。
 *
 * @param s
 * @param sep
 *
 * @return 次数，错误返回-1
 */
int S_Count(const char *s, const char *sep){
    CHECKNULL(s,0);
    CHECKNULL(sep, 0);
    int i = 0;
    int counter = 0;
    int pos = 0;
    while(i < strlen(s)){
        if(strlen(s + i) < strlen(sep)){
            return counter;
        }
        pos = SundayBackward(s+i,sep);
        if(pos == STRING_INVALID_POS){
            break;
        }
        counter++;
        i += pos + strlen(sep);
    }
    return counter;
}

/**
 * @brief 返回将字符串按照空白（IsSpace确定，可以是一到多个连续的空白字符）分割的多个字符串。如果字符串全部是空白或者是空字符串的话，会返回空切片。*会跳过开头和结尾的Space
 *
 * @param str 源字符
 * @param slice 切片
 *
 * @return  
 */
int S_Fields(const char *str, stringSlice_t *slice){
    const char *s = str;
    if(str == NULL || slice == NULL){
        errNo = ERRNULLPOINTER;
        return BAD;
    }
    int count = 1;
    int i = 0,pos = 0,flag = 0,j = 0;
    //开头跳过space
    for(i = 0;i < strlen(s);i++){
        if(!isspace(s[i])){
            break;
        }
    }
    //跳过末尾的space
    for(j = strlen(s) - 1 ; j > i;j--){
        if(!isspace(s[j])){
            break;
        }
    }
    //分析i和j之间的字符
    pos = i;
    for(;i <= j;i++){
        if(isspace(s[i])){
            if(flag == 0){
                AppendStrN(slice, s+ pos,i - pos);
                flag = 1;
                continue;
            }
        }else{
            if(flag == 1){
                flag = 0;
                pos = i;
            }
        }
    }
    AppendStrN(slice, s+ pos,i - pos);
    return OK;
}

/**
 * @brief 子串sep在字符串s中第一次出现的位置，不存在则返回-1
 *
 * @param str
 * @param sub
 *
 * @return 
 */
int S_Index(const char *str, const char *sub){
    return SundayBackward(str, sub);
}

/**
 * @brief 子串sep在字符串s中最后一次出现的位置，不存在则返回-1
 *
 * @param str
 * @param sub
 *
 * @return 
 */
int S_LastIndex(const char *str, const char *sub){
    return SundayForward(str, sub);
}


/**
 * @brief 返回将s中前n个不重叠old子串都替换为new的新字符串，如果n<0会替换所有old子串。
 *
 * @param str
 * @param old
 * @param new
 * @param n
 * @param slice
 *
 * @return 
 */
int S_Replace(const char *str, const char *old, const char *newstr, int n, stringSlice_t *slice){
    int pos = 0,pos1 = 0,count = 0;
    if(n == 0){
        return OK;
    }
    int used = 0;
    int size = strlen(str);
    const char *s = str;
    while(pos < strlen(s)){
        pos1 = SundayBackward(s + pos, old);
        if(pos1 == STRING_INVALID_POS){
            break;
        }
        AppendStrN(slice, s + pos, pos1);
        used += pos1 - pos;
        AppendStr(slice, newstr);
        used += strlen(newstr);
        count++;
        pos += pos1;
        pos += strlen(old);
        if(count == n){
            break;
        }
    }    
    //拷贝剩余字符串
    if(pos < strlen(s)){
        AppendStrN(slice, s + pos, strlen(s) - pos);
    }
    return OK;
}

/**
 * @brief 返回将s前端所有cutset包含的值都去掉的字符串。由调用则负责free
 *
 * @param s
 * @param cutset
 *
 * @return 
 */
char *S_TrimLeft(const char *s, const char *cutset){
    char *res = (char *)malloc(sizeof(char)*(strlen(s) + 1));
    memset(res, 0, sizeof(char)*(strlen(s) + 1));
    memcpy(res, s, sizeof(char)*strlen(s));
    if(cutset == NULL || strlen(cutset) == 0){
        return res;
    }
    char cutcollection[32] = {0};
    int i = 0;
    int pos = 0, m = 0;
    for(i = 0; i< strlen(cutset);i++){
        pos = cutset[i]/8;
        m = cutset[i]%8;
        cutcollection[pos] = cutcollection[pos] | 1 << m;
    }
    const char *p = s;
    for(i = 0; i < strlen(s);i++){
        pos = s[i]/8;
        m = s[i]%8;
        if((cutcollection[pos] & (1 << m)) == (1 << m)){
            p++;
            continue;
        }
        break;
    }
    memset(res, 0, sizeof(char)*(strlen(s) + 1));
    memcpy(res, p, strlen(p));
    return res;
}

/**
 * @brief 返回将s后端所有cutset包含的utf-8码值都去掉的字符串。由调用则负责free
 *
 * @param s
 * @param cutset
 *
 * @return 
 */
char * S_TrimRight(const char *s, const char *cutset){
    char *res = (char *)malloc(sizeof(char)*(strlen(s) + 1));
    memset(res, 0, sizeof(char)*(strlen(s) + 1));
    memcpy(res, s, sizeof(char)*strlen(s));
    if(cutset == NULL || strlen(cutset) == 0){
        return res;
    }
    char cutcollection[32] = {0};
    int i = 0;
    int pos = 0, m = 0;
    for(i = 0; i< strlen(cutset);i++){
        pos = cutset[i]/8;
        m = cutset[i]%8;
        cutcollection[pos] = cutcollection[pos] | 1 << m;
    }
    char *p = res + strlen(res) - 1;
    for(i = strlen(s) - 1; i >= 0;i--){
        pos = s[i]/8;
        m = s[i]%8;
        if((cutcollection[pos] & (1 << m))  == (1 << m)){
            *p = '\0';
            p--;
            continue;
        }
        break;
    }
    return res;
}
/**
 * @brief  根据sep分割str字符串
 *
 * @param str
 * @param sep
 * @param slice
 *
 * @return 
 */
int S_SplitString(const char *str, const char *sep, stringSlice_t *slice){
    const char *s = str;
    int pos = 0;
    int pos1 = 0;
    while(pos < strlen(s)){
        pos1 = SundayBackward(s + pos, sep);
        if(pos1 == STRING_INVALID_POS){
            break;
        }
        AppendStrN(slice, s + pos, pos1);
        pos += pos1;
        pos += strlen(sep);
    }
    if(pos < strlen(s)){
        AppendStrN(slice, s + pos, strlen(s) - pos);
    }
    return OK;
}

char * S_TrimSpace(const char *str){
    deferBegin(); 
    const char *cutset = " ";
    char *s = S_TrimLeft(str, cutset);
    defer(free,s);
    s =S_TrimRight(s, cutset);
    deferReturn(s);
}

