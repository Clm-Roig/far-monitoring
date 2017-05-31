#ifndef DEF_SERVEUR_ROBOT_POSITION
#define DEF_SERVEUR_ROBOT_POSITION

/**
* \file serveurRobotPosition.h
* \brief Header du fichier serveurRobotPosition.c
*
* Le fichier serveurRobotPosition.c instancie un serveur permettant de réceptionner les coordonnées envoyées depuis le Serveur de Position.
*/

// ---- FONCTIONS ---- //

/**
	@brief Point d'entrée du programme.
*/
int lancerServeurPosition();

// ---- FONCTIONS ---- //

// Sockets
/**
    @brief crée + connecte un socket sur le port demandé (protocole IP) par IP ou URL (l'un doit être  initialisé à "null" pour pouvoir utiliser l'autre)
    @param int port : le port sur lequel l'on doit se connecter
    @param char* IP : l'ip sur laquelle on veut se connecter
    @param char* URL : l'url sur laquelle on souhaite se connecter
    @return int, le socket créé et connecté, -1 si la création échoue
*/
int initSocket(int port, char* IP, char* URL);


/**
    @brief reçoit des données par un socket
    @param int socket : le socket sur lequel on reçoit les données
    @param char** buffer : l'adresse du buffer à remplir
    @return bool, 1 si ok, -1 sinon
*/
int receiveFromSocket(int socket, char** buffer);

/**
    @brief Vérifie si la partie est terminé
    @return int, 1 si la partie est terminée, 0 sinon
*/
int checkFinPartie();

/**
    @brief Renvoie les données contenues dans le dernier message sur Beebotte du type spécifié
    @param char* typedonnee, le type de messages que l'on souhaite récupérer (partie "type_msg" sur Beebotte)
    @return char* les données contenues dans la partie "data" du msg
*/
char* recepBeebotte(char* typedonnee);

#endif
