#!/bin/bash
echo `make`
cd ./recoloring;
echo `make`
cd ..
maker=$(g++ calculator.cpp -o calc)
click=11;
expansionSize=100;
perLoss=10;
perBias=50;
for i in {100..300..100}
  do
    expansionSize=$i;
    for j in {10..90..10}
    do
      perLoss=$j;
      for k in {50..90..20}
      do
        perBias=$k;
        for li in {1..1000..1}
        do
          executor=$(./Grow $click $expansionSize $perLoss $perBias)
          mv ./output.txt ./recoloring/
          cd ./recoloring/
          result=$(./Greedy <output.txt | grep "d")
          vary=$(echo $result | awk '{print $3}')
          rm ./output.txt
          cd ..
          echo $vary>> data.txt
        done
        puttit="$(./calc)"
        puttit2=$(echo $puttit| awk '{print $1}')
        coln=":"
        slash="/"
        FIRSTV=100;
        chiBias=`expr $FIRSTV - $perBias`
        echo -e $click'\t'$expansionSize'\t'$perLoss'\t'$perBias$slash$chiBias$coln'\t' $puttit2;
        rm ./data.txt
      done
      echo "                  "
    done
    echo "----------------------"
  done
