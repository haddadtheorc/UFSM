#!/bin/bash

tarefa1(){
    echo "1.Número total de pacotes"

    x=`grep -c "DST" $1`
    echo -e  "\t Pacotes enviados: ${x} \n"

}

tarefa2(){
    echo "2.Top 10 IPs fonte e quantos pacotes cada um"

    sed -n 's/.* SRC=\([^ ]*\).*/\1/p' $1 | sort | uniq -c | sort -rn | head -n10 
    
    echo -e "\n"
}


tarefa3(){
    echo "3.Top 10 IPs destino e quantos pacotes cada um"

    sed -n 's/.* DST=\([^ ]*\).*/\1/p' $1 | sort | uniq -c | sort -rn | head -n10 
    
    echo -e "\n"
}


tarefa4(){
    echo "4.Contagem de pacotes por protocolo (TCP, UDP, ICMP)"

    x=`grep "PROTO=TCP" $1 | grep -c ""`
    echo -e "\t Pacotes TCP enviados: ${x}"

    x=`grep "PROTO=UDP" $1 | grep -c ""`
    echo -e "\t Pacotes UDP enviados: ${x}"

    x=`grep "PROTO=ICMP" $1 | grep -c ""`
    echo -e "\t Pacotes ICMP enviados: ${x}"
}

tarefa1 $1
tarefa2 $1
tarefa3 $1
tarefa4 $1