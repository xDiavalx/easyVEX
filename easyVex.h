#ifndef __easyVex_h__
#define __easyVex_h__

/*
* This Software was originally developed by Dimtiri Shimanovskiy.
* Feel free to use as you wish (http://unlicense.org/). Feedback is appreciated
* Credit and dontations are appreciated. If you credit me in a project, 
* send me a message to dimitri.shima.dev@gmail.com, so I can find out about it.
* Contributers:
* Matthew Hendershot
*
* License:
* This is free and unencumbered software released into the public domain.
*
* Anyone is free to copy, modify, publish, use, compile, sell, or
* distribute this software, either in source code form or as a compiled
* binary, for any purpose, commercial or non-commercial, and by any
* means.
*
* In jurisdictions that recognize copyright laws, the author or authors
* of this software dedicate any and all copyright interest in the
* software to the public domain. We make this dedication for the benefit
* of the public at large and to the detriment of our heirs and
* successors. We intend this dedication to be an overt act of
* relinquishment in perpetuity of all present and future rights to this
* software under copyright law.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*
* For more information, please refer to <http://unlicense.org/>
*
*
*
* NAME:	easyVex.h (VEX)
*
* COMMENTS:	This include file contains functions to improve quality of life and geometry editing.
*
* Instrcutions:
* 1. Put the easyVex.h file into 
* $HOUDINI_USER_PREF_DIR/vex/include/
* Just create the folders, if they don't exist already.
* 2. Type
* #include "easyVex.h"
* in the wrangle to be able to use the functions.
* If the file is in a subfolder it will be something like:
* #include "subfolder/easyVex.h"
*/

//General utility functions

//Returns position of the point closest to given position
//Contributed by Matthew Hendershot
function vector nearptpos( const int input; const vector pos)
{
return vector(point(input, “P”, int(nearpoint(input, pos))));
} 

//Returns int array of unique values (no duplicates) sorted in ascending order. 
function int[] uniquearray(const int numbers[]) {
	int localNumbers[] = {};
	int clean[] = {};
	int temp = 0;

	//fail safe
	if (len(numbers) == 0) {
		warning("Passed empty array into uniquearray function");
		return clean;
	}

	localNumbers = sort(numbers); // sort ascending to simplify the elimination of duplicates

	append(clean, localNumbers[0]); // the first element is always unique 

	for (int i = 1; i<len(numbers); i++) {
		if (clean[temp]<localNumbers[i]) { //if the number is bigger than the previously added, add it
			append(clean, localNumbers[i]);
			temp++; //temp is the last index in the clean array
		}
	}
	return clean;
}

//Adds only new int values (no duplicates) to an int array and returns the modified array.
function int[] appendunique(int numbers[]; const int num) {
	if (find(numbers, num)<0) {
		append(numbers, num);
	}
	return numbers;
}

//Removes all instances of int value from int array
function void removevalues(int numbers[]; const int remove) {
	while (1) {
		int temp;
		temp = removevalue(numbers, remove);
		if (temp == 0) {
			break;
		}
	}
}

//Removes all instances of all int values in seccond array from first int array
function void removevalues(int numbers[]; const int remove[]) {
	foreach(int i; remove){
		while(1) {
			int temp;
			temp = removevalue(numbers, i);
			if (temp == 0) {
				break;
			}
		}
	}
}

//Returns int array of unique values of an arbitrary attribute at input 0
function int[] uniquevals(string componentType; string attribName){	
	int clean[] = {};
	int count = nuniqueval(0, componentType, attribName);
	for (int i = 0; i < count; i++) {
		int val = uniqueval(0, componentType, attribName, i);
		append(clean,val);
	}
	return clean;
}
//Returns int array of unique values of an arbitrary attribute at input
function int[] uniquevals(int input; string componentType; string attribName){	
	int clean[] = {};
	int count = nuniqueval(input, componentType, attribName);
	for (int i = 0; i < count; i++) {
		int val = uniqueval(input, componentType, attribName, i);
		append(clean,val);
	}
 	return clean;
}

//Returns point position at input
function vector pointp(const int input; const int point){
	return point(input,"P",point);
}
//Returns point position at input 0
function vector pointp(const int point){
	return point(0,"P",point);
}

