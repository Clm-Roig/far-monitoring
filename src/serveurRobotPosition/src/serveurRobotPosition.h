#ifndef DEF_SERVEUR_ROBOT_POSITION
#define DEF_SERVEUR_ROBOT_POSITION

/**
* \file serveurRobotPosition.h
* \brief Header du fichier serveurRobotPosition.c
*
* Le fichier serveurRobotPosition.c instancie un serveur permettant de réceptionner les coordonnées envoyées depuis le Serveur de Position.
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

#include "serveurRobotPositionUtil.h"

// ---- FONCTIONS ---- //

/**
	@brief Point d'entrée du programme.
*/
int main();

#endif
