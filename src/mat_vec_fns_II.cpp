#include "mat_vec_fns_II.h"
#include <iostream>
using namespace std;

///////////////// SECTION 0 ////////////////////
////////  Constants and scalar functions ///////
////////////////////////////////////////////////
//
///  check whether two scalars have the same sign 
template <class t_scalar> bool sameSign(t_scalar a, t_scalar b){
 // return a <= ffea_const::zero == b <= ffea_const::zero;
 if (a*b >= 0) return true;
 return false;
}

/** Given 3 integers n0, n1, n2
 *    return the index missing in the list [0,1,2,3] 
 */
int getMissingNode(int n0, int n1, int n2) {

  if ((n0 == 0) || (n1 == 0) || (n2 ==0)) {
    if ((n0 == 1) || (n1 == 1) || (n2 ==1)) {
      if ((n0 == 2) || (n1 == 2) || (n2 ==2)) {
        return 3;
      } else {
        return 2;
      }
    } else {
      return 1;
    }
  } else {
    return 0;
  }

}

////////////////// SECTION 1 ///////////////////////
///  Basic operations for arr3, i. e., scalar v[3]// 
////////////////////////////////////////////////////
/** Add vectors vecA and vecB into res. */
/** res can also be vecA or vecB */
template <class brr3> void arr3arr3Add(brr3 &vecA, brr3 &vecB, brr3 &res){

   for (int i=0; i<3; i++) {
     res[i] = vecA[i] + vecB[i];
    }

}

/** res = vecA - vecB */
/** res can be either vecA or vecB */
// void arr3arr3Substract(arr3 &vecA, arr3 &vecB, arr3 &res){
template <class brr3> void arr3arr3Substract(brr3 &vecA, brr3 &vecB, brr3 &res){

   for (int i=0; i<3; i++) {
     res[i] = vecA[i] - vecB[i];
    }

}

/** w = u x v */
/**  (w != u) && (w != v) */
// void arr3arr3VectorProduct(arr3 (&u), arr3 (&v), arr3 (&w)){
template <class brr3> void arr3arr3VectorProduct(brr3 (&u), brr3 (&v), brr3 (&w)){

    w[0] = u[1]*v[2] - v[1]*u[2];
    w[1] = -u[0]*v[2] + v[0]*u[2];
    w[2] = u[0]*v[1] - v[0]*u[1];


}

/** return the dot product for arrays vecA and vecB */
// scalar arr3arr3DotProduct(arr3 &vecA, arr3 &vecB) {
template <class t_scalar, class brr3> t_scalar arr3arr3DotProduct(brr3 &vecA, brr3 &vecB) {

  t_scalar result = 0;
  for (int i=0; i<3; i++) {
     // cout << "vecA[" << i << "]: " << vecA[i] << " vecB[" << i << "]: " << vecB[i] << endl; 
     result += vecA[i] * vecB[i];
  }
  return result;
}

/** Normalise vector arr3 e */
template <class t_scalar, class brr3> void arr3Normalise(brr3 &e){

   t_scalar norm = 0.0;
   for (int i=0; i<3; i++) {
     norm += e[i]*e[i];
   }
   norm = sqrt(norm);
   for (int i=0; i<3; i++) {
     e[i] /= norm;
   }

}

/** get the normalised vector of arr3 e into arr3 n */
template <class t_scalar, class brr3> void arr3Normalise2(brr3 &e, brr3 &n){

   t_scalar norm = 0.0;
   for (int i=0; i<3; i++) {
     norm += e[i]*e[i];
   }
   norm = sqrt(norm);
   for (int i=0; i<3; i++) {
     n[i] = e[i]/norm;
   }

}

/** resize vector u, given scalar f */
template <class t_scalar, class brr3> void arr3Resize(t_scalar f, brr3 &u){

   for (int i=0; i<3; i++) {
      u[i] *= f;
    }

}

/** resize vector u into vector v, given scalar f */
template <class t_scalar, class brr3> void arr3Resize2(t_scalar f, brr3 &u, brr3 &v){

   for (int i=0; i<3; i++) {
      v[i] = f*u[i];
    }

}

