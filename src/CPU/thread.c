#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
#include <Windows.h>
#include <intrin.h> 
// A normal C function that is executed as a thread
// when its name is specified in pthread_create()
void myThreadFun()
{
    //printf("Printing ebfhefb from Thread \n");
}
  
int main()
{
    pthread_t thread_id;
    printf("Before Thread\n");
	int cycles_low, cycles_high;
    int cycles_low1, cycles_high1;
    HANDLE process = GetCurrentProcess();
    DWORD_PTR processAffinityMask = 1;
    BOOL success = SetProcessAffinityMask(process, processAffinityMask);
	// Start the child process.
	for(int d=0;d<1000;d++)
	{
		asm ("CPUID\n\t"
				"RDTSC\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
				"%rax", "%rbx", "%rcx", "%rdx");
		pthread_create(&thread_id, NULL, myThreadFun, NULL);
		asm ("RDTSCP\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t"
				"CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
				"%rax", "%rbx", "%rcx", "%rdx");
		printf("Final Value is %d %d \n", cycles_high1 - cycles_high, cycles_low1-cycles_low);		
		pthread_join(thread_id, NULL);
    }
    return 0;
}