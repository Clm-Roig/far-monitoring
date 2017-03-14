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
const char* NOM_PIPE_PF;
const char* NOM_PIPE_FF;

// ---- FONCTIONS ---- //


// CREATION
/**
    @brief créer le serveur de position à partir d'un tableau de 6 IPs de robots
    @param char** tabIPs, le tableau des IPs des robots
    @return int, 1 si tout s'est bien passé, 0 sinon 
*/
int creerServeur();
 
/**
    @brief créer un pipe nommé en écriture 
    @param char* nomPipe, le nom du pipe dans lequel on écrira 
    @return int, 1 si tout s'est bien passé, 0 sinon 
*/
int creerPipeW(char* nomPipe);

/**
    @brief créer un pipe nommé en lecture
    @param char* nomPipe, le nom du pipe dans lequel on écrira 
    @return int, 1 si tout s'est bien passé, 0 sinon 
*/
int creerPipeR(char* nomPipe);


// COMMUNICATION AVEC LES FILS
/**
    @brief envoie une string au fils ciblé 
    @param int numFils, le fils auquel on souhaite envoyer la donnée
    @param char* donnees, la string à envoyer au fils
    @return int, 1 si tout s'est bien passé, 0 sinon 
*/
int pereEnvoiFils(int numFils, char* donnees);

/**
    @brief envoie une string au fils ciblé 
    @param int numFils, le fils auquel on souhaite envoyer la donnée
    @return char*,  
*/
char* pereReceptionFils(int numFils);




#endif
