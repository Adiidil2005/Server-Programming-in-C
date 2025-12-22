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

void func(int connfd){
    char buffer[50];
    while(1){
        bzero(buffer, sizeof(buffer));
        
        int n = read(connfd, buffer, sizeof(buffer));
        if(n <= 0) break;  // Client disconnected
        
        int len = strlen(buffer);
        
        // Reverse the string
        for(int i = 0; i < len/2; i++){
            char temp = buffer[i];
            buffer[i] = buffer[len-i-1];
            buffer[len-i-1] = temp;
        }
        
        printf("The reversed string: %s\n", buffer);
        write(connfd, buffer, sizeof(buffer));
    }
}

int main(){
    struct sockaddr_in addr, cli;
    int sockfd, connfd;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("Failed to create a socket");
        exit(1);
    } else {
        printf("Successfully created the socket\n");
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    int b = bind(sockfd, (SA*)&addr, sizeof(addr));
    if(b < 0){
        perror("Failed to bind");
        close(sockfd);
        exit(1);
    } else {
        printf("Successfully binded\n");
    }
    
    int l = listen(sockfd, 10);
    if(l < 0){
        perror("Failed to listen");
        close(sockfd);
        exit(1);
    } else {
        printf("Listening.......\n");
    }
    
    socklen_t len = sizeof(cli);
    connfd = accept(sockfd, (SA*)&cli, &len);
    if(connfd < 0){
        perror("Failed to accept");
        close(sockfd);
        exit(1);
    } else {
        printf("Accepted connection from %s:%d\n", 
               inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
    }
    
    func(connfd);
    close(connfd);
    close(sockfd);
    return 0;
}