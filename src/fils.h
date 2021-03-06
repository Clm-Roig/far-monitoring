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

// Temps + jeton
#include <time.h>

// Processus
#include <signal.h>
#include <sys/wait.h>

// Base
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "client.h"


// ---- CONSTANTES ---- //
const int LONGUEUR_GRILLE;
const int LARGEUR_GRILLE;
const int TAILLE_JETON;
const int DELAI_SAISIE;
const int NOMBRE_JOUEURS;
const char* CHEMIN_COORDONNEES;

// ---- FONCTIONS ---- //

/**
    @brief génère un token ring de 6 modules fils. Les fils écrivent dans fd[1] et lisent dans fd[0].
    @param tabIPs, le tableau des IPs des robot
    @return int, 1 si tout s'est bien passé, 0 sinon
*/
int creerFils(char** tabIPs);

/**
    @brief Algorithme de comportement d'un fils
    @param int num, le numéro du fils
    @param char* jeton, le jeton que le fils possède
*/
void act(int num, char* jeton);

// ==== SIGNAUX ==== //
/**
    @brief Traitement du signal SIGCHLD envoyé depuis act()
    au fils 0.
*/
void unFilsTermine();

/**
    @brief Traitement du signal SIGUSR1 envoyé depuis saisirInfos()
*/
void lireFichierCoords();

/**
    @brief Traitement du signal SIGTERM envoyé depuis act() par le fils 0
*/
void termChild();

// ==== Fin signaux ==== //

/**
    @brief permet la saisie pendant DELAI_SAISIE secondes de deux entiers et d'une information diverse
*/
void saisirInfos();

/**
    @brief permet la saisie d'un entier au clavier
    @return int, l'entier saisi au clavier
*/
int saisirInt();

/**
    @brief permet la saisie d'une string au clavier
    @return string, la string saisie au clavier
*/
char* saisirString();

/**
    @brief créer un jeton permettant de saisir des coordonnées
    @return char*, le jeton généré
*/
char* genererJeton();

/**
    @brief Bloque le premier fils tant que la partie n'a pas commencé
*/
void signalDebutPartie();

#endif
