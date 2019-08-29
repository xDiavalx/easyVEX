#ifndef __easyVex_h__
#define __easyVex_h__

//#include "tester.h"
#include "easyVexGeneral.h"
#include "easyVexGeo.h"

/*
* This Software was originally developed by Dimtiri Shimanovskiy.
* Feel free to use as you wish (http://unlicense.org/). 
* Feedback is highly appreciated.
* Giving credit is requested and appreciated.
* If you credit me in a project, please tell me (via dimitri.shima.dev@gmail.com), so I can find out!
* 
* Contributers:
* Matthew Hendershot
* bhenriksson (https://github.com/bhenriksson031/easyVEX_beh)
* Kyro from Think Procedural (Discord) - helped with a bug in circle
*
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
* 
* 
* 
* DESIGN CHOICES
* 
* Structs and functions:
* Usually an input parameter is the first input. 
* (example: point(0,"P",@ptnum) //0 is the input)
* If a function is defined inside the Struct definition the first paramater will be the Struct.
* To uphold convention, we put such functions outside the struct defintion.
* 
* -So what goes into the Struct defintion?
* It should probably only contain the most basic getters, setters and trivial operations.
* But I am not sure where the line is, yet.
*
* Functionnames:
* When possible override similar functions of existing name. 
* But instead of srcpoint and dstpoint we use pointa and pointb.
* When returning an array the name should include a plural "s". Example: getints() 
* Suffix _n stands for normalized output
* Suffix _d stands for degrees (as opposed to radians)
* Function-names are subject to change at the current stage of development.
*/

//General utility functions

//Function mappings //That doesn't work properly
//#define pointp(inp,pn) point(inp,"P",pn) //That doesn't work properly




////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////Edge struct/////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * \verbatim
 * An edgeStruct describes a geometry edge. It is defined by two points.
 *
 * To create a variable of type custom struct:
 * 	edgeStruct ed1 = edgeStruct(0,1,2);
 * 	edgeStruct ed1 = edgeStruct(1,2); //Also works, because of a helper function. The input then defaults to 0.
 *
 * To create a variable of type custom struct:
 * 	edgeStruct ed1 = edgeStruct(0,1,2);
 * 	edgeStruct ed1 = edgeStruct(1,2); //Also works, because of a helper function. The input then defaults to 0.
 *
 * To use an internal variable of the struct:
 * 	printf("%i\n",ed1.a );
 * 	ed1.a = 6;
 * 	int a = pointa(ed1) //Is kind of cleaner than just ed1.a
 *
 * To debug you can:
 * printfverbose(ed1);
 * To make visible in geometry spreadsheet/debug:
 * 	s@ed = getfullname(ed1);
 *
 * To make an array of custom struct:
 * 	edgeStruct ed1 = edgeStruct(3,2);
 *  edgeStruct ed2 = edgeStruct(4,5);
 *  edgeStruct edges[];
 *  push(edges,ed1);
 *  push(edges,ed2);
 *
 * To loop over a custom struct:
 * 	foreach(edgeStruct test; edges){
 * 		printfverbose(test);
 *	  	printf("a is %i \n",pointa(test));
 *  }
 *
 * To loop over a custom struct with index:
 * 	foreach(int index; edgeStruct test; edges){
 *	 	printf("At index %i ",index);
 * 	 	printf("a is %i \n",pointa(test));
 * 	}
 * \endverbatim
 */
struct edgeStruct{
	int input,a,b;

	/**
	 * Returns the int of the input of the edge
	 * 
	 * Example: int input = input(ed1);
	 */
	int input(){
		return this.input;
	}

	/**
	 * Returns the int for point a of the edge
	 * 
	 * Example: int pt_a = pointa(ed1);
	 */
	int pointa(){
		return this.a;
	}

	/**
	 * Returns the int for point b of the edge
	 * 
	 * Example: int pt_b = pointb(ed1);
	 */
	int pointb(){
		return this.b;
	}

	/**
	 * Sets the input of the edge
	 * 
	 * @param {int}	{input}   a point number
	 * 
	 * Example: setinput(ed1,1);
	 */
	int setinput(const int input){
		this.input = input;
	}

