#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12345
#define MAX_SIZE 1024

int main() {
    int server_socket, n;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[MAX_SIZE];

    // Create a UDP socket
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error binding socket");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        // Receive data from a client
        n = recvfrom(server_socket, buffer, MAX_SIZE, 0, (struct sockaddr *)&client_addr, &client_len);
        if (n == -1) {
            perror("Error receiving data");
            close(server_socket);
            exit(EXIT_FAILURE);
        }

        // Null-terminate the received data
        buffer[n] = '\0';

        if (strcmp(buffer, "CLOSE") == 0) {
            printf("Closing the chat session.\n");
            break;
        }

        printf("Received from %s:%d: %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);

        // Send an acknowledgment back to the client
        char ack_message[] = "ACK: Message Received";
        sendto(server_socket, ack_message, sizeof(ack_message), 0, (struct sockaddr *)&client_addr, client_len);
    }

    // Close the socket
    close(server_socket);

    return 0;
}