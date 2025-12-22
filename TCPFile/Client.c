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
    struct sockaddr_in addr;
    int sockfd;
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
    
    // Connect to server
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if(connect(sockfd, (SA*)&addr, sizeof(addr)) < 0){
        perror("Connection failed");
        exit(1);
    }
    printf("Connected to server\n");
    
    // Get filename from user
    printf("Enter filename to download: ");
    scanf("%s", filename);
    
    // Send filename to server
    write(sockfd, filename, strlen(filename));
    
    // Create output filename
    char output_file[150];
    sprintf(output_file, "downloaded_%s", filename);
    
    // Open file to write
    fp = fopen(output_file, "w");
    if(fp == NULL){
        perror("Cannot create file");
        exit(1);
    }
    
    // Receive and write file content
    int bytes;
    printf("Downloading...\n");
    while((bytes = read(sockfd, buffer, sizeof(buffer))) > 0){
        fwrite(buffer, 1, bytes, fp);
    }
    
    fclose(fp);
    printf("File downloaded as: %s\n", output_file);
    
    close(sockfd);
    return 0;
}