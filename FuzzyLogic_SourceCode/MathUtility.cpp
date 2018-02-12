/******************************************************************************/
/*!
\file MathUtility.cpp
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

#include "MathUtility.h"

#include <iostream>
#include <iomanip>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This validates if the point is on the line segment

\param pnt
the point
\param lns
the line segment

\return bool
if true, the point is on the line segment, otherwise false
*/
/******************************************************************************/
bool PointOnLineSegment(Point2D & pnt,LineSegment2D & lns)
{
	float res1 = lns.end.y - lns.start.y;
	float res2 = lns.end.x - lns.start.x;
	float res3 = pnt.x - lns.start.x;
	float res4 = pnt.y - lns.start.y;
	float t;
	if(res3*res1 == res4*res2)//the point is on the line of the segment
	{		
		if(res1 != 0.0f)
			t = res4/res1;
		else //if(res2 != 0)
			t = res3/res2;
		
		if((t >= 0.0f) && (t <= 1.0f))
			return true;
	}
	return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This classifies the point whether it is on, above or under the line segment

\param pnt
the point
\param lns
the line segment

\return CLASSIFY
enumeration values : CL_UNDER, CL_ABOVE, CL_ON
*/
/******************************************************************************/
CLASSIFY Classify_Point_To_LineSegment(Point2D pnt,LineSegment2D lns)
{
    //return Vector3D(Y*v.Z - Z*v.Y,Z*v.X - X*v.Z,X*v.Y - Y*v.X);
	Vector3D v1(pnt.x-lns.start.x,pnt.y-lns.start.y,0);
	Vector3D v2(lns.end.x-lns.start.x,lns.end.y-lns.start.y,0);
	Vector3D cross;
	cross.z = v1.x*v2.y - v1.y*v2.x;
	if(cross.z < 0.0f)
        return CL_UNDER;
	else if(cross.z > 0.0f)
        return CL_ABOVE;
	return CL_ON;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Compares whether two floating point values are similar

\param lhsValue
the floating point value
\param rhsValue
the floating point value
\return
*/
/******************************************************************************/
const bool FloatValueSame( const float lhsValue, const float rhsValue )
{
	float differenceVal = lhsValue - rhsValue;
	const float	EPSILON	= 0.00001F;

	//get the positive values of the difference
	if ( differenceVal < 0.0F )
	{
		differenceVal *= -1.0F;
	}

	//validate the difference against the Epsilon value that will allow a certain margin of difference
	if ( differenceVal > EPSILON )
	{
		return false;
	}
	else
	{
		return true;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Converts an angle from degrees to radians

\param value
the value in degrees

\return float
the angle in radians
*/
/******************************************************************************/
float DegreeToRadian( float value )
{
	return value * PI / 180.0F;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Converts an angle from radians to degrees

\param value
the value in radians

\return float
the angle in degrees
*/
/******************************************************************************/
float RadianToDegree(float value)
{
	return value * 180.0F / PI;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Computes a 2D vector based on two points

\param head
the starting 2D point
\param tail
the ending 2D point

\return Vector2D
the resulting 2D vector
*/
/******************************************************************************/
Vector2D ComputeVector( const Point2D & head, const Point2D & tail )
{
	Vector2D vec;
	vec.x = head.x - tail.x;
	vec.y = head.y - tail.y;
	return vec;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Normalizes a 2D vector

\param vec
the 2D vector

\return Vector2D
the normalized 2D vector
*/
/******************************************************************************/
Vector2D NormalizeVector( const Vector2D & vec )
{
	//compute the magnitude of the vector
	float magnitudeVal = Magnitude( vec );

	//normalize the vector
	Vector2D normalizedVec;
	normalizedVec.x = vec.x / magnitudeVal;
	normalizedVec.y = vec.y / magnitudeVal;

	return normalizedVec;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Computes the cross product

\param vec1
the 2D vector
\param vec2
the 2D vector

\return Vector3D
the resulting vector from the cross product that is orthogonal to both the input vectors
*/
/******************************************************************************/
Vector3D CrossProduct( const Vector2D & vec1, const Vector2D & vec2 )
{
	Vector3D vec3D1( vec1.x, vec1.y, 0.0F );
	Vector3D vec3D2( vec2.x, vec2.y, 0.0F );

	Vector3D orthoVec;
	//compute for the cross product
	orthoVec.x = ( vec3D1.y * vec3D2.z ) - ( vec3D1.z * vec3D2.y );
	orthoVec.y = ( vec3D1.z * vec3D2.x ) - ( vec3D1.x * vec3D2.z );
	orthoVec.z = ( vec3D1.x * vec3D2.y ) - ( vec3D1.y * vec3D2.x );

	return orthoVec;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Computes the dot product

\param vec1
the 2D vector
\param vec2
the 2D vector

\return float
the dot product scalar value
*/
/******************************************************************************/
float DotProduct( const Vector2D & vec1, const Vector2D & vec2 )
{
	float dotProdVal = ( vec1.x * vec2.x ) + ( vec1.y * vec2.y );
	return dotProdVal;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Computes the magnitude of a 2D vector

\param vec
the 2D vector

\return float
the magnitude of a 2D vector
*/
/******************************************************************************/
float Magnitude( const Vector2D & vec )
{
	float magnitudeVal = std::sqrtf( ( vec.x * vec.x ) + ( vec.y * vec.y ) );
	return magnitudeVal;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Computes the angle between two vectors

\param vec
the 2D vector
\param vec2
the 2D vector

\return float
the angle between the two vectors
*/
/******************************************************************************/
float ComputeAngleDegreesBetweenTwoVectors( const Vector2D & vec1, const Vector2D & vec2 )
{
	//compute the dot product
	float dotProdVal = DotProduct( vec1, vec2 );
	//get the magnitude of the vectors
	float magnitudeVec1 = Magnitude( vec1 );
	float magnitudeVec2 = Magnitude( vec2 );

	//std::cout << std::setfill (' ') << std::setw( 0 ) << "dotProdVal : " << dotProdVal << std::endl;

	//compute for the angle between the vectors
	float computedVal = dotProdVal / ( magnitudeVec1 * magnitudeVec2 );

	if ( computedVal > 1.0F )
		computedVal = 1.0F;
	else if ( computedVal < -1.0F )
		computedVal = -1.0F;

	float angleRadians = std::acosf( computedVal );

	//convert to degrees
	float angleDegrees = RadianToDegree( angleRadians );

	return angleDegrees;
}