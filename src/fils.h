#ifndef DEF_FILS
#define DEF_FILS

// EN-TETE fils.h

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
    @brief génère un fils en dupliquant le processus, puis renvoie le pid
    @return int, pid du fils si tout s'est bien passé, 0 sinon
*/
int creerFils(); 
 
/**
    @brief gère l'envoie d'informations du fils vers un autre processus
    @return int, 1 si tout s'est bien passé, 0 sinon
*/
int filsEnvoi(char* nomPipe);

/**
    @brief gère la reception d'informations du fils depuis un autre processus
    @return int, 1 si tout s'est bien passé, 0 sinon
*/
int filsReception(char* nomPipe);

#endif
