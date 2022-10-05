#!/bin/sh

if which mosquitto_pub -ne 0 ; then
    echo "Failed!"
    echo "Please install mosquitto_pub https://mosquitto.org/download/ !"
fi

echo "publish"
echo "loop..."

while true; do
    mosquitto_pub -h 127.0.0.1 \
    -m '{"mapWidth":1000,"mapHeight":1000,"checkpoints":[{"id":1,"x":0,"y":50},{"id":2,"x":400,"y":50},{"id":3,"x":600,"y":50},{"id":4,"x":800,"y":50}],"obstacles":[{"id":1,"angle":0,"x":250,"y":0},{"id":2,"angle":0,"x":250,"y":750},{"id":3,"angle":0,"x":750,"y":750},{"id":4,"angle":0,"x":750,"y":250}]}' \
    -t map
    sleep 1
done
