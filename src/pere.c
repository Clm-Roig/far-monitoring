// Fichier pere.c

#include "pere.h"

// ---- CONSTANTES ---- //
const char* NOM_PIPE_PF = "pipePF-"; // TODO : inutile pour le moment, à voir comment l'implémenter
const char* NOM_PIPE_FF = "pipeFF-"; // TODO : inutile pour le moment, à voir comment l'implémenter

// ---- FONCTIONS ---- //

// CREATION
int creerPere(char** tabIPs) {
    return 1;
}

// COMMUNICATION AVEC LES FILS
int pereEnvoiFils(int numFils, char* donnees){
    return 1;
}

char* pereReceptionFils(int numFils) {
    return "toto";
}
