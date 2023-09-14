#include<sys/types.h> 	
#include<sys/socket.h>  
#include<netdb.h>  
#include<fcntl.h>   
#include<unistd.h> 
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<math.h>

int main(){
  char str[100];
  int listen_fd,comm_fd;
  
  //object creation
  struct sockaddr_in servaddr;
  
  //socket()-socket creation
  
  listen_fd=socket(AF_INET,SOCK_STREAM,0);
  
  bzero(&servaddr,sizeof(servaddr));
  
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(21000);
  servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
  
  // using bind() function
  bind(listen_fd,(struct sockaddr *)&servaddr,sizeof(servaddr));
  
  // using listen() function
  listen(listen_fd,10);
  
  //using accept() function
  comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
  
  bzero( str, 100);
  
  recv(comm_fd,str,100,0);
  printf("Echoing back - %s",str);
  send(comm_fd,str,strlen(str),0);
  close(comm_fd);
}

