// CLIENT PROGRAM
// Save as: client.c
// Compile: gcc client.c -o client
// Run: ./client

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
    int BufferAMT;
    int BufferAccNo;
    char Buffername[50];
    char BufferType[50];
    char choice;
    
    while(1){
        // Clear buffers
        memset(&BufferAMT, 0, sizeof(BufferAMT));
        memset(&BufferAccNo, 0, sizeof(BufferAccNo));
        memset(Buffername, 0, sizeof(Buffername));
        memset(BufferType, 0, sizeof(BufferType));
        
        printf("\n--- Enter Account Details ---\n");
        printf("Enter the name: ");
        scanf("%s", Buffername);
        
        printf("Enter the Account No: ");
        scanf("%d", &BufferAccNo);
        
        printf("Enter the Amount: ");
        scanf("%d", &BufferAMT);
        
        printf("Enter the Type of transaction: ");
        scanf("%s", BufferType);
        
        // Convert to network byte order
        int netAMT = htonl(BufferAMT);
        int netAccNo = htonl(BufferAccNo);
        
        // Send data to server
        write(sockfd, &netAMT, sizeof(netAMT));
        write(sockfd, &netAccNo, sizeof(netAccNo));
        write(sockfd, Buffername, sizeof(Buffername));
        write(sockfd, BufferType, sizeof(BufferType));
        
        printf("\nAccount details sent to server.\n");
        
        printf("Add more accounts? (Y/N): ");
        scanf(" %c", &choice);
        
        if(choice == 'N' || choice == 'n'){
            printf("Exiting...\n");
            break;
        }
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