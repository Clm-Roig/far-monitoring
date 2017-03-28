// Fichier init.c

#include "init.h"

// ---- CONSTANTES ---- //
const int PORT = 2000;

// ---- FONCTIONS ---- //
int errno = 0;

int initPere(char* addrIp)
{

}
    
int initServeur(char* addrIp)
{
    
}


int init() {
    int verif = initSocket(PORT);
    if (errno != 0) 
    {
        (void)fprintf(stderr,"Erreur d'initialisation de socket: %s.\n", strerror(errno)); // A TESTER
    }
    //FAIRE BOUCLE POUR RECEVOIR LES DONNEES DE LA SOCKET
    char* addrIp[100] // Contient les addresses IP
    //fermer la socket
    //initPere enverra aussi le tableau des 6 adresses IP au père
    initPere();
    //initServer enverra aussi le tableau des 6 adresses IP au serveur
    initServeur();
    
    return 1;
}
