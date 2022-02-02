#!/bin/bash


paste <(head -n 1 $1 | cut -d " " -f1) <(tail -n 1 $1 | cut -d " " -f1)

a=`grep "IP" $1 | cut -d " " -f3 | grep "10.9.10.1" | sed 's/\.[0-9]\+$//g' | sort -n | uniq | grep -c ""`
b=`grep "IP" $1 | cut -d " " -f3 | grep -v "10.9.10.1" | sed 's/\.[0-9]\+$//g' | sort -n | uniq | grep -c ""`
echo $a $b

grep "IP" $1 | cut -d " " -f3 | sed 's/\.[0-9]\+$//g' | sort -n | uniq -c | sort -n -r | head -n 5 | sed 's/^[ ]\+//g'
