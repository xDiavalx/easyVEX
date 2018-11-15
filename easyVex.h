#ifndef __easyVex_h__
#define __easyVex_h__

/*
* This Software was originally developed by Dimtiri Shimanovskiy.
* Feel free to use as you wish (http://unlicense.org/). Feedback is appreciated
* Credit and dontations are appreciated. If you credit me in a project, 
* send me a message to dimitri.shima.dev@gmail.com, so I can find out about it.
* Contributers:
* Matthew Hendershot
* bhenriksson (https://github.com/bhenriksson031/easyVEX_beh)
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

// Function mappings

//#define pointp(inp,pn) point(inp,"P",pn)




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
function int[] uniquevals(const string componentType; const string attribName){	
	int clean[] = {};
	int count = nuniqueval(0, componentType, attribName);
	for (int i = 0; i < count; i++) {
		int val = uniqueval(0, componentType, attribName, i);
		append(clean,val);
	}
	return clean;
}

//Returns int array of unique values of an arbitrary attribute at input
function int[] uniquevals(const int input; const string componentType; const string attribName){	
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

//Return the area of a triangle given by points A B C
float trianglearea(const vector A,B,C){
	float a = distance2(A,B); //squared distance A to B
	float b = distance2(B,C); //squared distance B to C
	float c = distance2(C,A); //squared distance C to A
	return .25*sqrt( 2*b*c+ 2*c*a+ 2*a*b+ - a*a - b*b - c*c ); //http://mathworld.wolfram.com/TriangleArea.html
}


////////////////////////////////////
////////////////////////////////////
////////////////////////////////////
//Edge struct and helper functions//
////////////////////////////////////
////////////////////////////////////
////////////////////////////////////
struct edgeStruct{
	int input,a,b;
  //Bjorns note, the struct should keep what input it's using, defaulting to 0
	/*General info: 
	//To create a variable of type custom struct:
	edgeStruct ed1 = edgeStruct(0,1,2);
	
	//To use an internal variable of the struct:
	printf("%i\n",ed1.a );
	ed1.a = 6;
	int a = geta(ed1) //if you need to use the component in functions

	//To use a function defined in a custom struct:
	printfverbose(ed1);
	
	//To make an array of custom struct:
	edgeStruct ed2 = edgeStruct(0,3,2);
	edgeStruct ed3 = edgeStruct(0,4,5);
	edgeStruct edges[];
	push(edges,ed1);
	push(edges,ed2);
	push(edges,ed3);

	//To loop over a custom struct:
	foreach(edgeStruct test; edges){
	printfverbose(test);
	printf("a is %i \n",geta(test));
	}
	/////////////////////////////////////////
	/////////////////////////////////////////
	/////////////////////////////////////////
	/////////////////////////////////////////
	/////////REFACTOR INCOMMING!!!!!!!!!!!!!!
	/////////////////////////////////////////
	/////////////////////////////////////////
	/////////////////////////////////////////
	/////////////////////////////////////////
	//THE PROBLEM: Defining functins in here defies convention
	//Usually input parameter is the first input. 
	//This convention needs to be maintained! 
	//Since we cannot maintain it if we use the definitions in the struct, we need to put those function variations outside.
	*/

	//Returns the int for the input
	//Example: int input = getinput(ed1);
	int getinput(){
		return this.input;
	}
	//Returns the int for pt a
	//Example: int pt_a = geta(ed1);
	int geta(){
		return this.a;
	}
	//Returns the int for pt b
	//Example: int pt_b = getb(ed1);
	int getb(){
		return this.b;
	}

	//Print verbose edge description to log
	//Example: printfverbose(ed1); 
	void printfverbose(){
		printf("edge between points %i and %i, at input %i\n", this.a,this.b,this.input);
	}

	//Returns a string in standard Houdini edge format
	//Example: printf(getfullname(ed1)); 
	string getfullname(){
		return sprintf("p%i_%i", this.a, this.b);
	}

	//Swaps edge direction (a will b, and b will be a)
	//Example: swap(ed1);
	void swap(){
		int c;
		c = this.a;
		this.a=this.b;
		this.b=c;
	}

	//Returns 1 if a>b and 0 if b>a
	//Example: compare(ed1);
	int compare(){
		return this.a>this.b;
	}

	//Returns the position of the edgepoint a at input
	//Example: v@pos = posa(ed1,2);
	vector posa(const int input){
		return point(input,"P",this.a);
	}

	//Returns the position of the edgepoint a
	//Example: v@pos = posa(ed1);
	vector posa(){
		return point(this.input,"P",this.a);
	}

	//Returns the position of the edgepoint b at input
	//Example: v@pos = posb(ed1,2);
	vector posb(const int input){
		return point(input,"P",this.b);
	}

	//Returns the position of the edgepoint b
	//Example: v@pos = posb(ed1);
	vector posb(){
		return point(this.input,"P",this.b);
	}

	//Returns the length of the edge
	//Example: f@len = length(ed1);
	float length(){
		vector A = point(this.input,"P",this.a);
		vector B = point(this.input,"P",this.b);
		return distance(A,B);
	}

	//Returns the length of the edge at input
	//Example: f@len = length(ed1,2);
	float length(const int input){
		vector A = point(input,"P",this.a);
		vector B = point(input,"P",this.b);
		return distance(A,B);
	}


	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	//Following are functions for interpreting the edge as a vector//
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////

	//Returns the non-normalized vector AB == posB - posA at input
	//Example: v@vectorAB = vectorab(ed1,2);
	vector vectorab(const int input){
		return point(input,"P",this.b) - point(input,"P",this.a);
	}

	//Returns the non-normalized vector AB == posB - posA
	//Example: v@vectorAB = vectorab(ed1);
	vector vectorab(){
		return point(this.input,"P",this.b) - point(this.input,"P",this.a);
	}

	//Returns the non-normalized vector BA == posA - posB at input
	//Example: v@vectorBA = vectorba(ed1);
	vector vectorba(const int input){
		return point(input,"P",this.a) - point(input,"P",this.b);
	}

	//Returns the non-normalized vector BA == posA - posB
	//Example: v@vectorBA = vectorba(ed1);
	vector vectorba(){
		return point(this.input,"P",this.a) - point(this.input,"P",this.b);
	}

	//Returns the normalized vector AB == posB - posA at input
	//Example: v@vectorAB = vectorab_n(ed1,2);
	vector vectorab_n(const int input){
		return normalize( point(input,"P",this.b) - point(input,"P",this.a) );
	}

	//Returns the normalized vector AB == posB - posA
	//Example: v@vectorAB = vectorab_n(ed1);
	vector vectorab_n(){
		return normalize( point(this.input,"P",this.b) - point(this.input,"P",this.a) );
	}

	//Returns the normalized vector BA == posA - posB at input
	//Example: v@vectorBA = vectorba_n(ed1);
	vector vectorba_n(const int input){
		return normalize( point(input,"P",this.a) - point(input,"P",this.b) );
	}

	//Returns the normalized vector BA == posA - posB
	//Example: v@vectorBA = vectorba_n(ed1);
	vector vectorba_n(){
		return normalize( point(this.input,"P",this.a) - point(this.input,"P",this.b) );
	}

	//Returns the center position of the edge
	//Example: v@halfpos = halfpoint(ed1);
	vector midpoint(){
		return ( point(this.input,"P",this.a) + point(this.input,"P",this.b) )*.5;
	}

	//Returns the center position of the edge at input
	//Example: v@halfpos = halfpoint(ed1);
	vector midpoint(const int input){
		return ( point(input,"P",this.a) + point(input,"P",this.b) )*.5;
	}

}

