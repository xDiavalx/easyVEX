#ifndef __easyVexGeo_h__
#define __easyVexGeo_h__
/**
 * Functions that create or modify geometry. 
 */
 

/**
 * Creates a circle around "axis" with startpoint facing "up".
 * Returns array of temporary point IDs.
 * 
 * @param {vector}	{origin}  Location of the center/origin of the circle
 * @param {int}	{divisions}  Number of segments on the circle
 * @param {vector}	{up}  Direction in which the first and last points face. Should be different from axis. 
 * @param {vector}	{axis}  Center axis of the circle. Should be different from up.
 * @param {float}	{radius}  Radius of circle
 * @param {float}	{uv_v_offset}  The circle UVs are laid out left to right in UV space. This parameter shifts the UVs in height in UV space. 
 *                               	If you make two circles, one with uv_v_offset=0, the other with uv_v_offset=1 and use the skin sop to connect them, you get a cylinder with proper UVs.
 * @param {int}	{closed}	Polygon is closed if 1, polygon open if 0
 * 
 * Example:
 * //Make two circles and set point attribute "test" on the second one to 4
 * int divisions=8;
 * vector up = set(0,1,0);
 * vector axis = set(1,0,0);
 * float radius = 1;
 * int points[];
 * 
 * circle(set(0,0,0),divisions, up, axis, radius,0,0,1);
 * points = circle(set(1,0,0),divisions, up, axis, radius,1);
 * foreach(int pt; points){
 * setpointattrib(0,"test",pt,4,"set");
 * }
 */
int[] circle(const vector origin; const int divisions; const vector up; const vector axis; const float radius; const float uv_v_offset; const int closed){
	//init variables
	int points[];
	int verts[];
	vector up_n = normalize(up);
	vector axis_n = normalize(axis);
	int divisions_n = max(divisions,2); //make sure we get at least two divisions.
	matrix3 adjustmentMatrix = maketransform(axis_n,up_n);
	int pointid = 0;
	vector z = cross(up_n,axis_n); //Use z to ensure that the vectors are orthogonal to each other.

	for(int div=0; div<(closed?divisions_n:1+divisions_n); div++){
	    float angle = 2*PI*(div)/divisions_n; //angle of segment in radians
	    vector dir = set(sin(angle), cos(angle), 0); //Direction of segment point
	    dir *= adjustmentMatrix; //Adjust for axis and up
	    vector pos = dir * radius + origin; //And set radius
	    //Create point and set attributes
	    pointid = addpoint(0,pos);
	    float uv_u = float(div)/float(divisions_n);
	    append(points,pointid);
	    setpointattrib(0, "N", pointid, dir, "set");
	    setpointattrib(0, "up", pointid, axis_n, "set");
	    //setpointattrib(0, "uv", pointid, set(uv_u,uv_v_offset,0), "set");
	}
	string polyType = "polyline";
	if(closed){
		polyType = "poly";
		append(points,points[0]);
	}
	addprim(pointid,0,polyType,points,verts);
	foreach(int i; int div; verts){
		float uv_u = float(i)/float(divisions_n);
		vector uvs = set(uv_u,uv_v_offset,0);
		setvertexattrib(0, "uv", div, -1, uvs, "set");
	}
	return(points);
}

/**
 * Creates a polyline in a circle around "axis" with startpoint facing "up".
 * Returns array of temporary point IDs.
 * 
 * @param {vector}	{origin}  Location of the center/origin of the circle
 * @param {int}	{divisions}  Number of segments on the circle
 * @param {vector}	{up}  Direction in which the first and last points face. Should be different from axis. 
 * @param {vector}	{axis}  Center axis of the circle. Should be different from up.
 * @param {float}	{radius}  Radius of circle
 * @param {float}	{uv_v_offset}  The circle UVs are laid out left to right in UV space. This parameter shifts the UVs in height in UV space. 
 *                               	If you make two circles, one with uv_v_offset=0, the other with uv_v_offset=1 and use the skin sop to connect them, you get a cylinder with proper UVs.
 * 
 * Example:
 * //Make two circles and set point attribute "test" on the second one to 4
 * int divisions=8;
 * vector up = set(0,1,0);
 * vector axis = set(1,0,0);
 * float radius = 1;
 * int points[];
 * 
 * circle(set(0,0,0),divisions, up, axis, radius,0);
 * points = circle(set(1,0,0),divisions, up, axis, radius,1);
 * foreach(int pt; points){
 * 	setpointattrib(0,"test",pt,4,"set");
 * }
 */
int[] circle(const vector origin; const int divisions; const vector up; const vector axis; const float radius; const float uv_v_offset){
	return circle(origin, divisions, up, axis, radius, uv_v_offset, 0);
}


#endif
