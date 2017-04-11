#ifndef DEF_PERE
#define DEF_PERE

/**
 * \file pere.h
 * \brief Header du fichier pere.c
 *
 * Le fichier pere.c gère les processus fils (qui s'occupent de la saisie de coordonnées) et
 * communique ces coordonnées au serveur. Il s'occupe également de gérer les tokens et de contrôler
 * que ceux-ci transitent correctement.
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

// Gestion du temps
#include <time.h>

// ---- CONSTANTES ---- //
const char* NOM_PIPE_PF;    // Pipe Père-Fils
const char* NOM_PIPE_FF;    // Pipe Fils-Fils


// ---- FONCTIONS ---- //

// INITIALISATION
/**
    @brief créer le serveur de position à partir d'un tableau de 6 IPs de robots
    @param char** tabIPs, le tableau des IPs des robots
    @return int, 1 si tout s'est bien passé, -1 sinon
*/
int creerServeur(char** tabIPs);

// TOKEN
/**
    @brief créer un token permettant de saisir des coordonnées
    @return char*, le token généré
*/
char* genererToken();

// COMMUNICATION AVEC LES FILS
/**
    @brief envoie une string au fils ciblé
    @param int numFils, le fils auquel on souhaite envoyer la donnée
    @param char* donnees, la string à envoyer au fils
    @return int, 1 si tout s'est bien passé, -1 sinon
*/
int pereEnvoiFils(int numFils, char* donnees);

/**
    @brief envoie une string au fils ciblé
    @param int numFils, le fils auquel on souhaite envoyer la donnée
    @return char*, la string envoyée par le fils
*/
char* pereReceptionFils(int numFils);


#endif
