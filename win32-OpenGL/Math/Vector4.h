/******************************************************************************/
/*!
\file Vector4.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 12/12/2011
\brief
This Vector class contains methods to peform the following:
1. overload operators
2. reset the vector to zero
3. compute for length of a vector
4. compute for the distance between vectors
5. compute for the dot product
6. compute for the cross product
7. compute for the normalized vector
8. compute for the projection of a vector onto another
9. compute for the angle between vectors
10. gettors and settors

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef VECTOR_4_H
#define VECTOR_4_H
////////////////////////////////////////////////////////////////////////////////

#include "MyMath.h"


namespace Math
{
	class Vector4
	{
	public:
		//default constructor
		Vector4 (void);

		//constructor
		Vector4 (const float xVal, const float yVal, const float zVal, const float wVal);

		//copy constructor
		Vector4 (const Vector4& vectorVal);

		//methods
		//detailed comments can be found in the corresponding .cpp file
		void Zero (void);
		bool IsZero (void) const;
		void Set (void);
		void Set (const float xVal, const float yVal, const float zVal, const float wVal);
		float Length (void) const;
		float LengthSquared (void) const;
		float Distance (const Vector4& vectorVal) const;
		float DistanceSquared (const Vector4& vectorVal) const;
		float Dot (const Vector4& vectorVal) const;
		Vector4 Cross (const Vector4& vectorVal) const;
		void Normalize (void);
		Vector4 GetNormalized (void) const;
		Vector4 Project (const Vector4& vectorVal) const;
		Vector4 ProjectPerp (const Vector4& vectorVal) const;

		//operator overload
		//vector addition
		Vector4 operator+ (const Vector4& vectorVal) const;
		//vector substraction
		Vector4 operator- (const Vector4& vectorVal) const;
		//scalar multiplication
		Vector4 operator* (const float factor) const;
		//addition assignment operator
		Vector4& operator+= (const Vector4& vectorVal);
		//subtraction assignment operator
		Vector4& operator-= (const Vector4& vectorVal);
		//multiplication assignment operator
		Vector4& operator*= (const float factor);
		//equality operator
		bool operator== (const Vector4& vectorVal) const;
		//inequality operator
		bool operator!= (const Vector4& vectorVal) const;
		//compute for the difference
		bool IsDifferent (const Vector4& vectorVal) const;
		//unary negative operator
		Vector4 operator- (void) const;

		//settors
		void SetFloatX (float xVal);
		void SetFloatY (float yVal);
		void SetFloatZ (float zVal);
		void SetFloatW (float wVal);

		//gettors
		float GetFloatX (void) const;
		float GetFloatY (void) const;
		float GetFloatZ (void) const;
		float GetFloatW (void) const;

		//get the angle between two vectors
		const float ComputeAngleDegreesBetweenTwoVectors ( const Vector4& rhsVectorVal ) const;

	private:
		// Data
		float m_x, m_y, m_z, m_w;

		const bool CompareValue ( const float lhsValue, const float rhsValue ) const;
		const float ComputeWValueAddSub ( const Vector4& vectorVal ) const;
	};

	Vector4 operator* ( float scalar, const Math::Vector4& rhs );
}

#endif
////////////////////////////////////////////////////////////////////////////////