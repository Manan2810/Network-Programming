#include<sys/types.h> 	
#include<sys/socket.h>  
#include<netdb.h>  
#include<fcntl.h>   
#include<unistd.h> 
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<math.h>
int main() {
    int sockfd, n;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    bzero(&serverAddr, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    double a, b, c;

    printf("Enter the coefficients of the quadratic equation (a b c): ");
    scanf("%lf %lf %lf", &a, &b, &c);

    snprintf(buffer, sizeof(buffer), "%lf %lf %lf", a, b, c);
    sendto(sockfd, (const char *)buffer, strlen(buffer), 0, (const struct sockaddr *)&serverAddr, sizeof(serverAddr));

    n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), 0, NULL, NULL);
    buffer[n] = '\0';
    printf("Server Response: %s\n", buffer);

    close(sockfd);
    return 0;

