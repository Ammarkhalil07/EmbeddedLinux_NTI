#!/bin/bash

if [ -e ~/.bashrc ]
then
 export HELLO=$HOSTNAME
 	printenv HELLO
 	
 	LOCAL=$(whoami)
 	echo $LOCAL
 	sh
 fi
 	