//Returns a version of the edgeStruct where a<b
edgeStruct sort(const edgeStruct ed){
	if( compare(ed) ){
		return edgeStruct(getinput(ed), getb(ed),geta(ed));
		}
	return ed;
}

//Returns the position of the edgepoint a at input
//Example: v@pos = posa(2,ed1);
vector posa(const int input; const edgeStruct edge){
	return point(input,"P",edge.a);
}

//Returns the position of the edgepoint b at input
//Example: v@pos = posb(2,ed1);
vector posb(const int input; const edgeStruct edge){
	return point(input,"P",edge.b);
}

//Returns the length of the edge at input
//Example: f@len = length(2,ed1);
float length(const int input; const edgeStruct edge){
	vector A = point(input,"P",edge.a);
	vector B = point(input,"P",edge.b);
	return distance(A,B);
}

//Returns the non-normalized vector AB == posB - posA at input
//Example: v@vectorAB = vectorab(ed1,2);
vector vectorab(const int input; const edgeStruct edge){
	return point(input,"P",getb(edge)) - point(input,"P",geta(edge));
}
//Returns the non-normalized vector BA == posA - posB at input
//Example: v@vectorBA = vectorba(ed1);
vector vectorba(const int input; const edgeStruct edge; const edgeStruct edge){
		return point(input,"P",geta(edge)) - point(input,"P",getb(edge));
}
//Returns the normalized vector AB == posB - posA at input
//Example: v@vectorAB = vectorab_n(ed1,2);
vector vectorab_n(const int input; const edgeStruct edge){
	return normalize( point(input,"P",getb(edge)) - point(input,"P",geta(edge)) );
}
//Returns the normalized vector BA == posA - posB at input
//Example: v@vectorBA = vectorba_n(ed1);
vector vectorba_n(const int input; const edgeStruct edge){
	return normalize( point(input,"P",geta(edge)) - point(input,"P",getb(edge)) );
}
//Returns the center position of the edge at input
//Example: v@halfpos = halfpoint(ed1);
vector midpoint(const int input; const edgeStruct edge){
	return ( point(input,"P",geta(edge)) + point(input,"P",getb(edge)) )*.5;
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
		append( result, sprintf("a%i_b%i ", geta(ed), getb(ed) ) );
	}
	return result;
}

