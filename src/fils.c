// Fichier fils.c

#include "fils.h"

// ---- CONSTANTES ---- //

const int LONGUEUR_GRILLE = 11; // TODO : taille de la grille de jeu, pour éviter les saisies hors grile
const int LARGEUR_GRILLE = 7; // TODO

const int TAILLE_JETON = 32;
const int DELAI_SAISIE = 20; // Délai avant de passer le jeton à un frère
const int NOMBRE_JOUEURS = 6;

const char* CHEMIN_COORDONNEES = "data/coordonnees.txt";

// ---- VARIABLES ---- //
char* tableauIPs[6];
int keyboard;
int* coordSaisies;
char* diversSaisi;
pid_t childpid;
pid_t childSaisiePid;

char* canalBeebotteCoord = "GPpartie0";

// ---- FONCTIONS ---- //

int creerFils(char** tab) {
    // Initialisation des variables
    int i = 0;
    for(i=0; i<NOMBRE_JOUEURS ; i++) {
        tableauIPs[i] = tab[i];
    }

    coordSaisies = malloc(2*sizeof(int));
    coordSaisies[0] = -1;
    coordSaisies[1] = -1;
    diversSaisi = malloc(64*sizeof(char));

    // Mise en place du Token Ring
    // cf "Unix Systems Programming", chapitre 7, page 286
    int error;                          /* return value from dup2 call                */
    int* fd = malloc(2*sizeof(int));    /* file descriptors returned by pipe          */
    int nprocs = NOMBRE_JOUEURS;        /* total number of processes in ring          */

    keyboard = dup(STDIN_FILENO);

    // New pipe
    if (pipe (fd) == -1) {      /* connect std input to std output via a pipe */
       perror("Erreur création premier pipe Token Ring.");
       return 1;
    }

    // dup2
    if ((dup2(fd[0], STDIN_FILENO) == -1) ||
        (dup2(fd[1], STDOUT_FILENO) == -1)) {
       perror("Erreur connexion pipe.");
       return 1;
    }

    // Close I/O std
    if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) {
       perror("Erreur fermeture descripteur de fichier.");
       return 1;
    }
    // =================== //

    for (i = 0; i < nprocs-1;  i++) {         /* create the remaining processes */

        // New pipe + fork
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
        else {                  /* for child process, reassign stdin + handle SIGTERM */
            signal(SIGUSR2, termChild);
            error = dup2(fd[0], STDIN_FILENO);
        }
        if (error == -1) {
            fprintf(stderr, "[%ld]: erreur dup pipe %d: %s\n",(long)getpid(), i, strerror(errno));
            return 1;
        }
        // =================== //

        // Close I/O std
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

    while(!checkFinPartie()){

        // Attente de réception d'un jeton
        if(strcmp(copyJeton,"") == 0) {
            read(STDIN_FILENO,copyJeton,TAILLE_JETON*sizeof(char)+1);
            if(errno != 0) {
                perror("\nErreur réception jeton");
            }
        }

        // saisirInfos() est bloquant et gère le temps écoulé
        fprintf(stderr,"\n\n=============================\nRobot n°%d (IP = %s) à ton tour !",num,tableauIPs[num]);
        saisirInfos();

        // Envoi des coordonnées 
        if(coordSaisies[0] != -1 && coordSaisies[1] != -1) {
            fprintf(stderr,"\nJ'envoie x = %d, y = %d et divers = %s.",coordSaisies[0],coordSaisies[1],diversSaisi);

            // Envoi Beebotte
            char* data = malloc(256*sizeof(char));
            sprintf(data,"%d,%d,%s,%s",coordSaisies[0],coordSaisies[1],diversSaisi,tableauIPs[num]);
            char* aEnvoyer [4] = {"COORD","GP","1",data};

            envoiBeebotte(aEnvoyer,canalBeebotteCoord);

            char* sendToBot = malloc(256*sizeof(char));
            sprintf(sendToBot,"%d,%d,%s",coordSaisies[0],coordSaisies[1],diversSaisi);
            
            if(envoiRobot(sendToBot,tableauIPs[num]) == 0) {
                fprintf(stderr,"\nErreur d'envoi au robot, désolé...");
            }            
            
            coordSaisies[0] = -1;
            coordSaisies[1] = -1;
        }

        // Envoi du jeton au fils suivant
        write(STDOUT_FILENO,copyJeton,TAILLE_JETON*sizeof(char)+1);
        if(errno != 0) {
            perror("Erreur envoi jeton");
        }

        strcpy(copyJeton,"");
    }

    // Le num 0 arrête les autres process
    if(num == 0) {
        kill(childpid,SIGUSR2);
        wait(NULL);
        // Traitement fin de partie ?
        fprintf(stderr,"\n\n========================");
        fprintf(stderr,"\nPartie terminée !");
        fprintf(stderr,"\n========================\n");
        exit(0);
    }

}


