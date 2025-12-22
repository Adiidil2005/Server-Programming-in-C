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
struct Student{
    char Name[50];
    int RollNo;
};

void func(int connfd){
    int bufferRollNo;
    char bufferName[50];
    int bytes_read;
    int i=0;

    struct Student stud[50]={
        {"Aditya",10},
        {"Aishu",12},
        {"Adityan",9}
    };

    while(i<50){
        memset(&bufferRollNo,0,sizeof(bufferRollNo));
        memset(bufferName,0,sizeof(bufferName));

        //bytes_read=read(connfd,bufferName,sizeof(bufferName));
        //if(bytes_read<=0)break;

        bytes_read=read(connfd,&bufferRollNo,sizeof(bufferRollNo));
        if(bytes_read<=0)break;

        int rollNo=ntohl(bufferRollNo);
        for(int j=0;j<50;j++ ){
            if(stud[i].RollNo==rollNo){
                write(connfd,stud[i].Name,sizeof(bufferName));
                break;
            }
        }

    i++;
    }
}

int main(){
    struct sockaddr_in addr,cli;
    int sockfd,connfd;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){

        perror("failed to create a socket\n");
        exit(0);
    }else{
        printf("Successfully created the socket\n");
    }

    addr.sin_family=AF_INET;
    addr.sin_port=htons(PORT);
    addr.sin_addr.s_addr=htonl(INADDR_ANY);

    int b=bind(sockfd,(SA*)&addr,sizeof(addr));
    if(b<0){

        perror("failed to bind \n");
        exit(1);
    }else{
        printf("Successully binded to the server\n");
    }

    int l=listen(sockfd,10);
    if(l<0){
        perror("failed to liseten\n");
        exit(1);
    }else{
        printf("Listening.......\n");

    }
    socklen_t len=sizeof(cli);
    connfd=accept(sockfd,(SA*)&cli,&len);
    if(connfd<0){
        perror("failed to accept\n");
        close(sockfd);
        exit(1);
    }else{
        printf("Accepted Connection from %s:%d\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));

    }
    func(connfd);
    close(connfd);
    close(sockfd);

    return 0;
}
