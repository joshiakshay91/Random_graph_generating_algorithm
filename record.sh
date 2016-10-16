#!/bin/sh
echo `make`
cd ./recoloring;
echo `make`
cd ..
click=5;
expansionSize=100;
perLoss=10;
perBias=50;
for(())
