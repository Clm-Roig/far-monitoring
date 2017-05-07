#ifndef DEF_FILS
#define DEF_FILS

/**
 * \file fils.h
 * \brief Header du fichier fils.c
 *
 * Le fichier fils.c gère les processus qui permettent aux pilotes de saisir les coordonnées ainsi que le passage
 * du token entre eux.
 * Il permet également d'envoyer les coordonnées saisies aux robots.
 */

// Sockets / HTTP / IP
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// Threads
#include <pthread.h>

// Temps + Token
#include <time.h>

// Base
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"


// ---- CONSTANTES ---- //
const int LONGUEUR_GRILLE;
const int LARGEUR_GRILLE;
const char* SALT;

// ---- FONCTIONS ---- //

/**
    @brief génère 6 modules fils, 1 par robot, en forkant()
    @return int, 1 si tout s'est bien passé, 0 sinon
*/
int creerFils();

/**
    @brief permet la saisie de deux entiers dans un tableau.
    @return int*, [x,y] avec x la coordonnée en longueur et y en largueur si tout s'est bien passé, [-1,-1] sinon
*/
int* saisirCoord();

// TOKEN
/**
    @brief créer un token permettant de saisir des coordonnées
    @return char*, le token généré
*/
char* genererToken();


// ---- COMMUNICATION FILS ---- //

/**
    @brief
    @param char* nomPipe, le nom du pipe
    @param char* donnees, le token de communication
    @return int, 0 si tout s'est bien passé, 1 sinon
*/
int filsEnvoiFils(char* nomPipe, char* donnees);

/**
    @brief
    @param char* nomPipe, le nom du pipe
    @return char*, le jeton de communication
*/
char* filsReceptionFils(char* nomPipe);


// ---- COMMUNICATION SERVEUR ---- //

/**
    @brief Envoie une string au serveur de communication
    @param char* donnees, la string à envoyer au serveur
    @return int, 1 si tout s'est bien passé, -1 sinon
*/
int filsEnvoiServeur(char* donnees);

/**
    @brief Envoie une string au serveur de communication
    @return char*, la string envoyée par le serveur
*/
char* filsReceptionServeur();

#endif
