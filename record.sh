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
        for li in {1..10..1}
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
        fields=$(echo $puttit|awk --field-separator=" " "{ print NF }")
        if [ "$fields" = "1" ]
        then
          puttit2=$(echo $puttit| awk '{print $1}')
          coln=":"
          slash="/"
          FIRSTV=100;
          chiBias=`expr $FIRSTV - $perBias`
          echo -e $click'\t'$expansionSize'\t'$perLoss'\t'$perBias$slash$chiBias$coln'\t' $puttit2;
          rm ./data.txt
        elif [ "$fields" = "2" ]
        then
          puttit2=$(echo $puttit| awk '{print $1}')
          puttit3=$(echo $puttit| awk '{print $2}')
          coln=":"
          slash="/"
          FIRSTV=100;
          chiBias=`expr $FIRSTV - $perBias`
          echo -e $click'\t'$expansionSize'\t'$perLoss'\t'$perBias$slash$chiBias$coln'\t' $puttit2 $puttit3;
          rm ./data.txt
        else
          puttit2=$(echo $puttit| awk '{print $1}')
          puttit3=$(echo $puttit| awk '{print $2}')
          puttit4=$(echo $puttit| awk '{print $3}')
          coln=":"
          slash="/"
          FIRSTV=100;
          chiBias=`expr $FIRSTV - $perBias`
          echo -e $click'\t'$expansionSize'\t'$perLoss'\t'$perBias$slash$chiBias$coln'\t' $puttit2 $puttit3 $puttit4;
          rm ./data.txt
        fi
      done
      echo "                  "
    done
    echo "----------------------"
  done
