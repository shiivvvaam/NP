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

    // Accept connections and handle chat
    while (1) {
        int client = accept(server, NULL, NULL);

        pid_t pid = fork(); // Fork a new process to handle each client

        if (pid == 0) {
            // Child process: Handle client communication
            close(server); // Close the server socket in the child process

            char message[1024];

            while (1) {
                int bytes_received = recv(client, message, sizeof(message), 0);
                if (bytes_received <= 0) {
                    break;
                }

                message[bytes_received] = '\0';
                printf("Received from client: %s", message);

                printf("Enter a message to send back: ");
                fgets(message, sizeof(message), stdin);
                send(client, message, strlen(message), 0);
            }

            close(client);
            exit(0); // Exit the child process
        } else {
            // Parent process: Continue accepting connections
            close(client); // Close the client socket in the parent process
        }
    }

    close(server);
    return 0;
}
