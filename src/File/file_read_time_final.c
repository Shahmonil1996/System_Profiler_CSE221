//Perform random and sequential file block read experiment

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

const off_t BLOCKSIZE = 4*1024;
unsigned long int FILESIZE;

static inline unsigned long int rdtsc(void) {
    unsigned int lo, hi;
    __asm__ __volatile__("xor %%eax, %%eax;" "cpuid;" "rdtsc;": "=a" (lo), "=d" (hi));
    return (((unsigned long int)hi << 32) | lo);
}

double avg_seq_time(char *file, void* buf);

double avg_random_time(char *file, void* buf);

int main(int argc, const char *argv[]) //input the filesize and name of file
{
    
    srand((unsigned int)time(NULL));
    void *buf = malloc(BLOCKSIZE);
    int file_fd = open(argv[1], O_RDONLY);
    FILESIZE = lseek(file_fd, 0L, SEEK_END);
    double seq_ans = avg_seq_time(argv[1], buf);
    double ran_ans = avg_random_time(argv[1], buf);
    free(buf);
    printf("%.2lf %.2lf\n", seq_ans, ran_ans); // output 21 bits after point
    return 0;
}

double avg_seq_time(char * file, void* buf)
{
    int fd = open(file, O_SYNC);
    // if(fcntl(fd, F_NOCACHE, 1) == -1) {
    //     printf("Failed.\n"); //cannot disable cache
    // }
    system("echo 3 > /proc/sys/vm/drop_caches");
    unsigned long int st;
    unsigned long int ed;
    unsigned long int total_time;
    int count = 0;

    while (1) {
        st = rdtsc();
        ssize_t bytes = read(fd, buf, BLOCKSIZE); // return #byte when read successfully
        if (bytes <= 0) {
            break;
        }
        ed = rdtsc();
        total_time += ed - st;
    }
    close(fd);
    double num = FILESIZE / BLOCKSIZE;
    printf("[SEQ] total_time : %lu, num: %f\n", total_time, num);
    return total_time / num / 2.6 / 1000;
}

double avg_random_time(char * file, void* buf)
{
    int i = 0;
    int fd = open(file, O_SYNC); //open synchronously
    system("echo 3 > /proc/sys/vm/drop_caches");
    // if(fcntl(fd, F_NOCACHE, 1) == -1) //disable cache
    // {
    //     printf("Failed.\n"); //cannot disable cache
    // }
    off_t num = FILESIZE / BLOCKSIZE;
    printf("[RAND] num: %lu\n", num);
    unsigned long int st;
    unsigned long int ed;
    unsigned long int total_time = 0;
    int count = 0;

    for (i = 0; i < num; i++) {
        off_t k = rand() % num;
        st = rdtsc();
        lseek(fd, k * BLOCKSIZE, SEEK_SET); // offset
        read(fd, buf, BLOCKSIZE);
        ed = rdtsc();
        total_time += ed - st;
    }
    close(fd);
    printf("[RAND] total_time : %lu, num: %lu\n", total_time, num);
    return total_time / (double)num / 2.6 / 1000;
}