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


double sequential_reads(char * file, void* buf)
{
    int fd = open(file, O_SYNC);
    system("echo 3 > /proc/sys/vm/drop_caches");

	unsigned int cycles_high0, cycles_low0, cycles_high1, cycles_low1;
  unsigned long int timer_diff =0;

  while (1) {
      asm volatile ("cpuid\n\t"   \
        "rdtsc\n\t"           \
        "mov %%edx, %0\n\t"   \
        "mov %%eax, %1\n\t"   \
        : "=r" (cycles_high0), "=r" (cycles_low0)  \
        :: "%rax", "%rbx", "%rcx", "%rdx");

      ssize_t bytes = read(fd, buf, BLOCKSIZE); // return #byte when read successfully
      if (bytes <= 0) {
          break;
      }

      asm volatile ("rdtscp\n\t"   \
        "mov %%edx, %0\n\t"    \
        "mov %%eax, %1\n\t"    \
        "cpuid\n\t"            \
        : "=r" (cycles_high1), "=r" (cycles_low1)  \
        :: "%rax", "%rbx", "%rcx", "%rdx");

      timer_diff += concatenate(cycles_high1, cycles_low1) - concatenate(cycles_high0, cycles_low0);
  }
  close(fd);

  long num = FILESIZE / BLOCKSIZE;
  //printf("[SEQ] num:%lu \n",num);
  //printf("[SEQ] total_time : %lu, num: %lu, final time: %f\n", timer_diff, num, (timer_diff/num/3e9));
  return (timer_diff / num / 3e9);
}

double random_reads(char * file, void* buf)
{
    int i = 0;
    int fd = open(file, O_SYNC);
    system("echo 3 > /proc/sys/vm/drop_caches");

	unsigned int cycles_high0, cycles_low0, cycles_high1, cycles_low1;
    unsigned long int timer_diff =0;

    long num = FILESIZE / BLOCKSIZE;
    //printf("[RAND] num:%lu\n",num);
    for (i = 0; i < num; i++) {
        long k = rand() % num;
        
        asm volatile ("cpuid\n\t"   \
          "rdtsc\n\t"           \
          "mov %%edx, %0\n\t"   \
          "mov %%eax, %1\n\t"   \
          : "=r" (cycles_high0), "=r" (cycles_low0)  \
          :: "%rax", "%rbx", "%rcx", "%rdx");

        lseek(fd, k * BLOCKSIZE, SEEK_SET); // offset
        read(fd, buf, BLOCKSIZE);

        asm volatile ("rdtscp\n\t"   \
          "mov %%edx, %0\n\t"    \
          "mov %%eax, %1\n\t"    \
          "cpuid\n\t"            \
          : "=r" (cycles_high1), "=r" (cycles_low1)  \
          :: "%rax", "%rbx", "%rcx", "%rdx");

        timer_diff += concatenate(cycles_high1, cycles_low1) - concatenate(cycles_high0, cycles_low0);
    }
    close(fd);
    //printf("[RAND] total_time : %lu, num: %lu, final time: %f\n", timer_diff, num, (timer_diff/num/3e9));
    return (timer_diff / num / 3e9);
}

int main(int argc, const char *argv[]) //input the filesize and name of file
{
    printf("Usage : sudo sshfs -o allow_other,IdentityFile=/home/monils/.ssh/id_rsa.pub  <username>@ieng6-ece-20.ucsd.edu:<remote_dir_path> /mnt/remote_dir\n");
    srand((unsigned int)time(NULL));
    void *buf = malloc(BLOCKSIZE);
    printf("File(KB) Seq(s) Rand(s) BW_Seq(KB/s) BW_Rand(KB/s)\n");
    int remote = atoi(argv[1]);
    if(remote){
      char * files[8] = {"/mnt/remote_dir/log8kb","/mnt/remote_dir/log16kb","/mnt/remote_dir/log32kb","/mnt/remote_dir/log64kb","/mnt/remote_dir/log128kb","/mnt/remote_dir/log256kb","/mnt/remote_dir/log512kb","/mnt/remote_dir/log1mb"};
      printf("Remote Version\n");
      for(int i = 0; i < 8; i++){  
        int file_fd = open(files[i], __O_DIRECT|O_SYNC);
        FILESIZE = lseek(file_fd, 0L, SEEK_END);
        double seq_read_time = sequential_reads(files[i], buf);
        double rand_read_time = random_reads(files[i], buf);
        
        //printf("Sequential : %f (s) Random : %f (s) \n", seq_read_time, rand_read_time);
        printf("%lu , %f, %f, %f, %f\n", (FILESIZE/KB),  seq_read_time, rand_read_time, (BLOCK_SIZE/seq_read_time/KB), (BLOCK_SIZE/rand_read_time/KB));
      }
    }
    else{
      char * files[8] = {"log1mb","log2mb","log4mb","log8mb","log16mb","log32mb","log64mb","log128mb"};
      printf("Local Version\n");
      for(int i = 0; i < 8; i++){  
        int file_fd = open(files[i], __O_DIRECT|O_SYNC);
        FILESIZE = lseek(file_fd, 0L, SEEK_END);
        double seq_read_time = sequential_reads(files[i], buf);
        double rand_read_time = random_reads(files[i], buf);
        
        //printf("Sequential : %f (s) Random : %f (s) \n", seq_read_time, rand_read_time);
        printf("%lu , %f, %f, %f, %f\n", (FILESIZE/MB),  seq_read_time, rand_read_time, (BLOCK_SIZE/seq_read_time/MB), (BLOCK_SIZE/rand_read_time/MB));
      }
    }
    
    free(buf);
    return 0;
}


