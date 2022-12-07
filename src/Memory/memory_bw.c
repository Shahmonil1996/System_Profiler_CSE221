#include <stdio.h> 
#include <math.h>
#include <sched.h>
#include <string.h> 
#include <stdlib.h>
cpu_set_t  mask;
#define TOTAL_CACHE_SIZE (1<<25)
#define NO_OF_INTEGERS (TOTAL_CACHE_SIZE>>2)
#define NO_OF_INTEGERS_ARRAY 8388608
int array_a[NO_OF_INTEGERS],array_b[NO_OF_INTEGERS];
int array[NO_OF_INTEGERS_ARRAY];

int memory_read(int* start , int* end)
{
    long sum = 0;
    long long int cycle_high_start , cycle_low_start , cycle_high_end , cycle_low_end;
    int *ptr = start;
    asm("cpuid");
    asm volatile("rdtsc" : "=cycle_high" (cycle_high_start), "=cycle_low" (cycle_low_start));
    
    while (ptr < end)
    {
        sum += ptr[0];
        sum += ptr[8];
        sum += ptr[16];
        sum += ptr[24];
        sum += ptr[32];
        sum += ptr[40];
        sum += ptr[48];
        sum += ptr[56];
        sum += ptr[64];
        ptr = ptr + 72;
    }
    asm("cpuid");
    asm volatile("rdtsc" : "=cycle_high" (cycle_high_end), "=cycle_low" (cycle_low_end));
    //printf("Final Value is %lld %lld\n", cycle_high_end - cycle_high_start, cycle_low_end-cycle_low_start);
    return (cycle_low_end-cycle_low_start);
}

int memory_write(int* start , int* end)
{
    long sum = 0;
    long long int cycle_high_start , cycle_low_start , cycle_high_end , cycle_low_end;
    int *ptr = start;
    asm("cpuid");
    asm volatile("rdtsc" : "=cycle_high" (cycle_high_start), "=cycle_low" (cycle_low_start));
    
    while (ptr < end)
    {
        ptr[0] =  0;
        ptr[8] = 8;
        ptr[16] = 16;
        ptr[24] = 24;
        ptr[32] = 32;
        ptr[40] = 40;
        ptr[48] = 48;
        ptr[56] = 56;
        ptr[64] = 64;
        ptr = ptr + 72;
    }
    asm("cpuid");
    asm volatile("rdtsc" : "=cycle_high" (cycle_high_end), "=cycle_low" (cycle_low_end));
    //printf("Final Value is %lld %lld\n", cycle_high_end - cycle_high_start, cycle_low_end-cycle_low_start);
    return (cycle_low_end-cycle_low_start);
}



void assignToThisCore(int core_id)
{
    CPU_ZERO(&mask);
    CPU_SET(core_id, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
}
int main()
{
assignToThisCore(0);

int total_time_read=0;
int total_time_write=0;

for(int i=0; i <50; i++)
{
    memcpy(array_a,array_b,TOTAL_CACHE_SIZE);
    total_time_read += memory_read(array,array+NO_OF_INTEGERS_ARRAY);
}
printf("Total Read Time=%d \n",total_time_read);
printf("Average Read Time=%d \n",total_time_read/50);
float rd_bw=0;
float rd_total_time = 0.33*(total_time_read/50);
rd_bw = NO_OF_INTEGERS_ARRAY*4/rd_total_time;
printf("Read Bw=%f",rd_bw);
for(int i=0; i <50; i++)
{
    memcpy(array_a,array_b,TOTAL_CACHE_SIZE);
    total_time_write += memory_write(array,array+NO_OF_INTEGERS_ARRAY);
}
printf("Total Write Time=%d \n",total_time_write);
printf("Average Write Time=%d \n",total_time_write/50);
float wr_bw=0;
float wr_total_time = 0.33*(total_time_write/50);
wr_bw = NO_OF_INTEGERS_ARRAY*4/wr_total_time;
printf("Write Bw=%f",wr_bw);
return 0;
}