//Returns edges as an int array of point indexes
//Example: i[]@display1=getint(edges); 
int[] getint(const edgeStruct edges[]){
	int result[];
	foreach(edgeStruct ed; edges){
		append( result, geta(ed) );
		append( result, getb(ed) );
	}
	return result;
}

//Returns point indexes of first points of an array of edges
//Example: i[]@display1=getinta(edges); 
int[] getinta(const edgeStruct edges[]){
	int result[];
	foreach(edgeStruct ed; edges){
		append( result, geta(ed) );
	}
	return result;
}

//Returns point indexes of seccond points of an array of edges
//Example: i[]@display1=getintb(edges); 
int[] getintb(const edgeStruct edges[]){
	int result[];
	foreach(edgeStruct ed; edges){
		append( result, getb(ed) );
	}
	return result;
}

//Returns an array of int that represents edges, without a given edge 
//and without a swapped version of that edge. 
//Example:
//i[]@display1=getint(edges); 
//i[]@display2=removeedge(@display1, ed1);
int[] removeedge(const int edges[]; const edgeStruct ed){
	int result[];
	for(int i=0; i<len(edges); i = i+2) {
		if(!( (edges[i]==geta(ed) && edges[i+1]==getb(ed) ) || (edges[i]==getb(ed) && edges[i+1]==geta(ed) ) )  ){
			//append(result,edgeStruct(numbers[i],numbers[i+1]) );
			append(result,edges[i]);
			append(result,edges[i+1]);
		}
	}
	return result;
}

//Returns new array that does not contain given edge or the swapped version of that edge
//Example:
//i[]@display1=getint(edges); 
//i[]@display2=removeedge(@display1, ed1);
int[] removeedge(const edgeStruct edges[]; const edgeStruct ed){
	/*int nums[] = getint(edges);
	int result[];
	for(int i=0; i<len(nums); i = i+2) {
		if(!( (nums[i]==ed.a && nums[i+1]==ed.b) || (nums[i]==ed.b && nums[i+1]==ed.a) )  ){
			//append(result,edgeStruct(numbers[i],numbers[i+1]) );
			append(result,nums[i]);
			append(result,nums[i+1]);
		}
	}
	return result;*/
	return removeedge(getint(edges),ed);
}

