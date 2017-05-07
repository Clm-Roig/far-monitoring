 // Fichier clientutil.c

 #include "clientutil.h"

  // ---- FONCTIONS ---- //

int initSocket(int port, char* IP) {
    return 0;
}

int receiveFromSocket(int socket, char** data) {
    recv(socket,&data,sizeof(&data)-1,0);
    // Erreur ?
    if(errno) {
        printf("\nErreur reception données socket (receiveFromSocket() dans utilclient.c) par le socket %d", socket);
        perror("");
        exit(-1);
    }
    return 0;
}
