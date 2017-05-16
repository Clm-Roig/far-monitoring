// Fichier client.c

#include "client.h"

// ---- CONSTANTES ---- //
const char* THING_NAME = "IG3FARLECLERROIG";
// ---- FONCTIONS ---- //



int creerClient(char** addrIp) {

    return 1;
}

int sock;

void Error(char *mess)
{
    fprintf(stderr,"%s\n",mess);
    if (sock) close(sock);
    exit(-1);
}

int envoiDweet(int x, int y, char* adrIpEnvoi) {

    // URL de la forme : https://dweet.io/dweet/for/my-thing-name?type_msg=COORD&type_ent=GP&ent=1&data=5,3,192.168.1.1

    // Infos de connexion
    char host[100];
    host[0]='\0';
    strcpy(host,"dweet.io");

    // Cast des coord en string
    char strX[16];
    strX[0]='\0';
    sprintf(strX, "%d", x);
    char strY[16];
    strY[0]='\0';
    sprintf(strY, "%d", y);

    // Fichier
    char file[100];
    file[0]='\0';
    strcat(file,"/dweet/for/");
    strcat(file,THING_NAME);
    strcat(file,"?type_msg=COORD&type_ent=GP&ent=1"
    strcat(file,"&data=");
    strcat(file,strX);
    strcat(file,",");
    strcat(file,strY);
    strcat(file,",");
    strcat(file,addrIpEnvoi);
    printf("\n%s",file);
    printf("\n%s",host);

    // Port
    int port = 80;

    // Calcul de l'IP de l'hote
    struct hostent *hostinfo;
    hostinfo = gethostbyname(host);
    if (hostinfo) {
        struct in_addr  **pptr;
        pptr = (struct in_addr **)hostinfo->h_addr_list;
        printf("Adresse IP de l'hote : %s\n",inet_ntoa(**(pptr)));
    }

    // Creation de la socket
    if ( (sock = socket(AF_INET, SOCK_STREAM, 0)) <0 )
        Error("can't create socket");

    // Configuration de la connexion

    struct sockaddr_in sin;

    sin.sin_addr = *(struct in_addr *) hostinfo->h_addr;
    sin.sin_family = AF_INET;
    if ( (sin.sin_port = htons(port)) == 0)
        Error("unknown service");

    // Tentative de connexion au serveur
    if (connect(sock, (struct sockaddr*)&sin,sizeof(sin))<0)
    Error("can't connect");
    else printf("Connexion a %s sur le port %d\n", inet_ntoa(sin.sin_addr),
    htons(sin.sin_port));

    // Envoi de donnees au serveur
    char buffer[1024] = "GET ";
    strcat(buffer, file);
    strcat(buffer, " HTTP/1.1\nHost: ");
    strcat(buffer, host);
    strcat(buffer, "\n\n");
    printf("Requete : \n%s", buffer);

    // TO DO : test whether this suceeds or Erorr("write error on socket")
    send(sock, buffer, 1024, 0);

    // Fermeture de la socket client
    close(sock);

    return EXIT_SUCCESS;
}

int recvDweet(char* IP)
{
    return 1;
}

int envoiRobot(char* donnees, char* addrRobot){
    return 1;
}

int checkDebutPartie() {
    return 0;
}

int checkFinPartie() {
    return 0;
}
