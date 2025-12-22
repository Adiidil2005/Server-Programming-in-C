#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd){
    char buffer[50];
    int i=0;
    while(1){

        bzero(buffer,sizeof(buffer));

        printf("enter the sentence(or exit):");
        //scanf("%s",buffer);
        fgets(buffer,sizeof(buffer),stdin);
        buffer[strcspn(buffer,"\n")]='\0';
        
        printf("\n");
        if(strcmp(buffer,"exit")==0){
            break;
        }

        write(sockfd,buffer,sizeof(buffer));

        bzero(buffer,sizeof(buffer));

        read(sockfd,buffer,sizeof(buffer));

        printf("Recived :%s\n",buffer);



    }
}

int main(){
    struct sockaddr_in addr;
    int sockfd;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("Failed to create a socket");
        exit(1);
    } else {
        printf("Successfully created the socket\n");
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    int c = connect(sockfd, (SA*)&addr, sizeof(addr));
    if(c < 0){
        perror("Failed to connect");
        close(sockfd);
        exit(1);
    } else {
        printf("Connected to the server\n");
    }
    
    func(sockfd);
    
    close(sockfd);
    return 0;
}