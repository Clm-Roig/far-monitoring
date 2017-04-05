// Sockets / HTTP / IP
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// Threads 
#include <pthread.h>

// Base 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Erreur
#include <errno.h>

#include "src/util.c"

int main() {
	initSocket(80,"127.0.0.1");
	return 0;
}
