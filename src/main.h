#ifndef DEF_MAIN
#define DEF_MAIN

/**
 * \file main.h
 * \brief Header du fichier main.c
 *
 * Le fichier main.c est la porte d'entrée du programme. 
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
    @brief Fonction principale (porte d'entrée) du projet
    @return int, 0 si tout s'est bien passé
*/
 int main(int argc,char* args[]);

#endif
