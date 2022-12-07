#include <stdio.h> 
#include <math.h>
#include <sched.h>
#include <string.h> 
#include <stdlib.h>
#include <sys/types.h>
//#include <preempt.h>
cpu_set_t  mask;
#define TOTAL_CACHE_SIZE (1<<25)
#define NO_OF_INTEGERS_CACHE (TOTAL_CACHE_SIZE>>2)
#define PAGE_SIZE (1<<12)
int array_a[NO_OF_INTEGERS_CACHE],array_b[NO_OF_INTEGERS_CACHE];
#define TOTAL_MEMORY_SIZE (1<<30)
#define NO_OF_INTEGERS_MEMORY (1<<27)
int array_1[NO_OF_INTEGERS_MEMORY];
int array_2[NO_OF_INTEGERS_MEMORY];
int array_3[NO_OF_INTEGERS_MEMORY];
/*
int array_4[NO_OF_INTEGERS_MEMORY];
int array_5[NO_OF_INTEGERS_MEMORY];
int array_6[NO_OF_INTEGERS_MEMORY];
int array_7[NO_OF_INTEGERS_MEMORY];
int array_8[NO_OF_INTEGERS_MEMORY];
int array_9[NO_OF_INTEGERS_MEMORY];
int array_10[NO_OF_INTEGERS_MEMORY];
*/
int memory_read_array_1(int* start , int* end)
{
    long sum = 0,count=0;
    long long int cycle_high_start , cycle_low_start , cycle_high_end , cycle_low_end;
    int *ptr = start;
    int *ptr_end = end;
    int i = rand();
    while(ptr < ptr_end)
    {
        asm("cpuid");
        asm volatile("rdtsc" : "=cycle_high" (cycle_high_start), "=cycle_low" (cycle_low_start)); 
        
        //ptr[i] = (char)rand(); 
        //i = i + PAGE_SIZE;

        sum += ptr[2];    
        ptr = ptr + PAGE_SIZE;

        asm("cpuid");
        asm volatile("rdtsc" : "=cycle_high" (cycle_high_end), "=cycle_low" (cycle_low_end));
        count++;
        if(cycle_low_end-cycle_low_start>20000)
        {
            printf("Final Value is %lld %lld for page_fault = %x and count=%lu\n", cycle_high_end - cycle_high_start, cycle_low_end-cycle_low_start,ptr,count);
        }
    }
    if(cycle_low_end-cycle_low_start>20000)
        {
            printf("Final Value is %lld %lld for page_fault = %x and count=%lu\n", cycle_high_end - cycle_high_start, cycle_low_end-cycle_low_start,ptr,count);
        }
    return (cycle_low_end-cycle_low_start);
}
int memory_read_array_2(int* start , int* end)
{
    long sum = 0,count=0;
    long long int cycle_high_start , cycle_low_start , cycle_high_end , cycle_low_end;
    int *ptr = start;
    int *ptr_end = end;
   
    while(ptr < ptr_end)
    {
        asm("cpuid");
        asm volatile("rdtsc" : "=cycle_high" (cycle_high_start), "=cycle_low" (cycle_low_start)); 
    
        sum += ptr[2];    
        ptr = ptr + PAGE_SIZE;

        asm("cpuid");
        asm volatile("rdtsc" : "=cycle_high" (cycle_high_end), "=cycle_low" (cycle_low_end));
        count++;
        if(cycle_low_end-cycle_low_start>20000)
        {
            printf("Final Value is %lld %lld for page_fault = %x and count=%d\n", cycle_high_end - cycle_high_start, cycle_low_end-cycle_low_start,ptr,count);
        }
    }
    return (cycle_low_end-cycle_low_start);
}

int memory_read_array_3(int* start , int* end)
{
    long sum = 0,count=0;
    long long int cycle_high_start , cycle_low_start , cycle_high_end , cycle_low_end;
    int *ptr = start;
    int *ptr_end = end;
   
    while(ptr < ptr_end)
    {
        asm("cpuid");
        asm volatile("rdtsc" : "=cycle_high" (cycle_high_start), "=cycle_low" (cycle_low_start)); 
    
        sum += ptr[2];    
        ptr = ptr + PAGE_SIZE;

        asm("cpuid");
        asm volatile("rdtsc" : "=cycle_high" (cycle_high_end), "=cycle_low" (cycle_low_end));
        count++;
        if(cycle_low_end-cycle_low_start>20000)
        {
            printf("Final Value is %lld %lld for page_fault = %x and count=%d\n", cycle_high_end - cycle_high_start, cycle_low_end-cycle_low_start,ptr,count);
        }
    }
    return (cycle_low_end-cycle_low_start);
}

