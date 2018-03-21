#!/bin/bash
while true; do
vmstat 1 2| tail -n 1 | cut -c64- | mosquitto_pub -p 2000 -t "/vmstat" -l
sleep 1
done
