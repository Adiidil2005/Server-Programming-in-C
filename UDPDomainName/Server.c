#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define SA struct sockaddr
#define PORT 5000

struct Domain{
    char name[50];
    char IP[50];
};

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

    int b=bind(sockfd,(SA*)&addr,sizeof(addr));
    if(b<0){
        perror("failed to bind\n");
        exit(1);
    }else{
        printf("Successfully binded the server\n");
    }

    printf("New connection");

    struct Domain Dname[10]={
        {"Kalashnokov.com","127.10.10.1"},
        {"goDaddy.com","127.10.10.2"},

    };

    do{
        bzero(buffer,sizeof(buffer));
        recvfrom(sockfd,buffer,sizeof(buffer),0,(SA*)&addr,&s);

        buffer[strcspn(buffer,"\n")]='\0';

        for(int i=0;i<10;i++){
            if(strcmp(buffer,Dname[i].name)==0){
                sendto(sockfd,Dname[i].IP,sizeof(Dname[i].IP),0,(SA*)&addr,s);
                break;
            }

        }





    }while(strcmp(buffer,"exit")!=0);

    close(sockfd);
    return 0;
}