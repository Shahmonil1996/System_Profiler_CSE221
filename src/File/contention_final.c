#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

const long BLOCKSIZE = 4*1024;
unsigned long int FILESIZE;

#define KB 1024ULL
#define MB (1024ULL*1024ULL)
#define GB (1024ULL*1024ULL*1024ULL)
#define BLOCK_SIZE (4*KB)
#define concatenate(hi, lo) (((unsigned long int) hi << 32) | lo)

void startfilecontention(char * file, int pid){
  void *buf = malloc(BLOCK_SIZE);
  int fd = open(file, O_RDONLY);
  system("echo 3 > /proc/sys/vm/drop_caches");

  long num = FILESIZE / BLOCKSIZE;
  long *access_list = (long*)malloc(num * sizeof(long));
  int i;
  for (i = 0; i < num; i++) 
  {
     access_list[i] = rand() % num;
  }

  unsigned int cycles_high0, cycles_low0, cycles_high1, cycles_low1;
  unsigned long int timer_diff =0;

  for (i = 0; i < num; i++) {
    asm volatile ("cpuid\n\t"   \
          "rdtsc\n\t"           \
          "mov %%edx, %0\n\t"   \
          "mov %%eax, %1\n\t"   \
          : "=r" (cycles_high0), "=r" (cycles_low0)  \
          :: "%rax", "%rbx", "%rcx", "%rdx");

    lseek(fd, access_list[i] * BLOCK_SIZE, SEEK_SET); // offset
    read(fd, buf, BLOCK_SIZE);
    
    asm volatile ("rdtscp\n\t"   \
        "mov %%edx, %0\n\t"    \
        "mov %%eax, %1\n\t"    \
        "cpuid\n\t"            \
        : "=r" (cycles_high1), "=r" (cycles_low1)  \
        :: "%rax", "%rbx", "%rcx", "%rdx");

    timer_diff += concatenate(cycles_high1, cycles_low1) - concatenate(cycles_high0, cycles_low0);
  }

  close(fd);
  printf("%d pid , %lu Bytes, %f sec, %f B/s, %f KB/s\n",pid, BLOCKSIZE, (timer_diff/3e9), (BLOCKSIZE)/(timer_diff/3e9), (((BLOCKSIZE)/(timer_diff/3e9))/(KB)) );
}

int main(int argc, char const *argv[])
{
  int file_fd = open(argv[2], O_RDONLY);
  FILESIZE = lseek(file_fd, 0L, SEEK_END);
  srand((unsigned int)time(NULL));

  pid_t child_processes[100];
  int i;
  int n = atoi(argv[1]);

  for (i = 0; i < n; ++i) {
    if ((child_processes[i] = fork()) < 0) {
      printf("Child process creation error for number:%d\n",i);
      exit(0);
    } else if (child_processes[i] == 0) {
      startfilecontention(argv[2],child_processes[i]);
      exit(0);
    }
  }
  //int count = 0;
  while(wait(NULL) > 0);
  return 0;
}