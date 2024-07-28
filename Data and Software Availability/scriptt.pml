load antibody.pdb


cmd.wizard('mutagenesis')
cmd.do('refresh_wizard')

# Mutate
cmd.get_wizard().set_mode('PRO')
cmd.get_wizard().do_select('/antibody//X/55')

cmd.frame('20')
cmd.get_wizard().apply()
cmd.set_wizard('done')

# Save



select all


cmd.save('select.pdb')
	

quit 

