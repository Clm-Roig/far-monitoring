// Fichier pere.c

#include "pere.h"

// ---- CONSTANTES ---- //
const char* NOM_PIPE_PF = "pipePF-"; // TODO : inutile pour le moment, à voir comment l'implémenter
const char* NOM_PIPE_FF = "pipeFF-"; // TODO : inutile pour le moment, à voir comment l'implémenter 
// ---- FONCTIONS ---- //
int* tableauPID [6];

// CREATION
int creerPere(char** tabIPs) {
    
    for (int i = 0; i <6; i++)    
    {
        tableauPID[i] = fork();
        
    }
}

char* genererToken() {
    return "toto";
}

// COMMUNICATION AVEC LES FILS
int pereEnvoiFils(int numFils, char* donnees){
    return 1;
}

char* pereReceptionFilsChar(int numFils) {
    return "toto";
}

int pereReceptionFilsInt(int numFils) {
    return 1;    
}

//COMMUNICATION AVEC LE SERVEUR

int pereEnvoie
