 // Fichier util.c

 #include "util.h"

// ---- CONSTANTES ---- //
const char* CHEMIN_PIPE = "./data/pipes/";
const int TAILLE_MESSAGE_PIPE = 128;

// ---- FONCTIONS ---- //


// SOCKETS

int initSocket(int port, char* IP, char* URL) {
    int sock;
    struct sockaddr_in sin;

    // Creation de la socket
    errno = 0;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Erreur création socket ?
    if (errno) {
        printf("Erreur création socket (initSocket() dans util.c).");
        perror("");
        exit(-1);
    }

    // Configuration de la connexion
    sin.sin_family = AF_INET;

    // Calcul de l'IP de l'hote (si jamais on veut utiliser un nom de domaine au lieu de l'IP)
    if(strcmp(URL,"null") != 0) {

        struct hostent *hostinfo = gethostbyname(URL);

        if (hostinfo) {
            struct in_addr **pptr;
            pptr = (struct in_addr **)hostinfo->h_addr_list;
            sin.sin_addr = **pptr;
            printf("Adresse IP de l'hote : %s\n",inet_ntoa(sin.sin_addr));
        }

    }
    else {

        // Conversion de localhost en IP
        char* newIP = malloc(64*sizeof(char));
        if(strcmp(IP,"localhost") == 0){
            strcpy(newIP,"127.0.0.1");
        }
        else {
            strcpy(newIP,IP);
        }
        sin.sin_addr.s_addr = inet_addr(newIP);
    }

    sin.sin_port = htons(port);

    // Tentative de connexion au serveur
    errno = 0;
    connect(sock, (struct sockaddr*)&sin, sizeof(sin));

    // Erreur connexion ?
    if (errno) {
     printf("\nErreur initialisation socket (initSocket() dans util.c) sur %s",IP);
     perror("");
     exit(-1);
    }
    printf("Connexion réussie sur l'IP %s sur le port %d.\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));

    return sock;
}

 int sendToSocket(int socket, char* data) {
     send(socket,data,sizeof(data),0);
     // Erreur ?
     if(errno) {
         printf("\nErreur envoi données socket (sendToSocket() dans util.c) par le socket %d", socket);
         perror("");
         exit(-1);
     }
     return 0;
 }

 int receiveFromSocket(int socket, char** data) {
     recv(socket,&data,sizeof(&data)-1,0);
     // Erreur ?
     if(errno) {
         printf("\nErreur reception données socket (receiveFromSocket() dans util.c) par le socket %d", socket);
         perror("");
         exit(-1);
     }
     return 0;
 }


// FICHIERS
int nbLignesFichier(FILE* fichier) {
    int nbLignes = 0;
    char* a = NULL;
    a = malloc(100*sizeof(char));
    while(fgets(a, 100, fichier) != NULL) {
        nbLignes++;
    }
    fseek(fichier,0,0);
    return nbLignes;
}

 char* lireLigne(FILE* fichier, int n) {
    char* res = NULL;
    res = malloc(100*sizeof(char));
    int max = nbLignesFichier(fichier);
    // On cherche la ligne correspondante
    if (fichier && n <= max) {
        while(n>0) {
            fgets(res,100,fichier);
            n--;
        }
    }
    fseek(fichier,0,0);
    return res;
}

void nettoyerFichier(char* chemin) {
    char* cheminTemp = malloc(256*sizeof(char));
    strcpy(cheminTemp,chemin);
    strcat(cheminTemp,".tmp");

    FILE* fichierTemp = fopen(cheminTemp,"a");

    fprintf(fichierTemp,"%s","");

    if(remove(chemin) != 0) {
        printf("\nErreur suppression du fichier.");
    }

    if(rename(cheminTemp,chemin) != 0) {
        printf("\nErreur rennomage du fichier temp.");
    }
    fclose(fichierTemp);
}


// MISC

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;
    while (time(0) < retTime);
}