/** cp arr3 u into arr3 v */ 
template <class brr3> void arr3Store(brr3 &u, brr3 &v){

   for (int i=0; i<3; i++) {
     v[i] = u[i];
    }

}

/** return the distance from vecA to vecB */
template <class t_scalar, class brr3> t_scalar arr3arr3Distance(brr3 &vecA, brr3 &vecB){
 
    t_scalar d=0;
    for (int i=0; i<3; i++){ 
      d  += (vecA[i] - vecB[i])*(vecA[i] - vecB[i]); 
    } 
    return sqrt(d); 
}


/** Return the length of a vector v */
template <class t_scalar> t_scalar mag(t_scalar (&v)[3]) {

   t_scalar s;
   for (int i=0; i<3; i++) {
      s += v[i] * v[i];
   }
   return sqrt(s);

}

template <class brr3> void arr3Initialise(brr3 &v){

    for (int i=0; i<3; i++) {
      v[i] = ffea_const::zero;
    }

}




////////////////////////////////////////////////
////////////// END OF SECTION 1 ////////////////
////////////////////////////////////////////////


///////////////// SECTION 2 ////////////////////
////// Geometric functions for arr3 types //////
////////////////////////////////////////////////
/** t = unit(vecA - vecB) */
/** t can be either vecA or vecB */
// void tangent(arr3 &vecA, arr3 &vecB, arr3 &t){
template <class t_scalar, class brr3>  void tangent(brr3 &vecA, brr3 &vecB, brr3 &t){

   t_scalar w=0;
   for (int i=0; i<3; i++) {
     t[i] = vecA[i] - vecB[i];
     w += t[i] * t[i];
    }
    w = sqrt(w);
    for (int i=0; i<3; i++) {
      t[i] /= w;
    }

}

/** w = unit(u x v) */
/**  (w != u) && (w != v) */
template <class t_scalar, class brr3> void getUnitNormal(brr3 &u, brr3 &v, brr3 &w){

   w[0] = u[1]*v[2] - v[1]*u[2];
   w[1] = -u[0]*v[2] + v[0]*u[2];
   w[2] = u[0]*v[1] - v[0]*u[1];
   t_scalar l;
   l = sqrt( w[0]*w[0] + w[1]*w[1] + w[2]*w[2] );
   for (int i=0; i<3; i++) {
     w[i] /= l;
   }
}


/** calculate the normal vector n to the plane defined by the three points */
template <class t_scalar, class brr3> void getNormal(brr3 &v1, brr3 &v2, brr3 &v3, brr3 &n){

   brr3 pl1, pl2;
   arr3arr3Substract(v2, v1, pl1);
   arr3arr3Substract(v3, v1, pl2);
   getUnitNormal<t_scalar,brr3>(pl1, pl2, n);

}


/* Given the face formed by tetA[0]:tetA[1]:tetA[2] 
 * get n, the normal to a face pointing inwards.
 */
template <class t_scalar, class brr3> void getNormalInwards(brr3 (&tetA)[4], int n0, int n1, int n2, brr3 &n){

   // pl1 and pl2 are the unit vectors (tetA[n1] - tetA[n0]) and (tetA[n2] - tetA[n0]), 
   brr3 pl1, pl2, aux;
   arr3arr3Substract(tetA[n1], tetA[n0], pl1);
   arr3arr3Substract(tetA[n2], tetA[n0], pl2);
   // n is a unit vector normal to the face:
   arr3arr3VectorProduct(pl1, pl2, aux);
   arr3Normalise2<t_scalar,brr3>(aux, n);
   // but it must be inwards, i. e., on the same side of the plane than n3. 
   int n3 = getMissingNode(n0, n1, n2);
   arr3arr3Add(aux, tetA[n0], aux);
   t_scalar d = - arr3arr3DotProduct<t_scalar,brr3>(n, tetA[n0]);
   t_scalar t1 = arr3arr3DotProduct<t_scalar,brr3>(tetA[n3], n) + d;
   t_scalar t2 = arr3arr3DotProduct<t_scalar,brr3>(aux, n) + d;
   if (!sameSign(t1,t2)) arr3Resize<t_scalar>(ffea_const::mOne, n);

}


/** check if points vec and test are at the same side
 *  of the plane formed by p1, p2 and p3 
 */
