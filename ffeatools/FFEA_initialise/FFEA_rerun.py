import sys, os, time
import FFEA_script, FFEA_trajectory

if len(sys.argv) < 4:
	sys.exit("Usage: python FFEA_rerun.py [INPUT .ffea file] [num_frames to delete each restart] [num_frames required] [frames_already_completed (OPTIONAL)]")

# Get args
script_fname = sys.argv[1]
absscript_fname = os.path.abspath(sys.argv[1])
delete_frames = int(sys.argv[2])
num_frames_required = int(sys.argv[3])

# Do stuff with args
os.chdir(os.path.dirname(absscript_fname))
script = FFEA_script.FFEA_script(script_fname)
if num_frames_required > script.params.num_steps / script.params.check:
	print "num_frames_required larger than number set in script. Resetting..."
	num_frames_required = script.params.num_steps / script.params.check

# Run endless simulations like a boss
original_script_fname = script_fname
restarts = 0
num_frames_completed = 0
if len(sys.argv) == 5:
	num_frames_completed += int(sys.argv[4])
	restarts += 1

while(True):

	# If on zeroth restart, make sure script will run indefinitely
	if restarts == 0:
		script.params.num_steps = script.params.check * num_frames_required + num_frames_completed
		script_fname = script_fname.split(".")[0] + "_newnumframes.ffea"
		script.write_to_file(script_fname)

	# If on first restart, script needs changing
	if restarts == 1:
		script.params.restart = 1
		script_fname = script_fname.split(".")[0].split("_newnumframes")[0] + "_restarted.ffea"
		script.write_to_file(script_fname)

	# Run sim if possible
	if num_frames_completed < delete_frames and script.params.restart == 1:
		print "Error. Not enough frames to delete for the restart. Fix your simulation parameters."
		break
	else:
		os.system("ffea -l " + str(delete_frames) + " " + script_fname)

	# Completed runs
	restarts += 1

	# To enable ctrl+c quit if necessary
	time.sleep(2)

	# How many frames calculated before crash?
	num_frames_completed = FFEA_trajectory.get_num_frames(script.params.trajectory_out_fname)

	# Do we need to stop?
	if restarts > num_frames_completed:
		print "Restarting more often than frames are being produced. Time to stop."
		print "num_restarts = " + str(restarts)
		print "num_frames_completed = " + str(num_frames_completed)
		break

	if num_frames_completed >= num_frames_required:
		restarts -= 1
		print "Simulation completed!!!!"
		print "num_restarts = " + str(restarts)
		print "num_restarts / num_frames = " + str(float(restarts) / float(num_frames_completed))
		break

		



