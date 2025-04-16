#ifndef ECHO_SERVER_H
#define ECHO_SERVER_H

#include <netinet/in.h>

#define DEFAULT_PORT 8080
#define BUFFER_SIZE 1024
#define MAX_PENDING_CONNECTIONS 5

extern int server_socket;
extern int verbose_mode;

// Helps pass data to client handler threads
typedef struct {
    int client_socket;
    struct sockaddr_in client_address;
} client_connection_t;

void* handle_client_connection(void* arg);
void handle_interrupt_signal(int signal_number);
int initialize_server(int server_port);
void run_server_loop(void);

#endif 