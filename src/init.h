#ifndef DEF_INIT
#define DEF_INIT

// EN-TETE init.h

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
#include <errno.h>

// ---- CONSTANTES ---- //


// ---- FONCTIONS ---- //

/**
  @brief Obtient les identifiants des robots puis intiailise le père et lui fournit les informations
  @return int, 1 si tout s'est bien passé, 0 sinon
*/
int init();

#endif
