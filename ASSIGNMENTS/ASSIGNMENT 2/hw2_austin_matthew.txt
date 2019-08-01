#!/bin/bash

ps -ef | grep socket

count=1

#while loop
while [ $count -lt 11 ]
do
        touch  ~/test$count.txt
        count=$(($count+1))
done

#create directory
mkdir -p ~/TestBackup

count=1

#move
while [ $count -lt 11 ]
do
        mv ~/"test$count.txt" ~/"TestBackup"
        count=$(($count+1))
done

cd ~/TestBackup

count=1

#rename
while [ $count -lt 11 ]
do
        mv ~/TestBackup/"test$count.txt" ~/TestBackup/"test$count.pdf"
        count=$(($count+1))
done

ps -ef | grep socket