//Returns all edges connected to a point at input
//Example: printf(getfullname( edgestruct_frompoint(0, 0) ));
edgeStruct[] edgestruct_frompoint(const int input; const int point){
	int numbers[] = neighbours(input, point); 
	edgeStruct result[];
	foreach(int i; numbers ){
		push( result, edgeStruct(input,point,i) );
	}
	return result;
}

//Returns a edgeStruct array given an input and an array of point id pairs.
edgeStruct[] edgestruct_fromarray(const int input; const int numbers[]){
	edgeStruct result[];
	for(int i = 0; i<len(numbers); i=i+2 ){
		push( result, edgeStruct(input, numbers[i],numbers[i+1]) );
	}
	return result;
}

//Returns all edges connected to both points of an edge - without the source edge
//Example: printf(getfullname( edgestruct_fromedge(0, 0) ));
function edgeStruct[] edgestruct_fromedge(const int input; const edgeStruct ed){
	//int numbers[];
	edgeStruct result[];
	//numbers = getint(edgestruct_frompoint(input,ed.a) ) ;
	//append(numbers, getint(edgestruct_frompoint(input,ed.b) ) );
	push(result, edgestruct_frompoint(input,geta(ed)) );
	push(result, edgestruct_frompoint(input,getb(ed)) );
	return edgestruct_fromarray(input,removeedge(result,ed) );
}

//Returns an edgeStruct array given a Houdini edge group by input and name 
//Example: printf(getfullname( edgestruct_fromgroup(0, "test") ));
edgeStruct[] edgestruct_fromgroup(const int input; const string name){
	/*
	int numbers[] = expandedgegroup(input, name); 
	edgeStruct result[];
	for(int i = 0; i<len(numbers); i=i+2 ){
		push( result, edgeStruct(numbers[i],numbers[i+1]) );
	}
	return result;
	*/
	return edgestruct_fromarray(input,expandedgegroup(input, name));
}

//Returns an edgeStruct array given an input and a primitive.
//In other words, turns all edges of a polygon into edgeStructs.
edgeStruct[] edgestruct_fromprim(const int input; const int primnum){
    
    int skip_last = primintrinsic(input, "closed", primnum)==0 ?1 :0; //if open, don't create an edge between the end points

    edgeStruct result[];
    int vtxcount = primvertexcount(input, primnum);
    for(int i = 0; i<vtxcount-skip_last; i++){
            push( result, edgeStruct(input,vertexpoint(input, primvertex(input, primnum,i) ),vertexpoint(input, primvertex(input, primnum,(i+1)%vtxcount ) ) ) );
    }
    return result;
}


//Returns an array of edgeStructs, sorted by a (primary) and b (secondary) in increasing order
//Example: printf(getfullname( sort(edges) ));
edgeStruct[] sort(const edgeStruct edges[]){
	int amount;
	edgeStruct result[];
	int alla[], allb[], ordera[], orderb[];
	//split the edges into front points and rear points
	foreach(edgeStruct ed; edges){
		if(geta(ed)<getb(ed)){
			append( alla, geta(ed) );
			append( allb, getb(ed) );
		}
		else{
			append( alla, getb(ed) );
			append( allb, geta(ed) );
		}
	}
	amount = len(alla);
	//determine order
	ordera = argsort(alla);
	orderb = argsort(allb);
	//combine sorting orders and give greater weight to "a" 
	for(int i=0; i<amount ; i++ ){
		ordera[i] = (ordera[i]+2)*(amount+2)+orderb[i];
	}
	//fix the large numbers to range
	ordera = argsort(alla);

	alla = reorder(alla, ordera);
	allb = reorder(allb, ordera);
	//make edgeStruct array
	edgeStruct temp;
	for(int i=0; i<amount; i++){
		temp = edgeStruct(getinput(edges[0]),alla[i],allb[i]); //!!!!INPUT NEEDS TO BE FIXED
		push(result, temp);
	}
	return result;
}

//Returns the edges connected to point A
//Example: printf(getfullname( neighbours_a(ed1) ));
edgeStruct[] neighbours_a(const edgeStruct ed){
	edgeStruct result[];
	int points[];
	int input = getinput(ed);
	int a = geta(ed);
	int b = getb(ed);
	points = neighbours(input,a);
	removevalue(points,b);
	foreach(int i ; points){
		push(result,edgeStruct(input,a,i));
	}
	return result;
}

