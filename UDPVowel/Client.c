#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define PORT 5000
#define SA struct sockaddr

int main(){
	struct sockaddr_in addr;
	int sockfd;
	
	char buffer[50];
	int buffer2[10];
	
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	
	if(sockfd<0){
		perror("failed to create a socket\n");
		exit(0);
	}else{
		printf("successfully created the socket\n");
	}
	
	addr.sin_family=AF_INET;
	addr.sin_port=PORT;
	addr.sin_addr.s_addr=INADDR_ANY;
	
	int s=sizeof(struct sockaddr_in);
	
	int c=connect(sockfd,(SA*)&addr,sizeof(addr));
	
	if(c<0){
		perror("failed to connect\n");
		exit(0);
	}else{
		printf("successfully connected to the server\n");
	}
	do{
	
		printf("Enter the message:");
		fgets(buffer,sizeof(buffer),stdin);
	
		buffer[strcspn(buffer,"\n")]='\0';
		
		sendto(sockfd,buffer,sizeof(buffer),0,(SA*)&addr,s);
		
		recvfrom(sockfd,buffer,sizeof(buffer),0,(SA*)&addr,&s);
		
		printf("recved :%s",buffer);
		printf("\n");
		
	}while(strcmp(buffer,"exit")!=0);
	close(sockfd);
	return 0;
}
