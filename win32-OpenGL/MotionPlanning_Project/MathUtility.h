/******************************************************************************/
/*!
\file MathUtility.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1150
\par Project #02
\date 01/03/2012
\brief
This is the math utility class

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


#ifndef _MATHUTILITY_H_
#define _MATHUTILITY_H_

#include <cmath>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The Point2D struct

\param

\return
*/
/******************************************************************************/
struct Point2D
{
	Point2D() {};
	Point2D(float _x,float _y) {x=_x;y=_y;};
	Point2D & operator=(Point2D pnt) {x = pnt.x; y = pnt.y; return *this;};
	bool operator==(Point2D pnt) {return (x == pnt.x) && (y == pnt.y);};
	float x;
	float y;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The Vector2D struct

\param

\return
*/
/******************************************************************************/
struct Vector2D
{
	Vector2D() {x=0;y=0;};
	Vector2D(float _x,float _y) {x=_x;y=_y;};
	Vector2D & operator=(Vector2D vec) {x=vec.x;y=vec.y;return *this;};
	bool operator==(Vector2D vec) {return (x==vec.x) && (y==vec.y);};
	float x;
	float y;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The LineSegment2D struct

\param

\return
*/
/******************************************************************************/
struct LineSegment2D
{
	LineSegment2D() {};
	LineSegment2D(Point2D s,Point2D e) {start = s;end = e;};
	LineSegment2D & operator=(LineSegment2D lns) {start = lns.start;end = lns.end;normal = lns.normal;return *this;};
	bool operator==(LineSegment2D lns) {return (start == lns.start) && (end == lns.end);};
	Point2D start;
	Point2D end;
	
	Vector2D normal;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The Vector3D struct

\param

\return
*/
/******************************************************************************/
struct Vector3D
{
	Vector3D() {x=0;y=0;z=0;};
	Vector3D(float _x,float _y,float _z) {x=_x;y=_y;z=_z;};
	Vector3D & operator=(Vector3D vec) {x=vec.x;y=vec.y;z=vec.z;return *this;};
	bool operator==(Vector3D vec) {return (x==vec.x) && (y==vec.y) && (z==vec.z);};
	float x;
	float y;
	float z;
};


enum CLASSIFY {CL_ABOVE,CL_UNDER,CL_ON};


bool PointOnLineSegment(Point2D & pnt,LineSegment2D & lns);
CLASSIFY Classify_Point_To_LineSegment(Point2D pnt,LineSegment2D lns);

//added by Oliver Chong - March 3, 2012
const bool FloatValueSame( const float lhsValue, const float rhsValue );

//added by Oliver Chong - March 29, 2012
const float	PI = 3.1415926535897932384626433832795F;
float DegreeToRadian( float value );
float RadianToDegree( float value );

Vector2D ComputeVector( const Point2D & head, const Point2D & tail );
Vector2D NormalizeVector( const Vector2D & vec );
Vector3D CrossProduct( const Vector2D & vec1, const Vector2D & vec2 );
float DotProduct( const Vector2D & vec1, const Vector2D & vec2 ); 
float Magnitude( const Vector2D & vec ); 
float ComputeAngleDegreesBetweenTwoVectors( const Vector2D & vec1, const Vector2D & vec2 );

#endif