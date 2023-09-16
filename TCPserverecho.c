#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // Create a socket
    int server = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server address
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    bind(server, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Listen for connections
    listen(server, 5);

    printf("Server is listening...\n");

    // Accept connections and echo messages
    while (1) {
        int client = accept(server, NULL, NULL);
        char buffer[1024];
        int bytes_received;

        while ((bytes_received = recv(client, buffer, sizeof(buffer), 0)) > 0) {
            send(client, buffer, bytes_received, 0);
        }

        close(client);
    }

    close(server);
    return 0;
}
