#!/bin/bash
pwd




echo "load antibody.pdb


cmd.wizard('mutagenesis')
cmd.do('refresh_wizard')

# Mutate
cmd.get_wizard().set_mode('$1')
cmd.get_wizard().do_select('/antibody//X/$2')

cmd.frame('$3')
cmd.get_wizard().apply()
cmd.set_wizard('done')

# Save



select all


cmd.save('select.pdb')
	

quit 
" > scriptt.pml
pymol -c scriptt.pml
