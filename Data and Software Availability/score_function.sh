#!/bin/bash

set -e

declare -a arr=("GLY" "ALA"  "LEU" "ILE" "VAL" "SER" "THR"  "TYR" "ASN" "GLN" "ASP" "GLU" "ARG" "LYS" "HIS" "TRP" "MET" "PRO" )




declare -a aminoacidos=( 2 4 6 8 13 15 17 19 42 44 46 49 51 53 55 )





rm -f score.dat
touch score.dat

for aa in "${aminoacidos[@]}"
do

for str in "${arr[@]}"
do



for ((j=1;j<=20;j=j+1)); do
./pymol.sh $str $aa $j

./score.exe select.pdb antigen_template.pdb  $aa $j $str

done

rm -rf select.pdb

done

done