template <class t_scalar, class brr3> bool sameSidePlane(brr3 &vec, brr3 &test, brr3 &p1, brr3 &p2, brr3 &p3){

   brr3 pl1, pl2, n;
   arr3arr3Substract(p2, p1, pl1);
   arr3arr3Substract(p3, p1, pl2);
   arr3arr3VectorProduct(pl1, pl2, n);
   arr3Normalise<t_scalar,brr3>(n);
   t_scalar d = - arr3arr3DotProduct<t_scalar,brr3>(n, p1);
   t_scalar t1 = arr3arr3DotProduct<t_scalar,brr3>(vec, n) + d;
   t_scalar t2 = arr3arr3DotProduct<t_scalar,brr3>(test, n) + d;
   // if ((t1 * t2) >= 0 ) return true;
   // cout << "t1: " << t1 << " t2: " << t2 << endl; 
   if (sameSign(t1,t2)) return true;
   else return false;

}

/**  Given 4 co-planar points, check if ip and p1 lay on the same side 
 *     of the of the line formed by p2 and p3. 
 *   More specifically we check whether pl23 x pl21 and pl23 x pl2e 
 *     are parallel or antiparallel. 
 */
template <class t_scalar, class brr3> bool sameSideLine(brr3 &e, brr3 &p1, brr3 &p2, brr3 &p3) {

   // if (!samePlane(e, p1, p2, p3)) cout << "alarm" << endl;
   brr3 pl23, pl21, pl2e, v1, ve;
   arr3arr3Substract(p3, p2, pl23);
   arr3arr3Substract(p1, p2, pl21);
   arr3arr3Substract(e, p2, pl2e);
   arr3arr3VectorProduct(pl21, pl23, v1);
   arr3arr3VectorProduct(pl2e, pl23, ve);
   if (arr3arr3DotProduct<t_scalar,brr3>(v1,ve) >= 0) return true;
   return false;

}

/**  check whether vector vec is in tetrahedron B. */
/**  more specifically, it will be there if 
 *     for each plane of the tetrahedron, 
 *     the point is on the same side as the remaining vertex */
// bool nodeInTet(arr3 &vec, arr3 (tet)[4]){
template <class t_scalar,class brr3> bool nodeInTet(brr3 &vec, brr3 (tet)[4]){

   if (!sameSidePlane<t_scalar,brr3>(vec, tet[0], tet[1], tet[2], tet[3])) return false;
   if (!sameSidePlane<t_scalar,brr3>(vec, tet[1], tet[2], tet[3], tet[0])) return false;
   if (!sameSidePlane<t_scalar,brr3>(vec, tet[2], tet[3], tet[0], tet[1])) return false;
   if (!sameSidePlane<t_scalar,brr3>(vec, tet[3], tet[0], tet[1], tet[2])) return false;

   return true;

}

/** find the intersection point of the line that passes through the points e1 and e2, 
 *   and the plane defined by points p1, p2 and p3.
 *  \warning {this function should be called ONLY in the case 
 *            that intersection is known to occur.} 
 */
template <class t_scalar, class brr3> void linePlaneIntersectionPoint(brr3 &ip, brr3 &e1, brr3 &e2, brr3 &p1, brr3 &p2, brr3 &p3) {

   // v is the vector of the line L(t) = e1 + v*t
   brr3 v;
   arr3arr3Substract(e2, e1, v);

   // now we need the unit vector that defines the plane, pn:
   brr3 pl1, pl2, pn;
   arr3arr3Substract(p2, p1, pl1);
   arr3arr3Substract(p3, p2, pl2);
   getUnitNormal<t_scalar,brr3>(pl1, pl2, pn);

   // the plane is defined through: ax + by + cz + d = 0; 
   //   (a,b,c) = pn
   // so to find d we simply:
   t_scalar d = - arr3arr3DotProduct<t_scalar,brr3>(pn, p1);

   // now find t and the point:
   t_scalar t = - (arr3arr3DotProduct<t_scalar,brr3>(pn, e1) + d) / arr3arr3DotProduct<t_scalar,brr3>(pn, v);
   arr3Resize<t_scalar>(t, v);
   arr3arr3Add(e1, v, ip);

}

