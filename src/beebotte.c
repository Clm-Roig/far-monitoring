#include "beebotte.h"

// ---- VARIABLES ---- //
/* !! TODO remplacer 'testVB' par le canal dans lequel publier (ex: partie12)
    (ici msg est la "ressource" que ce canal attend */
char* channel = "testVB";

    /* Par convention dans FAR on parle sur ressource "msg"
      sur laquelle on envoie une chaine contenant les couples clef:valeur separes par des virgules */
char* ressource = "msg"; 

    // !! TO DO : mettre ci-dessous le token du canal !!
    // canal partie0 : 1494793564147_KNl54g97mG89kQSZ
    // canal testVB : 1494771555601_5SGQdxJaJ8O1HBj4
char* clefCanal = "1494771555601_5SGQdxJaJ8O1HBj4";

// ---- FONCTIONS ---- //

void error(const char *msg) { 
    perror(msg); 
    exit(0); 
}


int sendToBeBotte(char *data[]) {
    int i;
    char *host = "api.beebotte.com";

    char path[100] = "/v1/data/write/";
    strcat(path,canal); strcat(path,"/"); strcat(path,ressource);

    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd, bytes, sent, received, total, message_size;
    char *message, response[4096];

    // Necessaire pour envoyer des donnees sur beebotte.com (noter le token du canal a la fin) :
    char headers[300] ="Host: api.beebotte.com\r\nContent-Type: application/json\r\nX-Auth-Token: ";
    strcat(headers,clefCanal);strcat(headers,"\r\n"); 
    
    char donnees[4096] = "{\"data\":\""; // "data" est impose par beebotte.com

    // Norme d'envoi projet FAR 
    strcat(donnees,"type_msg=");
    strcat(donnees,data[0]);
    strcat(donnees,",");

    strcat(donnees,"type_ent=");
    strcat(donnees,data[1]);
    strcat(donnees,",");

    strcat(donnees,"num=");
    strcat(donnees,data[2]);
    strcat(donnees,",");

    strcat(donnees,"data=");
    strcat(donnees,data[3]);
    strcat(donnees,"\"}");

    /* How big is the whole HTTP message? (POST) */
    message_size=0;
    message_size+=strlen("%s %s HTTP/1.0\r\n")+strlen("POST")+strlen(path)+strlen(headers);
    message_size+=strlen("Content-Length: %d\r\n")+10+strlen("\r\n")+strlen(donnees); 

    message=malloc(message_size);

    /* Construit le message POST */
    sprintf(message,"POST %s HTTP/1.0\r\n",path); 
    sprintf(message+strlen(message), "%s",headers);
    sprintf(message+strlen(message),"Content-Length: %d\r\n",(int)strlen(donnees));
    strcat(message,"\r\n");              // blank line     
    strcat(message,donnees);             // body          

    printf("Request:\n%s\n-------------\n",message);

    // Socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        error("ERROR opening socket");
    }

    // Host
    server = gethostbyname(host);
    if (server == NULL) {
        error("ERROR, no such host");
    }

    /* fill in the structure (port 80)*/
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(80); 
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

    /* connect the socket */
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
    }

    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd,message+sent,total-sent);
        if (bytes < 0)
            error("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent+=bytes;
    } while (sent < total);

    /* receive the response */
    memset(response,0,sizeof(response));
    total = sizeof(response)-1;
    received = 0;
    do {
        bytes = read(sockfd,response+received,total-received);
        if (bytes < 0) error("ERROR reading response from socket");
        if (bytes == 0)
            break;
        received+=bytes;
    } while (received < total);

    if (received == total) {
        error("ERROR storing complete response from socket");
    }

    close(sockfd); 
    printf("Response:\n%s\n",response);
    free(message);

    return 0;
}