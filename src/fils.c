// Fichier fils.c

#include "fils.h"

// ---- CONSTANTES ---- //

const int LONGUEUR_GRILLE = 10; // TODO : taille de la grille de jeu, pour éviter les saisies hors grile
const int LARGEUR_GRILLE = 10; // TODO

const int TAILLE_JETON = 32;
const char* SALT = "F6"; // Sel aléatoire pour crypter le jeton
const char* NOM_PIPE_FF = "pipeFF-"; // TODO : inutile pour le moment, à voir comment l'implémenter
const int DELAI_SAISIE = 3; // Délai avant de passer le jeton à un frère
const int NOMBRE_JOUEURS = 6;

// ---- VARIABLES ---- //
char* tableauIPs[6];

// ---- FONCTIONS ---- //

int creerFils(char** tab) {
    // Recopie du tableau des IPs
    int i = 0;
    for(i=0; i<NOMBRE_JOUEURS ; i++) {
        tableauIPs[i] = malloc(NOMBRE_JOUEURS*20*sizeof(char));
        memcpy(tableauIPs[i], tab[i], strlen(tab[i])+1);
    }

    // Mise en place du Token Ring
    // cf "Unix Systems Programming", chapitre 7, page 286
    pid_t childpid;                     /* indicates process should spawn another     */
    int error;                          /* return value from dup2 call                */
    int* fd = malloc(2*sizeof(int));    /* file descriptors returned by pipe          */
    int nprocs = NOMBRE_JOUEURS;        /* total number of processes in ring          */

    if (pipe (fd) == -1) {      /* connect std input to std output via a pipe */
       perror("Erreur création premier pipe Token Ring.");
       return 1;
    }

    // ==== ERREURS ? ==== //
    if ((dup2(fd[0], STDIN_FILENO) == -1) ||
        (dup2(fd[1], STDOUT_FILENO) == -1)) {
       perror("Erreur connexion pipe.");
       return 1;
    }

    if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) {
       perror("Erreur fermeture descripteur de fichier.");
       return 1;
    }
    // =================== //

    for (i = 0; i < nprocs-1;  i++) {         /* create the remaining processes */

        // ==== ERREURS ? ==== //
        if (pipe (fd) == -1) {
            fprintf(stderr, "[%ld]: erreur création pipe %d: %s\n",(long)getpid(), i, strerror(errno));
            return 1;
        }

        if ((childpid = fork()) == -1) {
            fprintf(stderr, "[%ld]: erreur création fils pid %d: %s\n",(long)getpid(), i, strerror(errno));
            return 1;
        }
        // =================== //

        // Assignation stdin et stdout
        if (childpid > 0){      /* for parent process, reassign stdout */
            error = dup2(fd[1], STDOUT_FILENO);
        }
        else {                  /* for child process, reassign stdin */
            error = dup2(fd[0], STDIN_FILENO);
        }

        // ==== ERREURS ? ==== //
        if (error == -1) {
            fprintf(stderr, "[%ld]: erreur dup pipe %d: %s\n",(long)getpid(), i, strerror(errno));
            return 1;
        }
        if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) {
            fprintf(stderr, "[%ld]: erreur fermeture descripteurs %d: %s\n",(long)getpid(), i, strerror(errno));
            return 1;
        }
        // =================== //

        if (childpid)
        break;
    }

    // fprintf(stderr, "\nProcess %d with ID %ld and parent id %ld",i, (long)getpid(), (long)getppid());

    // Le premier fils génère un jeton puis il attend pour lancer le début de la partie
    // Les autres fils act() (en attente de jeton)
    if (i == 0) {
        char* jeton = genererJeton();
        fprintf(stderr,"\nJeton : %s",jeton);
        //signalDebutPartie();
        act(i,jeton);
    }
    else {
        char* jetonFils = malloc(TAILLE_JETON*sizeof(char));
        jetonFils = "";
        act(i,jetonFils);
    }

    return 0;
}

void act(int num, char* jeton) {
    char* copyJeton = malloc(TAILLE_JETON*sizeof(char));
    strcpy(copyJeton,jeton);
    int c=0;
    while(c < 2) {

        // Attente de réception d'un jeton
        if(strcmp(copyJeton,"") == 0) {
            read(STDIN_FILENO,copyJeton,TAILLE_JETON*sizeof(char)+1);

            if(errno != 0) {
                perror("\nErreur réception jeton");
            }

            fprintf(stderr,"\nProc n°%d vient de recevoir %s",num,copyJeton);
        }

        // On a la main, on attend une saisie
        int* coord = malloc(2*sizeof(int));

        // saisirXY() est bloquant et gère le temps écoulé
        coord = saisirXY();

        // Envoi des coordonnées au robot

        // Envoi du jeton au fils suivant
        write(STDOUT_FILENO,copyJeton,TAILLE_JETON*sizeof(char)+1);
        fprintf(stderr,"\nProc n°%d envoie %s.",num,copyJeton);
        if(errno != 0) {
            perror("Erreur envoi jeton");
        }

        strcpy(copyJeton,"");

        c++;
    }

}

int* saisirXY() {
    int pid = fork();
    int* res = malloc(2*sizeof(int));
    res[0] = -1;
    res[1] = -1;

    if(pid == 0) { // Saisie depuis le fils

        do {
            // Coord X
            fprintf(stderr,"\nVeuillez entrer la coordonnée X : ");
            int x = saisirInt();

            // Coord Y
            fprintf(stderr,"\nVeuillez entrer la coordonnée Y : ");
            int y = saisirInt();

            // Contrôle des valeurs
            if(x<0 || x > LONGUEUR_GRILLE) {
                fprintf(stderr,"\nErreur, la coordonnées x saisie est hors grille.");
            }
            else if(y<0 || y > LONGUEUR_GRILLE) {
                fprintf(stderr,"\nErreur, la coordonnées y saisie est hors grille.");
            }
            else {
                res[0] = x;
                res[1] = y;
            }
        } while(res[0]==-1 || res[1]==-1);

        kill(getppid(),SIGTERM);
        fprintf(stderr,"\n");
        return res;
    }
    else {  // Le père contrôle le temps passé
        waitFor(DELAI_SAISIE);
        // kill du fils
        kill(pid,SIGTERM);
        fprintf(stderr,"\nTemps écoulé, saisie stoppée.");
        return res;
    }

}

int saisirInt() {
    /*  Saisie sécurisée par fgets()
        Voir https://openclassrooms.com/courses/realiser-des-saisies-securisees-grace-a-fgets
        pour plus d'informations.
    */

    // TODO : ouvrir un flux stdin au clavier pour permettre la saisie

    char* x = malloc(10*sizeof(char));
    fgets(x, sizeof x, stdin);
    char *pY = strchr(x, '\n');
    // Retrait saut de ligne
    if (pY) {
        *pY = 0;
    }
    // Purge du flux stdin si saisie trop grand
    else {
        int c2;
        while ((c2 = getchar()) != '\n' && c2 != EOF){}
    }

    return atoi(x);
}

void signalDebutPartie() {
    fprintf(stderr,"\n===========================");
    fprintf(stderr,"\nEn attente du début de la partie...");

    // Vérification si la partie a commencé toutes les secondes
    while (checkDebutPartie() == 0){
        waitFor(1);
    }
}

char* genererJeton() {
    time_t seconds;
    seconds = time(NULL);
    char* jeton = malloc(TAILLE_JETON*sizeof(char));
    sprintf(jeton,"%ld",seconds*5+42 + seconds%2*23);
    return jeton;
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
