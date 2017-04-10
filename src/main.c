// Fichier main.c

#include "main.h"

// ---- CONSTANTES ---- //

// ---- FONCTIONS ---- //

 int main(int argc,char* args[]) {

     // Pour créer un serveur en local sur le terminal :
     // nc -l localhost "numDuPort"
     // nc -l localhost 1234

     // Test fils
     int* p = saisirCoord();
     printf("\nx = %d",p[0]);
     printf("\ny = %d",p[1]);

     return 0;
 }
