        // asm ("mov %1, %0\n\t"
        // "add $1, %0"
        // : "=r" (dst)
        // : "r" (src));

#include <stdio.h>
#include <Windows.h> 
int main()
{
        int cycles_low, cycles_high;
        int cycles_low1, cycles_high1;
        HANDLE process = GetCurrentProcess();
        DWORD_PTR processAffinityMask = 1;

        BOOL success = SetProcessAffinityMask(process, processAffinityMask);

        printf("success %d\n",success);
		for(int d=0;d<10000;d++)
		{
			int sum = 0;
			asm ("CPUID\n\t"
			"RDTSC\n\t"
			"mov %%edx, %0\n\t"
			"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
			"%rax", "%rbx", "%rcx", "%rdx");
			for(int c=0;c<10000;c++)
			{
				sum++;
			}
			asm ("RDTSCP\n\t"
			"mov %%edx, %0\n\t"
			"mov %%eax, %1\n\t"
			"CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
			"%rax", "%rbx", "%rcx", "%rdx");
			printf("Final Value is %d %d\n", cycles_high1 - cycles_high, cycles_low1-cycles_low);
		}
        sleep(10);
        
}