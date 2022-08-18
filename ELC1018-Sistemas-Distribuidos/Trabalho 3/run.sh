#!/bin/bash
javac -d /app/out/ -cp /app/src /app/src/ClientApplication/Main.java || exit -1; cd out/; java ClientApplication/Main