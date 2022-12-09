 // For WinXp as a target, change accordingly

#define _WIN32_WINNT 0x0501
#include <Windows.h>
#include <stdio.h>
#include <intrin.h>
#include <pthread.h>
int cycles_high2_child,cycles_low2_child;
int child_process()
	{
	int process_id = GetCurrentProcessId();
	int cycles_high2,cycles_low2;
    printf("Current Process Id in child file =%d\n",process_id);
	asm ("RDTSCP\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t"
				"CPUID\n\t": "=r" (cycles_high2), "=r" (cycles_low2)::
				"%rax", "%rbx", "%rcx", "%rdx");
	cycles_high2_child = cycles_high2;
	cycles_low2_child = cycles_low2;
	//printf("Value of RTDSC %u %u for process in child file =%d\n", cycles_high2_child, cycles_low2_child,process_id);
   return 0;
   }
int main()

{
	pthread_t thread_id;
	
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	int cycles_low, cycles_high;
    int cycles_low1, cycles_high1;
	int cycles_low2, cycles_high2;
    HANDLE process = GetCurrentProcess();
    DWORD_PTR processAffinityMask = 1;
	int c=0;
	int process_id = 0;
    BOOL success = SetProcessAffinityMask(process, processAffinityMask);
	process_id = GetCurrentProcessId();
	printf("Current Process Id in parent file =%d\n",process_id);
	// Start the child process.
	for(int d=0;d<100;d++)
	{
		asm ("CPUID\n\t"
				"RDTSC\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
				"%rax", "%rbx", "%rcx", "%rdx");
		
		
		pthread_create(&thread_id, NULL, child_process, NULL);
		asm ("RDTSCP\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t"
				"CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
				"%rax", "%rbx", "%rcx", "%rdx");
		
		// Wait until child process exits (in milliseconds). If INFINITE, the functions time-out interval never elapses except with user or other intervention.
		
		pthread_join(thread_id, NULL);
		asm ("RDTSCP\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t"
				"CPUID\n\t": "=r" (cycles_high2), "=r" (cycles_low2)::
				"%rax", "%rbx", "%rcx", "%rdx");
		//printf("Final Value After CTXSW is %u %u for child process\n", cycles_high2_child, cycles_low2_child);		
		printf("Final Value After CTXSW is %u %u for process is =%d\n", cycles_high2-cycles_high2_child, cycles_low2-cycles_low2_child,process_id);		
		
		/*asm ("RDTSCP\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t"
				"CPUID\n\t": "=r" (cycles_high2), "=r" (cycles_low2)::
				"%rax", "%rbx", "%rcx", "%rdx");
		*/
		//printf("Final Value After CTXSW is %u %u for process is =%d\n", cycles_high2, cycles_low2,process_id);				
		//printf("Final Value Before CTXSW is %d %d %d\n", cycles_high2 - cycles_high1, cycles_low2-cycles_low1,c);
	}
	//sleep(2);
return 0;
}