#include <sys/fcntl.h>
#include <stdint.h>
#include <sched.h>
#include <string.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <sched.h>
#include <assert.h>
#include <stdint.h>
#include <sys/resource.h>

#define KB 1024ULL
#define MB (1024ULL*1024ULL)
#define GB (1024ULL*1024ULL*1024ULL)
#define BLOCK_SIZE (4*KB)
#define concatenate(hi, lo) (((unsigned long int) hi << 32) | lo)

unsigned long int read_file ( int file_fd, char* buffer, unsigned long int read_size) {
	unsigned long int bytes_read = 0;
    unsigned long int timer_diff = 0;
	unsigned int cycles_high0, cycles_low0, cycles_high1, cycles_low1;

    asm volatile ("cpuid\n\t"   \
          "rdtsc\n\t"           \
          "mov %%edx, %0\n\t"   \
          "mov %%eax, %1\n\t"   \
          : "=r" (cycles_high0), "=r" (cycles_low0)  \
          :: "%rax", "%rbx", "%rcx", "%rdx");

	while (bytes_read < read_size) {
	    bytes_read += read(file_fd, buffer, BLOCK_SIZE);
	}
	
    asm volatile ("rdtscp\n\t"   \
          "mov %%edx, %0\n\t"    \
          "mov %%eax, %1\n\t"    \
          "cpuid\n\t"            \
          : "=r" (cycles_high1), "=r" (cycles_low1)  \
          :: "%rax", "%rbx", "%rcx", "%rdx");

    timer_diff = concatenate(cycles_high1, cycles_low1) - concatenate(cycles_high0, cycles_low0);
	return timer_diff;
}

int main(int argc, char *argv[]){

	if (argc != 2) {
		printf("Usage: ./file_cache_size filename");
        exit(1);
	}

	char *filename;
	filename = argv[1];
    // open the file for 
	int file_fd = open(filename, O_RDONLY);
    printf("Opened filename: %s for reading with fd: %d\n", filename, file_fd);

    unsigned long int file_size = lseek(file_fd, 0, SEEK_END);
    printf("Size of file is %luB\n", file_size);
    printf("Block size is %lluB\n", BLOCK_SIZE);

    unsigned long int file_sizes_to_read[] = {
	    1*MB,   2*MB,   4*MB,   8*MB,   16*MB,   32*MB,   64*MB,   128*MB,   256*MB,
        512*MB, 1*GB,   2*GB,   3*GB, 4*GB, 5*GB, 5.5*GB, 6*GB, 6.5*GB, 7*GB, 7.5*GB,  
        8*GB, 8.5*GB, 9*GB, 9.5*GB
    };

    unsigned long int cycles_taken = 0;
	char *buffer = (char *) malloc(BLOCK_SIZE);

    printf("%s, %s, %s, %s\n", "File Size(MB)", "Time(s)", "Bandwidth (B/s)", "Bandwidth (GB/s)");

    for (int i=0; i < (sizeof(file_sizes_to_read)/sizeof(unsigned long int)); i++) {
		unsigned long int size_to_read = file_sizes_to_read[i];

		system("sync");    // sync: disk writes
		system("echo 3 > /proc/sys/vm/drop_caches");

		lseek(file_fd, 0, SEEK_SET);
		cycles_taken = read_file(file_fd, buffer, size_to_read);
		lseek(file_fd, 0, SEEK_SET);
		cycles_taken = read_file(file_fd, buffer, size_to_read);

		// file size(B), time (m), bandwidth (MB/s)
		printf("%lu, %f, %f, %f\n", (size_to_read/MB), (cycles_taken/3e9), (size_to_read)/(cycles_taken/3e9), (((size_to_read)/(cycles_taken/3e9))/(1024 *1024 *1024)) );
	}
	free(buffer);
    close(file_fd);
    return 0;
}