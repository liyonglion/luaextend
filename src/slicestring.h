#ifndef __SLICE__H__LION
#define __SLICE__H__LION

typedef struct{
    int cap;
    int len;
    char **slice;
}stringSlice_t;

stringSlice_t *NewStringSlice(int cap);
void AppendStr(stringSlice_t *slice,const char *data);
void AppendStrN(stringSlice_t *slice,const char *data, int len);
int StringSliceLen(stringSlice_t *slice);
char *GetString(stringSlice_t *slice, int pos);
void DestroyStringSlice(void *slice);
#define MakeStringSlice() NewStringSlice(0)

#endif