//Returns the edges connected to point A at input
//Example: printf(getfullname( neighbours_a(0,ed1) ));
edgeStruct[] neighbours_a(const int input; const edgeStruct ed){
	edgeStruct result[];
	int points[];
	int a = geta(ed);
	int b = getb(ed);
	points = neighbours(input,a);
	removevalue(points,b);
	foreach(int i ; points){
		push(result,edgeStruct(input,a,i));
	}
	return result;
}

//Returns the edges connected to point B
//Example: printf(getfullname( neighbours_b(ed1) ));
edgeStruct[] neighbours_b(const edgeStruct ed){
	edgeStruct result[];
	int points[];
	int input = getinput(ed);
	int a = geta(ed);
	int b = getb(ed);
	points = neighbours(input,b);
	removevalue(points,a);
	foreach(int i ; points){
		push(result,edgeStruct(input,b,i));
	}
	return result;
}

//Returns the edges connected to point B at input
//Example: printf(getfullname( neighbours_b(0,ed1) ));
edgeStruct[] neighbours_b(const int input; const edgeStruct ed){
	edgeStruct result[];
	int points[];
	int a = geta(ed);
	int b = getb(ed);
	points = neighbours(input,b);
	removevalue(points,a);
	foreach(int i ; points){
		push(result,edgeStruct(input,b,i));
	}
	return result;
}


///////////////////////////////////
//Math operations on edgeStructs://
///////////////////////////////////

//Check if two given edges have the same points. Returns 1 if same and 0 if not.
int isequal(const edgeStruct ed1,ed2){
	return (geta(ed1)==geta(ed2) && getb(ed1)==getb(ed2) ) || (geta(ed1)==getb(ed2) && getb(ed1)==geta(ed2) );
}

//Dot product of two edges (as vectors). 
//Example: f@dot = dot(ed1,ed2);
float dot(const edgeStruct ed1,ed2){
	return dot(vectorab(ed1),vectorab(ed2));
}

//Dot product of two edges (as vectors) at inputs
//Example: f@dot = dot(0,ed1,1,ed2);
float dot(const int input1 ; const edgeStruct ed1 ; const int input2 ; const edgeStruct ed2){
	return dot(vectorab(input1,ed1),vectorab(input2,ed2));
}

//Dot product of two normalized edges. Both edges are normalized before the dot product, not after.
//Example: f@dot = dot_n(ed1,ed2);
float dot_n(const edgeStruct ed1,ed2){
	return dot(vectorab_n(ed1),vectorab_n(ed2));
}

//Dot product of two normalized edges at inputs
//Example: f@dot = dot_n(0,ed1,0,ed2);
float dot_n(const int input1 ; const edgeStruct ed1 ;const int input2;  const edgeStruct ed2){
	return dot(vectorab_n(input1,ed1),vectorab_n(input2,ed2));
}

//Returns the angle between two edges in degrees
//Example: f@angle = angle_d(ed1,ed2);
float angle_d(const edgeStruct ed1,ed2){
	return degrees( acos( dot_n( ed1,ed2)  ) );
}

//Returns the angle between two edges in radians
//Example: f@angle = angle(ed1,ed2);
float angle(const edgeStruct ed1,ed2){
	return acos( dot_n( ed1,ed2)  );
}



//Returns the angle between two edges in degrees at inputs
//Example: f@angle = angle_d(ed1,0,ed2,1);
float angle_d(const int input1 ; const edgeStruct ed1 ;const int input2;  const edgeStruct ed22){
	return degrees( acos( dot_n(input1,ed1,input2,ed2) )  );
}

