#!/bin/sh

if which mosquitto_pub -ne 0 ; then
    echo "Failed!"
    echo "Please install mosquitto_pub https://mosquitto.org/download/ !"
fi

echo "publish"
echo "loop..."

while true; do
    mosquitto_pub -h 127.0.0.1 \
    -m '{"mapWidth":1000,"mapHeight":1000,"checkpoints":[{"id":1,"x":0,"y":0} ,{"id" : 2 , "x" : 100 , "y" : 100} ,{"id" : 11 , "x" : 650 , "y" : 100}, { "id" : 30 , "x" : 10 , "y" : 50}],"obstacles":[{"id":120  , "angle" : 0 , "x" : 500 , "y" : 300} , {"id" : 121 , "angle" : 0 , "x" : 350 , "y":900}] }' \
    -t map
    sleep 1
done