// ==== SIGNAUX ====/
// Fonction de traitement du signal dans saisirInfos()
void lireFichierCoords() {
    FILE* fichierCoord = fopen(CHEMIN_COORDONNEES,"r");

    char* x = lireLigne(fichierCoord,1);
    coordSaisies[0] = atoi(x);
    char* y = lireLigne(fichierCoord,2);
    coordSaisies[1] = atoi(y);
    char* divers = lireLigne(fichierCoord,3);
    diversSaisi = divers;

    fclose(fichierCoord);

    char* chemin;
    chemin = malloc(sizeof(CHEMIN_COORDONNEES));
    strcpy(chemin,CHEMIN_COORDONNEES);
    nettoyerFichier(chemin);
}

void termChild() {
    fprintf(stderr,"\nProc %d stoppé.",getpid());
    if(childpid != 0) {
        kill(childpid,SIGUSR2);
        wait(NULL);
        kill(childSaisiePid,SIGUSR2);
        wait(NULL);
    }
    kill(getpid(),SIGKILL);
}

// ==== fin Signaux ==== //


void saisirInfos() {
    int pid = fork();

    coordSaisies[0] = -1;
    coordSaisies[1] = -1;

    if(pid == 0) { // Saisie depuis le fils

        do {
            signal(SIGUSR2, termChild);
            dup2(keyboard,STDIN_FILENO);

            // Coord X
            fprintf(stderr,"\nVeuillez entrer la coordonnée X : ");
            int x = saisirInt();

            // Coord Y
            fprintf(stderr,"Veuillez entrer la coordonnée Y : ");
            int y = saisirInt();

            // Coord Y
            fprintf(stderr,"Veuillez entrer une information diverse : ");
            char* divers = saisirString();

            // Contrôle des valeurs
            if(x<0 || x > LONGUEUR_GRILLE) {
                fprintf(stderr,"\nErreur, la coordonnées x saisie est hors grille.");
            }
            else if(y<0 || y > LONGUEUR_GRILLE) {
                fprintf(stderr,"\nErreur, la coordonnées y saisie est hors grille.");
            }
            else {
                coordSaisies[0] = x;
                coordSaisies[1] = y;
                diversSaisi = divers;
            }
        } while(coordSaisies[0]==-1 || coordSaisies[1]==-1);

        // formatage des données
        char buffer[512] = "";
        sprintf(buffer,"%d\n%d\n%s",coordSaisies[0],coordSaisies[1],diversSaisi);

        // écriture dans le fichier
        FILE* fichierCoord = fopen(CHEMIN_COORDONNEES,"w");
        fprintf(fichierCoord,"%s",buffer);
        fclose(fichierCoord);

        kill(getppid(),SIGUSR1);

        exit(0);
    }
    else {  // Le père contrôle le temps passé
        childSaisiePid = pid;

        // fprintf(stderr,"\nCPID = %d et FSaisiePID = %d",childpid,pid);

        signal(SIGUSR1,lireFichierCoords);
        // Wait for avec vérification
        unsigned int retTime = time(0) + DELAI_SAISIE;
        int affichage = 0;
        while (time(0) < retTime && coordSaisies[0] == -1 && coordSaisies[1] == -1) {
            if(time(0) == (retTime - 5) && !affichage) {
                fprintf(stderr,"\nAttention il ne vous reste plus que 5 secondes !\n\n");
                affichage = 1;                
                fprintf(stderr,"Veuillez entrer la dernière information demandée plus haut : ");
               

            }
        }
        if(coordSaisies[0] == -1 || coordSaisies[1] == -1) {
            kill(childSaisiePid,SIGTERM);
            fprintf(stderr,"\nTemps écoulé, saisie stoppée.");
        }
        wait(NULL);
    }
}



int saisirInt() {
    /*  Saisie sécurisée par fgets()
        Voir https://openclassrooms.com/courses/realiser-des-saisies-securisees-grace-a-fgets
        pour plus d'informations.
    */

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

char* saisirString() {
    /*  Saisie sécurisée par fgets()
        Voir https://openclassrooms.com/courses/realiser-des-saisies-securisees-grace-a-fgets
        pour plus d'informations.
    */

    char* x = malloc(128*sizeof(char));
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

    return x;
}

void signalDebutPartie() {
    fprintf(stderr,"\n===========================");
    fprintf(stderr,"\nEn attente du début de la partie...");

    // Vérification si la partie a commencé toutes les secondes
    while (!checkDebutPartie()){
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
