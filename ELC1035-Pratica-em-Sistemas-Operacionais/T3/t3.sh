#!/bin/bash

wget https://xkcd.com/info.0.json
num=$(jq .num info.0.json)
title=$(jq -r .title info.0.json)
url=$(jq -r .img info.0.json)
img_title="${num}-${title}.png"
rm info.0.json
if test -f "${img_title}"; then
    echo DIRETÓRIO ESTÁ ATUALIZADO
else
    find . -name "*.png" -delete
    echo SALVANDO "${img_title}"
    wget -q -O "$img_title" $url
    for x in 1 2 3
    do
        let "num--"
        echo $num
        wget https://xkcd.com/"$num"/info.0.json
        num=$(jq .num info.0.json)
        title=$(jq -r .title info.0.json)
        url=$(jq -r .img info.0.json)
        img_title="${num}-${title}.png"
        echo SALVANDO "${img_title}"
        wget -q -O "$img_title" $url
        rm info.0.json
    done
fi