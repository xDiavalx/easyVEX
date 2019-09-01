#ifndef __easyVexLines_h__
#define __easyVexLines_h__

//Required if included on its own:
#include "easyVexGeneral.h"
#include "easyVexEdges.h"

/**
 * Line struct and functions
 */

/**
 * The lineStruct represents a mathematical line. 
 * It has two points (A,B) and a type (type). 
 * The type is used like an enum. It determines whether the line ends at each point, 
 * or whether the line extends to mathematical infinity. 
 *
 *	type:
 *	(0) a line-segment
 *	(1) an infinite line
 *	(2) a line starting at B and extending (infinitely) in direction A
 *	(3) a line starting at A and extending (infinitely) in direction B
 */
struct lineStruct{
	vector A,B; //point A and B on a line 
	/*The type determines whether it is
	(0) a line-segment, 
	(1) an infinite line, 
	(2) a line starting at B and extending (infinitely) in direction A or
	(3) a line starting at A and extending (infinitely) in direction B.
	*/
	int type; //closed==0, open==1, openA==2, openB==3; See comment above 

	//lineStruct Functions:
	
	/**
 	 * Returns point A position on line
 	 *
 	 * Example: vector positiona = posa(line1);
 	 */
	vector posa(){
		return this.A;
	}

	/**
 	 * Returns point B position on line
 	 *
  	 * Example: vector positionb = posb(line1);
 	 */
	vector posb(){
		return this.B;
	}

	/**
	 * Returns type of line
 	 * 
	 * The type determines whether it is:
	 * (0) a line-segment
	 * (1) an infinite line 
	 * (2) a line starting at B and extending (infinitely) in direction A
	 * (3) a line starting at A and extending (infinitely) in direction B
	 *
 	 * Example: int lineType = type(line1);
	 */
	int type(){
		return this.type;
	}

	/**
 	 * Returns vector AB normalized
 	 *
 	 * Example: vector dir_n = vectorab_n(line1);
 	 */
	vector vectorab_n(){
		return normalize(this.B-this.A);
	}

	/**
 	 * Returns vector AB
 	 *
 	 * Example: vector dir = vectorab(line1);
 	 */
	vector vectorab(){
		return this.B-this.A;
	}


	/**
 	 * Returns 1 if A and B are NOT the same and otherwise returns 0. 
 	 * If A and B were equal (return 0) the struct would be invalid.
 	 *
 	 * Example: int verification = verify(line1);
 	 */
	int verify(){
		return this.A==this.B ? 0 : 1; 
	}
}

/**
 * Returns a line struct from an edgeStruct at input 0, of type 0 (closed)
 *
 * @param {edgeStruct}	{edge}   an edgeStruct
 */
lineStruct lineStruct(const edgeStruct edge){
	lineStruct line = lineStruct(posa(edge),posb(edge),0);
	return line;
}

/**
 * Returns a line struct from an edgeStruct at input 0, of type
 *
 * @param {edgeStruct}	{edge}   an edgeStruct
 * @param {int}	{type}	an integer indicating the type of the lineStruct (see lineStruct types)
 *
 * lineStruct types:
 * (0) a line-segment
 * (1) an infinite line 
 * (2) a line starting at B and extending (infinitely) in direction A
 * (3) a line starting at A and extending (infinitely) in direction B
 */
lineStruct lineStruct(const edgeStruct edge; const int type){
	lineStruct line = lineStruct(posa(edge),posb(edge),type);
	return line;
}

/**
 * Returns a line struct from an edgeStruct at input, of type 0 (closed)
 *
 * @param {int}	{input}   an integer that describes an input
 * @param {edgeStruct}	{edge}   an edgeStruct
 */
lineStruct lineStruct(const int input; const edgeStruct edge){
	lineStruct line = lineStruct(posa(input, edge),posb(input, edge),0);
	return line;
}

/**
 * Returns a line struct from an edgeStruct at input, of type
 *
 * @param {int}	{input}   an integer that describes an input
 * @param {edgeStruct}	{edge}   an edgeStruct
 * @param {int}	{type}	an integer indicating the type of the lineStruct (see lineStruct types)
 *
 * lineStruct types:
 * (0) a line-segment
 * (1) an infinite line 
 * (2) a line starting at B and extending (infinitely) in direction A
 * (3) a line starting at A and extending (infinitely) in direction B
 */
