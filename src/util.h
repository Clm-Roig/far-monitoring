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
#include <netdb.h>

// Pipes
#include <sys/stat.h> 
#include <fcntl.h>

// Erreurs
#include <errno.h>

// Base
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>


// ---- CONSTANTES ---- //
const char* CHEMIN_PIPE;
const int TAILLE_MESSAGE_PIPE;

// ---- FONCTIONS ---- //

// Sockets
/**
    @brief crée + connecte un socket sur le port demandé (protocole IP) par IP ou URL (l'un doit être  initialisé à "null" pour pouvoir utiliser l'autre)
    @param int port : le port sur lequel l'on doit se connecter
    @param char* IP : l'ip sur laquelle on veut se connecter
    @param char* URL : l'url sur laquelle on souhaite se connecter
    @return int, le socket créé et connecté, -1 si la création échoue
*/
int initSocket(int port, char* IP, char* URL);

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

// FICHIERS

/**
    @brief compte le nombre de lignes que contient un fihcier
    @param FILE* fichier, le fichier que l'on souhaite analyser
    @return int, le nombre de lignes du fichier
*/
int nbLignesFichier(FILE* fichier);

/**
    @brief lit la ligne n du fichier
    @param FILE* fichier, le fichier que l'on souhaite ouvrir
    @param int n, la ligne que l'on souhaite lire
    @return char*, la chaine de caractères représentant la ligne lue
*/
char* lireLigne(FILE* fichier, int n);

/**
    @brief vide un fichier
*/
void nettoyerFichier(char* chemin);


// MISC

/**
    @brief Bloque le processus pendant secs secondes
    @param int secs, le nb de secondes
*/
void waitFor(unsigned int secs);

#endif
