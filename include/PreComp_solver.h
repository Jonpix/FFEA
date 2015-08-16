#ifndef PRECOMP_H_INCLUDED
#define PRECOMP_H_INCLUDED

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <math.h>
#include <boost/algorithm/string.hpp>
#include "FFEA_return_codes.h"

#include <iostream>

#include "mat_vec_types.h"

using namespace std;
/**
 * @detail 
 * vector<string> types: types of beads present. \n
 * string folder: folder containing the tables. It can be either absolute or relative.\n
 * int inputData: 1 means read .force and .pot files,
 *                 while 2 means read .pot and calculate the forces \n
 * string approach: if vdw -> use .vdw files and solve faces;
 *                  if solid -> use .solid files and solve volumes.
 */
struct PreComp_params {
  vector<string> types;
  string folder;
  int inputData;
  string approach;
};

class PreComp_solver{
public:
  PreComp_solver();
  ~PreComp_solver();
  int init(PreComp_params &pc_params);
  scalar get_U(scalar x, int typei, int typej);
  scalar get_F(scalar x, int typei, int typej);

private: 
  /** msgc and msg are helpful while developing */
  int msgc;
  int msg(string whatever); 
  int msg(int whatever); 
  
  int read_tabulated_values(PreComp_params &pc_params, string kind, scalar *Z);

  int calc_force_from_pot();
  
  scalar finterpolate(scalar *Z, scalar x, int typei, int typej);

  /** delta x in tabulated potentials and forces"  */
  scalar Dx; 
  /** x_range */ 
  scalar x_range[2];
  /** number of pre-computed values per table */ 
  int n_values; 
  /** total number of interactions */
  int nint; 
  /** number of types of "beads */
  int ntypes; 
  /** pointer to array containing all the values for all the pair potentials. */
  scalar *U;
  /** pointer to array containing all the values for all the pair forces. */
  scalar *F;

};

#endif