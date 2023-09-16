#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // Create a socket
    int client = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server address
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    connect(client, (struct sockaddr*)&server_addr, sizeof(server_addr));

    char message[1024];
    while (1) {
        printf("Enter a message to send (or 'quit' to exit): ");
        fgets(message, sizeof(message), stdin);

        if (strcmp(message, "quit\n") == 0) {
            break;
        }

        send(client, message, strlen(message), 0);

        // Receive and print the server's response
        char response[1024];
        int bytes_received = recv(client, response, sizeof(response), 0);
        if (bytes_received > 0) {
            response[bytes_received] = '\0';
            printf("Received from server: %s", response);
        }
    }

    close(client);
    return 0;
}
