#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORT 8080
#define SA struct sockaddr

int main(){
    struct sockaddr_in addr, cli;
    int sockfd, connfd;
    char filename[100];
    char buffer[1024];
    FILE *fp;
    
    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("Socket creation failed");
        exit(1);
    }
    printf("Socket created\n");
    
    // Bind
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;
    
    if(bind(sockfd, (SA*)&addr, sizeof(addr)) < 0){
        perror("Bind failed");
        exit(1);
    }
    printf("Bind successful\n");
    
    // Listen
    if(listen(sockfd, 5) < 0){
        perror("Listen failed");
        exit(1);
    }
    printf("Server listening on port %d...\n", PORT);
    
    // Accept connection
    socklen_t len = sizeof(cli);
    connfd = accept(sockfd, (SA*)&cli, &len);
    if(connfd < 0){
        perror("Accept failed");
        exit(1);
    }
    printf("Client connected: %s:%d\n", 
           inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
    
    // Receive filename from client
    bzero(filename, sizeof(filename));
    read(connfd, filename, sizeof(filename));
    filename[strcspn(filename, "\n")] = '\0';
    printf("Client requested file: %s\n", filename);
    
    // Open file
    fp = fopen(filename, "r");
    if(fp == NULL){
        char *msg = "File not found";
        write(connfd, msg, strlen(msg));
        printf("File not found\n");
    }
    else{
        printf("Sending file...\n");
        
        // Send file content
        int bytes;
        while((bytes = fread(buffer, 1, sizeof(buffer), fp)) > 0){
            write(connfd, buffer, bytes);
        }
        
        fclose(fp);
        printf("File sent successfully\n");
    }
    
    close(connfd);
    close(sockfd);
    return 0;
}