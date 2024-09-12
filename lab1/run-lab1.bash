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
		./build/bin/PPC/sample-linux-PPC	
	elif [ $(uname -m) == "arm" ]
	then
		./build/bin/PPC/sample-linux-ARM	
	else
		./build/bin/LINUX_86/sample-linux-x86
	fi
	echo "finished excecuting"
fi
		
