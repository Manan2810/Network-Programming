#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<netdb.h>
#include<fcntl.h>
#include<string.h>
#include<math.h>
#include<arpa/inet.h>

int main(){
  char str[100];
  int listen_fd;
  struct sockaddr_in serv,cli;
  
  listen_fd=socket(AF_INET,SOCK_DGRAM,0);
  
  bzero(&serv,sizeof(serv));
  bzero(str,100);
  
  serv.sin_family=AF_INET;
  serv.sin_port=htons(5100);
  serv.sin_addr.s_addr=htonl(INADDR_ANY);
  
  bind(listen_fd,(struct sockaddr *) &serv,sizeof(serv));
  
  recvfrom(listen_fd,str,100,0,(struct sockaddr *) &cli,sizeof(cli));
  printf("recieved data is %s",str);
  
  char *clientaddr=inet_ntoa(cli.sin_addr);
  printf("address of client is %s",clientaddr);
  sendto(listen_fd,str,strlen(str),0,(struct sockaddr *) &cli,sizeof(cli));
  
  close(listen_fd);
  
}
