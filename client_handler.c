#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <arpa/inet.h>
#include "client_handler.h"
#include "echo_server.h"


// function that handles client connectins via different threads
void* handle_client_connection(void* arg) {
    client_connection_t* client_info = (client_connection_t*)arg;
    int client_socket = client_info->client_socket;
    struct sockaddr_in client_address = client_info->client_address;
    free(client_info);  // Free the allocated structure
    
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client_address.sin_addr), client_ip, INET_ADDRSTRLEN);
    int client_port = ntohs(client_address.sin_port);
    
    if (verbose_mode) {
        printf("Connection established with %s:%d\n", client_ip, client_port);
    }
    
    char buffer[BUFFER_SIZE];
    char current_byte;
    int buffer_index = 0;
    ssize_t bytes_read;
    
    // Loop to read data byte by byte until connection is closed
    while (1) {
        bytes_read = recv(client_socket, &current_byte, 1, 0);
        
        if (bytes_read <= 0) {
            if (verbose_mode) {
                if (bytes_read == 0) {
                    printf("Connection with %s:%d closed by client\n", client_ip, client_port);
                } else {
                    printf("Error reading from client %s:%d: %s\n", 
                           client_ip, client_port, strerror(errno));
                }
            }
            break;
        }
        
        // Add byte to buffer
        buffer[buffer_index++] = current_byte;
        
        // If we hit a newline or buffer is full, echo back the data
        if (current_byte == '\n' || buffer_index >= BUFFER_SIZE - 1) {
            buffer[buffer_index] = '\0';
            
            if (verbose_mode) {
                printf("Received from %s:%d: %s", client_ip, client_port, buffer);
                // No need to add newline as it's already in the buffer
            }
            
            // Echo data back to client
            if (send(client_socket, buffer, buffer_index, 0) != buffer_index) {
                if (verbose_mode) {
                    printf("Error sending to client %s:%d: %s\n", 
                           client_ip, client_port, strerror(errno));
                }
                break;
            }
            
            buffer_index = 0;  // Reset buffer index
        }
    }
    
    // Close the client socket
    close(client_socket);
    if (verbose_mode) {
        printf("Connection with %s:%d closed\n", client_ip, client_port);
    }
    
    pthread_exit(NULL);
}