lineStruct lineStruct(const int input; const edgeStruct edge; const int type){
	lineStruct line = lineStruct(posa(input, edge),posb(input, edge),type);
	return line;
}

/**
 * Returns minimum distance between a lineStruct and pos X 
 * http://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html
 *
 * @param {lineStruct}	{line}	a lineStruct
 * @param {vector}	{X}	a position
 */
float distance(const lineStruct line; const vector X){
	vector A = posa(line);
	vector B = posb(line);
	int type = type(line);
	float dist = length( cross(X-A,X-B) )/length(B-A);

	//infinite line
	if(type==1){ 
		return dist;
	}
	float dista = distance(A,X);
	float distb = distance(B,X);

	float dirAX = dot((X-A),(B-A));

	//closed at A
	if(type==3){ 
		if(dirAX<0){ //if X further from B than A
			return length((X-A));
		}
		return dist;
	}
	float dirBX = dot((X-B),(A-B));

	//closed at B
	if(type==2){
		if(dirBX<0){
			return length((X-B));
		}
		return dist;
	}

	//closed line segment
	if(type==0){
		if(dirAX<0){
			return dista;
		}
		if(dirBX<0){
			return distb;
		}
		return dist;
	}
	//fallback:
	return dist;
}

/**
 * Returns 1 if both lines are on the same infinite line (otherwise 0)
 *
 * @param {lineStruct}	{l1}	a lineStruct
 * @param {lineStruct}	{l2}	a lineStruct
 */
int sameline(const lineStruct l1,l2){
	lineStruct line = lineStruct(posa(l1),posb(l1),1);
	vector normal1 = vectorab_n(l1);
	vector normal2 = vectorab_n(l2);
	float threshold = 0.0001;
	if( (length( normal1 - normal2)<threshold)||(length(-normal1 - normal2)<threshold) ){
		if( distance(line,posa(l2))<threshold ){
			return 1;
		}
	}
	return 0;
}

/**
 * Returns 1 or 2 if both lines share the same points (otherwise 0)
 *
 * Returns == 2 -> locations a and b are exactly the same
 * Returns == 1 -> locations a and b are exactly the same, but reversed
 * Returns == 0 -> one or more locations are different
 * 
 * @param {lineStruct}	{l1}	a lineStruct
 * @param {lineStruct}	{l2}	a lineStruct
 */
int samepoints(const lineStruct l1,l2){
	vector pa1 = posa(l1);
	vector pb1 = posb(l1);
	vector pa2 = posa(l2);
	vector pb2 = posb(l2);
	if( pa1==pa2 && pb1==pb2 ){
		return 2; 
	}
	if( pa1==pb2 && pb1==pa2 ){
		return 1;
	}
	return 0;
}

/**
 * Returns 1 or 2 if both lines share the same direction (otherwise 0)
 *
 * Returns == 2 -> directions for l1 and l2 are exactly the same
 * Returns == 1 -> directions for l1 and l2 are exactly the same, but reversed
 * Returns == 0 -> one or more directions are different
 * 
 * @param {lineStruct}	{l1}	a lineStruct
 * @param {lineStruct}	{l2}	a lineStruct
 */
int samedirections(const lineStruct l1,l2){
	vector normal1 = vectorab_n(l1);
	vector normal2 = vectorab_n(l2);
	float threshold = 0.0001;
	if( length( normal1 - normal2)<threshold ){
		return 2;
	}
	if( length(-normal1 - normal2)<threshold ){
		return 1;
	}
	return 0;
}

