#ifndef __easyVexPlanes_h__
#define __easyVexPlanes_h__

//Required if included on its own:
#include "easyVexGeneral.h"
#include "easyVexEdges.h"
#include "easyVexLines.h" 

/**
 * Plane struct and functions.
 */

/**
 * The planeStruct represents an infinite plane in 3D space. 
 * It has a normal direction and goes through position pos.
 */
struct planeStruct{
	vector normal, pos; //normal = direction and normal of the plane. pos = a point on the plane

	/**
	 * Returns the normal of the plane
	 * 
	 * Example: vector norm = normal(plane1);
	 */
	vector normal(){
		return normalize(this.normal);//this normalization should be moved to a constructor
	}

	/**
	 * Returns a position on the plane
	 * 
	 * Example: vector position = pos(plane1);
	 */
	vector pos(){
		return this.pos;
	} 
}

/**
 * Returns a planeStruct given a primitive number and the input
 *
 * @param {int}	{input}   an integer that describes an input
 * @param {int}	{prim}   a primitive number (primitive id)
 */
planeStruct planeStruct(const int input; const int prim){
	int pts[] = primpoints(input, prim);
	vector pos = pointp(input,pts[0]);
	vector normal = {0,1,0}; //Definition for fallback
	if(hasprimattrib(input,"N")){ //Try to find primitive normal
		normal = normalize( prim(input, "N", prim) );
		return planeStruct(normal, pos);
	}
	if(haspointattrib(input,"N")){ //Try to find point normal
		normal = normalize( point(input, "N", pts[0]) );
		return planeStruct(normal, pos);
	}
	if(hasvertexattrib(input,"N")){ //Try to find vertex normal
		normal = normalize( vertex(input, "N", prim, 0) );
		return planeStruct(normal, pos);
	}
	if(len(pts)>2){ //Generate normal from point positions
		warning("planestruct_fromprim: Had to generate normal attribute from point positions.");
		normal = normalize ( cross(pointp(input,pts[1])-pointp(input,pts[0]), pointp(input,pts[0])-pointp(input,pts[2]) ) );
		return planeStruct(normal, pos);
	}
	warning("planestruct_fromprim: Could not find or generate normal. Using fallback {0,1,0}.");
	return planeStruct(normal, pos); // Backup
}

/**
 * Returns a planeStruct given a primitive number at input 0
 *
 * @param {int}	{prim}   a primitive number (primitive id)
 */
planeStruct planeStruct(const int prim){
	int input = 0;
	int pts[] = primpoints(input, prim);
	vector pos = pointp(input,pts[0]);
	vector normal = {0,1,0}; //Definition for fallback
	if(hasprimattrib(input,"N")){ //Try to find primitive normal
		normal = normalize( prim(input, "N", prim) );
		return planeStruct(normal, pos);
	}
	if(haspointattrib(input,"N")){ //Try to find point normal
		normal = normalize( point(input, "N", pts[0]) );
		return planeStruct(normal, pos);
	}
	if(hasvertexattrib(input,"N")){ //Try to find vertex normal
		normal = normalize( vertex(input, "N", prim, 0) );
		return planeStruct(normal, pos);
	}
	if(len(pts)>2){ //Generate normal from point positions
		warning("planestruct_fromprim: Had to generate normal attribute from point positions.");
		normal = normalize ( cross( pointp(input,pts[1])-pointp(input,pts[0]), pointp(input,pts[0])-pointp(input,pts[2]) ) );
		return planeStruct(normal, pos);
	}
	warning("planestruct_fromprim: Could not find or generate normal. Using fallback {0,1,0}.");
	return planeStruct(normal, pos); // Backup
}

/**
 * Returns the closest distance between a point and an (infinite) plane defined by a planeStruct.
 * If the point is under the plane (based on plane's normal) the value is negative.
 *
 * @param {int}	{input}   an integer that describes an input
 * @param {int}	{point}   a point number (point id)
 * @param {planeStruct}	{plane}	a planeStruct
 */
float distance(const int input; const int point; const planeStruct plane){
	float dist = dot( pointp(input,point)-pos(plane), normal(plane));
	return dist;
}

/**
 * Returns the closest distance between a position and an (infinite) plane defined by a planeStruct.
 * If the position is under the plane (based on plane's normal) the value is negative.
 *
 * @param {vector}	{pos}   position
 * @param {planeStruct}	{plane}	a planeStruct
 */
float distance(const vector pos; const planeStruct plane){
	float dist = dot( pos-pos(plane), normal(plane));
	return dist;
}

/**
 * Returns 1 if the line is on the plane. Otherwise it returns 0.
 *
 * @param {lineStruct}	{line}   a lineStruct
 * @param {planeStruct}	{plane}	a planeStruct
 */
