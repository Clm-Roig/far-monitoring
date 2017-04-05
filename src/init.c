// Fichier init.c

#include "init.h"

// ---- CONSTANTES ---- //
const int PORT = 2000;
const char* IPMONITOR; //TO DO
// ---- FONCTIONS ---- //
int errno = 0;

int initPere(char** addrIp)
{

}
    
int initServeur(char** addrIp)
{
    
}

int init() {
    int sock = initSocket(PORT, IPMONITOR);
    //FAIRE BOUCLE POUR RECEVOIR LES DONNEES DE LA SOCKET
    char buffer[512]; // Contient les addresses IP
    recieveFromSocket(sock, &buffer);
    for (int i = 0; i<6; i++)
    {
    //Traitement et mise des addresses IP dans un tableau d'adresses char** addrIp
    }
    //initPere enverra aussi le tableau des 6 adresses IP au père
    initPere(&AddrIp);
    
    //initServer enverra aussi le tableau des 6 adresses IP au serveur
    initServeur(&AddrIp);
    
    return 1;
}
