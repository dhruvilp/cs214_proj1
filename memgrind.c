/*
 @author 		Dhruvil Patel & Michael Yang
 @description 	CS214 Proj1 
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mymalloc.h"
#include "mymalloc.c"

#define malloc(x) mymalloc(x, __FILE__ , __LINE__ )
#define free(x) myfree(x, __FILE__ , __LINE__ )
#define MAX 4096

/*
 * A: malloc() 1 byte and immediately free it - do this 150 times
 */
double testA() {
  
  int a, b;
  double totalT = 0;
  clock_t start, end;

  for (a = 0; a < 100; a++) {
    start = clock();
    for (b = 0; b < 150; b++) {
      char* pointer = malloc(1);
      free(pointer);
    }
    end = clock();
    printf("%.12f",(double)start);
    printf("%.12f",(double)end);
    totalT += ((double)(end - start))/CLOCKS_PER_SEC;
  }
  return totalT/100;

}

/*
 * B: malloc() 1 byte, store the pointer in an array - do this 150 times.
   Once you've malloc()ed 50 byte chunks, then free() the 50 1 byte pointers one by one.
  */
double testB() {
  int a, b;
  double totalT = 0;
  clock_t start, end;

  for (a = 0; a < 100; a++) {
    start = clock();
    char* ptr[150];

    for (b = 0; b < 150; b++) {
      ptr[b] = (char*)malloc(1);
      if (ptr[b] == NULL) {
        return -1;
      }
  	}

  	for (b = 0; b < 150; b++) {
      free(ptr[b]);
  	}
  	end = clock();
    totalT += (double)(end - start)/CLOCKS_PER_SEC;
  }

  return totalT/100;
}

/*
 *  Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer - do this 50 times
 *  - Keep track of each operation so that you eventually malloc() 50 bytes, in total
	> if you have already allocated 50 times, disregard the random and just free() on each
 	  iteration
	- Keep track of each operation so that you eventually free() all pointers
 	> don't allow a free() if you have no pointers to free()
 */
double testC() {
  int a, r;
  int m = 0;
  int f = 0;
  int total = 0;
  double totalT = 0;
  clock_t start, end;

  for (a = 0; a < 100; a++) {
    char* ptr[50];
    start = clock();
    total = 0;
      while(total < 50){
        r = rand() % 2;
        if ((r == 0 && m > 0) || m >= 50-total) {
          m--;
          free(ptr[m]);
          f++;
          total++;
        }
        else if (r == 1 || m == 0) {
          ptr[m] = (char*)malloc(1);
          if (ptr[m] == NULL) {
            return -1;
          }
          m++;
          total++;
        }
      } 
    end = clock();
    totalT += (double)(end-start)/CLOCKS_PER_SEC;
  }
  return totalT/100;
}


/*
    Randomly choose between a randomly-sized malloc() or free()ing a pointer – do this many
    times (see below)
    - Keep track of each malloc so that all mallocs do not exceed your total memory capacity
    - Keep track of each operation so that you eventually malloc() 50 times
    - Keep track of each operation so that you eventually free() all ptr
    - Choose a random allocation size between 1 and 64 bytes
*/
double testD() {

  int a, r;
  int m = 0;
  int f = 0;
  int total = 0;
  int rand_size = 0;
  double totalT = 0;
  clock_t start, end;

  for (a = 0; a < 100; a++) {
    char* ptr[50];
    start = clock();
    total = 0;
      while (total < 50 && 0 <= m && m < 50) {
        r = rand() % 2;
        rand_size = rand() % 64 + 1;
        if ((r == 0 && m > 0) || m >= 50-total) {
          m--;
          free(ptr[m]);
          f++;
          total++;
        }
        else if (r == 1 || m == 0) {
          ptr[m] = (char*)malloc(rand_size);
          if (ptr[m] != NULL) {
            m ++;
            total++;
          }
        }

      }
    end = clock();
    totalT += (double)(end-start)/CLOCKS_PER_SEC;
  }
  return totalT/100;

}

/*
 * E: Freeing The Same Pointer
 */
double testE() {
	double totalT = 0;
	clock_t start, end;
	start = clock();
	
    char * a;
    a = (char *) malloc(150);
    free(a);
    a = (char *) malloc(150);
    free(a);
    free(a);
    
    end = clock();
    totalT += (double)(end-start)/CLOCKS_PER_SEC;
    return totalT/100;

}

/*
 * F: Freeing Memory that Was Never Dynamically Allocated
 */
double testF() {
	double totalT = 0;
	clock_t start, end;
	start = clock();
	
	int a = 15;
	free(&a);

    end = clock();
    totalT += (double)(end-start)/CLOCKS_PER_SEC;
    return totalT/100;

}

int main(int argc, char** argv) {
  srand(time(NULL));
  printf("Testcase A took on avg %.12f microsec to complete.\n", testA()*1000000);
  printf("Testcase B took on avg %.12f microsec to complete.\n", testB()*1000000);
  printf("Testcase C took on avg %.12f microsec to complete.\n", testC()*1000000);
  printf("Testcase D took on avg %.12f microsec to complete.\n", testD()*1000000);
  printf("Testcase E took on avg %.12f microsec to complete.\n", testE()*1000000);
  printf("Testcase F took on avg %.12f microsec to complete.\n", testF()*1000000);

  return 0;

}