	/**
	 * Sets the int for point a of the edge
	 * 
	 * @param {int}	{a}   a point number
	 * 
	 * Example: setpointa(ed1,1);
	 */
	int setpointa(const int a){
		this.a = a;
	}

	/**
	 * Sets the int for point b of the edge
	 * 
	 * @param {int}	{b}   a point number
	 * 
	 * Example: setpointb(ed1,1);
	 */
	int setpointb(const int b){
		this.b = b;
	}

	/**
	 * Print verbose edge description to log
	 * 
	 * Example: printfverbose(ed1);
	 */
	void printfverbose(){
		printf("edge between points %i and %i, at input %i\n", this.a,this.b,this.input);
	}

	/**
	 * Returns a string in standard Houdini edge format
	 * 
	 * Example: printf(getfullname(ed1));
	 */
	string getfullname(){
		return sprintf("p%i_%i", this.a, this.b);
	}

	/**
	 * Reverse edge direction (a will b, and b will be a)
	 * 
	 * Example: reverse(ed1);
	 */
	void reverse(){
		int c;
		c = this.a;
		this.a=this.b;
		this.b=c;
	}

	/**
	 * Returns 1 if a>b and 0 if b>a
	 * 
	 * Example: compare(ed1);
	 */
	int compare(){
		return this.a>this.b;
	}

	/**
	 * Returns the position of the edgepoint a
	 * 
	 * Example: v@pos = posa(ed1);
	 */
	vector posa(){
		return point(this.input,"P",this.a);
	}


	/**
	 * Returns the position of the edgepoint b
	 * 
	 * Example: v@pos = posb(ed1);
	 */
	vector posb(){
		return point(this.input,"P",this.b);
	}

	/**
	 * Returns the length of the edge
	 * 
	 * Example: f@len = length(ed1);
	 */
	float length(){
		vector A = point(this.input,"P",this.a);
		vector B = point(this.input,"P",this.b);
		return distance(A,B);
	}


	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	//Following are functions for interpreting the edge as a vector//
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////

	/**
	 * Returns the non-normalized vector AB == posB - posA
	 * 
	 * Example: v@vectorab = vectorab(ed1); 
	 */
	vector vectorab(){
		return point(this.input,"P",this.b) - point(this.input,"P",this.a);
	}

	/**
	 * Returns the non-normalized vector BA == posA - posB
	 * 
	 * Example: v@vectorba = vectorba(ed1); 
	 */
	vector vectorba(){
		return point(this.input,"P",this.a) - point(this.input,"P",this.b);
	}

	/**
	 * Returns the normalized vector AB == posB - posA
	 * 
	 * Example: v@vectorab = vectorab_n(ed1); 
	 */
	vector vectorab_n(){
		return normalize( point(this.input,"P",this.b) - point(this.input,"P",this.a) );
	}

	/**
	 * Returns the normalized vector BA == posA - posB
	 * 
	 * Example: v@vectorba = vectorba_n(ed1);
	 */
	vector vectorba_n(){
		return normalize( point(this.input,"P",this.a) - point(this.input,"P",this.b) );
	}

