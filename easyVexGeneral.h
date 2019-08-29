#ifndef __easyVexGeneral_h__
#define __easyVexGeneral_h__
/**
 * Functions that simplify general tasks. 
 */
 

/**
 * Returns position of the point closest to given position at input 0
 * 
 * @param	{vector}	{pos}	position that we examine 
 */
function vector nearpointp( const vector pos)
{
	return point(0, “P”, nearpoint(0, pos) );
}

/**
 * Returns position of the point closest to given position at input
 * 
 * @param {int}	{input}   number of the input that we look at to find the geometry   
 * @param {vector}	{pos}	position that we examine 
 * 
 * Contributed by Matthew Hendershot
 */
function vector nearpointp( const int input; const vector pos)
{
	return point(input, “P”, nearpoint(input, pos) );
}

/**
 * Returns 1, if both input values are the same +- tolerance, otherwise 0
 * 
 * @param {float}	{input1}   float number to compare   
 * @param {float}	{input2}   float number to compare   
 * @param {float}	{tolerance}  amount of tolerance (+-) between input1 and input2 
 *
 * Example:
 * i@equal1 = isequal(1.001,1.0, 0.0); //not equal
 * i@equal2 = isequal(1.001,1.0, 0.0001); //not equal
 * i@equal3 = isequal(1.001,1.0, 0.0011); //eqal
 */
function int isequal( const float input1, input2, tolerance)
{
	return abs(input1-input2)<tolerance;
}

/**
 * Returns 1, if both input values are the same +- tolerance, otherwise 0
 * 
 * @param {vector}	{input1}   float number to compare   
 * @param {vector}	{input2}   float number to compare   
 * @param {float}	{tolerance}  amount of tolerance (+-) between length of input1 and input2 
 *
 * Example:
 * vector tester1 = set(1.001, 1.0, 1.0);
 * vector tester2 = set(1.0, 1.0, 1.0);
 * i@equal1 = isequal(tester1,tester2, 0.0); //not equal
 * i@equal2 = isequal(tester1,tester2, 0.0001); //not equal
 * i@equal3 = isequal(tester1,tester2, 0.0006); //eqal
 * 
 * Keep in mind we look at total difference, not per vector component difference
 */
function int isequal( const vector input1, input2; const float tolerance)
{
	return abs(length(input1)-length(input2))<tolerance;
}

/**
 * Returns int array of unique values (no duplicates) sorted in ascending order.
 * 
 * @param {int array}	{numbers}   arbitrary integer array
 *
 * int testIntArray[] = {0,0,0,1};
 * i[]@array1 = uniquearray(testIntArray); //only {0,1} remains
 */
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


/**
 * Returns int array of unique values (no duplicates) sorted in ascending order.
 * 
 * @param {float array}	{numbers}   arbitrary float array
 * @param {float}	{tolerance}   Tolerance value (+-) for comparison 
 *
 * Example:
 * float testFloatArray[] = {0.0, 0.001, 0.0005, 1};
 * f[]@array1 = uniquearray(testFloatArray, 0.001); //0.001 stays in
 * f[]@array2 = uniquearray(testFloatArray, 0.0011); //0.001 gets removed
 * f[]@array3 = testFloatArray; //The original stays the same!
 */
function float[] uniquearray(const float numbers[]; const float tolerance) {
	float localNumbers[] = {};
	float clean[] = {};
	int temp = 0;

	//fail safe
	if (len(numbers) == 0) {
		warning("Passed empty array into uniquearray function");
		return clean;
	}

	localNumbers = sort(numbers); // sort ascending to simplify the elimination of duplicates

	append(clean, localNumbers[0]); // the first element is always unique 

	for (int i = 1; i<len(numbers); i++) {
		if (!isequal( clean[temp], localNumbers[i], tolerance)) { //if the number is not the same, add it
			append(clean, localNumbers[i]);
			temp++; //temp is the last index in the clean array
		}
	}
	return clean;
}

/**
 * Returns vector array of unique values (no duplicates) sorted in ascending order.
 * 
 * @param {float array}	{numbers}   arbitrary vector array
 * @param {float}	{tolerance}   Tolerance value (+-) for comparison 
 *
 * Example:
 * vector testVectorArray[] = {{1.001, 1.0, 1.0},{1.0, 1.0, 1.0},{2.0, 1.0, 1.0}};
 * v[]@array = uniquearray(testVectorArray,0.1); //Result: {1.001, 1.0, 1.0},{2.0, 1.0, 1.0}
 * v[]@array2 = testVectorArray; //The original stays the same!
 */
