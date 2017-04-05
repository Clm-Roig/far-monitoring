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
const int PORT;
const char* IPMONITOR;

// ---- FONCTIONS ---- //

/**
  @brief Obtient les identifiants des robots puis initialise le père et le serveur et leur fournit les addresses ip
  @return int, 1 si tout s'est bien passé, 0 sinon
*/
int init();

/**
  @brief Crée le processus père et lui fournit les addresses ip des robots
  @return int, 1 si tout s'est bien passé, 0 sinon
*/
/**
  @brief Crée le serveur de communication et lui fournit les addresses ip des robots
  @return int, 1 si tout s'est bien passé, 0 sinon
*/
#endif
