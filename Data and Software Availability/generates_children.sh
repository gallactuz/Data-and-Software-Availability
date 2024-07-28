#!/bin/bash

export PATH=$PATH:/usr/apps/pymol/


populacao=12


for ((i=1;i<=$populacao;i=i+1)); do

rm -rf pasta$i
mkdir pasta$i

done



for ((i=1;i<=$populacao;i=i+1)); do

 cp -i relax_system.pdb pasta$i/complex.pdb 
 cp -i antibody.pdb pasta$i/antibody.pdb
 cp -i antigen.pdb pasta$i/antigen.pdb
 cp -i ranking.dat pasta$i/ranking.dat
 cp -i pymol1.sh pasta$i/pymol1.sh
 cp -i script1.in pasta$i/script1.in
 cp -i script2.in pasta$i/script2.in
 cp -i script3.in pasta$i/script3.in
 cp -i mmpbsa.in pasta$i/mmpbsa.in
 cp -i min.in pasta$i/min.in
 cp -i heat.in pasta$i/heat.in
 cp -i prod.in pasta$i/prod.in
 cp -i prod2.in pasta$i/prod2.in
 cp -i crossing_over.dat pasta$i/crossing_over.dat
 

 
done







for ((i=1;i<=$populacao;i=i+1)); do


cd pasta$i
input="crossing_over.dat"
tamline=31
while IFS= read -r line
do
n="$(cut -d " " -f 1 <<<"$line")"

for ((k=3,l=4;k<=$tamline;k=k+2,l=l+2)); do
residuo="$(cut -d " " -f $k <<<"$line")"
pos="$(cut -d " " -f $l <<<"$line")"

echo ">>>>> $n $residuo $pos  "



if [ $n -eq $i ]
then
mv antibody.pdb select1.pdb
./pymol1.sh $residuo $pos
echo "$n $residuo $pos "
rm select1.pdb
mv select.pdb antibody.pdb
fi



if [ $n -eq $i ]
then
mv complex.pdb select1.pdb
./pymol1.sh $residuo $pos
echo "$n $residuo $pos"
rm select1.pdb
mv select.pdb complex.pdb
fi

done

done < "$input"
cd ..
done