function vector[] uniquearray(const vector numbers[]; const float tolerance) {
	vector clean[] = {};
	int inside = 0;

	//fail safe
	if (len(numbers) == 0) {
		warning("Passed empty array into uniquearray function");
		return clean;
	}

	foreach (vector vec; numbers) {
		foreach (vector vec2; clean)
		{
		    inside+=isequal(vec,vec2,tolerance); //increase if the number is already there
		}
		if (inside<1) { //if the number is not already there, add it
			append(clean, vec);
		}
		inside = 0;
	}
	return clean;
}

/**
 * Adds only new int values (no duplicates) to an int array and returns the modified array. The original gets modified.
 * 
 * @param {int array}	{numbers}   arbitrary integer array
 * @param {int}	{num}   number to add
 *
 * Example:
 * int testIntArray[] = {0,0,0,1};
 * i[]@array1 = appendunique(testIntArray,0); //does not append
 * i[]@array2 = appendunique(testIntArray,2); //appends
 * f[]@array3 = testIntArray; //The original gets modified!
 */
function int[] appendunique(int numbers[]; const int num) {
	if (find(numbers, num)<0) {
		append(numbers, num);
	}
	return numbers;
}

/**
 * Adds only new float values (no duplicates) to a float array and returns the modified array. The original gets modified.
 * 
 * @param {float array}	{numbers}   arbitrary float array
 * @param {float}	{num}   number to add
 *
 * Example:
 * float testFloatArray[] = {0.0, 0.001, 0.0005, 1};
 * f[]@array4 = appendunique(testFloatArray,0.0); //does not append
 * f[]@array5 = appendunique(testFloatArray,0.01); //appends
 * f[]@array6 = testFloatArray; // the origibnal gets modified!
 */
function float[] appendunique(float numbers[]; const float num) {
	if (find(numbers, num)<0) {
		append(numbers, num);
	}
	return numbers;
}

/**
 * Adds only new vector value (no duplicates) to a vector array and returns the modified array. The original gets modified.
 * 
 * @param {vector array}	{numbers}   arbitrary vector array
 * @param {vector}	{num}   vector to add
 *
 * Example:
 * vector testVectorArray[] = {{1.001, 1.0, 1.0},{1.0, 1.0, 1.0},{2.0, 1.0, 1.0}};
 * v[]@array7 = appendunique(testVectorArray,{1.001, 1.0, 1.0});//does not append
 * v[]@array8 = appendunique(testVectorArray,{1.002, 1.0, 1.0});//does append
 * v[]@array9 = testVectorArray; // the origibnal gets modified!
 */
function vector[] appendunique(vector numbers[]; const vector num) {
	if (find(numbers, num)<0) {
		append(numbers, num);
	}
	return numbers;
}

/**
 * Removes all instances of int value from int array
 * 
 * @param {int array}	{numbers}   arbitrary integer array
 * @param {int}	{remove}   integer value to be removed from the array
 */
function void removevalues(int numbers[]; const int remove) {
	while (1) {
		int temp;
		temp = removevalue(numbers, remove);
		if (temp == 0) {
			break;
		}
	}
}

/**
 * Removes all instances of all int values in seccond array from first int array
 * 
 * @param {int array}	{numbers}   arbitrary integer array
 * @param {int array}	{remove}   arbitrary integer array to be removed from the numbers array
 */
function void removevalues(int numbers[]; const int remove[]) {
	foreach(int num; remove){
		removevalues(numbers, num);
	}
}

/**
 * Returns int array of only unique values of an arbitrary attribute at input 0. 
 * I think, "uniquevals" was implemented as a native function in houdini vex after it was implemented in easyVex.
 * 
 * @param {string}	{componentType}	 Types: "detail" (or "global"), "point", "prim", or "vertex"
 * @param {string}	{attribName}   Arbitrary attribute name
 */
function int[] uniquevals(const string componentType; const string attribName){	
	return uniquevals(0,componentType, attribName);
}

/**
 * Returns point position at input
 * 
 * @param {int}	{input}	 number of the input that we look at to find the geometry
 * @param {int}	{point}  point index
 */
function vector pointp(const int input; const int point){
	return point(input,"P",point);
}

/**
 * Returns point position at input 0
 * 
 * @param {int}	{point}  point index
 */
function vector pointp(const int point){
	return point(0,"P",point);
}