/** Check whether point ip is  
  *    inside of the three half-planes formed by the triangle's edges p1, p2, p3.
  */
template <class t_scalar, class brr3> bool isPointInFace(brr3 &ip, brr3 &p1, brr3 &p2, brr3 &p3) {

  if (! sameSideLine<t_scalar,brr3>(ip, p1, p2, p3) ) return false;
  if (! sameSideLine<t_scalar,brr3>(ip, p3, p1, p2) ) return false;
  if (! sameSideLine<t_scalar,brr3>(ip, p2, p3, p1) ) return false;

  return true;
}


/** Check whether an edge and a plane intersect, 
 *    and return the intersection point ip and true if found, false otherwise.
 * more specifically check that both:
 *    - both ends of the edge (e1 and e2) are on different sides
 *           of the plane defined by the vectors (tet[f2] - tet[f1]) and (tet[f3] - tet[f1]).
 *    - the intersection of a line is a point in the plane 
 */
// bool intersectionPoint(arr3 &(ip), arr3 (&e1), arr3 (&e2), arr3 (&tet)[4], int f1, int f2, int f3){
template <class t_scalar,class brr3> bool intersectionPoint(brr3 &(ip), brr3 (&e1), brr3 (&e2), brr3 (&tet)[4], int f1, int f2, int f3){

  // check it e1 and e2 are on the same side of the plane:
  if ( sameSidePlane<t_scalar,brr3>(e1, e2, tet[f1], tet[f2], tet[f3]) ) return false;

  // given that they are on different sides of the plane look for the intersection point.
  linePlaneIntersectionPoint<t_scalar,brr3>(ip, e1, e2, tet[f1], tet[f2], tet[f3]);

  // and finally check whether this point ip belongs to the triangular face:
  if ( (isPointInFace<t_scalar,brr3>(ip, tet[f1], tet[f2], tet[f3])) ) return true;


  return false;

}

///////////////// SECTION 3 ////////////////////
/// Transition functions from vector3 to arr3 // 
////////////////////////////////////////////////
void vec3Vec3SubsToArr3(vector3 &u, vector3 &v, arr3 (&w)){

    w[0] = u.x - v.x;
    w[1] = u.y - v.y;
    w[2] = u.z - v.z;

}

void vec3Arr3SubsToArr3(vector3 &u, arr3 (&v), arr3 (&w)){

    w[0] = u.x - v[0];
    w[1] = u.y - v[1];
    w[2] = u.z - v[2];

}

void vec3Arr3AddToArr3(vector3 &u, arr3 (&v), arr3 (&w)){

    w[0] = u.x + v[0];
    w[1] = u.y + v[1];
    w[2] = u.z + v[2];

}

void vec3ResizeToArr3(scalar f, vector3 &u, arr3 (&v)){

    v[0] = f*u.x;
    v[1] = f*u.y;
    v[2] = f*u.z;

}

scalar vec3Arr3DotProduct(vector3 &u, arr3 &v) {

     scalar s;
     s = u.x * v[0];
     s += u.y * v[1];
     s += u.z * v[2];
     return s;

}


////////////// END OF SECTION 3 ////////////////


///////////////// SECTION 3 ////////////////////
// // // // Instantiate templates // // // // //
////////////////////////////////////////////////
template bool sameSign<scalar>(scalar a, scalar b);
template bool sameSign<geoscalar>(geoscalar a, geoscalar b);


template void arr3arr3Add<arr3>(arr3 &vecA, arr3 &vecB, arr3 &res);
template void arr3arr3Add<grr3>(grr3 &vecA, grr3 &vecB, grr3 &res);

template void arr3arr3Substract<arr3>(arr3 &vecA, arr3 &vecB, arr3 &res);
template void arr3arr3Substract<grr3>(grr3 &vecA, grr3 &vecB, grr3 &res);

template void arr3arr3VectorProduct<arr3>(arr3 (&u), arr3 (&v), arr3 (&w));
template void arr3arr3VectorProduct<grr3>(grr3 (&u), grr3 (&v), grr3 (&w));

