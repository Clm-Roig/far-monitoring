 =======================================================================
| Module de réception des positions envoyées par le Serveur de Position |
| Auteurs : Clément ROIG & Hugo LECLER                                  |
 =======================================================================

Pour faire fonctionner le serveur :
- ajoute simplement la ligne #include "serveurRobotPosition.h" à votre programme
- compiler le fichier serveurRobotPosition
- lancer la fonction lancerServeurPosition()

A tout moment, vous pouvez lire les dernières coordonnées reçues dans xSP, ySP et diversSP.
Le module se ferme tout seul automatiquement quand la fin de la partie est annoncée sur Beebotte.
