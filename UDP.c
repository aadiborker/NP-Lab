Server Side
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char const *argv[]) {
    int socket_fd, n;
    struct sockaddr_in server_address, client_address;
    char buffer[1024];

    // Creating socket file descriptor
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Clear server address structure
    memset(&server_address, 0, sizeof(server_address));

    // Set server address structure
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Bind socket to server address
    if (bind(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int client_address_length, valread;
    while (1) {
        // Receive data from client
        client_address_length = sizeof(client_address);
        memset(buffer, 0, sizeof(buffer));
        n = recvfrom(socket_fd, (char *)buffer, sizeof(buffer), MSG_WAITALL,
            (struct sockaddr *)&client_address, &client_address_length);
        buffer[n] = '\0';

        // Print client address and message
        printf("Client : %s\n", inet_ntoa(client_address.sin_addr));
        printf("Message : %s\n", buffer);

        // Send response to client
        sendto(socket_fd, "Hello from server", strlen("Hello from server"),
            MSG_CONFIRM, (const struct sockaddr *)&client_address, client_address_length);
    }

    return 0;
}
 
Client Side
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char const *argv[]) {
    int socket_fd, n;
    struct sockaddr_in server_address;
    char buffer[1024];

    // Creating socket file descriptor
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, 0, sizeof(server_address));

    // Set server address structure
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    int server_address_length, valread;
    while (1) {
        // Get user input
        printf("Enter message : ");
        fgets(buffer, sizeof(buffer), stdin);

        // Send message to server
        sendto(socket_fd, (const char *)buffer, strlen(buffer), MSG_CONFIRM,
            (const struct sockaddr *)&server_address, sizeof(server_address));
        printf("Message sent.\n");

        // Receive response from server
        server_address_length = sizeof
