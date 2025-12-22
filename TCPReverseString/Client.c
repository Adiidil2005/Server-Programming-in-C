#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define SA struct sockaddr
#define PORT 8080

void func(int sockfd){
    char buffer[50];
    char bufferRecv[50];
    
    while(1){
        bzero(buffer, sizeof(buffer));
        bzero(bufferRecv, sizeof(bufferRecv));
        
        printf("Enter the word (or 'quit' to exit): ");
        scanf("%s", buffer);
        
        if(strcmp(buffer, "quit") == 0) break;
        
        write(sockfd, buffer, sizeof(buffer));
        read(sockfd, bufferRecv, sizeof(bufferRecv));
        printf("The reversed string is: %s\n", bufferRecv);
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