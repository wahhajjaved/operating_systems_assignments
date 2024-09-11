#!/bin/bash

#NAKHBA MUBASHIR
#epl482
#11317060
if [ $# -ne 0 ]
then
	echo "ERROR: not enough arguments"
else
	echo "the machine hardware architecture: $(uname -m)"
	echo "excetuting"
	if [ $(uname -m) = "ppc" ]
	then
		
	elif [ $(uname -m) == "arm" ]
		
	else
		
	fi
	echo "finished excecuting"
fi
		
