/*
 @author 	Dhruvil Patel & Michael Yang
 @description 	CS214 Proj1 
*/

#ifndef mymalloc_h_
#define mymalloc_h_

#define malloc(x) mymalloc(x, __FILE__ , __LINE__ )
#define free(x) myfree(x, __FILE__ , __LINE__ )

typedef struct _meta meta;
struct _meta {
  unsigned char used : 1;
  unsigned char next : 1;
  unsigned short currsize : 14;
  unsigned short prevsize;
  char data[0];
};

#endif
