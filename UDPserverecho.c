#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // Create a UDP socket
    int server = socket(AF_INET, SOCK_DGRAM, 0);

    // Configure server address
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    bind(server, (struct sockaddr*)&server_addr, sizeof(server_addr));

    printf("Server is listening...\n");

    

    while (1) {
        char buffer[1024];
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
        // Receive a message from a client
        int bytes_received = recvfrom(server, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &client_addr_len);

        if (bytes_received < 0) {
            perror("Error receiving data");
            continue;
        }

        buffer[bytes_received] = '\0';
        printf("Received from %s:%d: %s", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);

        // Send a response back to the client
        sendto(server, buffer, bytes_received, 0, (struct sockaddr*)&client_addr, client_addr_len);
    }

    close(server);
    return 0;
}