//Returns the angle between two vectors in degrees
//Example: f@angle = angle({0,1,0},{1,0,0});
function float angle_d(const vector u,v){
	return degrees( acos( dot(u,v)/( length(v)*length(u) )  ) );
}
//Returns the angle between two 2d vectors in degrees
//Example: f@angle = angle({0,1},{1,0});
function float angle_d(const vector2 u,v){
	return degrees( acos( dot(u,v)/( length(v)*length(u) )  ) );
}

//Returns dot product of two vectors, but normalizes the vectors beforehand
float dot_n(const vector u,v ){
	return dot(normalize(u),normalize(v));
}
//Returns dot product of two vector2s, but normalizes the vectors beforehand
float dot_n(const vector2 u,v ){
	return dot(normalize(u),normalize(v));
}



//Edges 
struct edgeStruct{
	int a,b;

	/*General info: 
	//To create a variable of type custom struct:
	edgeStruct ed1 = edgeStruct(1,2);
	
	//To use an internal variable of the struct:
	printf("%i\n",ed1.a);
	ed1.a = 6;

	//To use a function defined in a custom struct:
	printfVerbose(ed1);
	
	//To make an array of custom struct:
	edgeStruct ed2 = edgeStruct(3,2);
	edgeStruct ed3 = edgeStruct(4,5);
	edgeStruct edges[];
	push(edges,ed1);
	push(edges,ed2);
	push(edges,ed3);

	//To loop over a custom struct:
	foreach(edgeStruct test; edges){
	printfVerbose(test);
	printf("a is %i \n",test.a);
	}
	*/


	//print verbose edge description to log
	//example: printf(ed1); 
	void printfVerbose(){
		printf("edge between points %i and %i \n", a,b);
	}

	//returns a string in standard Houdini edge format
	//example: getfullname(ed1); 
	string getfullname(){
		return sprintf("p%i_%i", this.a, this.b);
	}

	//Returns a reversed version of the edge (a will b, and b will be a)
	//example: swap(ed1);
	void swap(){
		int c;
		c = this.a;
		this.a=this.b;
		this.b=c;
	}

	//returns 0 if a>b and 1 if b>a
	//example: compare(ed1);
	int compare(){
		return this.a>this.b;
	}

	//sorts a and b in increasing order
	//example: sort(ed1);
	void sort(){
		if( compare(this) ){
			swap(this);
		}
	}

	//returns the position of the edgepoint a at input
	//example: v@pos = posA(ed1,2);
	vector posA(const int input){
		return pointp(input,this.a);
	}

	//returns the position of the edgepoint a at input 0
	//example: v@pos = posA(ed1);
	vector posA(){
		return pointp(this.a);
	}

	//returns the position of the edgepoint b at input
	//example: v@pos = posB(ed1,2);
	vector posB(const int input){
		return pointp(input,this.b);
	}
	//returns the position of the edgepoint b at input 0
	//example: v@pos = posB(ed1);
	vector posB(){
		return pointp(this.b);
	}

	//returns the length of the edge at input
	//example: f@len = length(ed1,2);
	float length(const int input){
		return distance(pointp(input,this.a),pointp(input,this.b));
	}
	//returns the length of the edge at input 0
	//example: f@len = length(ed1);
	float length(){
		return distance(pointp(0,this.a),pointp(0,this.b));
	}

	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	//Following are functions for interpreting the edge as a vector//
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////

	//returns the non-normalized vector AB == posB - posA at input
	//example: v@vectorAB = vectorab(ed1,2);
	vector vectorab(const int input){
		return pointp(input,this.b) - pointp(input,this.a);
	}
	//returns the non-normalized vector AB == posB - posA at input 0
	//example: v@vectorAB = vectorab(ed1);
	vector vectorab(){
		return pointp(0,this.b) - pointp(0,this.a);
	}
	//returns the non-normalized vector BA == posA - posB at input
	//example: v@vectorBA = vectorba(ed1);
	vector vectorba(const int input){
		return pointp(input,this.a) - pointp(input,this.b);
	}
	//returns the non-normalized vector BA == posA - posB at input 0
	//example: v@vectorBA = vectorba(ed1);
	vector vectorba(){
		return pointp(0,this.a) - pointp(0,this.b);
	}

