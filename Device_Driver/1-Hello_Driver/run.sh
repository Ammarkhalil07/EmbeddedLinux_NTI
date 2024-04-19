#!/bin/bash

case $1 in

insert)
make
sudo insmod hellodriver.ko
sudo chmod 777 /dev/test_class
;;

remove)
sudo rmmod hellodriver
make clean
;;

test)
sudo rmmod hellodriver
if [ $? -ne 0]
then
    echo "module not inserted yet"
    read -p "press y to continue" yes
fi
make clean
make
if [ $? -ne 0]
then
    exit -1
fi
sudo insmod hellodriver.ko
sudo chmod 777 /dev/test_class
cat /dev/test_class
dmesg
;;

esac