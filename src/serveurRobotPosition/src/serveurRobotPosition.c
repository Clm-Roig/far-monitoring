// Fichier serveurRobotPosition.c

#include "serveurRobotPosition.h"

// ---- VARIABLES ---- //
char* ipServeurPosition  = "127.0.0.42"; // TODO : à récupérer depuis Beeboot

// Variables qui stockent en permanence les dernières données reçues.
int x = -1;
int y = -1;
char* divers;

// ---- FONCTIONS ---- //

int main() {
	// Récupération de l'id du SP

	

	int sockServeurPos = initSocket(80,ipServeurPosition,"null");

	char* data[3];
	data[0] = malloc(32*sizeof(char));
	data[1] = malloc(32*sizeof(char));
	data[2] = malloc(256*sizeof(char));

	divers = malloc(256*sizeof(char));
	while(!checkFinPartie()) {
		// Attente des coordonnées sur le socket
		receiveFromSocket(sockServeurPos, data);

		x = atoi(data[0]);
		y = atoi(data[1]);
		divers = data[2];
	}
	// fin de partie

	return 0;
}
