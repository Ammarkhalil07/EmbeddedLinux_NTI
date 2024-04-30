#!/bin/bash

case $1 in

insert)
make
sudo insmod gpio.ko
sudo chmod 777 /dev/gpio_driver
;;

remove)
sudo rmmod gpio
make clean
;;

test)
sudo rmmod gpio
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
sudo insmod gpio.ko
sudo chmod 777 /dev/gpio_driver
cat /dev/gpio_driver
sudo dmesg
;;

esac