int memory_read_array_4(int* start , int* end)
{
    long sum = 0,count=0;
    long long int cycle_high_start , cycle_low_start , cycle_high_end , cycle_low_end;
    int *ptr = start;
    int *ptr_end = end;
   
    while(ptr < ptr_end)
    {
        asm("cpuid");
        asm volatile("rdtsc" : "=cycle_high" (cycle_high_start), "=cycle_low" (cycle_low_start)); 
    
        sum += ptr[2];    
        ptr = ptr + PAGE_SIZE;

        asm("cpuid");
        asm volatile("rdtsc" : "=cycle_high" (cycle_high_end), "=cycle_low" (cycle_low_end));
        count++;
        if(cycle_low_end-cycle_low_start>20000)
        {
            printf("Final Value is %lld %lld for page_fault = %x and count=%d\n", cycle_high_end - cycle_high_start, cycle_low_end-cycle_low_start,ptr,count);
        }
    }
    return (cycle_low_end-cycle_low_start);
}

int memory_read_array_5(int* start , int* end)
{
    long sum = 0,count=0;
    long long int cycle_high_start , cycle_low_start , cycle_high_end , cycle_low_end;
    int *ptr = start;
    int *ptr_end = end;
   
    while(ptr < ptr_end)
    {
        asm("cpuid");
        asm volatile("rdtsc" : "=cycle_high" (cycle_high_start), "=cycle_low" (cycle_low_start)); 
    
        sum += ptr[2];    
        ptr = ptr + PAGE_SIZE;

        asm("cpuid");
        asm volatile("rdtsc" : "=cycle_high" (cycle_high_end), "=cycle_low" (cycle_low_end));
        count++;
        if(cycle_low_end-cycle_low_start>20000)
        {
            printf("Final Value is %lld %lld for page_fault = %x and count=%d\n", cycle_high_end - cycle_high_start, cycle_low_end-cycle_low_start,ptr,count);
        }
    }
    return (cycle_low_end-cycle_low_start);
}

int memory_read_array_6(int* start , int* end)
{
    long sum = 0,count=0;
    long long int cycle_high_start , cycle_low_start , cycle_high_end , cycle_low_end;
    int *ptr = start;
    int *ptr_end = end;
   
    while(ptr < ptr_end)
    {
        asm("cpuid");
        asm volatile("rdtsc" : "=cycle_high" (cycle_high_start), "=cycle_low" (cycle_low_start)); 
    
        sum += ptr[2];    
        ptr = ptr + PAGE_SIZE;

        asm("cpuid");
        asm volatile("rdtsc" : "=cycle_high" (cycle_high_end), "=cycle_low" (cycle_low_end));
        count++;
        if(cycle_low_end-cycle_low_start>20000)
        {
            printf("Final Value is %lld %lld for page_fault = %x and count=%d\n", cycle_high_end - cycle_high_start, cycle_low_end-cycle_low_start,ptr,count);
        }
    }
    return (cycle_low_end-cycle_low_start);
}

int memory_read_array_7(int* start , int* end)
{
    long sum = 0,count=0;
    long long int cycle_high_start , cycle_low_start , cycle_high_end , cycle_low_end;
    int *ptr = start;
    int *ptr_end = end;
   
    while(ptr < ptr_end)
    {
        asm("cpuid");
        asm volatile("rdtsc" : "=cycle_high" (cycle_high_start), "=cycle_low" (cycle_low_start)); 
    
        sum += ptr[2];    
        ptr = ptr + PAGE_SIZE;

        asm("cpuid");
        asm volatile("rdtsc" : "=cycle_high" (cycle_high_end), "=cycle_low" (cycle_low_end));
        count++;
        if(cycle_low_end-cycle_low_start>20000)
        {
            printf("Final Value is %lld %lld for page_fault = %x and count=%d\n", cycle_high_end - cycle_high_start, cycle_low_end-cycle_low_start,ptr,count);
        }
    }
    return (cycle_low_end-cycle_low_start);
}

