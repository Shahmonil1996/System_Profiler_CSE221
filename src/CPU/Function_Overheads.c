#include <stdio.h>
#include <intrin.h>
#include <Windows.h>
#pragma intrinsic(__rdtsc)

unsigned __int64 k;

void add(){
    //int c = 4+5;
	//printf_s("%I64d in add function %I64d\n", c,k);
	//c += k%2;
	//return c;
}
void add_d1(int a){
    //int c = 4+a;
	//printf_s("%I64d in add_d function %I64d\n", c,k);
	//c += k%2;
	//return c;
}
void add_d2(int a,int b){
    //int c = a+b;
	//c += k%2;
	//printf_s("%I64d in add_d_d function %I64d\n", c,k);
	//return c;
}
void add_d3(int a,int b,int d){
    //int c = a+b;
	//c += k%2;
	//printf_s("%I64d in add_d_d function %I64d\n", c,k);
	//return c;
}
void add_d4(int a,int b,int d, int e){
    //int c = a+b;
	//c += k%2;
	//printf_s("%I64d in add_d_d function %I64d\n", c,k);
	//return c;
}
void add_d5(int a,int b,int d,int e, int f){
    //int c = 4+a;
	//printf_s("%I64d in add_d function %I64d\n", c,k);
	//c += k%2;
	//return c;
}
void add_d6(int a,int b,int d,int e,int f, int g){
    //int c = a+b;
	//c += k%2;
	//printf_s("%I64d in add_d_d function %I64d\n", c,k);
	//return c;
}
void add_d7(int a,int b,int d,int e,int f,int g, int h){
    //int c = a+b;
	//c += k%2;
	//printf_s("%I64d in add_d_d function %I64d\n", c,k);
	//return c;
}

int main()
{
    HANDLE process = GetCurrentProcess();
    DWORD_PTR processAffinityMask = 1;
    BOOL success = SetProcessAffinityMask(process, processAffinityMask);
    printf("success %d\n",success);
    unsigned __int64 i,x,j,y,z;
	int cycles_low, cycles_high;
    int cycles_low1, cycles_high1;
    
    for(z=0 ; z <100 ; z++)
    {
		asm ("CPUID\n\t"
        "RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
        "%rax", "%rbx", "%rcx", "%rdx");
		x = 4+5;
		asm ("RDTSCP\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
        "%rax", "%rbx", "%rcx", "%rdx");
		printf("Value is %d %d (no function)\n", cycles_high1 - cycles_high, cycles_low1-cycles_low);
		
		asm ("CPUID\n\t"
        "RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
        "%rax", "%rbx", "%rcx", "%rdx");
		add();
		asm ("RDTSCP\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
        "%rax", "%rbx", "%rcx", "%rdx");
		printf("Value is %d %d (0 arg)\n", cycles_high1 - cycles_high, cycles_low1-cycles_low);

		asm ("CPUID\n\t"
        "RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
        "%rax", "%rbx", "%rcx", "%rdx");
		add_d1(5);
		asm ("RDTSCP\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
        "%rax", "%rbx", "%rcx", "%rdx");
		printf("Value is %d %d (1 arg)\n", cycles_high1 - cycles_high, cycles_low1-cycles_low);
		 
		asm ("CPUID\n\t"
        "RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
        "%rax", "%rbx", "%rcx", "%rdx");
		add_d2(4,5);
		asm ("RDTSCP\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
        "%rax", "%rbx", "%rcx", "%rdx");
		printf("Value is %d %d (2 arg)\n", cycles_high1 - cycles_high, cycles_low1-cycles_low);
		
		asm ("CPUID\n\t"
        "RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
        "%rax", "%rbx", "%rcx", "%rdx");
		add_d3(4,5,6);
		asm ("RDTSCP\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
        "%rax", "%rbx", "%rcx", "%rdx");
		printf("Value is %d %d (3 arg)\n", cycles_high1 - cycles_high, cycles_low1-cycles_low);
		
		asm ("CPUID\n\t"
        "RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
        "%rax", "%rbx", "%rcx", "%rdx");
		add_d4(4,5,6,7);
		asm ("RDTSCP\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
        "%rax", "%rbx", "%rcx", "%rdx");
		printf("Value is %d %d (4 arg)\n", cycles_high1 - cycles_high, cycles_low1-cycles_low);
		
		asm ("CPUID\n\t"
        "RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
        "%rax", "%rbx", "%rcx", "%rdx");
		add_d5(4,5,6,7,8);
		asm ("RDTSCP\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
        "%rax", "%rbx", "%rcx", "%rdx");
		printf("Value is %d %d (5 arg)\n", cycles_high1 - cycles_high, cycles_low1-cycles_low);
		
		asm ("CPUID\n\t"
        "RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
        "%rax", "%rbx", "%rcx", "%rdx");
		add_d6(4,5,6,7,8,9);
		asm ("RDTSCP\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
        "%rax", "%rbx", "%rcx", "%rdx");
		printf("Value is %d %d (6 arg)\n", cycles_high1 - cycles_high, cycles_low1-cycles_low);
		
		asm ("CPUID\n\t"
        "RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
        "%rax", "%rbx", "%rcx", "%rdx");
		add_d7(4,5,6,7,8,9,10);
		asm ("RDTSCP\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
        "%rax", "%rbx", "%rcx", "%rdx");
		printf("Value is %d %d (7 arg)\n", cycles_high1 - cycles_high, cycles_low1-cycles_low);

		x=0;
    }
    Sleep(50);
}