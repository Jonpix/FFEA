// 
//  This file is part of the FFEA simulation package
//  
//  Copyright (c) by the Theory and Development FFEA teams,
//  as they appear in the README.md file. 
// 
//  FFEA is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
// 
//  FFEA is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
// 
//  You should have received a copy of the GNU General Public License
//  along with FFEA.  If not, see <http://www.gnu.org/licenses/>.
// 
//  To help us fund FFEA development, we humbly ask that you cite 
//  the research papers on the package.
//

#ifndef NOMASSCGSOLVER_HPP_INCLUDED
#define NOMASSCGSOLVER_HPP_INCLUDED

#include <stdio.h>
#include <set>

#include "FFEA_return_codes.h"
#include "mat_vec_types.h"
#include "mesh_node.h"
#include "tetra_element_linear.h"
#include "SimulationParams.h"
#include "Solver.h"
#include "NoMassCGSolver.h"
#include "SparseMatrixTypes.h"
#include "SparsityPattern.h"
#include "SparseMatrixFixedPattern.h"

class NoMassCGSolver : public Solver {
public:

    /** Constructor */
    NoMassCGSolver();

    /** Destructor */
    ~NoMassCGSolver();

    /** Builds a sparse matrix pattern for blob viscosity matrix from initial structure. Doesn't build the matrix though, just the key and whatnot */
    int init(int num_nodes, int num_elements, mesh_node *node, tetra_element_linear *elem, SimulationParams *params, int num_pinned_nodes, int *pinned_nodes_list, set<int> bsite_pinned_node_list);

    /** Adds values to sparse viscosity matrix and uses it to solve the system Kv = f using conjugate gradient*/
    int solve(vector3* x);

    /* */
    void print_matrices(vector3* force);

private:

    /** Pointer to the viscosity matrix that will be created */
    SparseMatrixFixedPattern *V;

    /** Error tolerance threshold (squared) to determine when solution has converged */
    scalar epsilon2;

    /** Maximum number of iterations the solver should use before giving up (as solution is not converging) */
    int i_max;

    /** Number of rows in V (3 * num_nodes due to x, y and z) */
    int num_rows;

    /** Number of nodes */
    int num_nodes;

    /** Jacobi preconditioner (inverse of the viscosity matrix diagonal) */
    scalar *preconditioner;

    /** Work vectors */
    vector3 *r, *p, *z, *q, *f;

    /** Unchanging memory locoation */
    scalar one;

    /* */
    scalar conjugate_gradient_residual_assume_x_zero(vector3 *b);

    /* */
    scalar residual2();

    /* */
    scalar modx(vector3 *x);

    scalar get_alpha_denominator();

    /* */
    scalar parallel_apply_preconditioner();

    /* */
    void check(vector3 *x);

    /* */
    void apply_matrix(scalar *in, scalar *result) {
    }

};

#endif