int lineonplane(const lineStruct line; const planeStruct plane){
	vector a = posa(line);
	vector b = posb(line);
	if( distance(a,plane)==0 && distance(b,plane)==0 ){
		return 1;
	}
	return 0;
}

/////////////////////////////////////////FIX THIS TO ACCOUNT FOR DIFFERENT lineStruct types/////////////////////
/**
 * Returns intersection location between lineStruct and planeStruct and edits an int "success" variable
 * WARNING: This currently does not account for different line types. 
 * Also the success results will be changed so failure will be encoded with 0 or a negative number and success will be a number greater
 * 
 * success:
 * 0 => Failure, no intersection. The planeStruct and the lineStruct never intersect
 * 1 => The plane intersects the line in the returned position
 * 2 => Failure. The lineStruct lies in the plane (is parallel to it) 
 * 3 => The intersection lies outside the segment
 *
 * @param {planeStruct}	{plane}	a planeStruct
 * @param {lineStruct}	{line}	a lineStruct
 * @param {int}	{success}	a variable that is passed by reference (is manipulated by the function). It will return "success" (as explained above) 
 * 
 * From: https://de.mathworks.com/matlabcentral/fileexchange/17751-straight-line-and-plane-intersection
 */
vector intersection(const planeStruct plane; const lineStruct line; int success){
	vector result = {0,0,0};
	vector linedir = direction(line);
	vector toline = posa(line) - pos(plane);
	float D = dot( normal(plane) - linedir);
	float N = - dot( normal(plane) , toline);
	success = 0;
	if(abs(D) < 0.0000001 ){ //The segment is parallel to plane  //10^-7
		if(N == 0){
			success = 2; //the segment lies on the plane
			return result;
		}
		else{
			success = 0; //no intersection
			return result;
		}
	}
	//compute the intersection parameter
	float sI = N / D;
	result = posa(line) + sI * linedir;

	success = sI<0||sI>1 ? 3:1; //If true, the intersection point lies outside the segment, so there is no intersection

	return result; 
}

/**
 * Returns 1 if two planeStructs are the same. Otherwise it returns 0.
 *
 * @param {planeStruct}	{p1}	a planeStruct
 * @param {planeStruct}	{p2}	a planeStruct
 */
int same(const planeStruct p1,p2){
	vector dir = cross(normal(p1),normal(p2)); //direction of line
    vector orthogonalp1 = cross( normal(p2), dir); //similar to p1 but orthogonal to p2    
    float numerator = dot( normal(p1), orthogonalp1); //length of p1 on orthogonalp1
    if(abs(numerator) <0.000001){ //bail if the planes are essentially the same
		return 1;
	}
	return 0;
}

/**
 * Returns lineStruct at the intersection of two planes
 *
 * @param {planeStruct}	{p1}	a planeStruct
 * @param {planeStruct}	{p2}	a planeStruct
 * 
 * Solution based on https://forum.unity.com/threads/how-to-find-line-of-intersecting-planes.109458/
 */
lineStruct lineStruct(const planeStruct p1,p2){
	vector dir = cross(normal(p1),normal(p2)); //direction of line

    vector orthogonalp1 = cross( normal(p2), dir); //similar to p1 but orthogonal to p2    
    float numerator = dot( normal(p1), orthogonalp1); //length of p1 on orthogonalp1

    if(abs(numerator) <0.000001){ //bail if the planes are essentially the same
		warning("linestruct_fromplanes(%e,%e): planes are parallel, therefore no line makes sense",p1, p2);
		return lineStruct({0,0,0},{0,1,0},1);
	}
	vector p2_pos = pos(p2);
    vector p2p1 = pos(p1) - p2_pos; //vector p2 to p1
	float t = dot( normal(p1), p2p1) / numerator; //p2p1 projected onto p1 normalized for orthogonalp1
	vector pos = p2_pos + t * orthogonalp1; //go from p2 via orthogonalp1 to p1

	return lineStruct(pos,dir+pos,1); 
}

////////////////////////////////////////
////////////////////////////////////////
///////////////do this//////////////////
////////////////////////////////////////

/**
 * Returns the angle between a planeStruct and a lineStruct in degrees
 * 
 * @param {lineStruct}	{l1}  a lineStruct
 * @param {planeStruct}	{plane}  a planeStruct
 * 
 * Example: f@angle = angle(line,plane);
 */
function float angle_d(const lineStruct l1; const planeStruct plane){
	vector u = vectorab_n(l1);
	vector v = normal(plane);
	return degrees( acos( dot(u,v)  ) );
}

//to do: line - plane intersection point (if line on plane return plane reference point, will require success parameter)
//to do: intersection of 3 planes http://geomalgorithms.com/a05-_intersect-1.html ?maybe
//to do: point closest to 3 planes ?maybe

#endif
