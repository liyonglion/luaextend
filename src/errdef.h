#ifndef __ERRNUM__H__LION
#define __ERRNUM__H__LION

#define ERRBASE 0
#define ERRNULLPOINTER 1
#define ENOENOUGHMEMERY ERRBASE + 1

extern int errNo;

char *GetErrMsg(int errnum);

#define OK 0
#define BAD -1
#endif


