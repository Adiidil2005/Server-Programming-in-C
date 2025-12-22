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

void func(int connfd){
	int bufferM1[50][50];
	int bufferM2[50][50];
	int bufferM3[50][50];
	
	do{
		bzero(bufferM1,sizeof(bufferM1));
		bzero(bufferM2,sizeof(bufferM2));
		bzero(bufferM3,sizeof(bufferM3));
		
		read(connfd,bufferM1,sizeof(bufferM1));
		read(connfd,bufferM2,sizeof(bufferM2));
		
		printf("Calculating sum...\n");
		
		// Perform addition BEFORE clearing the buffers
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				bufferM3[i][j]=bufferM1[i][j]+bufferM2[i][j];
				printf("%d ",bufferM3[i][j]);
			}
			printf("\n");
		}
		
		write(connfd,bufferM3,sizeof(bufferM3));
		
	}while(1);
}

int main(){
	struct sockaddr_in addr,cli;
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
	addr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	int b=bind(sockfd,(SA*)&addr,sizeof(addr));
	if(b<0){
		perror("failed to bind\n");
		exit(0);
	}else{
		printf("successfully binded\n");
	}
	
	int l=listen(sockfd,10);
	if(l<0){
		perror("failed to listen\n");
		exit(0);
	}else{
		printf("Listening....\n");
	}
	
	socklen_t len=sizeof(cli);
	int connfd=accept(sockfd,(SA*)&cli,&len);
	
	if(connfd<0){
		perror("failed to accept\n");
		exit(0);
	}else{
		printf("Accepted connection\n");
	}
	
	func(connfd);
	close(sockfd);
	
	return 0;
}