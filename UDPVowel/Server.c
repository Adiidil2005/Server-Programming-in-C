#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<ctype.h>
#include<arpa/inet.h>

void to_upper(char *str, char *result) {
    int i = 0;
    while(str[i] != '\0') {
        result[i] = toupper(str[i]);
        i++;
    }
    result[i] = '\0';
}

int main(){
    printf("Server Started\n");
    struct sockaddr_in server_addr, client_addr;
    char buffer[50];
    char upper[50];
    char response[100];
    int vowel_count;
    int sockfd;
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    if(bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(1);
    }
    
    printf("Connection has been successfully established!\n");
    printf("Waiting for messages...\n\n");
    
    socklen_t len = sizeof(client_addr);
    
    do {
        // Reset for each request
        memset(buffer, 0, sizeof(buffer));
        memset(upper, 0, sizeof(upper));
        memset(response, 0, sizeof(response));
        vowel_count = 0;
        
        // Receive from client
        int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, 
                        (struct sockaddr*)&client_addr, &len);
        
        if(n < 0) {
            perror("Receive failed");
            continue;
        }
        
        buffer[n] = '\0';
        printf("Received from client: %s\n", buffer);
        
        // Check for exit condition
        if(strcmp(buffer, "close") == 0) {
            printf("Client requested to close. Shutting down...\n");
            break;
        }
        
        // Convert to uppercase
        to_upper(buffer, upper);
        
        // Count vowels
        for(int i = 0; buffer[i] != '\0'; i++) {
            char lower_char = tolower(buffer[i]);
            if(lower_char == 'a' || lower_char == 'e' || 
               lower_char == 'i' || lower_char == 'o' || lower_char == 'u') {
                vowel_count++;
            }
        }
        
        // Prepare response
        sprintf(response, "Upper Case: %s | Number of vowels: %d", 
                upper, vowel_count);
        
        // Send response to client
        sendto(sockfd, response, strlen(response), 0, 
               (struct sockaddr*)&client_addr, len);
        
        printf("Sent to client: %s\n\n", response);
        
    } while(1);
    
    close(sockfd);
    printf("Server closed.\n");
    return 0;
}