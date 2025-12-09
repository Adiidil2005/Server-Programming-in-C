// SERVER PROGRAM
// Save as: server.c
// Compile: gcc server.c -o server
// Run: ./server

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

struct Account{
    int AMT;
    int AccNo;
    char name[50];
    char type[50];
};

void func(int connfd){
    int BufferAMT;
    int BufferAccNo;
    char Buffername[50];
    char BufferType[50];
    struct Account Accounts[50];
    int i=0;
    int bytes_read;
    
    while(i < 50){
        // Clear buffers
        memset(&BufferAMT, 0, sizeof(BufferAMT));
        memset(&BufferAccNo, 0, sizeof(BufferAccNo));
        memset(Buffername, 0, sizeof(Buffername));
        memset(BufferType, 0, sizeof(BufferType));
        
        // Read data from client
        bytes_read = read(connfd, &BufferAMT, sizeof(BufferAMT));
        if(bytes_read <= 0) break;
        
        bytes_read = read(connfd, &BufferAccNo, sizeof(BufferAccNo));
        if(bytes_read <= 0) break;
        
        bytes_read = read(connfd, Buffername, sizeof(Buffername));
        if(bytes_read <= 0) break;
        
        bytes_read = read(connfd, BufferType, sizeof(BufferType));
        if(bytes_read <= 0) break;
        
        // Convert from network byte order
        Accounts[i].AMT = ntohl(BufferAMT);
        Accounts[i].AccNo = ntohl(BufferAccNo);
        strcpy(Accounts[i].name, Buffername);
        strcpy(Accounts[i].type, BufferType);
        
        printf("Received Account %d:\n", i+1);
        printf("  Name: %s\n", Accounts[i].name);
        printf("  Account No: %d\n", Accounts[i].AccNo);
        printf("  Amount: %d\n", Accounts[i].AMT);
        printf("  Type: %s\n\n", Accounts[i].type);
        
        i++;
    }
    /*
    printf("\n=== Summary of All Accounts ===\n");
    printf("Total accounts received: %d\n\n", i);
    for (int j=0; j<i; j++){
        printf("Account %d:\n", j+1);
        printf("  Name: %s\n", Accounts[j].name);
        printf("  Account No: %d\n", Accounts[j].AccNo);
        printf("  Amount: %d\n", Accounts[j].AMT);
        printf("  Type: %s\n\n", Accounts[j].type);
    }*/
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