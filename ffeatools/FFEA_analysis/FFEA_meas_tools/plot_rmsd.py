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
import FFEA_script
import argparse as _argparse
import __builtin__

try:
    from matplotlib import pyplot as plt
    import numpy as np
except(ImportError):
    raise ImportError("ImportError recieved. Without the numpy and matplotlib libraries, this script cannot run. Please install these, or manually use gnuplot :)")

# Set up argparse
parser = _argparse.ArgumentParser(description="Test KE of blob against classical equipartition theorem")
parser.add_argument("script", action="store", help="Input script file (.ffea).")

def plot_rmsd(script):

    meas = script.load_measurement()
    top = [script.load_topology(i) for i in range(script.params.num_blobs)]
    
    # We need to plot a global measurement graph, and a graph for every blob
    
    #
    # First, global graph (strain and kinetic)
    #
    cmeas = meas.global_meas
    num_steps = len(cmeas["Time"])

    # Get x axis data (time)
    x = cmeas["Time"] * 1e9    # ns

    if script.params.num_blobs > 1:
	    plt.figure(0)
	    
	    # And y axis data (all energies)
	    rmsd = global_meas["RMSD"] * 1e10
	    
	    print "\nGlobal System:\n"
	    
	    rmsdplot, = plt.plot(x, rmsd, label='globrmsd')
	    
	    plt.xlabel("Time (ns)")
	    plt.ylabel("RMSD (Angstroms)")
	    plt.title("Global RMSD Trace")
	    
	    plt.show()
    
    #
    # Now, individual blobs (strain and kinetic), if we can
    #
    if meas.blob_meas == []:
        sys.exit()
    
    fig = plt.figure(1)

    hands = []
    for i in range(script.params.num_blobs):
    
        cmeas = meas.blob_meas[i]
    
        # Already got the x axis
    
        # And y axis data (all energies)
        rmsd = meas.blob_meas[i]["RMSD"] * 1e10

        print "\nBlob %d:\n" % (i)

        rmsdplot, = plt.plot(x, rmsd, label='blob' + str(i) + "rmsd")
        hands.append(rmsdplot)

    plt.xlabel("Time (ns)")
    plt.ylabel("RMSD (Angstroms)")
    plt.title("Blob RMSD Trace")

    # Put details on the graph
    plt.legend(hands, ['Blob %d RMSD' % (i)], loc = 4)
    plt.show()

if sys.stdin.isatty() and hasattr(__builtin__, 'FFEA_API_mode') == False:
    args = parser.parse_args()
    # Get args and build objects
    script = FFEA_script.FFEA_script(args.script)
    if not os.path.exists(script.params.measurement_out_fname):
        raise IOError("Error. Measurement file not found. Please supply a script with a completed measurement file.")
    plot_rmsd(script)
