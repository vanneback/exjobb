#!/bin/bash
if [ -z "$1" ]; then
        echo "no argument"
else
	sudo timeout 60 tcpdump -w $1 -tttt '(dst port 1883 && dst host 192.168.77.222) or (src port 1883 && src host 192.168.77.222)'
	echo "tcpdump 120 sec to $1"
fi