//Returns angle between two edges in radians around a rotation axis 
float angle_around(const edgeStruct ed1,ed2; vector axis){
    vector a = vectorab_n(ed1); 
    vector b = vectorab_n(ed2); 
    vector world_up = set(0,1,0);
    if(axis!= world_up ){ //rotate to align up axis to y
        //in a more generic context the following might be useful as it's own function, it's a common operation.
        vector4 q_align = dihedral(world_up, axis);
        vector at = vectorab_n(ed1);
        a = qrotate(q_align, a); 
        b = qrotate(q_align, b); 
    }
    vector4 q_align = dihedral(a, set(0,0,-1) ); //this rotates the vectors to align against the z axis, the atan2 function is zero for this
    b = qrotate(q_align, b); 
    return atan2( b.x, b.z);
}
//Returns angle between two edges in degrees around a rotation axis
float angle_around_d(const edgeStruct ed1,ed2; vector axis){
    return degrees(angle_around( ed1,ed2, axis));
}


///////////////////////
//Define lineStruct://
///////////////////////
/*
//pseudo enum. This works, but is dangerous,
//since it might conflict with other code
#define lineType int
#define closed 0
#define open 1
#define openA 2
#define openB 3
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

	//Returns point A on line
	vector geta(){
		return this.A;
	}
	//Returns point B on line
	vector getb(){
		return this.B;
	}
	//Returns type of line
	/*The type determines whether it is
	(0) a line-segment, 
	(1) an infinite line, 
	(2) a line starting at B and extending (infinitely) in direction A or
	(3) a line starting at A and extending (infinitely) in direction B.
	*/
	int gettype(){
		return this.type;
	}
	//Returns vector AB normalized
	vector getnormal(){
		return normalize(this.B-this.A);
	}

	//Returns 1 if A and B are NOT the same and 0 otherwise. 
	//If A and B were equal (return 0) the struct would be invalid.
	int isok(){
		return this.A==this.B ? 0 : 1; 
	}
}


//Returns a line struct from an edgeStruct at input 0, of type 0 (closed)
lineStruct linefromedge(const edgeStruct edge){
	lineStruct line = lineStruct(posa(edge),posb(edge),0);
	return line;
}
//Returns a line struct from an edgeStruct at input 0, of type
lineStruct linefromedge(const edgeStruct edge; const int type){
	lineStruct line = lineStruct(posa(edge),posb(edge),type);
	return line;
}
//Returns a line struct from an edgeStruct at input, of type 0 (closed)
lineStruct linefromedge(const int input; const edgeStruct edge){
	lineStruct line = lineStruct(posa(input, edge),posb(input, edge),0);
	return line;
}
//Returns a line struct from an edgeStruct at input, of type
lineStruct linefromedge(const int input; const edgeStruct edge; const int type){
	lineStruct line = lineStruct(posa(input, edge),posb(input, edge),type);
	return line;
}

//Returns minimum distance between a lineStruct and pos X 
//http://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html
float linetoposdist(const lineStruct line; const vector X){
	vector A = geta(line);
	vector B = getb(line);
	int type = gettype(line);
	float dist = length( cross(X-A,X-B) )/length(B-A);

	if(type==1){ //infinite line
		return dist;
	}
	float dista = distance(A,X);
	float distb = distance(B,X);

	float dirAX = dot((X-A),(B-A));
	if(type==3){ //closed at A
		if(dirAX<0){ //if X further from B than A
			return length((X-A));
		}
		return dist;
	}
	float dirBX = dot((X-B),(A-B));
	if(type==2){ //closed at B
		if(dirBX<0){
			return length((X-B));
		}
		return dist;
	}
	if(type==0){ //closed line segment
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

//Returns whether two lines are similar encoded as a result vector
//result.x == 1 -> all points of both lines lie on the same infinite line
//result.x == 0 -> both lines lie on the same infinite line
//result.y == 1 -> points on both lines are the same (ignoring point order)
//result.y == 0 -> points on both lines are not the same (ignoring point order)
//result.z == 1 -> types are the same
//result.z == 0 -> types are different
vector isequal(const lineStruct l1,l2){
	vector result; 
	vector p1 = getnormal(l1);
	vector p2 = getnormal(l2);
	result.x = normal1==normal2||normal1==-normal2 ? 1 : 0;//if normals match, then 1
	result.y = (geta(l1)==geta(l2)&&getb(l1)==getb(l2))||(geta(l1)==getb(l2)&&getb(l1)==geta(l2)) ? 1 : 0;//if points match, then 1
	result.z = gettype(l1)==gettype(l2);
	return result;
}

//to do: line to line has intersection point?
//to do: line to line intersection point or closest point (with success parameter)
//to do: line to line angle (angle between two lines)
//to do: angle around and angle around_d for lines

//The planeStruct represents an infinite plane in 3D space. It has a normal direction.
struct planeStruct{
	vector normal, pos; //normal = direction and normal of the plane. pos = a point on the plane

	vector getnormal(){
		return normalize(this.normal);//this normalization should be moved to a constructor
	}
	vector getpos(){
		return this.pos;
	} 
}


//Returns a planeStruct given a primitive number and the input
planeStruct planestruct_fromprim(const int input; const int prim){
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
		normal = normalize ( cross(pointp(input,pts[1])-pointp(input,pts[0]),pointp(input,pts[0])-pointp(input,pts[2]) ) );
		return planeStruct(normal, pos);
	}
	warning("planestruct_fromprim: Could not find or generate normal. Using fallback {0,1,0}.");
	return planeStruct(normal, pos); // Backup
}
//Returns a planeStruct given a primitive number at input 0
planeStruct planestruct_fromprim(const int prim){
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
		normal = normalize ( cross(pointp(input,pts[1])-pointp(input,pts[0]),pointp(input,pts[0])-pointp(input,pts[2]) ) );
		return planeStruct(normal, pos);
	}
	warning("planestruct_fromprim: Could not find or generate normal. Using fallback {0,1,0}.");
	return planeStruct(normal, pos); // Backup
}

