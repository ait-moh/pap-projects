#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<sys/time.h>

#include "implementation.h"

//DON'T CHANGE THIS FILE!!!
//DON'T CHANGE THIS FILE!!!
//DON'T CHANGE THIS FILE!!!
//DON'T CHANGE THIS FILE!!!

#define SIZE 16384


int main(){

    int *src = (int*) malloc(sizeof(int)*SIZE*SIZE);
    int *dst = (int*) malloc(sizeof(int)*SIZE*SIZE);

    //matrix initialization
    for(int s=0; s < SIZE*SIZE; s++)
    {
        src[s] = s;
        dst[s] = 0;
    }

    //flush cache by fetching unrelated data
    int *dum = (int*) malloc(sizeof(int)*32000*32000);
    for(int s=0; s < 32000*32000; s++)
    {
        dum[s] = s;
    }

    printf("Attempting to transpose a 16384 x 16384 matrix...");

    //start timer
    double timer;
    struct timeval begin, end;
    long seconds;
    long microseconds;
    gettimeofday(&begin, 0);

    #if defined(_N)
        naive(src, dst, SIZE);
    #endif
    #if defined(_O)
        oblivious(src, dst, SIZE);
    #endif
    #if defined(_A)
        aware(src, dst, SIZE);
    #endif
    #if defined(_OPTIMIZED)
        optimized(src, dst, SIZE);
    #endif

    //stop timer
    gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    timer = seconds + microseconds*1e-6;

    //validate result
    for(int i=0; i < SIZE; i++)
        for(int j=0; j < SIZE; j++)
        {
            if(dst[(i * SIZE) + j] != src[(j * SIZE) + i])
            {
                printf("Transposition WRONG!\n");
                exit(-1);
            }
        }

    printf("Transposition SUCESSFUL!\nTIME: %lf seconds\n",timer);
    
    free(dum);
    free(src);
    free(dst);
    return 0;
}