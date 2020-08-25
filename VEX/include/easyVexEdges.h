#ifndef __easyVexEdges_h__
#define __easyVexEdges_h__

/**
 * Edge struct and functions
 */

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
		temp = edgeStruct(input(edges[0]),alla[i],allb[i]); //!!!!INPUT Could BE FIXED
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

#endif
