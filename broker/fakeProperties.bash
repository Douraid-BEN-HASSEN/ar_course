#!/bin/sh

if which mosquitto_pub -ne 0 ; then
    echo "Failed!"
    echo "Please install mosquitto_pub https://mosquitto.org/download/ !"
fi

echo "publish"

mosquitto_pub -h 127.0.0.1 \
-m '{"lapsNb":3 , "teamNb":4 , "circleRadius":50 , "rectangleWidth":30 , "rectangleHeight":40 , "checkpointRadius":30 , "bananaNb":10, "bombNb":5, "rocketNb":3 , "bananaCd":10, "bombCd":30, "rocketCd":100, "rocketSpeed":50.5 , "bananaTtl":10 , "bombTtl":2  , "vehicleOptions":[{"vehicle" : "bike" , "maxSpeed" : 20 , "acceleration" : 10 , "weight" : 25 , "steeringAngle" : 16.5} , {"vehicle" : "car" , "maxSpeed" : 200 , "acceleration" : 30 , "weight": 1500 , "steeringAngle" : 30.5} , {"vehicle" : "truck" , "maxSpeed": 100 , "acceleration" : 50 , "weight": 300 , "steeringAngle" : 36.5}]}' \
-t /game/properties

echo "done"