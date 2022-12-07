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
#define PORT 8080
#define SA struct sockaddr

long int tick_start_server , tick_end_server , average_total_tick_start_client ,total_time_tick_start_client=0,total_time_taken=0;

cpu_set_t  mask;
uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}
 
void assignToThisCore(int core_id)
{
    CPU_ZERO(&mask);
    CPU_SET(core_id, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
}

void func(int sockfd)
{
	char buff[MAX];
	char concatenated_string[] = "Debu";
	int iteration_count = 1000;
	long int total_time = 0;
	float total_bw = 0;
	int transfer_size[] ={400,800,1600,3200,6400,12800,16370,16374,25600};
	int length_of_array = sizeof(transfer_size)/sizeof(int); 
	int iter = 0;
	float burst_size = 0;
	while(iter<length_of_array)
	{
		for(int i=0 ; i<transfer_size[iter] ; i++)
		{
			strcat(buff,concatenated_string);
			//printf("Size of buff =%ld\n",(sizeof(buff)));
		}

		for(int i=0;i<iteration_count;i++)
		{	
			int length = strlen(buff);
			//printf("Length of the string =%d \n",length);
			int write_bytes = 0;
			char *buff_to_be_sent;
			char *buff_to_be_received;
			buff_to_be_sent = (char *)malloc(sizeof(char) * (length + 1));
			buff_to_be_received = (char *)malloc(sizeof(char) * (length + 1));
			//char buff_to_be_sent[length+1];
			//char buff_to_be_received[length+1];
			strcpy(buff_to_be_sent,buff);
			//printf("Iteration Count =%d and size sent =%ld and this is for iter=%d \n",i,sizeof(buff_to_be_sent),iter);
			int n;
			
			struct tcp_info info;
			
			uint64_t tick_start_client , tick_end_client , time_taken;
			bzero(buff_to_be_received, length+1);
			//tick_start_client = rdtsc();
			tick_start_client = rdtsc();
			write_bytes = write(sockfd, buff_to_be_sent, length+1);
			read(sockfd, buff_to_be_received, length+1);
			tick_end_client = rdtsc();
			float bw = 0;
			time_taken = (tick_end_client - tick_start_client)*0.33;
			total_time_taken += time_taken;
			//printf("Size =%d and time_taken =%ld \n",transfer_size[iter]*4,time_taken);
			bw = ((float)transfer_size[iter]*4)/(time_taken);
			if(write_bytes != length+1)
			{
				printf("Write Bytes =%d and expected size =%d",write_bytes,length+1);
				printf("error \n");
				exit(0);
			}
			if(strcmp(buff_to_be_received,buff_to_be_sent)!=0)
			{
				printf("Size of Buff Received =%ld and Size of Buff Sent =%ld \n",strlen(buff_to_be_received),strlen(buff_to_be_sent));
				printf("error \n");
				exit(0);
			}
			bzero(buff_to_be_sent, sizeof(buff_to_be_sent));
			strcpy(buff_to_be_sent,"");
			
			//float time_taken = 0;
			//total_time_tick_start_client += tick_start_client ;
			
			printf("bw=%f for time =%ld\n",bw,time_taken);
			burst_size = length+1;
			total_bw += bw;
			free(buff_to_be_received);
			free(buff_to_be_sent);
		}
		//average_total_tick_start_client = total_time_tick_start_client/iteration_count;
		float average_bw,average_time;
		average_time = total_time_taken/iteration_count;
		//float average_bw = 0;
		average_bw = total_bw/iteration_count;
		//printf("Average average_total_tick_start_client=%ld for iter= %d \n",average_total_tick_start_client,iter);
		printf("Average bw =%.5f and average time=%f for size=%d\n",average_bw,average_time,4*transfer_size[iter]);
		iter++;
		strcpy(buff,"");
	}
	bzero(buff, sizeof(buff));
	read(sockfd, buff, sizeof(buff));
	printf("From Server : %s", buff);

    char buff_second[] = "exit";
	int n2;

	uint64_t tick_start , tick_end ;
    
	tick_start = rdtsc();
	write(sockfd, buff_second, sizeof(buff_second));
	//bzero(buff_second, sizeof(buff_second));
	read(sockfd, buff_second, sizeof(buff_second));
	tick_end = rdtsc();
	printf("From Server : %s", buff_second);
	if ((strncmp(buff_second, "exit", 4)) == 0) {
			printf("Client Exit...\n");
			return ;
		}
}

int main()
{
	assignToThisCore(1);
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
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
	servaddr.sin_addr.s_addr = inet_addr("192.168.43.90"); //inet_addr("192.168.43.90");//inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);
	long long int cycle_high_start , cycle_low_start , cycle_high_end , cycle_low_end;

	// connect the client socket to server socket
	asm("cpuid");
    asm volatile("rdtsc" : "=cycle_high" (cycle_high_start), "=cycle_low" (cycle_low_start)); 
	
	//int return_flag = connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
	///printf("Return Flag =%d \n",return_flag);
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
		!= 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
    {   
        asm("cpuid");
    	asm volatile("rdtsc" : "=cycle_high" (cycle_high_end), "=cycle_low" (cycle_low_end));
		printf("connected to the server..\n");
    	printf("Final Value is %lld %lld \n", cycle_high_end - cycle_high_start, cycle_low_end-cycle_low_start);
    }
	// function for chat
	func(sockfd);

	// close the socket
	close(sockfd);
}
