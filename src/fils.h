#ifndef DEF_FILS
#define DEF_FILS

/**
 * \file fils.h
 * \brief Header du fichier fils.c
 *
 * Le fichier fils.c gère les processus qui permettent aux pilotes de saisir les coordonnées ainsi que le passage
 * du jeton entre eux.
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

// Temps + jeton
#include <time.h>

// SIGTERM
#include <signal.h>

// Base
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "serveur.h"


// ---- CONSTANTES ---- //
const int LONGUEUR_GRILLE;
const int LARGEUR_GRILLE;
const int TAILLE_JETON;
const char* SALT;
const int DELAI_SAISIE;
const int NOMBRE_JOUEURS;

// ---- FONCTIONS ---- //

/**
    @brief génère un token ring de 6 modules fils. Les fils écrivent dans fd[1] et lisent dans fd[0].
    @return int, 1 si tout s'est bien passé, 0 sinon
*/
int creerFils();

/**
    @brief Algorithme de comportement d'un fils
    @param int num, le numéro du fils
    @param char* jeton, le jeton que le fils possède
*/
void act(int num, char* jeton);

/**
    @brief permet la saisie de deux entiers dans un tableau.
    @return int*, [x,y] avec x la coordonnée en longueur et y en largueur si tout s'est bien passé, [-1,-1] sinon
*/
int* saisirXY();

/**
    @brief permet la saisie d'un entier au clavier
    @return int, l'entier saisi au clavier
*/
int saisirInt();

/**
    @brief créer un jeton permettant de saisir des coordonnées
    @return char*, le jeton généré
*/
char* genererJeton();

/**
    @brief Bloque le premier fils tant qu'on n'a pas appuyé sur une touche du clavier (début de la partie)
*/
void signalDebutPartie();






// ---- COMMUNICATION FILS ---- //

/**
    @brief
    @param char* nomPipe, le nom du pipe
    @param char* donnees, le jeton de communication
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
