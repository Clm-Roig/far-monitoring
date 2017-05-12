#ifndef DEF_SERVEUR
#define DEF_SERVEUR

/**
 * \file serveur.h
 * \brief Header du fichier serveur.c
 *
 * Le fichier serveur.c gère la communication avec les robots.
 */


// Sockets / HTTP / IP
#include <netdb.h>
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
  @brief Initialisation du serveur
  @param int addrIp, Le tableau des adresses IP des robots
  @return int, 1 si tout s'est bien passé, 0 sinon
*/
int creerServeur(char** addrIp);

/**
  @brief Envoi des logs de coordonnées sur dweet.io
  @param donnees, les donnees à envoyer sous forme de log
  @return int, 1 si tout s'est bien passé, 0 sinon

*/
int envoiDweet(char* donnees);

/**
  @brief Envoi des donnes à un robot
  @param int* donnees, les données à envoyer au robot
  @param char* addrRobot, l'adresse IP du robot auquel on envoie les coordonnées
  @return int, 1 si tout s'est bien passé, 0 sinon
*/
int envoiRobot(char* donnees, char* addrRobot);

/**
    @brief Vérifie si la partie a commencé
    @return int, 1 si la partie a commencé, 0 sinon
*/
int checkDebutPartie();

#endif
