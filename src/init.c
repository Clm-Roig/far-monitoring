// Fichier init.c

#include "init.h"

// ---- CONSTANTES ---- //
const int PORT = 2000;

// ---- FONCTIONS ---- //
int errno = 0;

int init() {
    //int verif = initSocket(PORT);
    int nul = 5/0;
    if (errno != 0) 
    {
        fprintf("Erreur d'initialisation de socket: %s.\n", strerror(errno));
    }
    return 1;
}