template scalar arr3arr3DotProduct<scalar,arr3>(arr3 &vecA, arr3 &vecB);
template geoscalar arr3arr3DotProduct<geoscalar,grr3>(grr3 &vecA, grr3 &vecB);

template void arr3Normalise<scalar,arr3>(arr3 &e);
template void arr3Normalise<geoscalar,grr3>(grr3 &e);

template void arr3Normalise2<scalar,arr3>(arr3 &e, arr3 &n);
template void arr3Normalise2<geoscalar,grr3>(grr3 &e, grr3 &n);

template void arr3Resize<scalar,arr3>(scalar f, arr3 &u);
template void arr3Resize<geoscalar,grr3>(geoscalar f, grr3 &u);

template void arr3Resize2<scalar,arr3> (scalar f, arr3 &u, arr3 &v);
template void arr3Resize2<geoscalar,grr3> (geoscalar f, grr3 &u, grr3 &v);

template void arr3Store<arr3>(arr3 &u, arr3 &v);
template void arr3Store<grr3>(grr3 &u, grr3 &v);

template scalar arr3arr3Distance<scalar,arr3>(arr3 &vecA, arr3 &vecB); 
template geoscalar arr3arr3Distance<geoscalar,grr3>(grr3 &vecA, grr3 &vecB); 

template scalar mag<scalar>(scalar (&v)[3]);
template geoscalar mag<geoscalar>(geoscalar (&v)[3]);

template void arr3Initialise<arr3>(arr3 &v);
template void arr3Initialise<grr3>(grr3 &v);




template void tangent<scalar,arr3>(arr3 &vecA, arr3 &vecB, arr3 &t);
template void tangent<geoscalar,grr3>(grr3 &vecA, grr3 &vecB, grr3 &t);

template void getUnitNormal<scalar,arr3>(arr3 &u, arr3 &v, arr3 &w);
template void getUnitNormal<geoscalar,grr3>(grr3 &u, grr3 &v, grr3 &w);

template void getNormal<scalar,arr3>(arr3 &v1, arr3 &v2, arr3 &v3, arr3 &n);
template void getNormal<geoscalar,grr3>(grr3 &v1, grr3 &v2, grr3 &v3, grr3 &n);

template void getNormalInwards<scalar,arr3>(arr3 (&tetA)[4], int n0, int n1, int n2, arr3 &n);
template void getNormalInwards<geoscalar,grr3>(grr3 (&tetA)[4], int n0, int n1, int n2, grr3 &n);

template bool sameSidePlane<scalar,arr3>(arr3 &vec, arr3 &test, arr3 &p1, arr3 &p2, arr3 &p3);
template bool sameSidePlane<geoscalar,grr3>(grr3 &vec, grr3 &test, grr3 &p1, grr3 &p2, grr3 &p3);

template bool sameSideLine<scalar,arr3>(arr3 &e, arr3 &p1, arr3 &p2, arr3 &p3);
template bool sameSideLine<geoscalar,grr3>(grr3 &e, grr3 &p1, grr3 &p2, grr3 &p3);

template bool nodeInTet<scalar,arr3>(arr3 &vec, arr3 (tet)[4]);
template bool nodeInTet<geoscalar,grr3>(grr3 &vec, grr3 (tet)[4]);

template void linePlaneIntersectionPoint<scalar,arr3>(arr3 &ip, arr3 &e1, arr3 &e2, arr3 &p1, arr3 &p2, arr3 &p3);
template void linePlaneIntersectionPoint<geoscalar,grr3>(grr3 &ip, grr3 &e1, grr3 &e2, grr3 &p1, grr3 &p2, grr3 &p3);

template bool isPointInFace<scalar,arr3>(arr3 &ip, arr3 &p1, arr3 &p2, arr3 &p3);
template bool isPointInFace<geoscalar,grr3>(grr3 &ip, grr3 &p1, grr3 &p2, grr3 &p3);

template bool intersectionPoint<scalar,arr3>(arr3 &(ip), arr3 (&e1), arr3 (&e2), arr3 (&tet)[4], int f1, int f2, int f3);
template bool intersectionPoint<geoscalar,grr3>(grr3 &(ip), grr3 (&e1), grr3 (&e2), grr3 (&tet)[4], int f1, int f2, int f3);

