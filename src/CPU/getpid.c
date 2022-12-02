#include <stdio.h>
#include <intrin.h>
#include <Windows.h>
#pragma intrinsic(__rdtsc)

int main()
{
    HANDLE process = GetCurrentProcess();
    DWORD_PTR processAffinityMask = 1;
    BOOL success = SetProcessAffinityMask(process, processAffinityMask);
    printf("success %d\n",success);
    unsigned __int64 i,x,y,z;
	int cycles_low, cycles_high;
    int cycles_low1, cycles_high1;
    for(int c=0;c<10000;c++)
    {
        asm ("CPUID\n\t"
        "RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
        "%rax", "%rbx", "%rcx", "%rdx");
        GetCurrentProcess();
        asm ("RDTSCP\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
        "%rax", "%rbx", "%rcx", "%rdx");
        printf("Value is %d %d\n", cycles_high1 - cycles_high, cycles_low1-cycles_low);
    }
	
	asm ("CPUID\n\t"
        "RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
        "%rax", "%rbx", "%rcx", "%rdx");
        GetCurrentProcess();
        asm ("RDTSCP\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
        "%rax", "%rbx", "%rcx", "%rdx");
        printf("Final Value is %d %d\n", cycles_high1 - cycles_high, cycles_low1-cycles_low);
    sleep(5);
}