#ifndef DEF_BEEBOTTE
#define DEF_BEEBOTTE

/**
 * \file beebotte.h
 * \brief Header du fichier beebotte.c
 *
 * Le fichier beebotte.c permet d'envoyer une donnée sur Beebotte
 */

#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit, atoi, malloc, free */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */


// ---- CONSTANTES ---- //


// ---- FONCTIONS ---- //

/**
    @brief Envoie un tableau de données sur Beebotte
    @param char* data[], le tableau des données 
    			=> case 0 : type_msg
    			=> case 1 : type_ent 
    			=> case 2 : num
    			=> case 3 : data
    @return int, 0 si tout s'est bien passé
*/
int sendToBeBotte(char *data[]);

#endif
