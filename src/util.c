// Fichier util.c

#include "util.h"

// ---- CONSTANTES ---- //

// ---- FONCTIONS ---- //

int initSocket(int port, char* IP) {
    int sock;
    struct sockaddr_in sin;

    // Creation de la socket
    errno = 0;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    // Erreur création socket ?     
    if (errno) {
        printf("Erreur création socket (initSocket() dans util.c.",IP);
        perror();
        exit(-1);
    }

    // Configuration de la connexion 
    sin.sin_family = AF_INET;

    // Calcul de l'IP de l'hote (pas nécessaire ici)
    // struct hostent *hostinfo;
    // hostinfo = gethostbyname(url); 

    if (hostinfo) {
        struct in_addr **pptr;
        char** adr; 
        adr[0] = IP;
        pptr = (struct in_addr **)adr;
        sin.sin_addr = **pptr;
        printf("Adresse IP de l'hote : %s\n",inet_ntoa(sin.sin_addr));
    }

    sin.sin_port = htons(strtoul(port,NULL,10));
    
    // Tentative de connexion au serveur 
    errno = 0;
    connect(sock, (struct sockaddr*)&sin, sizeof(sin));

    // Erreur connexion ?     
    if (errno) {
        printf("Erreur initialisation socket (initSocket() dans util.c sur l'adresse %s",IP);
        perror();
        exit(-1)
    }
    
    printf("Connexion à %s sur le port %d réussie.\n", inet_ntoa(sin.sin_addr),
         htons(sin.sin_port));   
    
    return socket;
}

int sendtoSocket(int socket, char* data) {
    return 1;    
}
