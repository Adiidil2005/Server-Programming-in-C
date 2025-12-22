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
	int bufferM1[50][50];
	int bufferM2[50][50];
	int bufferM3[50][50];
	
	do{
		bzero(bufferM1,sizeof(bufferM1));
		bzero(bufferM2,sizeof(bufferM2));
		bzero(bufferM3,sizeof(bufferM3));
        
        printf("Enter the first matrix:\n");
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                scanf("%d",&bufferM1[i][j]);  // Added & here
            }
        }
        write(sockfd,bufferM1,sizeof(bufferM1));
        
		printf("Enter the second matrix:\n");
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                scanf("%d",&bufferM2[i][j]);  // Added & here
            }
        }
		write(sockfd,bufferM2,sizeof(bufferM2));
		
		printf("Result from server:\n");
		
		read(sockfd,bufferM3,sizeof(bufferM3));
        
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				printf("%d ",bufferM3[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		
	}while(1);
}

int main(){
	struct sockaddr_in addr;
	int sockfd;
	
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	if(sockfd<0){
		perror("failed to create a socket\n");
		exit(0);
	}else{
		printf("successfully created the socket\n");
	}
	
	addr.sin_family=AF_INET;
	addr.sin_port=htons(PORT);
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	int c=connect(sockfd,(SA*)&addr,sizeof(addr));
	
	if(c<0){
		perror("failed to connect");
		exit(0);
	}else{
		printf("connected to the server\n");
	}
	
	func(sockfd);
	close(sockfd);
	
	return 0;
}