int memory_read_array_8(int* start , int* end)
{
    long sum = 0,count=0;
    long long int cycle_high_start , cycle_low_start , cycle_high_end , cycle_low_end;
    int *ptr = start;
    int *ptr_end = end;
   
    while(ptr < ptr_end)
    {
        asm("cpuid");
        asm volatile("rdtsc" : "=cycle_high" (cycle_high_start), "=cycle_low" (cycle_low_start)); 
    
        sum += ptr[2];    
        ptr = ptr + PAGE_SIZE;

        asm("cpuid");
        asm volatile("rdtsc" : "=cycle_high" (cycle_high_end), "=cycle_low" (cycle_low_end));
        count++;
        if(cycle_low_end-cycle_low_start>20000)
        {
            printf("Final Value is %lld %lld for page_fault = %x and count=%d\n", cycle_high_end - cycle_high_start, cycle_low_end-cycle_low_start,ptr,count);
        }
    }
    return (cycle_low_end-cycle_low_start);
}

int memory_read_array_9(int* start , int* end)
{
    long sum = 0,count=0;
    long long int cycle_high_start , cycle_low_start , cycle_high_end , cycle_low_end;
    int *ptr = start;
    int *ptr_end = end;
   
    while(ptr < ptr_end)
    {
        asm("cpuid");
        asm volatile("rdtsc" : "=cycle_high" (cycle_high_start), "=cycle_low" (cycle_low_start)); 
    
        sum += ptr[2];    
        ptr = ptr + PAGE_SIZE;

        asm("cpuid");
        asm volatile("rdtsc" : "=cycle_high" (cycle_high_end), "=cycle_low" (cycle_low_end));
        count++;
        if(cycle_low_end-cycle_low_start>20000)
        {
            printf("Final Value is %lld %lld for page_fault = %x and count=%d\n", cycle_high_end - cycle_high_start, cycle_low_end-cycle_low_start,ptr,count);
        }
    }
    return (cycle_low_end-cycle_low_start);
}

int memory_read_array_10(int* start , int* end)
{
    long sum = 0,count=0;
    long long int cycle_high_start , cycle_low_start , cycle_high_end , cycle_low_end;
    int *ptr = start;
    int *ptr_end = end;
   
    while(ptr < ptr_end)
    {
        asm("cpuid");
        asm volatile("rdtsc" : "=cycle_high" (cycle_high_start), "=cycle_low" (cycle_low_start)); 
    
        sum += ptr[2];    
        ptr = ptr + PAGE_SIZE;

        asm("cpuid");
        asm volatile("rdtsc" : "=cycle_high" (cycle_high_end), "=cycle_low" (cycle_low_end));
        count++;
        if(cycle_low_end-cycle_low_start>20000)
        {
            printf("Final Value is %lld %lld for page_fault = %x and count=%d\n", cycle_high_end - cycle_high_start, cycle_low_end-cycle_low_start,ptr,count);
        }
    }
    return (cycle_low_end-cycle_low_start);
}


// void assignToThisCore(int core_id)
// {
//     CPU_ZERO(&mask);
//     CPU_SET(core_id, &mask);
//     sched_setaffinity(0, sizeof(mask), &mask);
// }
int main()
{
//assignToThisCore(0);
printf("Current Process Id=%d",getpid());
int total_time_read=0;
memcpy(array_a,array_b,TOTAL_CACHE_SIZE);

total_time_read += memory_read_array_1(array_1,array_1+NO_OF_INTEGERS_MEMORY);

memcpy(array_a,array_b,TOTAL_CACHE_SIZE);
total_time_read += memory_read_array_2(array_2,array_2+NO_OF_INTEGERS_MEMORY);

memcpy(array_a,array_b,TOTAL_CACHE_SIZE);
total_time_read += memory_read_array_3(array_3,array_3+NO_OF_INTEGERS_MEMORY);
/*
total_time_read += memory_read_array_4(array_4,array_4+NO_OF_INTEGERS_MEMORY);
total_time_read += memory_read_array_5(array_5,array_5+NO_OF_INTEGERS_MEMORY);
total_time_read += memory_read_array_6(array_6,array_6+NO_OF_INTEGERS_MEMORY);
total_time_read += memory_read_array_7(array_7,array_7+NO_OF_INTEGERS_MEMORY);
total_time_read += memory_read_array_8(array_8,array_8+NO_OF_INTEGERS_MEMORY);
total_time_read += memory_read_array_9(array_9,array_9+NO_OF_INTEGERS_MEMORY);
total_time_read += memory_read_array_10(array_10,array_10+NO_OF_INTEGERS_MEMORY);
*/
printf("Total Read Time=%d",total_time_read);
printf("Average Read Time=%d",total_time_read/50);
char command[128];
char command_result[138];
int current_process_id;
current_process_id = getpid();
snprintf(command,sizeof(command), "ps -o min_flt,maj_flt %d",current_process_id);
system(command);
//strcpy(command_result,system(command));
//printf("Command Result is %s",command_result);
return 0;
}