//Returns the closest distance between a point and an (infinite) plane defined by a planeStruct.
//If the point is under the plane (based on plane's normal) the value is negative.
float dist(const int input; const  int point; const planeStruct plane){
	float dist = dot(pointp(input,point)-getpos(plane),getnormal(plane));
	return dist;
}


//Returns intersection point between line and plane
//success
//0 => disjoint (no intersection)
//1 => the plane intersects the line in the returned point
//2 => the segment lies in the plane
//3 => the intersection lies outside the segment
//From: https://de.mathworks.com/matlabcentral/fileexchange/17751-straight-line-and-plane-intersection
vector intersection(const planeStruct plane; const lineStruct line; int success){
	vector result = {0,0,0};
	vector linedir = getb(line) - geta(line);
	vector toline = geta(line) - getpos(plane);
	float D = dot(getnormal(plane) - linedir);
	float N = - dot(getnormal(plane) , toline);
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
	result = geta(line) + sI * linedir;

	success = sI<0||sI>1 ? 3:1; //If true, the intersection point lies outside the segment, so there is no intersection

	return result; 
	////////////////////////Fix this to account for different line types!!!!
}


//Returns line at the intersection of two planes
//Solution based on https://forum.unity.com/threads/how-to-find-line-of-intersecting-planes.109458/
lineStruct linestruct_fromplanes(const planeStruct p1,p2){
	vector dir = cross(getnormal(p1),getnormal(p2)); //direction of line

    vector orthogonalp1 = cross(getnormal(p2), dir); //similar to p1 but orthogonal to p2    
    float numerator = dot(getnormal(p1), orthogonalp1); //length of p1 on orthogonalp1

    if(abs(numerator) <0.000001){ //bail if the planes are essentially the same
		warning("linestruct_fromplanes(%e,%e): planes are parallel, therefore no line makes sense",p1, p2);
		return lineStruct({0,0,0},{0,1,0},1);
	}
    vector p2p1 = getpos(p1) - getpos(p2); //vector p2 to p1
	float t = dot(getnormal(p1), p2p1) / numerator; //p2p1 projected onto p1 normalized for orthogonalp1
	vector pos = getpos(p2) + t * orthogonalp1; //go from p2 via orthogonalp1 to p1

	return lineStruct(pos,dir+pos,1); 
}

//to do: angle between line and plane https://www.vitutor.com/geometry/distance/line_plane.html
//to do: is line on plane? (both points have dist 0 to plane)
//to do: line - plane intersection point (if line on plane return plane reference point, will require success parameter)
//to do: intersection of 3 planes http://geomalgorithms.com/a05-_intersect-1.html ?maybe
//to do: point closest to 3 planes ?maybe

#endif
