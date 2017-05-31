// Fichier serveurRobotPosition.c

#include "serveurRobotPosition.h"

// ---- VARIABLES ---- //

// Variables qui stockent en permanence les dernières données reçues.
int xSP = -1;
int ySP = -1;
char* diversSP;

// ---- FONCTIONS ---- //

int lancerServeurPosition() {
	// Récupération de l'id du SP
	char* IPServeurPosition = recepBeebotte("IP_SP");

	int sockServeurPos = initSocket(80,IPServeurPosition,"null");

	char* data[3];
	data[0] = malloc(32*sizeof(char));
	data[1] = malloc(32*sizeof(char));
	data[2] = malloc(256*sizeof(char));

	diversSP = malloc(256*sizeof(char));
	while(!checkFinPartie()) {
		// Attente des coordonnées sur le socket
		receiveFromSocket(sockServeurPos, data);

		xSP = atoi(data[0]);
		ySP = atoi(data[1]);
		diversSP = data[2];
	}
	// fin de partie

	return 0;
}
