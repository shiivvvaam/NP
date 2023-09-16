#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // Create a socket
    int client = socket(AF_INET, SOCK_DGRAM, 0);

    // Configure server address
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    char message[1024];
    while (1) {
        printf("Enter a message to send (or 'quit' to exit): ");
        fgets(message, sizeof(message), stdin);

        if (strcmp(message, "quit\n") == 0) {
            break;
        }

        // Send data to the server using sendto
        sendto(client, message, strlen(message), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

        // Receive and print the server's response using recvfrom
        char response[1024];
        socklen_t server_addr_len = sizeof(server_addr);
        int bytes_received = recvfrom(client, response, sizeof(response), 0, (struct sockaddr*)&server_addr, &server_addr_len);
        if (bytes_received > 0) {
            response[bytes_received] = '\0';
            printf("Received from server: %s", response);
        }
    }

    close(client);
    return 0;
}
