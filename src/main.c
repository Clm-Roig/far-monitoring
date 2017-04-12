// Fichier main.c

#include "main.h"

// ---- CONSTANTES ---- //

// ---- FONCTIONS ---- //

 int main(int argc,char* args[]) {

     // Pour créer un serveur en local sur le terminal :
     // nc -l localhost "numDuPort"
     // nc -l localhost 1234

     // Test pipe
     char* pipe = creerPipe("coucou");

     printf("%s",pipe);
     int descPipe = openPipeW(pipe);
     close(descPipe);

     return 0;
 }
