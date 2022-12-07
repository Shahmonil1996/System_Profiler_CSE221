#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#include <time.h>
#include <sys/types.h>
#include <sched.h>
#include <netinet/tcp.h>

#define MAX 4000000
#define PORT 80
#define SA struct sockaddr

long int tick_start_server , tick_end_server , average_total_tick_start_client ,total_time_tick_start_client=0,total_time_taken=0;

cpu_set_t  mask;
uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}


int main()
{
	//assignToThisCore(1);
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	int iter = 1000;
    int i=0;
    while(i < iter)
    {
        sockfd = socket(AF_INET,SOCK_STREAM,0);//socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
            printf("socket creation failed...\n");
            exit(0);
        }
        else
            printf("Socket successfully created..\n");
        bzero(&servaddr, sizeof(servaddr));

        // assign IP, PORT
        servaddr.sin_family = AF_INET ;//AF_INET;
        servaddr.sin_addr.s_addr = inet_addr("142.250.80.100");  //inet_addr("127.0.0.1") -loopback and inet_addr("142.250.80.100") for remote (https://urldefense.com/v3/__http://www.google.com__;!!Mih3wA!CsXTlR31pQ6zZoygAhLfVddtSqDAp6hoPyKfcHyAyl4bufFRymyh7X1Sk48zIuX1ouFZdB0SN8x51w$ ) 
        servaddr.sin_port = htons(PORT);
        long long int cycle_high_start , cycle_low_start , cycle_high_end , cycle_low_end;

        // connect the client socket to server socket
        //asm("cpuid");
        //asm volatile("rdtsc" : "=cycle_high" (cycle_high_start), "=cycle_low" (cycle_low_start)); 
        
        //int return_flag = connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
        ///printf("Return Flag =%d \n",return_flag);
        uint64_t tick_start_connect,tick_end_connect;
        tick_start_connect = rdtsc();
        int result = connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
        tick_end_connect = rdtsc();
        if (result!= 0) {
            printf("connection with the server failed...\n");
            exit(0);
        }
        else
        {   
            tick_end_connect = rdtsc();
            //asm("cpuid");
            //asm volatile("rdtsc" : "=cycle_high" (cycle_high_end), "=cycle_low" (cycle_low_end));
            printf("connected to the server..\n");
            printf("Final Value of Startup in iteration=%d  is  =%ld cycles = %f (s) \n", i ,tick_end_connect - tick_start_connect,(tick_end_connect - tick_start_connect)/3e9);
        }
        // function for chat

        // close the socket
        uint64_t tick_start_down,tick_end_down;
        tick_start_down = rdtsc();
        close(sockfd);
        tick_end_down = rdtsc();
        printf("Final Value of Tearing down in iteration=%d is  =%ld cycles = %f s\n", i,tick_end_down - tick_start_down, (tick_end_down - tick_start_down)/3e9);
        i++;
    }
}