/**
 * Returns an integer array that describes the relationships between two lineStructs
 *
 * result[0] == 2 -> locations a and b are exactly the same
 * result[0] == 1 -> locations a and b are exactly the same, reversed
 * result[0] == 0 -> one or more locations are different
 *
 * result[1] == 2 -> normalized directions are exactly the same
 * result[1] == 1 -> normalized directions exactly the same, but reversed
 * result[1] == 0 -> normalized directions are different
 *
 * result[2] == 3 -> position of point a2 and b2 is on line l1
 * result[2] == 2 -> position of point b2 is on line l1
 * result[2] == 1 -> position of point a2 is on line l1
 * result[2] == 0 -> neither point a2 or b2 are on line l1
 *
 * result[3] == 3 -> position of point a1 and b1 is on line l2
 * result[3] == 2 -> position of point b1 is on line l2
 * result[3] == 1 -> position of point a1 is on line l2
 * result[3] == 0 -> neither point a1 or b1 are on line l2
 *
 * result[4] == 3 -> position of point a2 and b2 is on line segment a1b1
 * result[4] == 2 -> position of point b2 is on line segment a1b1
 * result[4] == 1 -> position of point a2 is on line segment a1b1
 * result[4] == 0 -> neither point a2 or b2 are on line segment a1b1
 *
 * result[5] == 3 -> position of point a1 and b1 is on line segment a2b2
 * result[5] == 2 -> position of point b1 is on line segment a2b2
 * result[5] == 1 -> position of point a1 is on line segment a2b2
 * result[5] == 0 -> neither point a1 or b1 are on line segment a2b2
 * 
 * @param {lineStruct}	{l1}	a lineStruct
 * @param {lineStruct}	{l2}	a lineStruct
 */
int[] same(const lineStruct l1,l2){
	int result[] = {0,0,0,0,0}; 
	vector normal1 = vectorab_n(l1);
	vector normal2 = vectorab_n(l2);
	vector pa1 = posa(l1);
	vector pb1 = posb(l1);
	vector pa2 = posa(l2);
	vector pb2 = posb(l2);
	float threshold = 0.0001;
	//position comparison
	if( pa1==pa2 && pb1==pb2 ){
		result[0] = 2;
	}
	if( pa1==pb2 && pb1==pa2 ){
		result[0] = 1;
	}

	//directions comparison
	if( length( normal1 - normal2)<threshold ){
		result[1] = 2;
	}
	if( length(-normal1 - normal2)<threshold ){
		result[1] = 1;
	}

	//l2 inside l1
	if( distance(l1, pa2)<threshold ){
		result[2] = 1; //a2 is on l1
	}
	if( distance(l1, pb2)<threshold ){
		//are both points inside? 
		if(result[2] == 1){ 
			result[2] = 3; //a2 and b2 are on l1
		}
		else{
			result[2] = 2; //b2 is on l1
		}
	}
	//l1 inside l2
	if( distance(l2, pa1)<threshold ){
		result[3] = 1; //a1 is on l1
	}
	if( distance(l2, pb1)<threshold ){
		//are both points inside? 
		if(result[3] == 1){ 
			result[3] = 3; //a1 and b1 are on l1
		}
		else{
			result[3] = 2; //b2 is on l1
		}
	}

	if( distance(pa2,pa1)+distance(pa2,pb1)-distance(pa1,pb1)<threshold ){
		result[4] = 1; //a2 lies on segment a1b1
	}
	if( distance(pb2,pa1)+distance(pb2,pb1)-distance(pa1,pb1)<threshold ){
		if(result[4] == 1){ 
			result[4] = 3; //segement a2b2 lies on segment a1b1
		}
		result[4] = 2; //b2 lies on segment a1b1
	}

	if( distance(pa1,pa2)+distance(pa1,pb2)-distance(pa2,pb2)<threshold ){
		result[5] = 1; //a1 lies on segment a2b2
	}
	if( distance(pb1,pa2)+distance(pb1,pb2)-distance(pa2,pb2)<threshold ){
		if(result[5] == 1){ 
			result[5] = 3; //segement a1b1 lies on segment a2b2
		}
		result[5] = 2; //b1 lies on segment a2b2
	}

	//result.z = type(l1)==type(l2);
	return result;
}

/**
 * Returns the angle between two lines in degrees
 * 
 * @param {lineStruct}	{l1}  a lineStruct
 * @param {lineStruct}	{l2}  a lineStruct
 * 
 * Example: f@angle = angle(l1,l2);
 */
function float angle_d(const lineStruct l1,l2){
	vector u = vectorab_n(l1);
	vector v = vectorab_n(l2);
	return degrees( acos( dot(u,v)  ) );
}

////////////////////////////////////////
////////////////////////////////////////
///////////////do this//////////////////
////////////////////////////////////////
//to do: line to line has intersection point?
//to do: line to line intersection point or closest point (with success parameter)
//to do: angle around and angle around_d for lines

#endif
