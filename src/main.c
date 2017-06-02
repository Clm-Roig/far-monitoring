// Fichier main.c

#include "main.h"

// ---- FONCTIONS ---- //

int main(int argc,char* args[]) {
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

	// Envoi de l'IP sur beebotte
	char* data [4] = {"IP_SP","SP","1","128.42.123.42"};
  	envoiBeebotte(data);

	// Création du token ring et lancement de la partie
	creerFils(tableauIPs);

    return 0;
}
