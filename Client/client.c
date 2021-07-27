#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

#define SIZE 1024
//int a = 0;

void write_file(int sockfd)
{
    int n; 
    FILE *fp;
    char *filename = "final.mp4";
    char buffer[SIZE];

    fp = fopen(filename, "w");
    if(fp==NULL)
    {
        perror("[-]Error in creating file.");
        exit(1);
    }
    
    while(1)
    {
        n = recv(sockfd, buffer, SIZE, 0);
        if(n<=0)
        {
            break;
            return;
        }
        fprintf(fp, "%s", buffer);
        //a++;
        bzero(buffer, SIZE);
        
        
        // sending ack to the server.
        char ack[4] = "ACK1";
        send(sockfd, ack, sizeof(ack), 0);
        
        //srand(time(0));
        //printf("%d ", rand());
        
        /*if (rand()%1000 < 1000)
        {
            //printf(";");
            char ack[4] = "ACK1";
            send(sockfd, ack, sizeof(ack), 0);
        }
        else
        {
            //printf(".");
            char ack[4] = "ACK2";
            send(sockfd, ack, sizeof(ack), 0);
        }*/
            
    }
    //printf("a: %d \n", a);
    return;
}

int main()
{
    char *ip = "127.0.0.1";
    int port = 8080;
    int e;

    int sockfd;
    struct sockaddr_in server_addr;
    
    // creating a socket
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

     // connect with the server
     e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
     if(e == -1)
     {
         perror("[-]Error in Connecting");
         exit(1);
     }
     printf("[+]Connected to server.\n");
     
     
     printf("[+]Data writing started in the file.\n");
     
     clock_t start, end;
     double cpu_time_used;
     start = clock();
     
     write_file(sockfd);//new_sock);
     
     end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
     
     printf("[+]Data writing complete in the file.\n");
     printf("Time taken: %fs\n", cpu_time_used);
     
     
     close(sockfd);
     printf("[+]Disconnected from the server.\n");
     return 0;

}
