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

#include "FFEA_math.hpp"
#include <cmath>

//
// vector3i
//

// Constructor / Destructor
vector3i::vector3i() {
	comp[0] = 0;
	comp[1] = 0;
	comp[2] = 0;
	magnitude = 0.0;
}

vector3i::~vector3i() {
	comp[0] = 0;
	comp[1] = 0;
	comp[2] = 0;
	magnitude = 0.0;
}

// Overloaded operators
vector3i vector3i::operator+(vector3i rvalue) {
	int i;
	int sum = 0;
	vector3i result;
	for(i = 0; i < 3; ++i) {
		result.comp[i] = comp[i] + rvalue.comp[i];
		sum += result.comp[i] * result.comp[i];
	}
	
	result.magnitude = sqrt(sum);
	return result;
}

vector3i vector3i::operator+=(vector3i rvalue) {
	int i;
	int sum = 0;
	for(i = 0; i < 3; ++i) {
		comp[i] += rvalue.comp[i];
		sum += comp[i] * comp[i];
	}

	magnitude = sqrt(sum);
}

vector3i vector3i::operator-(vector3i rvalue) {
	int i;
	int sum = 0;
	vector3i result;
	for(i = 0; i < 3; ++i) {
		result.comp[i] = comp[i] - rvalue.comp[i];
		sum += result.comp[i] * result.comp[i];
	}
	
	result.magnitude = sqrt(sum);
	return result;
}

vector3i vector3i::operator-=(vector3i rvalue) {
	int i;
	int sum = 0;
	for(i = 0; i < 3; ++i) {
		comp[i] -= rvalue.comp[i];
		sum += comp[i] * comp[i];
	}

	magnitude = sqrt(sum);
}

vector3i vector3i::operator*(float rvalue) {
	int i;
	vector3i result;
	for(int i = 0; i < 3; ++i) {
		result.comp[i] = comp[i] * rvalue;
	}
	
	result.magnitude = magnitude * rvalue;
	return result;
}

vector3i vector3i::operator*=(float rvalue) {
	int i;
	for(int i = 0; i < 3; ++i) {
		comp[i] *= rvalue;
	}
	
	magnitude *= rvalue;
}

// Data access functions
void vector3i::set_components(int a, int b, int c) {
	comp[0] = a;
	comp[1] = b;
	comp[2] = c;
	
	int i, sum = 0;
	for(i = 0; i < 3; ++i) {
		sum += comp[i] * comp[i];
	}

	magnitude = sqrt(sum);
}

float vector3i::get_magnitude() {

	return magnitude;
}

void vector3i::normalise() {

	int i;
	for(i = 0; i < 3; ++i) {
		comp[i] *= 1.0 / magnitude;
	}

	magnitude = 1.0;
}

//
// vector3f
//

// Constructor / Destructor
vector3f::vector3f() {
	comp[0] = 0.0;
	comp[1] = 0.0;
	comp[2] = 0.0;
	magnitude = 0.0;
}

vector3f::~vector3f() {
	comp[0] = 0.0;
	comp[1] = 0.0;
	comp[2] = 0.0;
	magnitude = 0.0;
}

// Overloaded operators
vector3f vector3f::operator+(vector3f rvalue) {
	int i;
	float sum = 0.0;
	vector3f result;
	for(i = 0; i < 3; ++i) {
		result.comp[i] = comp[i] + rvalue.comp[i];
		sum += result.comp[i] * result.comp[i];
	}
	
	result.magnitude = sqrt(sum);
	return result;
}

vector3f vector3f::operator+=(vector3f rvalue) {
	int i;
	float sum = 0.0;
	for(i = 0; i < 3; ++i) {
		comp[i] += rvalue.comp[i];
		sum += comp[i] * comp[i];
	}

	magnitude = sqrt(sum);
}

vector3f vector3f::operator-(vector3f rvalue) {
	int i;
	float sum = 0;
	vector3f result;
	for(i = 0; i < 3; ++i) {
		result.comp[i] = comp[i] - rvalue.comp[i];
		sum += result.comp[i] * result.comp[i];
	}
	
	result.magnitude = sqrt(sum);
	return result;
}

vector3f vector3f::operator-=(vector3f rvalue) {
	int i;
	float sum = 0;
	for(i = 0; i < 3; ++i) {
		comp[i] -= rvalue.comp[i];
		sum += comp[i] * comp[i];
	}

	magnitude = sqrt(sum);
}

vector3f vector3f::operator*(float rvalue) {
	int i;
	vector3f result;
	for(int i = 0; i < 3; ++i) {
		result.comp[i] = comp[i] * rvalue;
	}
	
	result.magnitude = magnitude * rvalue;
	return result;
}

vector3f vector3f::operator*=(float rvalue) {
	int i;
	for(int i = 0; i < 3; ++i) {
		comp[i] *= rvalue;
	}
	
	magnitude *= rvalue;
}

// Data access functions
void vector3f::set_components(float a, float b, float c) {
	comp[0] = a;
	comp[1] = b;
	comp[2] = c;
	
	int i, sum = 0;
	for(i = 0; i < 3; ++i) {
		sum += comp[i] * comp[i];
	}

	magnitude = sqrt(sum);
}

float vector3f::get_magnitude() {

	return magnitude;
}

void vector3f::normalise() {

	int i;
	for(i = 0; i < 3; ++i) {
		comp[i] *= 1.0 / magnitude;
	}

	magnitude = 1.0;
}
