// Fichier init.c

#include "init.h"

// ---- CONSTANTES ---- //
const int PORT = 2000;
const char* IPMONITOR; // TODO : IP du serveur de monitoring

// ---- FONCTIONS ---- //

int init() {
    int sock = initSocket(PORT, IPMONITOR);

    //FAIRE BOUCLE POUR RECEVOIR LES DONNEES DE LA SOCKET
    char buffer[512]; // Contient les addresses IP
    receiveFromSocket(sock, &buffer);
    for (int i = 0; i<6; i++) {
    //TODO Traitement et mise des addresses IP dans un tableau d'addresses char** addrIp
    }

    //TODO initPere enverra aussi le tableau des 6 addresses IP au père
    initPere(&AddrIp);

    //TODO initServer enverra aussi le tableau des 6 addresses IP au serveur
    initServeur(&AddrIp);

    return 1;
}

int initPere(char** addrIp) {
    return 0;
}

int initServeur(char** addrIp) {
    return 0;
}
