# AR_Course

## Description du projet

Le but du projet est de développer un jeu multijoueur de course automobile inspiré du jeu micro-machines.

![Alt text](images/micro_machine.jpg?raw=true "Architecture du système")

Le parcours sera déterminé par des jetons physiques analysés par une webcam et la partie sera visible sur une interface graphique.

Il pourra être jouable par des joueurs physiques, mais aussi par des joueurs machines reposants sur IA. 

Le but sera de relier tous les points d’un circuit (physiquement représentés par des jetons possédant des AR Codes) dans un ordre précis :

Les points de passage auront une valeur unique et devront être passés dans leur ordre croissant.
Plusieurs tours de circuit (paramètre pouvant varier) seront nécessaires pour finir la course
Le point de passage ayant la plus faible valeur sera le point de départ, celui qui a la plus grande valeur, le point d’arrivée.
Les obstacles devront être évités.

Les points de passage et les obstacles pourront se déplacer en cours de partie.

Deux modes de jeu seront disponibles : solo ou par équipes (nombre d’équipes à déterminer avant le début de la partie).

## Architecture du système
Les informations seront échangées au travers d’un serveur MQTT, au travers d'un format identique pour toutes les équipes.
Les données seront envoyées au format JSON.
Les joueurs et les bots enverront notamment la vitesse et l’angle du volant.

Le moteur du jeu enverra régulièrement la position des véhicules ainsi que toutes les informations utiles à la partie.
![Alt text](images/MQTT.png?raw=true "Architecture du système")

## Carte
La carte sera composée de jeton contenant tous un code AR , dont l'id determinera son utilité. 

De 0 à 9: Marqueurs symbolisant les limites de la carte, en forme de carré.

De 100 à 199: Marqueurs symbolisant les points de passage (checkpoits).

De 200 à 249: Obstacles, les Id pairs seront des obstacles circulaires, les id impairs quand à eux seront des obstacles rectangulaires.

La carte sera acquise par une webcam et traitée grace à la librairie OPEN CV. 

## Le client (joueur physique)
Le client pourra ce connecter, choisir son véhicule et le controler par le clavier, une manette ou un volant.
Il permettra d’envoyer les angles et l'accélération.

Il est également possible au joueur d'envoyé des objets (roquette, bombe et banane) que ce soit par le clavier, la manette ou même le volant qui comporte 5 boutons.

Développée en C++/Qt. 

Chaque objet possèdera des caractéristiques.

Banane : nombre, temps entre deux utilisations, taille de la banane, temps que la banane reste une fois posée.

Bombe : nombre, temps entre deux utilisations, temps avant explosion, rayon de l'explosion.

Roquette : Nombre, temps entre deux utilisations, vitesse, rayon. 

## Moteur de jeu 
Le moteur de jeu gère, à l'aide de calcul, tout ce qui va se passer pendant la partie. Il est à l'écoute des ordres mqtt des joueurs, afin de traiter leur déplacements.

Il gère, les collisions, les utilisations d'objets et les déplacement.  

### Vehicules
3 véhicules sont disponibles pour chaque partie, un moto, une voiture et un camion.

Les véhicules possèdent tous des statistiques aux valeurs différents : la vitesse maximale, l'acceleration, le poids, l'angle de braquage, la longueur et la largeur.

### Objets 
3 objets peuvent être utilisés pendant la partie, les bananes, les bombes et les roquettes. Le moteur de jeu determine le même nombre pour chaque joueur en début de partie.

## Interface graphique 
Deux interfaces graphiques sont disponibles afin d'observer la partie.

Un client 2d vue du dessus, et un client 3d, avec une caméra suivant le véhicule. 
Les interfaces affichent les joueurs, les checkpoints, les obstacles ainsi que les objets. 

Les deux interfaces sont développées en C++/Qt. 

### Commandes clavier (pour le joueur physique)
 - Z pour avancer
 - Q pour tourner à gauche 
 - D pour tourner à droite 
 - S pour freiner/reculer
 - 1 banane 
 - 2 bombe 
 - 3 rocket

### Commandes manette (pour le joueur physique)
 - joystick gauche contrôle de l'angle 
 - R2 accéleration 
 - L2 frein 
 - Croix banane 
 - Rond bombe 
 - Triangle roquette

## Volant  (pour le joueur physique)

![Alt text](images/Volant.png?raw=true "Architecture du système")

### Hors course
Pour la selection du vehicule : 

 - Bouton 🔴 Rouge Valider
 - Bouton 🟢🔵 Vert/Bleu Vehicule précédent/suivant 

### En course 
Pencher le volant en avant pour accelerer 

Pencher le volant en arriere pour freiner/reculer 

Tourner le volant a gauche/droite pour tourner à gauche/droite

- Bouton 🔴 Rouge - Accélerer
- Bouton 🟡 Jaune - Reculer
- Bouton 🟢 Vert - Banane
- Bouton 🔵 Bleu - Rocket
- Bouton ⚪ Blanc - Bombe

## L'intelligence artificielle
Le bot est capable de déterminer la meilleure alternative pour aller de point en point en évitant les obstacles et sans toucher les limites du terrain.
Pour cela, comme pour le joueur physique, il enverra les angles du volant et de la commande d’accélération.

Sa position exacte lui sera renvoyée par le moteur du jeu qui lui permettra de recalculer sa nouvelle trajectoire.

L'intelligence artificielle est conçue de sorte à déterminer son trajet au début, et lors de la recontre d'un obstacle, de determiner un checkpoint "d'évitement" afin de relier deux checkpoints. 

Développée en C++. 


# Authors and Team
    
> LADG

 - Alexis DEVLEESCHAUWER <alexis.devleeschauwer@imerir.com>,
 - Lucas AUXACHS <lucas.auxachs@imerir.com>,
 - Pierre FERER <pierre.ferer@imerir.com>,
 - Douraid BEN HASSEN <douraid.ben-hassen@imerir.com>,
 - Laurent CROUZIL <laurent.crouzil@imerir.com>
 - Sonia BELABBAS <sonia.belabbas@imerir.com>