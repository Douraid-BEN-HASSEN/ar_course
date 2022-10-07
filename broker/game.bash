
if which mosquitto_pub -ne 0 ; then
    echo "Failed!"
    echo "Please install mosquitto_pub https://mosquitto.org/download/ !"
fi

echo "publish"
echo "loop..."


while true; do
    mosquitto_pub -h 127.0.0.1 \
    -m '{
"players": [{
"uuid": "test",
"pseudo": "pseudo",
"color": "color",
"team": 1,
"x": 0,
"y": 0,
"angle": 0,
"speed": 0,
"vehicle": "vehicle",
"items": {
"banana": 0,
"bomb": 0,
"rocket": 0
},
"lastCheckpoint": 0,
"currentLap": 0,
"status": "status",
"controller": "controller"
}
],
"items": [
    {
    "x": 0,
    "y": 0,
    "angle": 0,
    "status": "placed",
    "type": "banana"
    }
],
"elapsedTime": 0,
"infoMessage": "infoMessage",
"status": "waiting"
}' \
    -t game

    sleep 1

done

'{
"players": [{
"uuid": str,
"pseudo": str,
"color": str,
"team": int
"x": int,
"y": int,
"angle": float, // en rad
"speed": int,
"vehicle": str, // type de vehicle : bike, car, truck
"items": { // nombre d’objet que le joueur possède
"banana": int,
"bomb": int,
"rocket": int
},
"lastCheckpoint": int, // dernier point de passage passé
"currentLap": int,
"status": str, // driving, accident
"controller": str // ia, keyboard, controller, vr, phone // pour
}
],
"items": [
{
"x": int,
"y": int,
"angle": float, // en rad
"status": str // banana : placed; bomb : flying, waiting,
exploding; rocket : flying, exploding
"type": str // banana, bomb, rocket
}
],
"elapsedTime": int,
"infoMessage": str, // ex : "la partie commence dans 10 secondes"
"status": str // waiting, progress, ended, paused
}'