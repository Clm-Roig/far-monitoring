#ifndef DEF_SERVEUR
#define DEF_SERVEUR

// EN-TETE serveur.h

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


// ---- CONSTANTES ---- //


// ---- FONCTIONS ---- //

/**
  @brief Initialisation du serveur
  @return int, 1 si tout s'est bien passé, 0 sinon
*/
int init();

#endif
