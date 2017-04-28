// Fichier pere.c

#include "pere.h"

// ---- CONSTANTES ---- //
const char* NOM_PIPE_PF = "pipePF-"; // TODO : inutile pour le moment, à voir comment l'implémenter
const char* NOM_PIPE_FF = "pipeFF-"; // TODO : inutile pour le moment, à voir comment l'implémenter 

// Variables
int tableauPID[6];

// ---- FONCTIONS ---- //

// CREATION
int creerPere(char** tabIPs) {
    int i = 0;
    for (i; i <6 ; i++) {
        tableauPID[i] = fork();        
    }

    
    return 1;
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

int pereEnvoiServeur(char* donnees) {
	return 1;
}

char* pereReceptionServeur() {
	return "toto";
}
