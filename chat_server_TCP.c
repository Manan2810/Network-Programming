//Chat Server -- Server side
#include<sys/types.h> 	
#include<sys/socket.h>  
#include<netdb.h>  
#include<fcntl.h>   // provides functions for opening a connection
#include<unistd.h>   //	used to close a connection
#include<stdio.h>
#include<string.h>
int main()
{
	int listen_fd,comm_fd;
	char str[100];
	struct sockaddr_in servaddr;
	
	listen_fd=socket(AF_INET,SOCK_STREAM,0);  

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	servaddr.sin_port=htons(2200);
	
	bind(listen_fd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	listen(listen_fd,5);
	
	comm_fd=accept(listen_fd,(struct sockaddr *)NULL,NULL);
	
	while(1)
	{
	bzero(str,100);
	
	//recieving the info from client
	recv(comm_fd,str,100,0);
	printf("Recieved data is : %s",str);
	
	if(strncmp(str,"exit",4)==0)
	break;
	
	//sending info back to client
	char s[100];
	fgets(s,100,stdin);
	send(comm_fd,s,strlen(s),0);
	}

	close(comm_fd);
	close(listen_fd);
}
