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
  char str[100];
  int sockid;
  struct sockaddr_in server,client;
  
  sockid=socket(AF_INET,SOCK_DGRAM,0);
  
  bzero(&server,sizeof(server));
  //bzero(str,100);
  
  server.sin_family=AF_INET;
  server.sin_port=htons(2100);
  server.sin_addr.s_addr=htonl(INADDR_ANY);
  
  bind(sockid,(struct sockaddr *) &server,sizeof(server));
  
  while(1)
  {
    int len = sizeof(client);
    bzero(str,100);
    recvfrom(sockid,str,sizeof(str),0,(struct sockaddr*)&client,&len);
    printf("%s",str);
    fgets(str,100,stdin); 
    sendto(sockid,str,sizeof(str),0,(struct sockaddr*)&client,sizeof(client));
  }
  
  close(sockid);
  
  
  
  
}