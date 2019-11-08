#!/bin/bash

mkdir   originales respaldo 
mkdir   originales/Nivel
mkdir   originales/Nivel/Segundo
cat /etc/passwd >  originales/Listado
mv thumb_3.png originales/thumb_3.png
mv practica9.txt originales/practica9.txt
ls  -R >  originales/Nivel/Segundo/Listado.txt
ln  originales/Listado respaldo/Arch1
ln  -s ../originales/thumb_3.png  respaldo/Arch2
ln originales/thumb_3.png  respaldo/Arch3
