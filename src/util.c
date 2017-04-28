 // Fichier util.c
 
 #include "util.h"
  
  // ---- CONSTANTES ---- //
  const char* CHEMIN_PIPE = "./data/pipes/";
 const int TAILLE_MESSAGE_PIPE = 128;
  
  // ---- FONCTIONS ---- //
  
 
 // SOCKETS
 
 int initSocket(int port, char* IP) {
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
     /*
     struct hostent *hostinfo;
     hostinfo = gethostbyname(IP);
 
     if (hostinfo) {
         struct in_addr **pptr;
         char** adr = malloc(512*sizeof(char));
         adr[0] = IP;
         pptr = (struct in_addr **)adr;
         sin.sin_addr = **pptr;
         printf("Adresse IP de l'hote : %s\n",inet_ntoa(sin.sin_addr));
     }
     */
 
     // Conversion de localhost en IP
     char* newIP = malloc(64*sizeof(char));
     if(strcmp(IP,"localhost") == 0){
         strcpy(newIP,"127.0.0.1");
     }
     else {
         strcpy(newIP,IP);
     }
 
     // Configuration IP et port  du socket
     sin.sin_addr.s_addr = inet_addr(newIP);
     sin.sin_family = AF_INET;
     sin.sin_port = htons(port);
 
     // Tentative de connexion au serveur
     errno = 0;
     connect(sock, (struct sockaddr*)&sin, sizeof(sin));
 
     // Erreur connexion ?
     if (errno) {
         printf("\nErreur initialisation socket (initSocket() dans util.c) sur l'adresse %s",newIP);
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
 
 
 // PIPES
 
 char* creerPipe(char* nomPipe) {
     char* pipeName = malloc(64*sizeof(char));
     strcat(pipeName,CHEMIN_PIPE);
     strcat(pipeName,nomPipe);
     // Par convention, les tubes nommés se terminent par .fifo
     strcat(pipeName,".fifo");
 
     errno = 0;
     // Création du tube avec tous les droits pour tout le monde (USER, GROUP et OTHERS)
     if (mkfifo((pipeName), S_IRWXU | S_IRWXG | S_IRWXO) == -1) {
 
         // On néglige l'erreur "tube déjà existant" qui correspond à errno == 17
         if(errno != 17) {
             printf("\nErreur création tube nommé %s (creerPipe() dans util.c).",nomPipe);
             perror("");
         }
     }
 
     return pipeName;
 }
 
 int openPipeW(char* cheminPipe) {
     errno = 0;
     int desc = open(cheminPipe, O_WRONLY);
     if (desc == -1) {
         printf("\nErreur ouverture en écriture tube nommé %s (openPipeW() dans util.c).",cheminPipe);
         perror("");
         exit(-1);
     }
     return desc;
 }
 
 int openPipeR(char* cheminPipe) {
     errno = 0;
     int desc = open(cheminPipe, O_RDONLY);
     if (desc == -1) {
         printf("\nErreur ouverture en lecture tube nommé %s (openPipeR() dans util.c).",cheminPipe);
         perror("");
         exit(-1);
     }
     return desc;
 }
 
 int writeInPipe(int descPipe, char* data) {
     errno = 0;
     int nbByte = write(descPipe, data, TAILLE_MESSAGE);
     if(nbByte == -1) {
         printf("\nErreur écriture dans le tube nommé %d (writeInPipe() dans util.c).",descPipe);
         perror("");
         exit(-1);
     }
     return nbByte;
 }
 
 int readInPipe(int descPipe, char* data) {
     errno = 0;
     int nbByte = read(descPipe, data, TAILLE_MESSAGE);
     if(nbByte == -1) {
         printf("\nErreur lecture dans le tube nommé %d (readInPipe() dans util.c).",descPipe);
         perror("");
         exit(-1);
     }
     return nbByte;
 }
