#!/bin/bash

tarefa1(){
    echo "Task 1:"
    cat $1 | sort -t "|" -k 1 | cut -d '|' -f2 | sed 's/\(.*\)/  \1/g'
}

tarefa2(){
    echo "Task 2:"
    cat $1 | sort -t "|" -k 2 | cut -d '|' -f2 | sed 's/\(.*\)/  \1/g'
}

tarefa3(){
    echo "Task 3:"
    for inf in $(cat $1 | sort -t "|" -k 3 | cut -d '|' -f3 | uniq | sed 's/\(.*\)/  \1/g')
    do
    	echo "  $inf:"
    	cat $1 | grep $inf | sort -t "|" -k 2 -r | cut -d '|' -f2 | sed 's/\(.*\)/    \1/g'
    done    	
}

tarefa4(){
    echo "Task 4:"
    cat $1 | sort -t "|" -k 4 -n | cut -d '|' -f2 | sed 's/\(.*\)/  \1/g'
}

tarefa1 $1
tarefa2 $1
tarefa3 $1
tarefa4 $1
