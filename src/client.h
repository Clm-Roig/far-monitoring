#ifndef DEF_CLIENT
#define DEF_CLIENT

/**
 * \file client.h
 * \brief Header du fichier client.c
 *
 * Le fichier client.c gère la communication avec les robots.
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
  @brief Envoi des logs de coordonnées sur dweet.io
  @param x, Les coordonnées saisies pour x
  @param y, les coordonnées saisies pour y
  @param AddrIpEnvoi, l'adresse IP correspondant au robot
  @return int, 1 si tout s'est bien passé, 0 sinon
*/
int envoiDweet(int x, int y, char* AdrIpEnvoi);

/**
  @brief Envoi des donnes à un robot
  @param int* donnees, les données à envoyer au robot
  @param char* addrRobot, l'adresse IP du robot auquel on envoie les coordonnées
  @return int, 1 si tout s'est bien passé, 0 sinon
*/
int envoiRobot(char* donnees, char* addrRobot);

/**
    @brief Envoie un tableau de données sur Beebotte
    @param char* data[], le tableau des données 
          => case 0 : type_msg
          => case 1 : type_ent 
          => case 2 : num
          => case 3 : data
    @return int, 0 si tout s'est bien passé
*/
int envoiBeebotte(char *data[]);

/**
    @brief Vérifie si la partie a commencé
    @return int, 1 si la partie a commencé, 0 sinon
*/
int checkDebutPartie();

/**
    @brief Vérifie si la partie est terminé
    @return int, 1 si la partie est terminée, 0 sinon
*/
int checkFinPartie();

#endif
