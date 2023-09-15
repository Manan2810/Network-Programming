#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>

#define PORT 12345
#define MAX_SIZE 1024

// Function to count and return the maximum occurring alphabet in a string
char getMaxOccurringAlphabet(char *str) {
    int char_count[26] = {0}; // Array to store counts of each alphabet

    // Convert the input string to lowercase and count alphabet occurrences
    for (int i = 0; str[i]; i++) {
        char c = tolower(str[i]);
        if (isalpha(c)) {
            char_count[c - 'a']++;
        }
    }

    int max_count = 0;
    char max_char = '\0';

    // Find the alphabet with the maximum count
    for (int i = 0; i < 26; i++) {
        if (char_count[i] > max_count) {
            max_count = char_count[i];
            max_char = 'a' + i;
        }
    }

    return max_char;
}

int main() {
    int client_socket, n;
    struct sockaddr_in server_addr;
    char buffer[MAX_SIZE];
    char input_string[MAX_SIZE];

    // Create a UDP socket
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    while (1) {
        printf("Enter your message (or 'CLOSE' to exit): ");
        fgets(input_string, sizeof(input_string), stdin);

        // Remove the newline character
        input_string[strlen(input_string) - 1] = '\0';

        // Send the message to the server
        sendto(client_socket, input_string, strlen(input_string), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

        if (strcmp(input_string, "CLOSE") == 0) {
            printf("Closing the chat session.\n");
            break;
        }

        // Receive an acknowledgment from the server
        n = recvfrom(client_socket, buffer, MAX_SIZE, 0, NULL, NULL);
        if (n == -1) {
            perror("Error receiving data");
            close(client_socket);
            exit(EXIT_FAILURE);
        }

        buffer[n] = '\0';
        printf("Server says: %s\n", buffer);

        // Calculate and print the maximum occurring alphabet in the input string
        char max_alphabet = getMaxOccurringAlphabet(input_string);
        printf("Maximum occurring alphabet in the input string: %c\n", max_alphabet);
    }

    // Close the socket
    close(client_socket);

    return 0;
}