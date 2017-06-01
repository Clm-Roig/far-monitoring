// Fichier main.c

#include "main.h"

// ---- CONSTANTES ---- //

// ---- FONCTIONS ---- //

int main(int argc,char* args[]) {

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


	// Test envoi Beebotte
/*
	char* data [4] = {"IP_SP","SP","1","128.42.123.42"};
  	envoiBeebotte(data);

	// Test réception Beebotte
	
	char* donnees = malloc(4096*sizeof(char));
	donnees = recepBeebotte("COORD");
	printf("\nDonnées reçues : %s",donnees);
*/
/*
	// ===================== "VRAI" CODE ========================== //

	// Récupération des IPs des robots (sur Beebotte)
	// pour l'instant on saisit les IP à la main
	char* tableauIPs[6];
	int i = 0;
	for (i = 0; i < 6; i++) {
		printf("\nVeuillez saisir l'IP du robot %d : ",i);
		char* IP = malloc(20*sizeof(char));
	    fgets(IP, sizeof IP, stdin);
	    char *p = strchr(IP, '\n');
	    // Retrait saut de ligne
	    if (p) {
	        *p = 0;
	    }
	    // Purge du flux stdin si saisie trop grande
	    else {
	        int c2;
	        while ((c2 = getchar()) != '\n' && c2 != EOF){}
	    }
		tableauIPs[i] = IP;
	}

	// Création du token ring et lancement de la partie
	creerFils(tableauIPs);
*/
    return 0;
}
