/*
 @author 	Dhruvil Patel & Michael Yang
 @description 	CS214 Proj1 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mymalloc.h"

#define malloc(x) mymalloc(x, __FILE__ , __LINE__ )
#define free(x) myfree(x, __FILE__ , __LINE__ )
#define MAX 4096

static char myblock[MAX] = {0};

meta* inext(meta* b) {
  return b->next?((meta*)(b->data+b->currsize)):NULL;
}

int divfunc(meta* b, size_t x) {

  meta* n;
  if (b->currsize<x)
    return 0;
    
  if(b->currsize >= x + sizeof(meta)) {
    n=(meta*)(b->data+x);
    n->next = b->next;
    b->next = 1;
    b->used = 1;
    n->currsize = b->currsize-x-sizeof(meta);
    n->used=0;
    b->currsize = x;
    n->prevsize = x;
    if ((b = inext(n)))
      b->prevsize = n->currsize;
    return 1;
  }

  b->used = 1;
  return 1;

}

void * mymalloc(size_t x, char * file, int line) {

  if(x == 0)
    return NULL;

  if(x > MAX - sizeof(meta)) {
    printf("\tError: There is not enough space to allocate %zu bytes.\n", x);
    return NULL;
  }

  meta* block = (meta*)myblock;

  if(!block->used && !block->currsize) {
    block->currsize = sizeof(myblock)-sizeof(meta);
  }

  do{
    if (!block->used && divfunc(block,x)){
      return block->data;
    }
  } while ((block = inext(block)));

  return NULL;

}


void myfree(void * x, char * file, int line) {

  meta* b = (meta*)(((char*)x) - sizeof(meta)), *c=NULL, *d=NULL;
  char cprev = 0, cnext = 0;

  if ((char*)b < myblock || (char*)b >= myblock+sizeof(myblock)){
    printf("\tError: pointer to free (%p) from file: %s, line: %d.\n", x, file, line);
    return;
  }

  if (!b->used) {
    printf("\tError: pointer to free (%p) from file: %s, line: %d.\n", x, file, line);
    return;
  }

  if (b->prevsize) {
    c = (meta*)(((char*)b) - b->prevsize - sizeof(meta));

    if (!c->used)
      cprev=1;
  }
  if (b->next) {
    d = (meta*)(b->data + b->currsize);

    if(!d->used)
      cnext=1;
  }

  if (cprev && cnext) {
    c->currsize += b->currsize + d->currsize + 2*sizeof(meta);
    if ((c->next = d->next)){
      d = (meta*)(d->data + d->currsize);
      d->prevsize = c->currsize;
    }
  } else if (cprev){
    c->currsize += b->currsize+sizeof(meta);
    if ((c->next = b->next)) {
      d->prevsize = c->currsize;
    }
  } else if (cnext) {
    b->used = 0;
    b->currsize += d->currsize+sizeof(meta);
    if ((b->next = d->next)) {
      c = (meta*)(d->data+d->currsize);
      c->prevsize = b->currsize;
    }
  } else{
    b->used=0;
  }

}
