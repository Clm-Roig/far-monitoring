// Fichier main.c

#include "main.h"

// ---- CONSTANTES ---- //

// ---- FONCTIONS ---- //

 int main(int argc,char* args[]) {

     // Pour créer un serveur en local sur le terminal :
     // nc -l localhost "numDuPort"
     // nc -l localhost 1234

     // Test pipe
     if(strcmp(args[1],"client") == 0) {
         printf("\nJe suis le client, j'attends un message.");
         char* pipeL = creerPipe("pipeTest");
         printf("\nTube %s créé",pipeL);
         int descPipeL = openPipeR(pipeL);
         printf("\nPipe ouvert !");

         char donnees[128];
         int nb = 0;

         nb = readInPipe(descPipeL,donnees);

         printf("\nJ'ai reçu %d octets.",nb);
         printf("\nJ'ai lu ça : \n%s",donnees);

     }
     else {
         printf("\nJe suis le serveur, je vais envoyer un message.");
         char* pipeL = creerPipe("pipeTest");
         printf("\nTube %s créé",pipeL);
         int descPipeW = openPipeW(pipeL);

         int res = writeInPipe(descPipeW,"coucou mon client");
         printf("\nres vaut %d",res);
     }

     printf("test commit");

     return 0;
 }
