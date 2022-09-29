#!/bin/sh

if which mosquitto_pub -ne 0 ; then
    echo "Failed!"
    echo "Please install mosquitto_pub https://mosquitto.org/download/ !"
fi

echo "publish"
echo "loop..."

mosquitto_pub -h 127.0.0.1 \
-m '{"lapsNb":3 , "teamNb":4 , "circleRadius":50 , "rectangleWidth":30 , "rectangleHeight":40 , "checkpointRadius":30 , "bananaNb":10, "bombNb":5, "rocketNb":3 , "bananaCd":10, "bombCd":30, "rocketCd":100, "rocketSpeed":50.5 , "bananaTtl":10 , "bombTtl":2  , "vehicleOptions":[{"vehicle" : "bike" , "maxSpeed" : 20 , "acceleration" : 10 , "weight" : 25 , "steeringAngle" : 16.5} , {"vehicle" : "car" , "maxSpeed" : 200 , "acceleration" : 30 , "weight": 1500 , "steeringAngle" : 30.5} , {"vehicle" : "truck" , "maxSpeed": 100 , "acceleration" : 50 , "weight": 300 , "steeringAngle" : 36.5}]}' \
-t /game/properties




while true; do
    mosquitto_pub -h 127.0.0.1 \
    -m '{"mapWidth":1000,"mapHeight":1000,"checkpoints":[{"id":1,"x":500,"y":50},{"id":2,"x":50,"y":250},{"id":3,"x":500,"y":450},{"id":4,"x":950,"y":250}],"obstacles":[{"id":1,"angle":0,"x":250,"y":250},{"id":2,"angle":0,"x":250,"y":750},{"id":3,"angle":0,"x":750,"y":750},{"id":4,"angle":0,"x":750,"y":250}]}' \
    -t /map
    sleep 1
    
    mosquitto_pub -h 127.0.0.1 \
    -m '{}' \
    -t /game/properties
     
done
