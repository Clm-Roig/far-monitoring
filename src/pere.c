// Fichier pere.c

#include "pere.h"

// ---- CONSTANTES ---- //
const char* NOM_PIPE_PF = "pipePF-";
const char* NOM_PIPE_FF = "pipeFF-";

// ---- FONCTIONS ---- //

// CREATION
int creerServeur() {
    return 1;
}

int creerPipeW(char* nomPipe) {
    return 1;
}

int creerPipeR(char* nomPipe) {
    return 1;
}


// COMMUNICATION AVEC LES FILS

int pereEnvoiFils(int numFils, char* donnees){
    return 1;
}

char* pereReceptionFils(int numFils) {
    return "toto";
}   
