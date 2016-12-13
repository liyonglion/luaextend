#include "errdef.h"
#include <stdio.h>
int errNo = 0;

char* Errmsg[] = {
    NULL,
    "Null pointer\n",
    "No enough memery\n",
    NULL
};

char *GetErrMsg(int errnum){
    return Errmsg[errnum];
}

