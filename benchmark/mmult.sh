#!/bin/bash
echo $'Tamano,Tiempo' >> salida.txt
for i in 4 8 16 32 64 128 256 512 1024 2048 4096
do
   echo $i, $(./mmult $i) >> salida.txt
done