/******************************************************************************/
/*!
\file MyMath.h
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


////////////////////////////////////////////////////////////////////////////////
#ifndef MYMATH_H
#define MYMATH_H
////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <exception>

namespace Math
{
	//used for approximation when comparing floating point values
	const float	EPSILON				= 0.00001F;
    const float	PI					= 3.1415926535897932384626433832795F;
    const float TWO_PI				= PI * 2.0F;
    const float HALF_PI				= PI / 2.0F;
    const float QUARTER_PI			= PI / 4.0F;
	const float REVOLUTION_DEGREES	= 360.0F;

    float DegreeToRadian( float value );
    float RadianToDegree( float value );

	const bool FloatValueSame( const float lhsValue, const float rhsValue );

} //end namespace Math

#endif
////////////////////////////////////////////////////////////////////////////////