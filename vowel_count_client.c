#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_MESSAGE_SIZE 1024

int countVowels(const char* message) {
    int vowel_count = 0;
    for (int i = 0; message[i]; i++) {
        char current_char = message[i];
        if (strchr("AEIOUaeiou", current_char) != NULL) {
            vowel_count++;
        }
    }
    return vowel_count;
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char message[MAX_MESSAGE_SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    while (1) {
        printf("Enter a message: ");
        fgets(message, sizeof(message), stdin);

        message[strlen(message) - 1] = '\0';

        sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

        if (strcmp(message, "CLOSE") == 0) {
            printf("Closing the connection.\n");
            break;
        }

        char ack_message[MAX_MESSAGE_SIZE];
        recvfrom(sockfd, ack_message, sizeof(ack_message), 0, NULL, NULL);
        printf("Server: %s\n", ack_message);

        int vowel_count = countVowels(message);
        printf("Vowel count in the message: %d\n", vowel_count);
    }

    close(sockfd);
    return 0;
}
