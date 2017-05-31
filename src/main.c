// Fichier main.c

#include "main.h"

// ---- CONSTANTES ---- //

// ---- FONCTIONS ---- //

int main(int argc,char* args[]) {
/*
	// Pour créer un serveur en local sur le terminal :
	// nc -l localhost "numDuPort"
	// nc -l localhost 1234

	// Test socket

	char* tableauIPs[6];

	tableauIPs[0] = "128.42.42.32";
	tableauIPs[1] = "129.42.42.14";
	tableauIPs[2] = "130.42.42.32";
	tableauIPs[3] = "131.42.42.32";
	tableauIPs[4] = "132.42.42.32";
	tableauIPs[5] = "133.42.42.32";
	creerFils(tableauIPs);
*/

	// Test envoi Beebotte
	char* data [4] = {"COORD","SP","1","1,1,123.5.5.5"};
	envoiBeebotte(data);

	// Test réception Beebotte
	char* donnees = malloc(512*sizeof(char));
	donnees = recepBeebotte("COORD");



    return 0;
}
