
#ifndef DEF_SERVEUR_ROBOT_POSITION_UTIL
#define DEF_SERVEUR_ROBOT_POSITION_UTIL

/**
* \file serveurRobotPositionUtil.h
* \brief Header du fichier serveurRobotPositionUtil.c
*
* Le fichier serveurRobotPositionUtil.c comprend de nombreuses fonctions utiles au serveur du robot.
*/

// Sockets / HTTP / IP
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// Erreurs
#include <errno.h>

// Base
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---- FONCTIONS ---- //

// Sockets
/**
    @brief crée + connecte un socket sur le port demandé (protocole IP) par IP ou URL (l'un doit être  initialisé à "null" pour pouvoir utiliser l'autre)
    @param int port : le port sur lequel l'on doit se connecter
    @param char* IP : l'ip sur laquelle on veut se connecter
    @return int, le socket créé et connecté, -1 si la création échoue
*/
int initSocket(int port, char* IP);


/**
    @brief reçoit des données par un socket
    @param int socket : le socket sur lequel on reçoit les données
    @param char** buffer : l'adresse du buffer à remplir
    @return bool, 1 si ok, -1 sinon
*/
int receiveFromSocket(int socket, char** buffer);


// Communication Beebotte
/**
    @brief Vérifie si la partie est terminé
    @return int, 1 si la partie est terminée, 0 sinon
*/
int checkFinPartie();
