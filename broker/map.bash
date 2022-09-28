#!/bin/sh

if which mosquitto_pub -ne 0 ; then
    echo "Failed!"
    echo "Please install mosquitto_pub https://mosquitto.org/download/ !"
fi

echo "publish"
echo "loop..."

while true; do
    mosquitto_pub -h 127.0.0.1 \
    -m '{"mapWidth":1000,"mapHeight":1000,"checkpoints":[{"id":1,"x":500,"y":50},{"id":2,"x":50,"y":250},{"id":3,"x":500,"y":450},{"id":4,"x":950,"y":250}],"obstacles":[{"id":1,"angle":0,"x":250,"y":250},{"id":2,"angle":0,"x":250,"y":750},{"id":3,"angle":0,"x":750,"y":750},{"id":4,"angle":0,"x":750,"y":250}]}' \
    -t /map
    sleep 1
done

