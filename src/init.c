// Fichier init.c

#include "init.h"

// ---- CONSTANTES ---- //
const int PORT = 2000;
const char* IPMONITOR; //TO DO
// ---- FONCTIONS ---- //

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
    //TO DO Traitement et mise des addresses IP dans un tableau d'addresses char** addrIp
    }
    //TO DO initPere enverra aussi le tableau des 6 addresses IP au père
    initPere(&AddrIp);
    
    //TO DO initServer enverra aussi le tableau des 6 addresses IP au serveur
    initServeur(&AddrIp);
    
    return 1;
}
