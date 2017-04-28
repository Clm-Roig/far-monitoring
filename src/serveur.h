#ifndef DEF_SERVEUR
#define DEF_SERVEUR

/**
 * \file serveur.h
 * \brief Header du fichier serveur.c
 *
 * Le fichier serveur.c gère la communication avec les robots.
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
  @brief Initialisation du serveur
  @param int AddrIp, Le tableau des adresses IP des robots
  @return int, 1 si tout s'est bien passé, 0 sinon
*/
int creerServeur(char** AddrIp);

/**
  @brief Envoi des logs de coordonnées sur Dweet.io
  @param Coordonnees, Les coordonnées à envoyer sous forme de log
  @return int, 1 si tout s'est bien passé, 0 sinon
  
*/
int envoiDweet(int* Coordonnees);

/**
  @brief Envoi des coordonnées aux robots
  @param int* Coordonnees, Les coordonnées à envoyer au robot
  @param char* AddrRobot, l'adresse IP du robot auquel on envoie les coordonnées
  @return int, 1 si tout s'est bien passé, 0 sinon
*/
int envoiRobot(int* Coordonnees, char* AddrRobot);

#endif
