// Fichier serveurRobotPositionUtil.c

#include "serveurRobotPositionUtil.h"

// ---- FONCTIONS ---- //

// Socket
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
     printf("\nErreur initialisation socket (initSocket() dans util) sur %s",IP);
     perror("");
     exit(-1);
    }
    printf("Connexion réussie sur l'IP %s sur le port %d.\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));

    return sock;
}

int receiveFromSocket(int socket, char** data) {
    recv(socket,&data,sizeof(&data)-1,0);
    // Erreur ?
    if(errno) {
        printf("\nErreur reception données socket (receiveFromSocket() dans util) par le socket %d", socket);
        perror("");
        exit(-1);
    }
    return 0;
}

char* recepBeebotte(char* typedonnee)
{
    //http://api.beebotte.com/v1/public/data/read/vberry/testVB/msg?limit=2&time-range=1hour
    char *host = "api.beebotte.com";

    char path[200] = "/v1/public/data/read/vberry/";
    strcat(path,canal); strcat(path,"/"); strcat(path,ressource2);

    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd, bytes, sent, received, total;
    char* message = malloc(4096*sizeof(char));

    strcat(message,"GET ");
    strcat(message,path);
    strcat(message," HTTP/1.0\r\n");
    strcat(message,"Host: ");
    strcat(message,host);
    strcat(message,"\r\n\r\n");

    // Socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        Error("ERROR opening socket");
    }

    // Host
    server = gethostbyname(host);
    if (server == NULL) {
        Error("ERROR, no such host");
    }

    /* fill in the structure (port 80)*/
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(80);
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

    /* connect the socket */
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
        Error("ERROR connecting");
    }

    printf("\nRequete : %s", message);
    /* receive the response */
    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd,message+sent,total-sent);
        if (bytes < 0)
            Error("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent+=bytes;
    } while (sent < total);

    // TODO : à changer
    char response[50000];


    memset(response,0,sizeof(response));
    total = sizeof(response)-1;
    received = 0;
    do {
        bytes = read(sockfd,response+received,total-received);
        printf("\n");
        if (bytes < 0) Error("ERROR reading response from socket");
        if (bytes == 0)
            break;
        received+=bytes;
    } while (received < total);

    if (received == total) {
        Error("ERROR storing complete response from socket");
    }
    close(sockfd);

    /* Traitement du message reçu*/
    printf("%s", response);
    char typeMsg[200]="type_msg=";
    strcat(typeMsg,typedonnee);

    char* verifType = strstr(response, typeMsg);

    char* verifData;
    char* data;
    data = malloc(200*sizeof(char));
    if (verifType == NULL) {
        printf("Pas de message trouvé");
    }
    else {
        verifData = strstr(verifType, "data=");
        data = strtok(verifData,"\"");
        printf("%s", data);
    }
    return data;
}

int checkFinPartie() {
    return 0;
}
