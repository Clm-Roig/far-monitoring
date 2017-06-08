// Fichier main.c

#include "main.h"

// ---- VARIABLES ---- //
char* IP_SP = "162.38.111.44"; // TODO : IP du serveur de position

// ---- FONCTIONS ---- //

int main(int argc,char* args[]) {
	// Récupération des IPs des robots (sur Beebotte)
	// pour l'instant on saisit les IP à la main

	char* tabIPs[6];
	int i = 0;
	for (i = 0; i < 6; i++) {
		printf("\nVeuillez saisir l'IP du robot %d : ",i);
		char IP[20];
	    fgets(IP, sizeof IP, stdin);

	    char *p = strchr(IP, '\n');
	    // Retrait saut de ligne
	    if (p) {
	        *p = 0;
	    }
	    // Purge du flux stdin si saisie trop grande
	    else {
	        int c;
	        while ((c = getchar()) != '\n' && c != EOF){}
	    }

		tabIPs[i] = malloc(20*sizeof(char));
		strcpy(tabIPs[i],IP);
	}
	// Envoi de l'IP sur beebotte
	char* data [4] = {"IP","GP","1",IP_SP};
  	envoiBeebotte(data, "partie1");

	// Création du token ring et lancement de la partie
	creerFils(tabIPs);

    return 0;
}
