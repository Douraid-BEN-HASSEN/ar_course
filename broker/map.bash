#!/bin/sh

if which mosquitto_pub -ne 0 ; then
    echo "Failed!"
    echo "Please install mosquitto_pub https://mosquitto.org/download/ !"
fi

echo "publish"
echo "loop..."

mosquitto_pub -h 127.0.0.1 \
-m '{"lapsNb":3 , "teamNb":4 , "circleRadius":50 , "rectangleWidth":30 , "rectangleHeight":40 , "checkpointRadius":30 , "bananaNb":10, "bombNb":5, "rocketNb":3 , "bananaCd":10, "bombCd":30, "rocketCd":100, "rocketSpeed":50.5 , "bananaTtl":10 , "bombTtl":2  , "vehicleOptions":[{"vehicle" : "bike" , "maxSpeed" : 20 , "acceleration" : 10 , "weight" : 25 , "steeringAngle" : 16.5} , {"vehicle" : "car" , "maxSpeed" : 200 , "acceleration" : 30 , "weight": 1500 , "steeringAngle" : 30.5} , {"vehicle" : "truck" , "maxSpeed": 100 , "acceleration" : 50 , "weight": 300 , "steeringAngle" : 36.5}]}' \
-t game/properties




while true; do
    mosquitto_pub -h 127.0.0.1 \
    -m '{"mapWidth":1000,"mapHeight":1000,"checkpoints":[{"id":1,"x":500,"y":50},{"id":2,"x":50,"y":250},{"id":3,"x":500,"y":450},{"id":4,"x":950,"y":250}],"obstacles":[{"id":1,"angle":0,"x":250,"y":250},{"id":2,"angle":0,"x":250,"y":750},{"id":3,"angle":0,"x":750,"y":750},{"id":4,"angle":0,"x":750,"y":250}]}' \
    -t map

    mosquitto_pub -h 127.0.0.1 \
    -m '{"players":[{"uuid":"1211sqsdsq22112","pseudo":"Alexis","color":"red","team":"1","x":95,"y":256,"angle":90,"speed":0,"vehicle":"string","items":{"banana":1,"bomb":2,"rocket":3},"lastCheckpoint":0,"currentLap":0,"status":"string","controller":"keyboard"}],"items":[{"x":1,"y":2,"angle":1,"status":"string","type":"string"}],"elapsedTime":1,"infoMessage":"string","status":"string"}' \
    -t game
    
    sleep 1
   
    mosquitto_pub -h 127.0.0.1 \
    -m '{"players":[{"uuid":"1211sqsdsq22112","pseudo":"Alexis","color":"red","team":"1","x":150,"y":300,"angle":90,"speed":0,"vehicle":"string","items":{"banana":1,"bomb":2,"rocket":3},"lastCheckpoint":0,"currentLap":0,"status":"string","controller":"keyboard"}],"items":[{"x":1,"y":2,"angle":1,"status":"string","type":"string"}],"elapsedTime":1,"infoMessage":"string","status":"string"}' \
    -t game



done
