#!/bin/bash

source /home/anderson/Documentos/AmberTools24/amber24/amber.sh



set -e


populacao=12



for ((i=1;i<=$populacao;i=i+1)); do

cd pasta$i







tleap  -f  script1.in 

tleap  -f  script2.in

tleap  -f  script3.in







echo -e "minimization  $i"

pmemd.cuda -O -i min.in -o min.out -p cpxa.prmtop -c cpxa.inpcrd -r min.ncrst 

pmemd.cuda -O -i min.in -o min.out -p cpxa.prmtop -c min.ncrst -r min.ncrst

echo -e "equilibration $i"

pmemd.cuda -O -i heat.in -o heat.out -p cpxa.prmtop -c min.ncrst -r heat.ncrst -x heat.nc

echo -e "production  $i"

pmemd.cuda -O -i prod.in -o prod.out -p cpxa.prmtop -c heat.ncrst -r prod.ncrst -x prod.nc

pmemd.cuda -O -i prod2.in -o prod2.out -p cpxa.prmtop -c prod.ncrst -r prod2.ncrst -x prod.nc


echo -e "MMPBSA  $i"

  amber.python MMPBSA.py -O -i mmpbsa.in -o FINAL_RESULTS_MMPBSA.dat -sp cpxa.prmtop -cp cpxv.prmtop -rp antibody.prmtop -lp antigen.prmtop -y prod.nc




cd ..

done


