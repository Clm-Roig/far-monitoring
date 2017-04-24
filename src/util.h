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

// Pipes
#include <sys/stat.h> // mkfifo
#include <fcntl.h> // open()

// Erreurs
#include <errno.h>

// Base
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ---- CONSTANTES ---- //
const char* CHEMIN_PIPE;
const int TAILLE_MESSAGE_PIPE;

// ---- FONCTIONS ---- //

// Sockets
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
@return bool, 1 si ok, -1 sinon
*/
int sendToSocket(int socket, char* data);

/**
@brief reçoit des données par un socket
@param int socket : le socket sur lequel on reçoit les données
@param char** buffer : l'adresse du buffer à remplir
@return bool, 1 si ok, -1 sinon
*/
int receiveFromSocket(int socket, char** buffer);


// PIPES

/**
    @brief créer un pipe nommé. Ne génère pas d'erreur si le tube existe déjà
    @param char* nomPipe, le nom du pipe dans lequel on écrira
    @return char*, le chemin vers le tube nommé créé (nomPipe.fifo)
*/
char* creerPipe(char* nomPipe);

/**
    @brief ouvre un pipe nommé en écriture
    @param char* cheminPipe, le chemin vers le pipe dans lequel on écrira
    @return int, le descripteur du pipe si ok, sinon -1
*/
int openPipeW(char* cheminPipe);

/**
    @brief ouvre un pipe nommé en lecture
    @param char* cheminPipe, le chemin vers le pipe dans lequel on lira
    @return int, le descripteur du pipe si ok, sinon -1
*/
int openPipeR(char* cheminPipe);

/**
    @brief écrit dans un pipe nommé ouvert en écriture au préalable  (voir fonction openPipe ci-dessus)
    @param int descPipe, le descripteur du pipe dans lequel on veut écrire
    @param char* data, les données à envoyer par le biais du pipe
    @return int, le nombre d'octets écrit, sinon, en cas d'erreur, -1
*/
int writeInPipe(int descPipe, char* data);

/**
    @brief lit dans un pipe nommé ouvert en lecture au préalable (voir fonction openPipe ci-dessus)
    @param int descPipe, le descripteur du pipe dans lequel on veut lire
    @param char* data, les données dans lesquelles on stockera le message lu
    @return int, le nombre d'octets lu, sinon, en cas d'erreur, -1
*/
int readInPipe(int descPipe, char* data);

#endif
