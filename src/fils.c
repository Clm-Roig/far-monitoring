// Fichier fils.c

#include "fils.h"

// ---- CONSTANTES ---- //

const int LONGUEUR_GRILLE = 10; // TODO : taille de la grille de jeu, pour éviter les saisies hors grile
const int LARGEUR_GRILLE = 10; // TODO

const char* NOM_PIPE_FF = "pipeFF-"; // TODO : inutile pour le moment, à voir comment l'implémenter 

// ---- VARIABLES ---- //
int tableauPIDs[6];
char* tableauIPs[6];

// ---- FONCTIONS ---- //

int creerFils(char** tab) {

    // Recopie du tableau des IPs
    int i = 0;
    for(i; i<6 ; i++) {        
        tableauIPs[i] = malloc(6*20*sizeof(char));
        memcpy(tableauIPs[i], tab[i], strlen(tab[i])+1);
    }

    // Fork et stockage des PIDs 

    return 1;
}

int* saisirCoord() {
    char coordX[10], coordY[10];

    /*  Saisie sécurisée par fgets()
        Voir https://openclassrooms.com/courses/realiser-des-saisies-securisees-grace-a-fgets
        pour plus d'informations.
    */

    // Coord X
    printf("\nVeuillez entrer la coordonnées X : ");
    fgets(coordX, sizeof coordX, stdin);
    char *pX = strchr(coordX, '\n');
    // Retrait saut de ligne
    if (pX) {
        *pX = 0;
    }
    // Purge du flux stdin si saisie trop grand
    else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF){}
    }

    // Coord X
    printf("\nVeuillez entrer la coordonnées Y : ");
    fgets(coordY, sizeof coordY, stdin);
    char *pY = strchr(coordY, '\n');
    // Retrait saut de ligne
    if (pY) {
        *pY = 0;
    }
    // Purge du flux stdin si saisie trop grand
    else {
        int c2;
        while ((c2 = getchar()) != '\n' && c2 != EOF){}
    }

    // Formatage du résultat
    int x = atoi(coordX);
    int y = atoi(coordY);
    int* res = malloc(2*sizeof(int));
    res[0] = x;
    res[1] = y;

    // Contrôle des valeurs
    if(x<0 || x > LONGUEUR_GRILLE) {
        printf("\nErreur, la coordonnées x saisie est hors grille.");
        res[0] = -1;
        res[1] = -1;
    }
    if(y<0 || y > LONGUEUR_GRILLE) {
        printf("\nErreur, la coordonnées y saisie est hors grille.");
        res[0] = -1;
        res[1] = -1;
    }

    return res;
}


char* genererToken() {
    return "toto";
}


// ---- COMMUNICATION FILS ---- //

int filsEnvoiFils(char* nomPipe, char* donnees) {
    int descPipe = openPipeW(nomPipe);
    
    // TODO : boucle while(donnees) pas totalement envoyée (utiliser TAILLE_MESSAGE_PIPE)    
    int nbBytesSent = 0;
    while(nbBytesSent < strlen(donnees)) {
        nbBytesSent = writeInPipe(descPipe,donnees);
    }
    return 1;
}

char* filsReceptionFils(char* nomPipe) {
    int descPipe = openPipeR(nomPipe);
    char* donneesLues = malloc(TAILLE_MESSAGE_PIPE*sizeof(char));
    int nbBytes = readInPipe(descPipe,donneesLues);    
    return donneesLues;
}
