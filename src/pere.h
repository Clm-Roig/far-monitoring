#ifndef DEF_PERE
#define DEF_PERE

// EN-TETE pere.h

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
    @brief créer le serveur de position à partir d'un tableau de 6 IPs de robots
    @param char** tabIPs, le tableau des IPs des robots
    @return int, 1 si tout s'est bien passé, 0 sinon 
*/
int creerServeur();
 

#endif
