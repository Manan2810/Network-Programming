#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>

int main(){
  char sendline[100];
  char recvline[100];
  int sock_fd;
  struct sockaddr_in servaddr;
  //socket creation 
  sock_fd=socket(AF_INET,SOCK_STREAM,0);
  
  bzero(&servaddr,sizeof(servaddr));
  bzero(sendline,100);
  bzero(recvline,100);
  
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(21000);
  servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
  
  connect(sock_fd,(struct sockaddr *) &servaddr,sizeof(servaddr));
  
  fgets(sendline,100,stdin); //inputing data from command line
  
  send(sock_fd,sendline,strlen(sendline),0);
  
  recv(sock_fd,recvline,100,0);
  
  printf("Recieved from server %s",recvline);
}

