// Fichier fils.c

#include "fils.h"

// ---- CONSTANTES ---- //

const int LONGUEUR_GRILLE = 10; // TODO : taille de la grille de jeu, pour éviter les saisies hors grile
const int LARGEUR_GRILLE = 10; // TODO

// ---- FONCTIONS ---- //

int creerFils() {
    return 1;
}

// ---- COMMUNICATION PERE ---- //

int filsEnvoiPere(char* nomPipe, char* donnees) {
    return 1;
}

char* filsReceptionPere(char* nomPipe) {
    return "toto";
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


// ---- COMMUNICATION FILS ---- //

int filsEnvoiFils(char* nomPipe, char* donnees) {
    int descPipe = openPipeW(nomPipe);
    
    // TODO : boucle while(donnees) pas totalement envoyée
    int nbBytes = writeInPipe(descPipe,donnees);
    return 1;
}

char* filsReceptionFils(char* nomPipe) {
    int descPipe = openPipeR(nomPipe);
    char* donneesLues = malloc(TAILLE_MESSAGE*sizeof(char));
    int nbBytes = readInPipe(descPipe,donneesLues);    
    return donneesLues;
}
