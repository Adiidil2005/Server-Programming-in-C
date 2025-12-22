
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<time.h>

#define SA struct sockaddr
#define PORT 5000


int main(){

    struct sockaddr_in addr;
    int sockfd;
    char buffer[50];

    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0){
        perror("failed to create a socket\n");
        exit(1);
    }else{
        printf("Successfully createdd the the socket\n");

    }

    addr.sin_family=AF_INET;
    addr.sin_port=PORT;
    addr.sin_addr.s_addr=INADDR_ANY;

    int s=sizeof(struct sockaddr_in);

    int c=connect(sockfd,(SA*)&addr,sizeof(addr));
    if(c<0){
        perror("failed to connect\n");
        exit(1);
    }else{
        printf("Successfully conneced to the server\n");
    }
    while(1){
        bzero(buffer,sizeof(buffer));

        printf("Enter the domain:");
        fgets(buffer,sizeof(buffer),stdin);
        buffer[strcspn(buffer,"\n")]='\0';

        sendto(sockfd,buffer,sizeof(buffer),0,(SA*)&addr,s);

        bzero(buffer,sizeof(buffer));

        recvfrom(sockfd,buffer,sizeof(buffer),0,(SA*)&addr,&s);
        printf("IP:%s\n",buffer);
    }
    close(sockfd);
    return 0;

    
}