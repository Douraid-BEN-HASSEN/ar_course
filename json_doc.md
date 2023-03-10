# MQTT JSON

## Route
### Transmetteur -> Receveur

Description

---


`map`

### OpenCV -> GameEngine, Clients

> Informations de la map (longueur, largeur), informations obstacles (angle orientation, longueur, largeur):


A RENVOYER A CHAQUE X SECONDES ?

```json
{
    "mapWidth": "int",
    "mapHeight": "int",
    "checkpoints": [
        {
            "id": "int",
            "x": "int",
            "y": "int",
        },
    ],
    "obstacles": [
        {
            "id": "int",
            "angle": "float",
            "x": "int",
            "y": "int"
        },
    ]
}
```

--- 

`player/register`

### joueur -> GameEngine

> Informations de base du joueur qui se connecte à la partie (salon, attente des joueurs)

```json
{
    "uuid": "string", // utiliser QUuid de Qt
    "pseudo":"string",
    "controller": "string", // ia, keyboard, controller, vr, phone // pour le graphique
    "vehicle": "string",
    "team": "int" // null automatiquement si partie libre
}
```

---

`player/control`

### Joueur -> GameEngine

```json
{
    "uuid": "string",
    "angle": "float", // [-90°;90°]
    "power": "int", // [-100%;100%]
    "buttons": { // état des boutons
        "banana": "bool",
        "bomb": "bool",
        "rocket": "bool"
    }
}
```

--- 

`game`

### Moteur de jeu -> Joueur

> Informations de la partie en temps réel (coordonnées des joueurs, leur véhicule, leur
vitesse… )
Informations des items placés sur la map en temps réel (coordonnées)

```json
{
    "players": [
        {
            "uuid": "string",
            "pseudo": "string",
            "color": "string",
            "team": "string",
            "x": "int",
            "y": "int",
            "angle": "float",
            "speed": "int",
            "vehicle": "string", // type de vehicle : bike, car, truck
            "items": { // nombre d’objet que le joueur possède
                "banana": "int",
                "bomb": "int",
                "rocket": "int"
            },
            "lastCheckpoint": "int", // dernier point de passage passé
            "currentLap": "int",
            "status": "string", // driving, accident
            "controller": "string" // ia, keyboard, controller, vr, phone // pour de l’affichage seulement
        },
    ],
    "items": [
        {
            "x": "int",
            "y": "int",
            "angle": "float",
            "status": "string", // banana : placed; bomb : flying, waiting,exploding; rocket : flying, exploding
            "type": "string" // banana, bomb, rocket
        },
    ],
    "elapsedTime": "int",
    "infoMessage": "string", // ex : "la partie commence dans 10 secondes"
    "status": "string" // waiting, progress, ended, paused
}
```

---

`/game/properties`

### GameEngine -> Joueur

> Initialisation de la partie (propriété de la partie)
Taille de la carte
Nombre d’items

```json
{
    "lapsNb": "int", // nombre de tour à faire
    "teamNb": "int", // nombre d’équipe dans la partie
    
    "circleRadius": "int",
    "rectangleWidth": "int",
    "rectangleHeight": "int",
    "checkpointRadius": "int",
    
    "bananaNb": "int", // -1 = infinie
    "bananaCd": "int", // temps entre deux utilisations
    "bananaTtl": "int", // temps avant que la banane disparaisse
    "bananaRadius": "int", // taille de la banane

    "bombNb": "int", // -1 = infinie
    "bombCd": "int", // temps entre deux utilisations
    "bombTtl": "int", // temps avant explosion
    "bombRadius": "int",
    "bombExplosionRadius": "int", // taille de l’explosion

    "rocketNb": "int",// -1 = infinie
    "rocketCd": "int", // temps entre deux utilisation
    "rocketSpeed": "float", // vitesse d’une roquette
    "rocketRadius": "int", // taille d’une roquette

    "vehicleOptions" {
        "<vehicle>": { // vehicle : bike, car, truck
            "maxSpeed": "int",
            "acceleration": "float",
            "weight": "int",
            "steeringAngle": "float", // angle de braquage, en rad
            "width": "int", // largeur du véhicule
            "height": "int" // longueur du véhicule
        }
    }
}

```