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

	char* tableauIPs[6];

    tableauIPs[0] = "128.42.42.32";
    tableauIPs[1] = "129.42.42.14";
    tableauIPs[2] = "130.42.42.32";
    tableauIPs[3] = "131.42.42.32";
    tableauIPs[4] = "132.42.42.32";
    tableauIPs[5] = "133.42.42.32";

    creerFils(tableauIPs);

    return 0;
}
