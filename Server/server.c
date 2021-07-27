#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

#define SIZE 1024
int nACK = 5;
//int aa = 0;

void send_file(FILE *fp, int sockfd)
{
    char data[SIZE] = {0};

    while(nACK > 0 && fgets(data, SIZE, fp)!=NULL)
    {   
        if (nACK > 999999)
        {
            printf("Server Down. \n");
            exit(1);
        }
            
        //printf("%d ", congession);
        if (nACK > 100)
            sleep(0);
        else
            sleep(.0001);
        //printf(".");
        int s = send(sockfd, data, sizeof(data), 0);
        //aa++;
        if(s == -1)
        {
            perror("[-] Error in sending data");
            exit(1);
        }
        bzero(data, SIZE);
        
        nACK--;
        
        
        // getting ACK from client.
        struct timeval tv;
        tv.tv_sec = 1;       /* Timeout in seconds */
        
        //setsockopt(sockid, SOL_SOCKET, SO_SNDTIMEO,(struct timeval *)&tv,sizeof(struct timeval));
        
        // wait for 1 sec, if data not received, then ignore the recv()
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,(struct timeval *)&tv,sizeof(struct timeval));
        
        char ack[4];
        int n = recv(sockfd, ack, sizeof(ack), 0);
        if(n < 0)
            continue;
        else if (ack[0] == 'A' && ack[1] == 'C' && ack[2] == 'K')
        {
            int a = (int)(ack[3]) - 48;
            nACK += a;
            //printf("%d ", congession);
        }
    }
    //printf("aa: %d \n", aa);
}


int main ()
{
    char *ip = "127.0.0.1";
    int port = 8080;
    int e;

    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    
    socklen_t addr_size;
    char buffer[SIZE];

    // socket create
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0)
    {
        perror("[-]Error in socket");
        exit(1);
    }
     printf("[+]Server socket created. \n");

     
     // specify an address for the socket
     server_addr.sin_family = AF_INET;
     server_addr.sin_port = port;
     server_addr.sin_addr.s_addr = inet_addr(ip);

     // binding---- like connecting
     e = bind(sockfd,(struct sockaddr*)&server_addr, sizeof(server_addr));
     if(e<0)
     {
         perror("[-]Error in Binding");
         exit(1);
     }
     printf("[+]Binding Successfull.\n");
     

     // Listening for client connecting
     e = listen(sockfd, 10);
     if(e==0)
     {
         printf("[+]Listening...\n");
     }
     else 
     {
         perror("[-]Error in Binding");
         exit(1);
     }
     
     addr_size = sizeof(new_addr);
     new_sock = accept(sockfd,NULL, NULL);//(struct sockaddr*)&new_addr, &addr_size);
     
     printf("[+]Client connected.\n");

     FILE *fp;
     char *filename = "gias.mp4";
     
     fp = fopen(filename, "r");
     if(fp == NULL)
     {
         perror("[-]Error in reading file.");
         exit(1);
     }
     
     printf("[+]Data sending started.\n");
     
     clock_t start, end;
     double cpu_time_used;
     start = clock();
     
     send_file(fp,new_sock); //sockfd);
     
     end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
     
     printf("[+]File data send successfully. \n");
     printf("Time taken: %fs\n", cpu_time_used);
     
     
     close(sockfd);
     printf("[+]Server closed.\n");
     return 0;
}
