#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <sys/resource.h>
#include <unistd.h>
#include "benchmark.h"
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#define concatenate(hi, lo) (((unsigned long int) hi << 32) | lo)

unsigned long int alpha(long int size, long int stride, int flip){
    int x = rand() % size;
    x = (x < 0) ? (x)*(-1) : (x);
    unsigned long int val = (stride*(x))%(size/2);
    val = (flip*(size/2)) + val;
    return val;
}

int* random_alloc(long int size, long int stride){
    int* buf = (int*)calloc(size, sizeof(int));
    unsigned long int val;
    int i, allocs;
    int index;
    srand(420);
    int flip = 1;
    val = alpha(size,stride,flip);
    index = 0;
    i = 0;
    allocs = size/stride;
    while(i < allocs-1){
        while(buf[val] != 0 || index == val){
            val = alpha(size,stride,flip);
        }
        buf[index] = val;
        index = val; 
        flip = 1-flip;
        val = alpha(size,stride,flip);
        i++;
    }
    buf[index] = 0;
    return buf;
}

double start_access(int size, int stride, int iterations){
    int val, i, allocs;
    int index;
    int* buf = random_alloc(size, stride);
    i = 0;
    index = 0;
    int acc = 0;
    unsigned int cycles_high0, cycles_low0, cycles_high1, cycles_low1;
    unsigned long int timer_diff =0;

    asm volatile ("cpuid\n\t"   \
        "rdtsc\n\t"           \
        "mov %%edx, %0\n\t"   \
        "mov %%eax, %1\n\t"   \
        : "=r" (cycles_high0), "=r" (cycles_low0)  \
        :: "%rax", "%rbx", "%rcx", "%rdx");

    while(i<iterations){
        index = buf[index];
        i++;
    }
    
     asm volatile ("rdtscp\n\t"   \
        "mov %%edx, %0\n\t"    \
        "mov %%eax, %1\n\t"    \
        "cpuid\n\t"            \
        : "=r" (cycles_high1), "=r" (cycles_low1)  \
        :: "%rax", "%rbx", "%rcx", "%rdx");

    timer_diff = concatenate(cycles_high1, cycles_low1) - concatenate(cycles_high0, cycles_low0);
    free(buf);
    return (timer_diff/iterations);
}

int main(int argc, char** argv){

    long long unsigned int size;
    unsigned long int stride;
    unsigned int iterations = 1000;
    setpriority(PRIO_PROCESS, getpid(), -20);
    int sizes [12];
    int strides[12];
    sizes[0] = 4096; // Sizes 4K and above... 
    for(int i = 1 ; i < 12; i++)
        sizes[i] = sizes[i-1]*2;

    strides[0] = 4; // Strides 4 and above....
    for(int i = 1 ; i < 12; i++)
        strides[i] = strides[i-1]*4;

    for(int i = 0; i < 12; i++){
        for (int j = 0; j < 12; j++){
            stride = strides[j];
            size = sizes[i];
            if(stride < size){
                double timer_diff = start_access(size, stride, iterations);
                printf("[FINAL] (stride,iterations,size,timer): %d, %d, %llu, %f\n", stride, iterations, size, timer_diff);
            }
        }
    }   
    return 0;
}