	//returns the normalized vector AB == posB - posA at input
	//example: v@vectorAB = vectorab_n(ed1,2);
	vector vectorab_n(const int input){
		return normalize( pointp(input,this.b) - pointp(input,this.a) );
	}
	//returns the normalized vector AB == posB - posA at input 0
	//example: v@vectorAB = vectorab_n(ed1);
	vector vectorab_n(){
		return normalize( pointp(0,this.b) - pointp(0,this.a) );
	}
	//returns the normalized vector BA == posA - posB at input
	//example: v@vectorBA = vectorba_n(ed1);
	vector vectorba_n(const int input){
		return normalize( pointp(input,this.a) - pointp(input,this.b) );
	}
	//returns the normalized vector BA == posA - posB at input 0
	//example: v@vectorBA = vectorba_n(ed1);
	vector vectorba_n(){
		return normalize( pointp(0,this.a) - pointp(0,this.b) );
	}
	//returns the center position of the edge at input 0
	//example: v@halfpos = halfpoint(ed1);
	vector halfpoint(){
		return ( pointp(0,this.a) + pointp(0,this.b) )*.5;
	}
	//returns the center position of the edge at input
	//example: v@halfpos = halfpoint(ed1);
	vector halfpoint(const int input){
		return ( pointp(input,this.a) + pointp(input,this.b) )*.5;
	}
	
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//Following are functions to handle edge array data://
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

//Returns a string in standard Houdini edge format
//Example: printf(getfullname(edges)); 
string getfullname(const edgeStruct edges[]){
	string result;
	foreach(edgeStruct ed; edges){
		append( result, sprintf("p%i_%i ", ed.a, ed.b) );
	}
	return result;
}
//Returns edges as an int array of point indexes
//Example: i[]@display1=getint(edges); 
int[] getint(const edgeStruct edges[]){
	int result[];
	foreach(edgeStruct ed; edges){
		append( result, ed.a );
		append( result, ed.b );
	}
	return result;
}

/* - probably broken
//Returns an array of int that represents edges, without a given edge
//Example:
//i[]@display1=getint(edges); 
//i[]@display2=removeedge(@display1, ed1);
int[] removeedge(const int edges[]; const edgeStruct ed){
	int result[];
	for(int i=0; i<len(edges); i = i+2) {
		if(!( (edges[i]==ed.a && edges[i+1]==ed.b) || (edges[i]==ed.b && edges[i+1]==ed.a) )  ){
			//append(result,edgeStruct(numbers[i],numbers[i+1]) );
			append(result,edges[i]);
			append(result,edges[i+1]);
		}
	}
	return result;
}
*/

/* - 
	//This is probably broken

	//Returns the edges connected to point A at input 0
	//Example: edgeStruct[]
	edgeStruct[] neighboursedges(){
		edgeStruct result[];
		int points[];
		points = neighbours(0,this.a);
		removevalues(points,this.b);
		
		foreach(int i ; points){
			edgeStruct ed;
			ed = edgeStruct(i,this.a);
			push(result,ed);
		}
		
		return result;
	}
	*/

/* - probably does not work
//Returns new array that does not contain given edge or its reverse
//Example: printf(getfullname( removevalues(edges, ed1) ));
function int[] removevalues(const edgeStruct edges[]; const edgeStruct ed) {
	//edgeStruct result[]; 
	int result[];
	int numbers[] = getint(edges[]);
	for(int i ; i<len(numbers)*.5; i = i+2) {
		if(!( (numbers[i]==ed.a && numbers[i+1]==ed.b) || (numbers[i]==ed.b && numbers[i+1]==ed.a) )  ){
			//append(result,edgeStruct(numbers[i],numbers[i+1]) );
			append(result,numbers[i]);
			append(result,numbers[i+1]);
		}
	}
	return result;
}
*/

/*
//Returns all edges connected to a point at input
//Example: printf(getfullname( edgestruct_frompoint(0, 0) ));
edgeStruct[] edgestruct_frompoint(const int input; const int point){
	int numbers[] = neighbours(input, point); 
	edgeStruct result[];
	foreach(int i; numbers ){
		push( result, edgeStruct(point,i) );
	}
	return result;
}
*/

/* broken
//Returns all edges connected to both points of an edge
//Example: printf(getfullname( edgestruct_fromedge(0, 0) ));
function edgeStruct[] edgestruct_fromedge(const int input; const edgeStruct ed){
	edgeStruct result[];
	getint(edgestruct_frompoint(input,ed.a) );

	//push(result, edgestruct_frompoint(input,ed.a) );
	//push(result, edgestruct_frompoint(input,ed.b) );

	return result;
}
*/


//Returns an edgeStruct array given a Houdini edge group by input and name 
//Example: printf(getfullname( edgestruct_fromgroup(0, "test") ));
edgeStruct[] edgestruct_fromgroup(const int input; const string name){
	int numbers[] = expandedgegroup(input, name); 
	edgeStruct result[];
	for(int i = 0; i<len(numbers); i=i+2 ){
		push( result, edgeStruct(numbers[i],numbers[i+1]) );
	}
	return result;
}

//returns a string in standard Houdini edge format
//example: getfullname(edges); 
edgeStruct[] edgestruct_fromarray(const int numbers[]){
	edgeStruct result[];
	for(int i = 0; i<len(numbers); i=i+2 ){
		push( result, edgeStruct(numbers[i],numbers[i+1]) );
	}
	return result;
}



//to do: sorts edgeStruct array by first element in increasing order
/*
//returns an array of edgeStructs, sorted in increasing values
//example: 
edgeStruct[] sort(const edgeStruct numbers[]){
	edgeStruct result[];
	for(int i = 0; i<len(numbers); i=i+2 ){
		push( result, edgeStruct(numbers[i],numbers[i+1]) );
	}
	return result;
}
*/

/*
//Returns the edges connected to point A at input 0
//Example: edgeStruct[]
int[] neighboursA(const edgeStruct u){
	//edgeStruct[] result;
	int points[];
	points = neighbours(0,u.a);
	/*
	removevalues(points,u.b);
	foreach(int i ; points){
		edgeStruct ed = edgeStruct(i,u.a);
		push(result,ed);
	}
	return result;
	/
	return points[];
}
*/

//Math operations on edgeStructs:

//Check if two given edges are identical. Returns 1 if same and 0 if not.
int isequal(const edgeStruct u,v){
	return (u.a==v.a && u.b==v.b) || (u.a==v.b && u.b==v.a);
}


//dot product of two edges (as vectors) at input 0
//example: f@dot = dot(ed1,ed2);
float dot(const edgeStruct u,v){
	return dot(vectorab(u),vectorab(v));
}
//dot product of two edges (as vectors) at inputs
//example: f@dot = dot(ed1,0,ed2,1);
float dot(const edgeStruct u ; const int inputU ; const edgeStruct v ; const int inputV){
	return dot(vectorab(u,inputU),vectorab(v,inputV));
}

//dot product of two normalized edges at input 0
//example: f@dot = dot_n(ed1,ed2);
float dot_n(const edgeStruct u,v){
	return dot(vectorab_n(u),vectorab_n(v));
}
//dot product of two normalized edges at inputs
//example: f@dot = dot_n(ed1,0,ed2,1);
float dot_n(const edgeStruct u ; const int inputU ; const edgeStruct v ; const int inputV){
	return dot(vectorab_n(u,inputU),vectorab_n(v,inputV));
}


//returns the angle between two edges in degrees at input 0
//example: f@angle = angle_d({0,1},{1,0});
float angle_d(const edgeStruct u,v){
	return degrees( acos( dot_n( u,v)  ) );
}
//returns the angle between two edges in degrees at input 0
//example: f@angle = angle({0,1},{1,0});
float angle(const edgeStruct u,v){
	return acos( dot_n( u,v)  );
}
	
//returns the angle between two edges in degrees at inputs
//example: f@angle = angle_d(ed1,0,ed2,1);
float angle_d(const edgeStruct u ; const int inputU ; const edgeStruct v ; const int inputV){
	return degrees( acos( dot_n(u,inputU,v,inputV) )  );
}


//to do: define line struct 
//to do: define line struct from edgeStruct
//to do: line to point distance

//to do: plane struct
//to do: is line on plane?
//to do: line - to plane intersection point (if line on plane return plane reference point)

#endif
