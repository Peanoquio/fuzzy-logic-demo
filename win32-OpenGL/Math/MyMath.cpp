/******************************************************************************/
/*!
\file MyMath.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 12/12/2011
\brief
This contains general math functions such as converting degree to radians and vice-versa

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "MyMath.h"

namespace Math
{
	/******************************************************************************/
	/*! 
	\brief 
	Converts an angle from degrees to radians

	\param value
	the value in degrees
	\return
	*/
	/******************************************************************************/
	float DegreeToRadian(float value)
	{
		return value * PI / 180.0F;
	}


	/******************************************************************************/
	/*! 
	\brief 
	Converts an angle from radians to degrees

	\param value
	the value in radians
	\return
	*/
	/******************************************************************************/
	float RadianToDegree(float value)
	{
		return value * 180.0F / PI;
	}


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

		//get the positive values of the difference
		if ( differenceVal < 0.0F )
		{
			differenceVal *= -1.0F;
		}

		//validate the difference against the Epsilon value that will allow a certain margin of difference
		if ( differenceVal > Math::EPSILON )
		{
			return false;
		}
		else
		{
			return true;
		}
	}

} //end namespace Math