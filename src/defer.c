#include "defer.h"


defer_t * deferbegin(){
    defer_t *res = (defer_t *)malloc(sizeof(defer_t));
    if(res == NULL){
        exit(ENOENOUGHMEMERY);
    }
    memset(res, 0, sizeof(defer_t));
    return res;
}

void deferAdd(defer_t *d,Freefn fn, void *data){
    fnode_t *node = (fnode_t *)malloc(sizeof(fnode_t));
    if(node == NULL){
        exit(ENOENOUGHMEMERY);
    }
    memset(node, 0, sizeof(fnode_t));
    node->fn = fn;
    node->data = data;

    if(d->header == NULL){
        d->header = node;
        return;
    }
    node->next = d->header;
    d->header = node;
    return;
}

void deferEnd(defer_t *d){
    fnode_t *p = d->header;
    fnode_t *q = NULL;
    while(p != NULL){
        q = p->next;
        p->fn(p->data);
        free(p);
        p = q;
    }
    free(d);
    d = NULL;
    return;
}

/*
 void frees(void *s){
    printf("free: %s\n", s);
}

int main(int argc, char *argv[]){
    deferBegin();

    defer(frees, "1");
    defer(frees, "2");
    deferReturn(0);
}
 */


