#!/usr/bin/env python3

import urllib.request
import json 
import requests
import os


with urllib.request.urlopen("http://xkcd.com/info.0.json") as url:
    data = json.loads(url.read().decode())
    img_data = requests.get(data['img']).content
    img_name = str(data['num'])+"-"+data['title']+".png"

    if(not os.path.exists('./'+img_name)):
        print("DIRETÓRIO NÃO ESTÁ ATUALIZADO. BAIXANDO A COMIC MAIS RECENTE.")
        with open(img_name, 'wb') as handler:
            handler.write(img_data)
    else:
        print("DIRETÓRIO ESTÁ ATUALIZADO. NÃO HÁ NOVAS COMICS A SEREM BAIXADAS.")