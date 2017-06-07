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

// Base
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

// ---- CONSTANTES ---- //


// ---- FONCTIONS ---- //


/**
  @brief Envoi des donnes à un robot et ferme le socket utilisé après l'envoi
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
int envoiBeebotte(char *data[], char* canal);

/**
    @brief Renvoie les données contenues dans le dernier message sur Beebotte du type spécifié
    @param char* typedonnee, le type de messages que l'on souhaite récupérer (partie "type_msg" sur Beebotte)
    @return char* les données contenues dans la partie "data" du msg
*/
char* recepBeebotte(char* typedonnee, char* canal);


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
