#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#include <sched.h>
#include <sched.h>


long int tick_start_server , tick_end_server , total_tick_end_server, average_total_tick_end_server=0;
#define MAX 4000000
#define PORT 8080
#define SA struct sockaddr

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
// Function designed for chat between client and server.
void func(int connfd)
{
	
	int n;
	char buff_from_client[MAX]; 
	int iteration_count = 1000;
	int transfer_size[] ={400,800,1600,3200,6400,12800,16370,16374,25600};
	int length_of_array = sizeof(transfer_size)/sizeof(int); 
	int iter = 0;
	while(iter<length_of_array)
	{
		for(int i=0;i<iteration_count;i++)
		{
			long long int cycle_high_start , cycle_low_start , cycle_high_end , cycle_low_end;
		
			
			int length;
			length = transfer_size[iter]*4;
			char *buff_from_client;
			buff_from_client = (char *)malloc(sizeof(char) * (length + 1));
		

			read(connfd, buff_from_client,4*transfer_size[iter]+1);
			//tick_end_server = rdtsc();16370*4
			write(connfd,buff_from_client,4*transfer_size[iter]+1);
			//total_tick_end_server += tick_end_server;
			//printf("Time End Server =%ld \n",tick_end_server);
		}
		//average_total_tick_end_server = total_tick_end_server/iteration_count;
		//printf("Average Time End Server =%ld \n",average_total_tick_end_server);
		//printf("Average average_total_tick_end_server=%ld for iter= %d \n",average_total_tick_end_server,iter);
		iter++;
	}
	char buff[] = "Hi Sananya";
	write(connfd, buff, sizeof(buff));

    
	int n2;
	char second_buff_from_client[MAX];
	read(connfd, second_buff_from_client, sizeof(second_buff_from_client));
	printf("From Client : %s", second_buff_from_client);
	char buff_second[] = "exit";
    write(connfd, buff_second, sizeof(buff_second));
	
	if ((strncmp(buff_second, "exit", 4)) == 0) {
			printf("Server Exit...\n");
			return;
		}
}

// Driver function
int main()
{
	assignToThisCore(0);
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);//socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET ;// AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr("192.168.43.12") ;//"192.168.43.12";//htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(0);
	}
	else
		printf("server accept the client...\n");

	// Function for chatting between client and server
	func(connfd);

	// After chatting close the socket
	close(sockfd);
}
