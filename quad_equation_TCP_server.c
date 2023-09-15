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
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t len;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    bzero(&serverAddr, sizeof(serverAddr));
    bzero(&clientAddr, sizeof(clientAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (const struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    len = sizeof(clientAddr);
    n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddr, &len);
    buffer[n] = '\0';

    if (n < 0) {
        perror("Error receiving data from client");
        exit(EXIT_FAILURE);
    }

    double a, b, c;
    sscanf(buffer, "%lf %lf %lf", &a, &b, &c);

    double discriminant = b * b - 4 * a * c;
    double root1, root2;

    if (discriminant > 0) {
        root1 = (-b + sqrt(discriminant)) / (2 * a);
        root2 = (-b - sqrt(discriminant)) / (2 * a);
        snprintf(buffer, sizeof(buffer), "Root 1: %lf, Root 2: %lf", root1, root2);
    } else if (discriminant == 0) {
        root1 = -b / (2 * a);
        snprintf(buffer, sizeof(buffer), "Root 1: %lf (only one real root)", root1);
    } else {
        double realPart = -b / (2 * a);
        double imaginaryPart = sqrt(-discriminant) / (2 * a);
        snprintf(buffer, sizeof(buffer), "Root 1: %lf + %lfi, Root 2: %lf - %lfi", realPart, imaginaryPart, realPart, imaginaryPart);
    }

    sendto(sockfd, (const char *)buffer, strlen(buffer), 0, (const struct sockaddr *)&clientAddr, len);

    close(sockfd);
    return 0;
}
	
