#ifndef DEF_UTIL
#define DEF_UTIL

/**
* \file util.h
* \brief Header du fichier util.c
*
* Le fichier util.c comprend de nombreuses fonctions utiles au programme. 
*/

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
@brief créer + connecte un socket sur le port demandé (protocole IP)
@param int port : le port sur lequel l'on doit se connecter
@param char* IP : l'ip sur laquelle on veut se connecter 
@return int, le socket créé et connecté, -1 si la création échoue
*/
int initSocket(int port, char* IP);

/**
@brief envoie des données par un socket
@param int socket : le socket sur lequel on envoie les données
@param char* data : la String à envoyer
@return bool, 1 si ok, 0 sinon
*/
int sendToSocket(int socket, char* data);


#endif
