#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <math.h>
//#include <s.h>
#include <unistd.h>
#include <string.h> 
#include <stdlib.h>
#include <sys/types.h>
int main(int argc, char ** argv) {
  long sum = 0,count=0;
  long long int cycle_high_start , cycle_low_start , cycle_high_end , cycle_low_end;
  int fd = open(argv[1], O_RDONLY);
  struct stat stats;
  fstat(fd, &stats);
  posix_fadvise(fd, 0, stats.st_size, POSIX_FADV_DONTNEED);
  char * map = (char *) mmap(NULL, stats.st_size, PROT_READ, MAP_SHARED, fd, 0);
  if (map == MAP_FAILED) {
    perror("Failed to mmap");
    return 1;
  }
  int result = 0;
  int i;
  //int count = 0;
  printf("size is %lu\n",stats.st_size);
  char command[128];
    char command_result[138];
    int current_process_id;
    current_process_id = getpid();
    snprintf(command,sizeof(command), "ps -o min_flt,maj_flt %d",current_process_id);
    system(command);
  for (i = 0; i < stats.st_size; i+= 32768) {
    asm("cpuid");
    asm volatile("rdtsc" : "=cycle_high" (cycle_high_start), "=cycle_low" (cycle_low_start)); 
    result += map[i];
    asm volatile("rdtsc" : "=cycle_high" (cycle_high_end), "=cycle_low" (cycle_low_end));
    asm("cpuid");
    count++;
    printf("Final Value is %lld %lld and count=%lu\n", cycle_high_end - cycle_high_start, cycle_low_end-cycle_low_start,count);
  }
  munmap(map, stats.st_size);
    snprintf(command,sizeof(command), "ps -o min_flt,maj_flt %d",current_process_id);
    system(command);
  return result;
}