#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include "echo_server.h"

// handle client connections in seperate threads
void* handle_client_connection(void* arg);

#endif