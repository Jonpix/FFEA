# 
#  This file is part of the FFEA simulation package
#  
#  Copyright (c) by the Theory and Development FFEA teams,
#  as they appear in the README.md file. 
# 
#  FFEA is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
# 
#  FFEA is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
# 
#  You should have received a copy of the GNU General Public License
#  along with FFEA.  If not, see <http://www.gnu.org/licenses/>.
# 
#  To help us fund FFEA development, we humbly ask that you cite 
#  the research papers on the package.
#

import sys, os
import numpy as np
import FFEA_node, FFEA_kinetic_map, FFEA_pdb

if len(sys.argv) != 5:
	sys.exit("Usage: python " + os.path.basename(os.path.abspath(sys.argv[0])) + " [INPUT .pdb fname] [OUTPUT fname] [INPUT ffea .map fname] [FFEA scale factor]\n")

# Get args
innpdb = sys.argv[1]
out_traj = sys.argv[2]
inmap = sys.argv[3]
scale = float(sys.argv[4])

# Get nodes
input_atoms = FFEA_pdb.FFEA_pdb(innpdb)

# Get map
kinetic_map = FFEA_kinetic_map.FFEA_kinetic_map(inmap)

# Apply matrix!
output_nodes = kinetic_map.apply_sparse(input_atoms)

# Print to file

# Finding these values would take to long, so set all to surface as this is just a test script
num_frames = len(output_nodes)
num_nodes = len(output_nodes[0])

fout = open(out_traj, "w")

if os.path.splitext(out_traj)[1] == ".out":
	fout.write("FFEA_trajectory_file\n\nInitialisation\n")
	fout.write("Number of Blobs 1\nNumber of Conformations 1\n")
	fout.write("Blob 0:	Conformation 0 Nodes %d\n\n" % (num_nodes))
	fout.write("*\n")

	for i in range(num_frames):
		f = output_nodes[i] * scale
		fout.write("Blob 0, Conformation 0, step %d\nDYNAMIC\n" % (i))
		for j in range(num_nodes):
			fout.write("%8.6e %8.6e %8.6e %8.6e %8.6e %8.6e %8.6e %8.6e %8.6e %8.6e\n" % (f[j][0], f[j][1], f[j][2], 0, 0, 0, 0, 0, 0, 0))
		fout.write("*\n")
		fout.write("Conformation Changes:\nBlob 0: Conformation 0 -> Conformation 0\n*\n")


elif os.path.splitext(out_traj)[1] == ".pdb":
	#for i in range(num_frames):
	#	fout.write("MODEL      %d" % ())
	for i in range(num_frames):
		for j in range(num_nodes):
			input_atoms.blob[0].frame[i].pos[j] = output_nodes[i][j]
			
	input_atoms.write_to_file(out_traj)
fout.close()