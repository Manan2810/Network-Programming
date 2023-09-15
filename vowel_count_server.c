#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_MESSAGE_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[MAX_MESSAGE_SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(12345);

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening...\n");

    while (1) {
        int recv_len = recvfrom(sockfd, buffer, MAX_MESSAGE_SIZE, 0, (struct sockaddr*)&client_addr, &client_len);
        if (recv_len == -1) {
            perror("Error in receiving data");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        buffer[recv_len] = '\0';

        if (strcmp(buffer, "CLOSE") == 0) {
            printf("Client closed the connection.\n");
            break;
        }

        printf("Received message from %s:%d: %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);

        char ack_message[] = "ACK : Message Received";
        sendto(sockfd, ack_message, strlen(ack_message), 0, (struct sockaddr*)&client_addr, client_len);
    }

    close(sockfd);
    return 0;
}