	/**
	 * Returns the center position of the edge
	 * 
	 * @param {int}	{input}   an integer that describes an input
	 * 
	 * Example: v@halfpos = halfpoint(ed1);
	 */
	vector posmid(){
		return ( point(this.input,"P",this.a) + point(this.input,"P",this.b) )*.5;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////edgeStruct defintion end. Following are functions using edgeStructs///////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * Returns an edgeStruct at input 0
 *
 * @param {int}	{a}   a point number
 * @param {int}	{b}   a point number
 *
 * This function will simplify working with edgeStructs. 
 * If you want to work with just first input, there is no need to specify the input. 
 */
edgeStruct edgeStruct(const int a,b){
	return edgeStruct(0,a,b);
}

/**
 * Returns an edgeStruct at input 0, given a half-edge
 *
 * @param {int}	{hedge}   a half-edge id 
 */
edgeStruct edgeStruct(const int hedge){
	int a = hedge_srcpoint(0,hedge);
	int b = hedge_dstpoint(0,hedge);
	if(a<0 || b<0){
		warning("Half-edge: %i in edgeStuct(hedge) is not valid.", hedge);
	}
	return edgeStruct(0,a,b);
}

/**
 * Returns a half-edge when given an edgeStruct. Returns -1 if no such half-edge can be found. 
 * Cares about edge direction.
 * Wrapper around pointhedge().
 * 
 * @param {edgeStruct}	{edge}   an edgeStruct
 */
int pointhedge(const edgeStruct edge){
	return pointhedge(input(edge),pointa(edge),pointb(edge));
}

/**
 * Returns a half-edge when given an edgeStruct. Returns -1 if no such half-edge can be found.
 * Does not care about edge direction.
 * Wrapper around pointedge()
 * 
 * @param {edgeStruct}	{edge}   an edgeStruct
 */
int pointedge(const edgeStruct edge){
	return pointedge(input(edge),pointa(edge),pointb(edge));
}

/**
 * Print verbose edge description to log
 *
 * @param {edgeStruct[]}	{edges}   an edgeStruct array
 * 
 * Example: printfverbose(edges);
 */
void printfverbose(const edgeStruct edges[]){
	foreach(edgeStruct edge; edges){
		printf("edge between points %i and %i, at input %i\n", edge.a,edge.b,edge.input);
	}
}

/**
 * Returns a version of the edgeStruct where a<b
 *
 * @param {edgeStruct}	{edge}   an edgeStruct
 */
edgeStruct sort(const edgeStruct edge){
	if( compare(edge) ){
		return edgeStruct(input(edge), pointb(edge),pointa(edge));
		}
	return edge;
}

/**
 * Returns the position of the edgepoint a at input
 *
 * @param {int}	{input}   an integer that describes an input
 * @param {edgeStruct}	{edge}   an edgeStruct
 * 
 * Example: v@pos = posa(2,ed1);
 */
vector posa(const int input; const edgeStruct edge){
	return point(input,"P",pointa(edge));
}

/**
 * Returns the position of the edgepoint b at input
 *
 * @param {int}	{input}   an integer that describes an input
 * @param {edgeStruct}	{edge}   an edgeStruct
 * 
 * Example: v@pos = posb(2,ed1);
 */
vector posb(const int input; const edgeStruct edge){
	return point(input,"P",pointb(edge));
}

/**
 * Returns the length of the edge at input
 *
 * @param {int}	{input}   an integer that describes an input
 * @param {edgeStruct}	{edge}   an edgeStruct
 * 
 * Example: f@len = length(2,ed1);
 */
float length(const int input; const edgeStruct edge){
	vector A = point(input,"P",pointa(edge));
	vector B = point(input,"P",pointb(edge));
	return distance(A,B);
}

/////////////////////////////////////////////////////////////////
//Following are functions for interpreting the edge as a vector//
/////////////////////////////////////////////////////////////////

/**
 * Returns the non-normalized vector AB == posB - posA at input
 *
 * @param {int}	{input}   an integer that describes an input
 * @param {edgeStruct}	{edge}   an edgeStruct
 * 
 * Example: v@vectorab = vectorab(2,ed1);
 */
vector vectorab(const int input; const edgeStruct edge){
	return point(input,"P",pointb(edge)) - point(input,"P",pointa(edge));
}

/**
 * Returns the non-normalized vector BA == posA - posB at input
 *
 * @param {int}	{input}   an integer that describes an input
 * @param {edgeStruct}	{edge}   an edgeStruct
 * 
 * Example: v@vectorab = vectorab(2,ed1);
 */
vector vectorba(const int input; const edgeStruct edge){
	return point(input,"P",pointa(edge)) - point(input,"P",pointb(edge));
}

/**
 * Returns the normalized vector AB == posB - posA at input
 *
 * @param {int}	{input}   an integer that describes an input
 * @param {edgeStruct}	{edge}   an edgeStruct
 * 
 * Example: v@vectorabn = vectorab_n(2,ed1);
 */
vector vectorab_n(const int input; const edgeStruct edge){
	return normalize( point(input,"P",pointb(edge)) - point(input,"P",pointa(edge)) );
}

/**
 * Returns the normalized vector BA == posA - posB at input
 *
 * @param {int}	{input}   an integer that describes an input
 * @param {edgeStruct}	{edge}   an edgeStruct
 *
 * Example: v@vectorban = vectorba_n(2,ed1);
 */
vector vectorba_n(const int input; const edgeStruct edge){
	return normalize( point(input,"P",pointa(edge)) - point(input,"P",pointb(edge)) );
}

/**
 * Returns the center position of the edge at input
 *
 * @param {int}	{input}   an integer that describes an input
 * @param {edgeStruct}	{edge}   an edgeStruct
 * 
 * Example: v@halfpos = halfpoint(2,ed1);
 */
vector posmid(const int input; const edgeStruct edge){
	return ( point(input,"P",pointa(edge)) + point(input,"P",pointb(edge)) )*.5;
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//Following are functions to handle edge array data://
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

/**
 * Returns a string in standard Houdini edge format
 *
 * @param {edgeStruct array}	{edges}   an array of edgeStructs
 * 
 * Example: printf(getfullname(edges)); 
 */
string getfullname(const edgeStruct edges[]){
	string result;
	foreach(edgeStruct ed; edges){
		append( result, sprintf("a%i_b%i ", pointa(ed), pointb(ed) ) );
	}
	return result;
}

/**
 * Returns edges as an int array of point indexes
 *
 * @param {edgeStruct array}	{edges}   an array of edgeStructs
 * 
 * Example: i[]@display1=getints(edges); 
 */
int[] getints(const edgeStruct edges[]){
	int result[];
	foreach(edgeStruct ed; edges){
		append( result, pointa(ed) );
		append( result, pointb(ed) );
	}
	return result;
}

/**
 * Returns point indexes of first points of an array of edges
 *
 * @param {edgeStruct array}	{edges}   an array of edgeStructs
 * 
 * Example: i[]@display1=getintsa(edges); 
 */
int[] getintsa(const edgeStruct edges[]){
	int result[];
	foreach(edgeStruct ed; edges){
		append( result, pointa(ed) );
	}
	return result;
}

/**
 * Returns point indexes of seccond points of an array of edges
 *
 * @param {edgeStruct array}	{edges}   an array of edgeStructs
 * 
 * Example: i[]@display1=getintsb(edges);  
 */
int[] getintsb(const edgeStruct edges[]){
	int result[];
	foreach(edgeStruct ed; edges){
		append( result, pointb(ed) );
	}
	return result;
}

/**
 * Returns new array of point id pairs representing edges
 * that does not contain given edge or the reversed version of that edge
 *
 * @param {int array}	{edges}   an array of integers where every two numbers describe an edge start and end point
 * @param {edgeStruct}	{edge}   an edgeStruct that should be removed from edges
 * 
 * Example:
 * i[]@display1=getints(edges); 
 * i[]@display2=removevalue(@display1, ed1);
 */
int[] removevalue(const int edges[]; const edgeStruct edge){
	int result[];
	for(int i=0; i<len(edges); i = i+2) {
		if(!( (edges[i]==pointa(edge) && edges[i+1]==pointb(edge) ) || (edges[i]==pointb(edge) && edges[i+1]==pointa(edge) ) )  ){
			//append(result,edgeStruct(numbers[i],numbers[i+1]) );
			append(result,edges[i]);
			append(result,edges[i+1]);
		}
	}
	return result;
}

/**
 * Returns new array of point id pairs representing edges
 * that does not contain given edge or the reversed version of that edge
 *
 * @param {edgeStruct array}	{edges}   an array of edgeStructs
 * @param {edgeStruct}	{edge}   an edgeStruct that should be removed from edges
 * 
 * Example:
 * i[]@display1=getints(edges); 
 * i[]@display2=removevalue(@display1, ed1);
 */
int[] removevalue(const edgeStruct edges[]; const edgeStruct edge){
	/*int nums[] = getints(edges);
	int result[];
	for(int i=0; i<len(nums); i = i+2) {
		if(!( (nums[i]==edge.a && nums[i+1]==edge.b) || (nums[i]==edge.b && nums[i+1]==edge.a) )  ){
			//append(result,edgeStruct(numbers[i],numbers[i+1]) );
			append(result,nums[i]);
			append(result,nums[i+1]);
		}
	}
	return result;*/
	return removevalue(getints(edges),edge);
}

/**
 * Returns new array of edges
 * that does not contain given edge or the reversed version of that edge
 *
 * @param {edgeStruct array}	{edges}   an array of edgeStructs
 * @param {edgeStruct}	{edge}   an edgeStruct that should be removed from edges
 * 
 * Example:
 * i[]@display1=getints(edges); 
 * i[]@display2=removevalue(@display1, ed1);
 */
edgeStruct[] removevalue(const edgeStruct edges[]; const edgeStruct edge){
	edgeStruct result[];
	foreach(int i; edgeStruct ed; edges) {
		if(!( (pointa(ed)==pointa(edge) && pointb(ed)==pointb(edge) ) || (pointa(ed)==pointb(edge) && pointb(ed)==pointa(edge) ) )  ){	
			push(result,ed);
		}
	}
	return result;
}

/**
 * Returns all edges connected to a point at input
 *
 * @param {int}	{input}   an integer that describes an input
 * @param {int}	{point}   an integer that describes a point number
 * 
 * Example: printf(getfullname( edgestructs_frompoint(0, 0) ));
 */
edgeStruct[] edgestructs_frompoint(const int input; const int point){
	int numbers[] = neighbours(input, point); 
	edgeStruct result[];
	foreach(int i; numbers ){
		push( result, edgeStruct(input,point,i) );
	}
	return result;
}

/**
 * Returns all edges of a polygon as edgeStructs
 *
 * @param {int}	{input}   an integer that describes an input
 * @param {int}	{primnum}   primitive id (primitive number)
 */
edgeStruct[] edgestructs_fromprim(const int input; const int primnum){
    
    int skip_last = primintrinsic(input, "closed", primnum)==0 ?1 :0; //if open, don't create an edge between the end points

    edgeStruct result[];
    int vtxcount = primvertexcount(input, primnum);
    for(int i = 0; i<vtxcount-skip_last; i++){
            push( result, edgeStruct(input,vertexpoint(input, primvertex(input, primnum,i) ),vertexpoint(input, primvertex(input, primnum,(i+1)%vtxcount ) ) ) );
    }
    return result;
}

/**
 * Returns a edgeStruct array given an input and an array of point id pairs.
 *
 * @param {int}	{input}   an integer that describes an input
 * @param {int array}	{edges}   an array of integers where every two numbers describe an edge start and end point
 */
edgeStruct[] edgestructs_fromarray(const int input; const int edges[]){
	edgeStruct result[];
	for(int i = 0; i<len(edges); i=i+2 ){
		push( result, edgeStruct(input, edges[i], edges[i+1]) );
	}
	return result;
}

/**
 * Returns all edges connected to both points of an edge - without the source edge
 *
 * @param {int}	{input}   an integer that describes an input
 * @param {edgeStruct}	{edge}   an edgeStruct 
 * 
 * Example: printf(getfullname( edgestructs_fromedge(0, 0) ));
 */
function edgeStruct[] edgestructs_fromedge(const int input; const edgeStruct edge){
	//int numbers[];
	edgeStruct result[];
	//numbers = getints(edgestructs_frompoint(input,ed.a) ) ;
	//append(numbers, getints(edgestructs_frompoint(input,ed.b) ) );
	push(result, edgestructs_frompoint(input,pointa(edge)) );
	push(result, edgestructs_frompoint(input,pointb(edge)) );
	return removevalue(result,edge);
}

/**
 * Returns an edgeStruct array given a Houdini edge group by input and name 
 *
 * @param {int}	{input}   an integer that describes an input
 * @param {string}	{name}   name of a Houdini edge group
 * 
 * Example: printf(getfullname( edgestructs_fromgroup(0, "test") ));
 */
edgeStruct[] edgestructs_fromgroup(const int input; const string name){
	/*
	int numbers[] = expandedgegroup(input, name); 
	edgeStruct result[];
	for(int i = 0; i<len(numbers); i=i+2 ){
		push( result, edgeStruct(numbers[i],numbers[i+1]) );
	}
	return result;
	*/
	return edgestructs_fromarray(input,expandedgegroup(input, name));
}

////////////FIX THIS> IT DOES NOT SORT BY b///////////////////////////////////
/**
 * Returns an array of edgeStructs, sorted by a (primary) and b (secondary) in increasing order
 *
 * @param {edgeStruct array}	{edges}   an array of edgeStructs
 * 
 * Example: printf(getfullname( sort(edges) ));
 */
edgeStruct[] sort(const edgeStruct edges[]){
	int amount;
	edgeStruct result[];
	int alla[], allb[], ordera[], orderb[];
	//split the edges into front points and rear points
	foreach(edgeStruct ed; edges){
		if(pointa(ed)<pointb(ed)){
			append( alla, pointa(ed) );
			append( allb, pointb(ed) );
		}
		else{
			append( alla, pointb(ed) );
			append( allb, pointa(ed) );
		}
	}
	//Determine order
	//First we sort by b, then by a. 
	//The order of a overrides the previous sorting, but the b order is naturally preserved for identical a values.
	orderb = argsort(allb);
	alla = reorder(alla, orderb);
	allb = reorder(allb, orderb);

	ordera = argsort(alla);
	alla = reorder(alla, ordera);
	allb = reorder(allb, ordera);

	amount = len(alla);
	edgeStruct temp;
	for(int i=0; i<amount; i++){
		temp = edgeStruct(input(edges[0]),alla[i],allb[i]); //!!!!INPUT NEEDS TO BE FIXED
		push(result, temp);
	}
	return result;
}

/**
 * Returns the edges connected to point A of a given edgeStruct
 *
 * @param {edgeStruct}	{edge}   an edgeStruct 
 *
 * Example: printf(getfullname( neighbours_a(ed1) ));
 */
edgeStruct[] neighbours_a(const edgeStruct edge){
	edgeStruct result[];
	int points[];
	int input = input(edge);
	int a = pointa(edge);
	int b = pointb(edge);
	points = neighbours(input,a);
	removevalue(points,b);
	foreach(int i ; points){
		push(result,edgeStruct(input,a,i));
	}
	return result;
}

/**
 * Returns the edges connected to point A of a given edgeStruct at input
 *
 * @param {int}	{input}   an integer that describes an input
 * @param {edgeStruct}	{edge}   an edgeStruct 
 * 
 * Example: printf(getfullname( neighbours_a(0,ed1) ));
 */
edgeStruct[] neighbours_a(const int input; const edgeStruct edge){
	edgeStruct result[];
	int points[];
	int a = pointa(edge);
	int b = pointb(edge);
	points = neighbours(input,a);
	removevalue(points,b);
	foreach(int i ; points){
		push(result,edgeStruct(input,a,i));
	}
	return result;
}

/**
 * Returns the edges connected to point B of a given edgeStruct
 *
 * @param {edgeStruct}	{edge}   an edgeStruct 
 *
 * Example: printf(getfullname( neighbours_b(ed1) ));
 */
edgeStruct[] neighbours_b(const edgeStruct edge){
	edgeStruct result[];
	int points[];
	int input = input(edge);
	int a = pointa(edge);
	int b = pointb(edge);
	points = neighbours(input,b);
	removevalue(points,a);
	foreach(int i ; points){
		push(result,edgeStruct(input,b,i));
	}
	return result;
}

/**
 * Returns the edges connected to point B of a given edgeStruct at input
 *
 * @param {int}	{input}   an integer that describes an input
 * @param {edgeStruct}	{edge}   an edgeStruct 
 * 
 * Example: printf(getfullname( neighbours_b(0,ed1) ));
 */
edgeStruct[] neighbours_b(const int input; const edgeStruct edge){
	edgeStruct result[];
	int points[];
	int a = pointa(edge);
	int b = pointb(edge);
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

/**
 * Returns 1 if two given edges have the same points. Returns 0 otherwise.
 *
 * @param {edgeStruct}	{ed1}   an edgeStruct
 * @param {edgeStruct}	{ed2}   an edgeStruct 
 */
int isequal(const edgeStruct ed1,ed2){
	return (pointa(ed1)==pointa(ed2) && pointb(ed1)==pointb(ed2) ) || (pointa(ed1)==pointb(ed2) && pointb(ed1)==pointa(ed2) );
}

/**
 * Returns dot product of two edges (as vectors). 
 *
 * @param {edgeStruct}	{ed1}   an edgeStruct 
 * @param {edgeStruct}	{ed2}   an edgeStruct
 *  
 * Example: f@dot = dot(ed1,ed2);
 */
float dot(const edgeStruct ed1,ed2){
	return dot(vectorab(ed1),vectorab(ed2));
}

/**
 * Returns dot product of two edges (as vectors) at inputs
 *
 * @param {int}	{input1}   an integer that describes an input of ed1
 * @param {edgeStruct}	{ed1}   an edgeStruct 
 * @param {int}	{input2}   an integer that describes an input of ed1
 * @param {edgeStruct}	{ed2}   an edgeStruct 
 * 
 * Example: f@dot = dot(0,ed1,1,ed2);
 */
float dot(const int input1 ; const edgeStruct ed1 ; const int input2 ; const edgeStruct ed2){
	return dot(vectorab(input1,ed1),vectorab(input2,ed2));
}

/**
 * Returns dot product of two normalized edges. 
 * Both edges are normalized before the dot product, not after.
 *
 * @param {edgeStruct}	{ed1}   an edgeStruct 
 * @param {edgeStruct}	{ed2}   an edgeStruct
 * 
 * Example: f@dot = dot_n(ed1,ed2);
 */
float dot_n(const edgeStruct ed1,ed2){
	return dot(vectorab_n(ed1),vectorab_n(ed2));
}

/**
 * Returns dot product of two normalized edges at inputs
 *
 * @param {int}	{input1}   an integer that describes an input of ed1
 * @param {edgeStruct}	{ed1}   an edgeStruct 
 * @param {int}	{input2}   an integer that describes an input of ed1
 * @param {edgeStruct}	{ed2}   an edgeStruct 
 *
 * Example: f@dot = dot_n(0,ed1,0,ed2);
 */
float dot_n(const int input1 ; const edgeStruct ed1 ;const int input2;  const edgeStruct ed2){
	return dot(vectorab_n(input1,ed1),vectorab_n(input2,ed2));
}

/**
 * Returns the angle between two edges in degrees
 *
 * @param {edgeStruct}	{ed1}   an edgeStruct 
 * @param {edgeStruct}	{ed2}   an edgeStruct
 * 
 * Example: f@angle = angle_d(ed1,ed2);
 */
float angle_d(const edgeStruct ed1,ed2){
	return degrees( acos( dot_n( ed1,ed2)  ) );
}

/**
 * Returns the angle between two edges in radians
 *
 * @param {edgeStruct}	{ed1}   an edgeStruct 
 * @param {edgeStruct}	{ed2}   an edgeStruct
 * 
 * Example: f@angle = angle(ed1,ed2);
 */
float angle(const edgeStruct ed1,ed2){
	return acos( dot_n( ed1,ed2)  );
}

/**
 * Returns the angle between two edges in degrees at inputs
 *
 * @param {int}	{input1}   an integer that describes an input of ed1
 * @param {edgeStruct}	{ed1}   an edgeStruct 
 * @param {int}	{input2}   an integer that describes an input of ed1
 * @param {edgeStruct}	{ed2}   an edgeStruct 
 *
 * Example: f@angle = angle_d(0,ed1,1,ed2);
 */
float angle_d(const int input1 ; const edgeStruct ed1 ;const int input2;  const edgeStruct ed2){
	return degrees( acos( dot_n(input1,ed1,input2,ed2) )  );
}

/**
 * Returns angle between two edges in radians around a rotation axis 
 */
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


/**
 * Returns angle between two edges in degrees around a rotation axis
 *
 * @param {edgeStruct}	{ed1}   an edgeStruct 
 * @param {edgeStruct}	{ed2}   an edgeStruct 
 * @param {vector}	{axis}	rotation axis around which we measure the angle
 */
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


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////planeStruct//////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
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
