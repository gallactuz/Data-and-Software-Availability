#!/bin/bash



populacao=12

for ((i=1; i<=$populacao; i=i+1)); do
    rm -rf  pasta$i
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
 
 ls
cd pasta$i
input="ranking.dat"

while IFS= read -r line
do
n="$(cut -d " " -f 1 <<<"$line")" 
residuo="$(cut -d " " -f 2 <<<"$line")"
rotamero="$(cut -d " " -f 5 <<<"$line")"
pos="$(cut -d " " -f 3 <<<"$line")"




if [ $n -eq $i ]
then
mv antibody.pdb select1.pdb
./pymol1.sh $residuo $pos $rotamero 
echo "$n $residuo $pos $rotamero $sum"
rm select1.pdb
mv select.pdb antibody.pdb
fi



if [ $n -eq $i ]
then
mv complex.pdb select1.pdb
./pymol1.sh $residuo $pos $rotamero
echo "$n $residuo $pos $rotamero $sum"
rm select1.pdb
mv select.pdb complex.pdb
fi



done < "$input"
cd ..
done

