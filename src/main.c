// Fichier main.c

#include "main.h"

// ---- CONSTANTES ---- //

// ---- FONCTIONS ---- //

int main(int argc,char* args[]) {

	// Pour créer un serveur en local sur le terminal :
	// nc -l localhost "numDuPort"
	// nc -l localhost 1234

	// Test socket
    // initSocket(80,"54445","google.com");
	int* res = malloc(2*sizeof(int));
	res = saisirXY();
	printf("%d | %d\n",res[0],res[1]);

    return 0;
}
