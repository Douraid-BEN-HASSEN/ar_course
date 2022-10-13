#!/bin/sh

if which mosquitto_pub -ne 0 ; then
    echo "Failed!"
    echo "Please install mosquitto_pub https://mosquitto.org/download/ !"
fi

echo "publish"
echo "loop..."

while true; do
    mosquitto_pub -h 127.0.0.1 \
    -m '{"mapWidth":1000,"mapHeight":1000,"checkpoints":[{"id":1,"x":500,"y":1} , {"id" : 2 , "x" : 500 , "y" : 555},{"id" : 3 , "x" : 700 , "y" : 990 }, {"id" : 4 , "x" : 200 , "y" : 851} , {"id" : 5 , "x" : 100 , "y" : 300}],"obstacles":[{"id":120  , "angle" : 0 , "x" : 500 , "y" : 333} , {"id" : 121 , "angle" : 0 , "x" : 500 , "y":666 } , {"id" : 122 , "x" : 600 , "y" : 800} , {"id" : 124 , "x" : 777 , "y" : 777} , {"id" : 126 , "x" : 400 , "y" : 913}] }' \
    -t map
    sleep 1
done
