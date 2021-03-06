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

#include "Spring.h"

Spring::Spring() {
    blob_index = new int[2];
    conformation_index = new int[2];
    node_index = new int[2];
    k = 0.0;
    l = 0.0;
    am_i_active = false;
}

Spring::~Spring() {
    delete[] blob_index;
    blob_index = NULL;
    delete[] conformation_index;
    conformation_index = NULL;
    delete[] node_index;
    node_index = NULL;
    k = 0.0;
    l = 0.0;
    am_i_active = false;
}

