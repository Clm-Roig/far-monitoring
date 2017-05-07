// Fichier fils.c

#include "fils.h"

// ---- CONSTANTES ---- //

const int LONGUEUR_GRILLE = 10; // TODO : taille de la grille de jeu, pour éviter les saisies hors grile
const int LARGEUR_GRILLE = 10; // TODO

const char* SALT = "F6";

const char* NOM_PIPE_FF = "pipeFF-"; // TODO : inutile pour le moment, à voir comment l'implémenter

// ---- VARIABLES ---- //
char* tableauIPs[6];

// ---- FONCTIONS ---- //

int creerFils(char** tab) {
    // Recopie du tableau des IPs
    int i = 0;
    for(i=0; i<6 ; i++) {
        tableauIPs[i] = malloc(6*20*sizeof(char));
        memcpy(tableauIPs[i], tab[i], strlen(tab[i])+1);
    }

    // Mise en place du Token Ring
    // cf "Unix Systems Programming", chapitre 7, page 286

    pid_t childpid;     /* indicates process should spawn another     */
    int error;          /* return value from dup2 call                */
    int fd[2];          /* file descriptors returned by pipe          */
    int nprocs = 6;     /* total number of processes in ring          */

    if (pipe (fd) == -1) {      /* connect std input to std output via a pipe */
       perror("Erreur création premier pipe Token Ring.");
       return 1;
    }

    if ((dup2(fd[0], STDIN_FILENO) == -1) ||
        (dup2(fd[1], STDOUT_FILENO) == -1)) {
       perror("Erreur connection pipe.");
       return 1;
    }

    if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) {
       perror("Erreur fermeture descripteur de fichier.");
       return 1;
    }

    for (i = 1; i < nprocs;  i++) {         /* create the remaining processes */
        if (pipe (fd) == -1) {
            fprintf(stderr, "[%ld]: erreur création pipe %d: %s\n",
                (long)getpid(), i, strerror(errno));
            return 1;
        }

        if ((childpid = fork()) == -1) {
            fprintf(stderr, "[%ld]: erreur création fils pid %d: %s\n",
                (long)getpid(), i, strerror(errno));
            return 1;
        }

        if (childpid > 0) {               /* for parent process, reassign stdout */
            error = dup2(fd[1], STDOUT_FILENO);
        }
        else {                              /* for child process, reassign stdin */
            error = dup2(fd[0], STDIN_FILENO);
        }

        if (error == -1) {
            fprintf(stderr, "[%ld]: erreur dup pipe %d: %s\n",
                (long)getpid(), i, strerror(errno));
            return 1;
        }
        if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) {
            fprintf(stderr, "[%ld]: erreur fermeture descripteurs %d: %s\n",
                (long)getpid(), i, strerror(errno));
            return 1;
        }
        if (childpid)
        break;
    }

    fprintf(stderr, "This is process %d with ID %ld and parent id %ld\n",
        i, (long)getpid(), (long)getppid());

    // Le premier fils génère un token puis tout le monde attend
    if (i == 1) {
        char* token = genererToken();
        fprintf(stderr,"\nTOKEN : %s",token);
    }
    return 0;
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
    time_t seconds;
    seconds = time(NULL);
    char* token = malloc(32*sizeof(char));
    sprintf(token,"%ld",seconds*5+42 + seconds%2*23);
    return token;
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
    readInPipe(descPipe,donneesLues);
    return donneesLues;
}
