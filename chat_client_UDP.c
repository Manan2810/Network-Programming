#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<math.h>

int main(){
  char str1[100],str2[100];
  int sockid;
  struct sockaddr_in server;
  
  sockid=socket(AF_INET,SOCK_DGRAM,0);
  
  bzero(&server,sizeof(server));
  
  server.sin_family=AF_INET;
  server.sin_port=htons(2100);
  server.sin_addr.s_addr=inet_addr("127.0.0.1");
  
  while(1){
    bzero(str1,100);
    bzero(str2,100);
    fgets(str1,100,stdin);
    sendto(sockid,str1,strlen(str1),0,(struct sockaddr *) &server,sizeof(server));
    recv(sockid,str2,100,0);
    printf("recieved data is %s",str2);
  }
  
  close(sockid);
  return 0;
  
}