// Fichier pere.c

#include "pere.h"

// ---- CONSTANTES ---- //
const char* NOM_PIPE_PF = "pipePF-"; // TODO : inutile pour le moment, à voir comment l'implémenter
const char* NOM_PIPE_FF = "pipeFF-"; // TODO : inutile pour le moment, à voir comment l'implémenter

// ---- FONCTIONS ---- //

// CREATION
int creerServeur(char** tabIPs) {
    return 1;
}

char* creerPipeW(char* nomPipe) {
    errno = 0;
    char* pipeName = malloc(64*sizeof(char));
    strcat(pipeName,nomPipe);
    // Par convention, les tubes nommés se terminent par .fifo
    strcat(pipeName,".fifo");

    // Création du tube avec tous les droits pour tout le monde (USER, GROUP et OTHERS)
    if (mkfifo((pipeName), S_IRWXU | S_IRWXG | S_IRWXO) == -1) {
        printf("Erreur création tube nommé (creerPipeW() dans pere.c).");
        perror("");
        exit(EXIT_FAILURE);
    }

    // Ouverture du tube en écriture
    if (open(pipeName,O_WRONLY) == -1) {
        printf("Erreur ouverture tube nommé (creerPipeW() dans pere.c).");
        perror("");
        exit(EXIT_FAILURE);
    }

    return pipeName;
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
