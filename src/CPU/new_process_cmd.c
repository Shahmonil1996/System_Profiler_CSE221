 // For WinXp as a target, change accordingly

#define _WIN32_WINNT 0x0501
#include <Windows.h>
#include <stdio.h>
#include <intrin.h>
#include "new_process_cmd.h"
//int cycles_high2_child,cycles_low2_child;
int main()

{
	
	int process_id = GetCurrentProcessId();
	int cycles_high2,cycles_low2;
    printf("Current Process Id in child file =%d\n",process_id);
	asm ("RDTSCP\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t"
				"CPUID\n\t": "=r" (cycles_high2), "=r" (cycles_low2)::
				"%rax", "%rbx", "%rcx", "%rdx");
	int cycles_high2_child = cycles_high2;
	int cycles_low2_child = cycles_low2;
	printf("Value of RTDSC %u %u for process in child file =%d\n", cycles_high2_child, cycles_low2_child,process_id);
   return 0;
}