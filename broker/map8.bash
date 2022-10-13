#!/bin/sh

if which mosquitto_pub -ne 0 ; then
    echo "Failed!"
    echo "Please install mosquitto_pub https://mosquitto.org/download/ !"
fi

echo "publish"
echo "loop..."

while true; do
    mosquitto_pub -h 127.0.0.1 \
    -m '{"mapWidth":1000,"mapHeight":1000,"checkpoints":[{"id":1,"x":1,"y":1} , {"id" : 2 , "x" : 555 , "y" : 555},{"id" : 3 , "x" : 888 , "y" : 888}],"obstacles":[{"id":120  , "angle" : 0 , "x" : 333 , "y" : 333} , {"id" : 121 , "angle" : 0 , "x" : 666 , "y":666}] }' \
    -t map
    sleep 1
done
