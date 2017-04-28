// Fichier init.c

#include "init.h"

// ---- CONSTANTES ---- //
const int PORT = 2000;
const char* IP_MONITOR; // TODO : IP du serveur de monitoring
const char* PIPE_PERE_SERVEUR = "PS";
const char* PIPE_SERVEUR_PERE = "SP";

// ---- FONCTIONS ---- //

int init() {
    int sock = initSocket(PORT, IP_MONITOR);

    //FAIRE BOUCLE POUR RECEVOIR LES DONNEES DE LA SOCKET
    char* buffer = malloc(sizeof(char)*512);  // Contient les addresses IP
    receiveFromSocket(sock, &buffer);
    for (int i = 0; i<6; i++) {
    //TODO Traitement et mise des addresses IP dans un tableau d'addresses char** addrIp
    }

    initPere(&AddrIp);
    initServeur(&AddrIp);
    
    free(buffer);
    return 1;
}

int initPere(char** addrIp) {
    creerPere(&addrIp);
    char* cheminPS = creerPipe(PIPE_PERE_SERVEUR);
    return 0;
}

int initServeur(char** addrIp) {
    creerServeur(&addrIp);
    char* cheminSP = creerPipe(PIPE_SERVEUR_PERE);
    return 0;
}
