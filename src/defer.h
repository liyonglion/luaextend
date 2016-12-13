#ifndef __DEFER__H__LION
#define __DEFER__H__LION
#include "errdef.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void(*Freefn)(void *);

typedef struct fnode_s{
    Freefn fn;
    void *data;
    struct fnode_s *next;
}fnode_t;

typedef struct {
    fnode_t *header;
}defer_t;

defer_t * deferbegin();
void deferAdd(defer_t *d,Freefn fn, void *data);
void deferEnd(defer_t *d);

#define deferBegin() defer_t *curdefer = deferbegin()
#define defer(fn, data) deferAdd(curdefer, fn, data)
#define deferReturn(ret) deferEnd(curdefer); return ret
#endif