/**
 * Returns the angle between two vectors in degrees
 * 
 * @param {vector}	{u}  arbitrary vector
 * @param {vector}	{v}  arbitrary vector
 * 
 * Example: f@angle = angle({0,1,0},{1,0,0}); //f@angle == 90
 */
function float angle_d(const vector u,v){
	return degrees( acos( dot(u,v)/( length(v)*length(u) )  ) );
}

/**
 * Returns the angle between two 2d vectors in degrees
 * 
 * @param {vector2}	{u}  arbitrary 2d vector
 * @param {vector2}	{v}  arbitrary 2d vector
 * 
 * Example: f@angle = angle({0,1},{1,0}); //f@angle == 90
 */
function float angle_d(const vector2 u,v){
	return degrees( acos( dot(u,v)/( length(v)*length(u) )  ) );
}

/**
 * Returns dot product of two vectors, but normalizes the vectors beforehand
 * 
 * @param {vector}	{u}  arbitrary vector
 * @param {vector}	{v}  arbitrary vector
 */
float dot_n(const vector u,v ){
	return dot(normalize(u),normalize(v));
}

/**
 * Returns dot product of two vector2s, but normalizes the vectors beforehand
 * 
 * @param {vector2}	{u}  arbitrary 2d vector
 * @param {vector2}	{v}  arbitrary 2d vector
 */
float dot_n(const vector2 u,v ){
	return dot(normalize(u),normalize(v));
}

/**
 * Returns the area of a triangle described by point positions A B C
 * 
 * @param {vector}	{A}  arbitrary vector describing a position
 * @param {vector}	{B}  arbitrary vector describing a position
 * @param {vector}	{C}  arbitrary vector describing a position
 */
float trianglearea(const vector A,B,C){
	float a = distance2(A,B); //squared distance A to B
	float b = distance2(B,C); //squared distance B to C
	float c = distance2(C,A); //squared distance C to A
	return .25*sqrt( 2*b*c+ 2*c*a+ 2*a*b+ - a*a - b*b - c*c ); //http://mathworld.wolfram.com/TriangleArea.html
}

/**
 * Calculates the distance to target position for every point and normalizes it across the geometry. 
 * Sets a point attribute Cd to have this value.
 * Processes all points at first input when executed once. 
 * 
 * @param {vector}	{target}  target position that we calculate distance to
 */
void distances_n(const vector target){
	float maxDistance,minDistance;
	float distancesToTarget[];
	//Store distances
	for(int perPoint=0;perPoint<npoints(0);perPoint++){
    	vector targetPos = point(0,"P",perPoint);
    	float distanceToTarget = distance(targetPos,target);
    	append(distancesToTarget,distanceToTarget);
	}
	//Calculate min and max distances
	minDistance = min(distancesToTarget);
	maxDistance = max(distancesToTarget);
	maxDistance -= minDistance;
	//Set normalized attribute
	for(int i=0;i<npoints(0);i++ ){
	    float normalizedDistanceToTarget = (distancesToTarget[i]-minDistance)/maxDistance;
	    vector color =  set(normalizedDistanceToTarget,normalizedDistanceToTarget,normalizedDistanceToTarget);
	    setpointattrib(0,"Cd",i,color,"set");
	}
}

/**
 * Calculates the distance to target position for every point and normalizes it across the geometry. 
 * Sets a point attribute "name" to have this value.
 * Processes all points at first input when executed once. 
 * 
 * @param {string}	{name}  point attribute to write to
 * @param {vector}	{target}  target position that we calculate distance to
 */
void distances_n(const string name; const vector target){
	float maxDistance,minDistance;
	float distancesToTarget[];
	//Store distances
	for(int perPoint=0;perPoint<npoints(0);perPoint++){
    	vector targetPos = point(0,"P",perPoint);
    	float distanceToTarget = distance(targetPos,target);
    	append(distancesToTarget,distanceToTarget);
	}
	//Calculate min and max distances
	minDistance = min(distancesToTarget);
	maxDistance = max(distancesToTarget);
	maxDistance -= minDistance;
	//Set normalized attribute
	for(int i=0;i<npoints(0);i++ ){
	    float normalizedDistanceToTarget = (distancesToTarget[i]-minDistance)/maxDistance; 
	    setpointattrib(0,name,i,normalizedDistanceToTarget,"set");
	}
}

///////////TO DO: distances_n for an array of input locations, potentially with varying interpolation methods



#endif
