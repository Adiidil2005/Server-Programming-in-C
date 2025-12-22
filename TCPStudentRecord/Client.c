#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 8080
#define SA struct sockaddr


void func(int sockfd){
    int bufferrollNo;
    char buffername[50];
    char choice;
    int bytes_read;
    while(1){

        memset(&bufferrollNo,0,sizeof(bufferrollNo));

        printf("enter the Rollno:");
        scanf("%d",&bufferrollNo);

        int rollNo=htonl(bufferrollNo);
        write(sockfd,&rollNo,sizeof(rollNo));

        printf("Send\n");

        bytes_read=read(sockfd,buffername,sizeof(buffername));
        if(bytes_read<0)break;

        printf("Name of Student:%s\n",buffername);

        printf("Do you wnat to continue(Y/N):");
        scanf("%s",&choice);
        if(choice=='N'|| choice=='n'){
            printf("Exiting...\n");
            break;
        }

    }


}

int main(){

    struct sockaddr_in addr,cli;
    int sockfd;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        perror("failed to create a socket\n");
        exit(1);
    }else{
        printf("Successfully created the socket\n");
    }

    addr.sin_family=AF_INET;
    addr.sin_port=htons(PORT);
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");


    int c=connect(sockfd,(SA*)&addr,sizeof(addr));
    if(c<0){
        perror("failed to connect\n");
        exit(1);
    }else{
        printf("Connected to the server\n");

    }
    func(sockfd);
    close(sockfd);
    return 0;
}