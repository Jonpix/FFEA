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

from os import path
from time import sleep

class FFEA_binding_sites:

	def __init__(self, fname):
	
		self.reset()

		try:
			self.load(fname)
		except:
			return

	def load(self, fname):

		print("Loading FFEA binding sites file...")

		# Test file exists
		if not path.exists(fname):
			print("\tFile '" + fname + "' not found.")
			return
	
		# File format?
		base, ext = path.splitext(fname)
		if ext == ".bsites":
			try:
				self.load_bsites(fname)
				self.valid = True
			except:
				print("\tUnable to load FFEA_binding_sites from " + fname + ". Returning empty object...")

		else:
			print("\tUnrecognised file extension '" + ext + "'.")

	def load_bsites(self, fname):

		# Open file
		try:
			fin = open(fname, "r")
		except(IOError):
			print("\tFile '" + fname + "' not found.")
			self.reset()
			raise

		# Test format
		line = fin.readline().strip()
		if line != "ffea binding sites file" and line != "walrus binding sites file":
			print("\tExpected 'ffea binding sites file' but found " + line)
			raise TypeError

		num_binding_sites = int(fin.readline().split()[1])

		fin.readline()

		# Read bsites now
		while(True):

			# Get a site
			site = FFEA_binding_site()

			# First get type line, then get face list line
			sline = fin.readline().split()

			try:
				site.set_type(sline[1])
				faces = fin.readline().split()[1:]
				site.set_indices(faces)

			except(IndexError):
				break



			self.add_bsite(site)

		fin.close()

	def add_bsite(self, s):

		self.bsite.append(s)
		self.num_binding_sites += 1
		
	def print_details(self):

		print("num_binding_sites = %d" % (self.num_binding_sites))
		sleep(1)

		i = -1
		for s in self.bsite:
			i += 1
			outline = "Binding Site %d (Type %d):" % (i, s.type)
			for f in s.index:
				outline += " %d" % (f)
			
			print(outline)
	
	def reset(self):

		self.bsite = []
		self.num_binding_sites = 0
		self.valid = False

class FFEA_binding_site:

	def __init__(self):

		self.type = 0
		self.num_faces = 0
		self.index = []

	def set_type(self, anint):
		self.type = int(anint)

	def set_indices(self, alist):

		for i in alist:
			self.index.append(int(i))
		
		self.num_faces = len(self.index)
		
