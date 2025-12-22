
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<time.h>

#define SA struct sockaddr
#define PORT 5000

int IOTSensor(){
    static int i=24;
    sleep(1);
    return i++;
}

int main(){

    struct sockaddr_in addr;
    int sockfd;
    char buffer[50];

    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0){
        perror("failed to create a socket\n");
        exit(1);
    }else{
        printf("Successfully createdd the the socket\n");

    }

    addr.sin_family=AF_INET;
    addr.sin_port=PORT;
    addr.sin_addr.s_addr=INADDR_ANY;

    int s=sizeof(struct sockaddr_in);

    int c=connect(sockfd,(SA*)&addr,sizeof(addr));
    if(c<0){
        perror("failed to connect\n");
        exit(1);
    }else{
        printf("Successfully conneced to the server\n");
    }
    while(1){
        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo=localtime(&rawtime);

        int iot=IOTSensor();

        sprintf(buffer,"Temperature :%d at %d:%d:%d",iot,
            timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);

        sendto(sockfd,buffer,sizeof(buffer),0,(SA*)&addr,s);
        //write(sockfd,buffer,sizeof(buffer));
        printf("\n");

    }
    close(sockfd);
    return 0;

    
}