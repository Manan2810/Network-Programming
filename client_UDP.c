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
  char str1[100],str2[100];
  int sockid;
  struct sockaddr_in serv;
  
  sockid=socket(AF_INET,SOCK_DGRAM,0);
  
  bzero(&serv,sizeof(serv));
  bzero(str1,100);
  bzero(str2,100);
  
  serv.sin_family=AF_INET;
  serv.sin_port=htons(5100);
  serv.sin_addr.s_addr=inet_addr("127.0.0.1");
  
  fgets(str1,100,stdin);
  int c=sizeof(serv);
  sendto(sockid,str1,strlen(str1),0,(struct sockaddr *) &serv,c);
  recvfrom(sockid,str2,strlen(str2),0,(struct sockaddr *) &serv,&c);
  printf("recieved data is %s",str2);
  
  close(sockid);
  
}
