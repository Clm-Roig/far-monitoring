// Fichier pere.c

#include "pere.h"

// ---- CONSTANTES ---- //
const char* NOM_PIPE_PF = "pipePF-";
const char* NOM_PIPE_FF = "pipeFF-";

// ---- FONCTIONS ---- //

// CREATION
int creerServeur(char** tabIPs) {
    return 1;
}

char* creerPipeW(char* nomPipe) {
    return "pipe.fifo";
}

char* creerPipeR(char* nomPipe) {
    return "pipe.fifo";
}


// COMMUNICATION AVEC LES FILS
int pereEnvoiFils(int numFils, char* donnees){
    return 1;
}

char* pereReceptionFils(int numFils) {
    return "toto";
}
