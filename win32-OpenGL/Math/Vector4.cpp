/******************************************************************************/
/*!
\file Vector4.cpp
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


#include "Vector4.h"


namespace Math
{

	/******************************************************************************/
	/*!
	\brief
	Vector4::Vector4 (void)
	This is the default constructor

	\param void
	
	\exception None
	\return void
	*/
	/******************************************************************************/
	Vector4::Vector4 (void)
		: m_x(0.0F), m_y(0.0F), m_z(0.0F), m_w(0.0F)
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	Vector4::Vector4 (const float xVal, const float yVal, const float zVal, const float wVal)
	This is the constructor if the user passed x, y, z and w values
	
	\param xVal
	the x value
	\param yVal
	the y value
	\param zVal
	the z value
	\param wVal
	the w value

	\exception None
	\return void
	*/
	/******************************************************************************/
	Vector4::Vector4 (const float xVal, const float yVal, const float zVal, const float wVal)
		: m_x(xVal), m_y(yVal), m_z(zVal), m_w(wVal)
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	Vector4::Vector4 (const Vector4& vectorVal) : m_x(vectorVal.m_x), m_y(vectorVal.m_y), m_z(vectorVal.m_z), m_w(vectorVal.m_w)
	This is the copy constructor

	\param const Vector4& vectorVal - right hand side vector
	
	\exception None
	\return void
	*/
	/******************************************************************************/
	Vector4::Vector4 (const Vector4& vectorVal) 
		: m_x(vectorVal.m_x), m_y(vectorVal.m_y), m_z(vectorVal.m_z), m_w(vectorVal.m_w)
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//methods
	/******************************************************************************/
	/*!
	\brief
	void Vector4::Zero (void)
	This method is used to set the vector values to zero

	\param void
	
	\exception None
	\return void
	*/
	/******************************************************************************/
	void Vector4::Zero (void)
	{
		this->m_x = 0.0F;
		this->m_y = 0.0F;
		this->m_z = 0.0F;
		//this->m_w = 0.0F;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	bool Vector4::IsZero (void) const
	This method is used to validate if the vector values are zero

	\param void
	
	\exception None
	\return boolean: true if vector values are zero, false if vector values are not zero
	*/
	/******************************************************************************/
	bool Vector4::IsZero (void) const
	{
		float xAbs = abs(m_x);
		float yAbs = abs(m_y);
		float zAbs = abs(m_z);
		//float wAbs = abs(m_w);

		if (xAbs >= 0.0F && yAbs >= 0.0F && zAbs >= 0.0F //&& wAbs >= 0.0F
			&& xAbs <= Math::EPSILON && yAbs <= Math::EPSILON && zAbs <= Math::EPSILON) //&& wAbs <= Math::EPSILON) 
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Vector4::Set (void)
	This method is used to set the vector values to zero

	\param void
	
	\exception None
	\return void
	*/
	/******************************************************************************/
	void Vector4::Set (void)
	{
		this->m_x = 0.0F;
		this->m_y = 0.0F;
		this->m_z = 0.0F;
		//this->m_w = 0.0F;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Vector4::Set (const float xVal, const float yVal, const float zVal, const float wVal)
	This method is used to set the vector values based on the values the user provided

	\param const float xVal - m_x unit value of the vector
	\param const float yVal - m_y unit value of the vector
	\param const float zVal - m_z unit value of the vector
	\param const float wVal - m_w unit value of the vector
	
	\exception None
	\return void
	*/
	/******************************************************************************/
	void Vector4::Set (const float xVal, const float yVal, const float zVal, const float wVal)
	{
		this->m_x = xVal;
		this->m_y = yVal;
		this->m_z = zVal;
		this->m_w = wVal;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	float Vector4::Length (void) const
	This method is used to get the length (magnitude) of the vector

	\param void
	
	\exception None
	\return float: magnitude of vector
	*/
	/******************************************************************************/
	float Vector4::Length (void) const
	{
		float length = sqrt(this->LengthSquared());
		return length;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	float Vector4::LengthSquared (void) const
	This method is used to get the squared length (magnitude) of the vector

	\param void
	
	\exception None
	\return float: squared magnitude of vector
	*/
	/******************************************************************************/
	float Vector4::LengthSquared (void) const
	{
		float length = (m_x * m_x) + (m_y * m_y) + (m_z * m_z); //+ (m_w * m_w);
		return length;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	float Vector4::Distance (const Vector4& vectorVal) const
	This method is used to get the distance between 2 vectors

	\param const Vector4& vectorVal - right hand side vector
	
	\exception None
	\return float: distance between 2 vectors
	*/
	/******************************************************************************/
	float Vector4::Distance (const Vector4& vectorVal) const
	{
		float distance = sqrt (this->DistanceSquared(vectorVal));
		return distance;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	float Vector4::DistanceSquared (const Vector4& vectorVal) const
	This method is used to get the squared distance between 2 vectors

	\param const Vector4& vectorVal - right hand side vector
	
	\exception None
	\return float: squared distance between 2 vectors
	*/
	/******************************************************************************/
	float Vector4::DistanceSquared (const Vector4& vectorVal) const
	{
		float xDiff = this->m_x - vectorVal.m_x;
		float yDiff = this->m_y - vectorVal.m_y;
		float zDiff = this->m_z - vectorVal.m_z;
		//float wDiff = this->m_w - vectorVal.m_w;

		float distance = (xDiff * xDiff) + (yDiff * yDiff) + (zDiff * zDiff); //+ (wDiff * wDiff);
		return distance;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	float Vector4::Dot (const Vector4& vectorVal) const
	This method is used to get the dot product between 2 vectors

	\param const Vector4& vectorVal - right hand side vector
	
	\exception None
	\return float: dot product between 2 vectors
	*/
	/******************************************************************************/
	float Vector4::Dot (const Vector4& vectorVal) const
	{
		//compute for the dot product based on this formula
		float dotProduct = (m_x * vectorVal.m_x) + (m_y * vectorVal.m_y) + (m_z * vectorVal.m_z) + (m_w * vectorVal.m_w);
		return dotProduct;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	Vector4 Vector4::Cross (const Vector4& vectorVal) const
	This method is used to get the cross product between 2 vectors

	\param const Vector4& vectorVal - right hand side vector
	
	\exception None
	\return Vector: containing the computed m_x, m_y, m_z, m_w values based on the cross product
	*/
	/******************************************************************************/
	Vector4 Vector4::Cross (const Vector4& vectorVal) const
	{
		//compute for the cross product for m_x, m_y and m_z based on this formula
		float crossProdX = (this->m_y * vectorVal.m_z) - (this->m_z * vectorVal.m_y);
		float crossProdY = (this->m_z * vectorVal.m_x) - (this->m_x * vectorVal.m_z);
		float crossProdZ = (this->m_x * vectorVal.m_y) - (this->m_y * vectorVal.m_x);

		Vector4 myVector (crossProdX, crossProdY, crossProdZ, 0.0F);

		/*
		float crossProdX = (this->m_z * vectorVal.m_w) - (this->m_w * vectorVal.m_z);
		float crossProdY = (this->m_w * vectorVal.m_x) - (this->m_x * vectorVal.m_w);
		float crossProdZ = (this->m_x * vectorVal.m_y) - (this->m_y * vectorVal.m_x);
		float crossProdW = (this->m_y * vectorVal.m_z) - (this->m_z * vectorVal.m_y);

		Vector4 myVector (crossProdX, crossProdY, crossProdZ, crossProdW);
		*/		

		return myVector;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Vector4::Normalize (void)
	This method is used to normalize the vector

	\param void
	
	\exception None
	\return void
	*/
	/******************************************************************************/
	void Vector4::Normalize (void)
	{
		//get the magnitude of the vector
		float vectorMagnitude = this->Length();

		//normalize the vector by we dividing the vector by its magnitude
		*this = *this * (1 / vectorMagnitude);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	Vector4 Vector4::GetNormalized (void) const
	This method is used to get the normalized value of the vector

	\param void
	
	\exception None
	\return Vector: containing the normalized m_x, m_y, m_z values
	*/
	/******************************************************************************/
	Vector4 Vector4::GetNormalized (void) const
	{
		//get the magnitude of the vector
		float vectorMagnitude = Length();

		//to get normalized value, we divide the vector by its magnitude
		Vector4 myVector = *this * (1 / vectorMagnitude);

		return myVector;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	Vector4 Vector4::Project (const Vector4& vectorVal) const
	This method is used to get the projection of vector U onto vector V

	\param const Vector4& vectorVal - right hand side vector
	
	\exception None
	\return Vector: projection of vector U onto vector V
	*/
	/******************************************************************************/
	Vector4 Vector4::Project (const Vector4& vectorVal) const
	{
		//get the dot product
		float dotProduct = this->Dot (vectorVal);
		//get the squared magnitude
		float vectorMagnitudeSquared = vectorVal.LengthSquared();

		//to get the projection, divide the dot product by the squared magnitude of vector v
		//and then multiply it by vector v
		Vector4 myVector = (dotProduct / vectorMagnitudeSquared) * vectorVal;

		return myVector;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	Vector4 Vector4::ProjectPerp (const Vector4& vectorVal) const
	This method is used to get the perpendicular vector between vector u and the projection of vector U onto vector V

	\param const Vector4& vectorVal - right hand side vector
	
	\exception None
	\return Vector: perpendicular vector between vector u and the projection of vector U onto vector V
	*/
	/******************************************************************************/
	Vector4 Vector4::ProjectPerp (const Vector4& vectorVal) const
	{
		Vector4 myVector = *this - this->Project (vectorVal);

		return myVector;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	const float Vector4::ComputeAngleDegreesBetweenTwoVectors ( const Vector4& rhsVectorVal ) const
	This method gets the angle between two vectors

	\param const Vector4& rhsVectorVal - right hand side vector
	
	\exception None
	\return float: the computed angle in degrees
	*/
	/******************************************************************************/
	const float Vector4::ComputeAngleDegreesBetweenTwoVectors ( const Vector4& rhsVectorVal ) const
	{
		float angleDegrees = 0.0F;

		angleDegrees = acosf ( this->Dot( rhsVectorVal ) / ( this->Length() * rhsVectorVal.Length() ) );

		return angleDegrees;
	}
	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	const bool Vector4::CompareValue ( const float lhsValue, const float rhsValue ) const
	This method is used to compare two floating point values

	\param lhsValue
	the left-hand side value	
	\param rhsValue
	the right-hand side value

	\exception None
	\return 
	boolean - true is the floating point values are approximately the same, otherwise false
	*/
	/******************************************************************************/
	const bool Vector4::CompareValue ( const float lhsValue, const float rhsValue ) const
	{
		bool boolValSame = true;

		//get the positive value of the difference
		float valDiff = abs ( lhsValue - rhsValue );

		//validate the difference against the EPSILON value that will allow a certain margin of difference
		if (valDiff > Math::EPSILON)
		{
			boolValSame = false;
		}

		return boolValSame;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	const float Vector4::ComputeWValueAddSub ( const Vector4& vectorVal ) const
	This method is used to compute for the w value based on the operations done 
	on the homogenous coordinates of vectors and points

	\param vectorVal
	the right-hand side vector

	\exception None
	\return 
	float - the w value for the homogenous coordinate of the vector
	*/
	/******************************************************************************/
	const float Vector4::ComputeWValueAddSub ( const Vector4& vectorVal ) const
	{
		//0.0F pertains to a vector
		//1.0F pertains to a point
		float wValue = 0.0F;

		//compare floating point values
		bool isThisWZero = this->CompareValue ( this->m_w, 0.0F );
		bool isThisWOne = this->CompareValue ( this->m_w, 1.0F );
		bool isRhsWZero = this->CompareValue ( vectorVal.m_w, 0.0F );
		bool isRhsWOne = this->CompareValue ( vectorVal.m_w, 1.0F );

		//vector
		if ( isThisWZero && isRhsWZero )
		{
			wValue = 0.0F;
		}
		//point
		else if ( isThisWOne && isRhsWOne )
		{
			wValue = 0.0F;
		}
		//point and vector
		else
		{
			wValue = 1.0F;
		}

		return wValue;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//operator overload
	/******************************************************************************/
	/*!
	\brief
	unary negative operator
	Vector4 Vector4::operator- (void) const
	This method is used to overload the unary negative operator to be applied on the vector

	\param void
	
	\exception None
	\return Vector: negated vector
	*/
	/******************************************************************************/
	Vector4 Vector4::operator- (void) const
	{
		Vector4 myVector;
		myVector.m_x = -m_x;
		myVector.m_y = -m_y;
		myVector.m_z = -m_z;
		//myVector.m_w = -m_w;

		return myVector;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	vector subtraction
	Vector4 Vector4::operator- (const Vector4& vectorVal) const
	This method is used to overload the subtraction operator so we can subtract a vector from another vector

	\param const Vector4& vectorVal - right hand side vector
	
	\exception None
	\return Vector: the difference between 2 vectors
	*/
	/******************************************************************************/
	Vector4 Vector4::operator- (const Vector4& vectorVal) const
	{
		float wValue = this->ComputeWValueAddSub ( vectorVal );

		Vector4 myVector (
			m_x - vectorVal.GetFloatX(), 
			m_y - vectorVal.GetFloatY(), 
			m_z - vectorVal.GetFloatZ(),
			wValue);
			//m_w - vectorVal.GetFloatW());
		return myVector;	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	vector addition
	Vector4 Vector4::operator+ (const Vector4& vectorVal) const
	This method is used to overload the addition operator so we can add a vector to another vector

	\param const Vector4& vectorVal - right hand side vector
	
	\exception None
	\return Vector: the sum of 2 vectors
	*/
	/******************************************************************************/
	Vector4 Vector4::operator+ (const Vector4& vectorVal) const
	{
		float wValue = this->ComputeWValueAddSub ( vectorVal );

		Vector4 myVector (
			m_x + vectorVal.GetFloatX(), 
			m_y + vectorVal.GetFloatY(), 
			m_z + vectorVal.GetFloatZ(),
			wValue);
			//m_w + vectorVal.GetFloatW());
		return myVector;
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	scalar multiplication
	Vector4 Vector4::operator* (const float factor) const
	This method is used to overload the multiplication operator so we can multiply the vector by the factor

	\param const Vector4& vectorVal - right hand side vector
	
	\exception None
	\return Vector: the vector scaled by the factor
	*/
	/******************************************************************************/
	Vector4 Vector4::operator* (const float factor) const
	{
		Vector4 myVector (m_x * factor, m_y * factor, m_z * factor, m_w); //m_w * factor);
		return myVector;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	addition assignment operator
	Vector4& Vector4::operator+= (const Vector4& vectorVal)
	This method is used to overload the addition assignment operator so we can perform addition 
	and assign the value back to the vector

	\param const Vector4& vectorVal - right hand side vector
	
	\exception None
	\return Vector: reference of the computed vector
	*/
	/******************************************************************************/
	Vector4& Vector4::operator+= (const Vector4& vectorVal)
	{
		//contains an implicit: Vector4* this
		this->m_x += vectorVal.m_x;
		this->m_y += vectorVal.m_y;
		this->m_z += vectorVal.m_z;
		//this->m_w += vectorVal.m_w;

		return *this;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	subtraction assignment operator
	Vector4& Vector4::operator-= (const Vector4& vectorVal)
	This method is used to overload the subtraction assignment operator so we can perform subtraction 
	and assign the value back to the vector

	\param const Vector4& vectorVal - right hand side vector
	
	\exception None
	\return Vector: reference of the computed vector
	*/
	/******************************************************************************/
	Vector4& Vector4::operator-= (const Vector4& vectorVal)
	{
		//contains an implicit: Vector4* this
		this->m_x -= vectorVal.m_x;
		this->m_y -= vectorVal.m_y;
		this->m_z -= vectorVal.m_z;
		//this->m_w -= vectorVal.m_w;

		return *this;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	multiplication assignment operator
	Vector4& Vector4::operator-= (const Vector4& vectorVal)
	This method is used to overload the multiplication assignment operator so we can perform multiplication 
	and assign the value back to the vector

	\param const Vector4& vectorVal - right hand side vector
	
	\exception None
	\return Vector: reference of the computed vector
	*/
	/******************************************************************************/
	Vector4& Vector4::operator*= (const float factor)
	{
		//contains an implicit: Vector4* this
		this->m_x *= factor;
		this->m_y *= factor;
		this->m_z *= factor;
		//this->m_w *= factor;

		return *this;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	equality operator
	bool Vector4::operator== (const Vector4& vectorVal) const
	This method is used to overload the equality operator so we can compare the values between vectors

	\param const Vector4& vectorVal - right hand side vector
	
	\exception None
	\return boolean: true if the vectors are the same, otherwise, return false
	*/
	/******************************************************************************/
	bool Vector4::operator== (const Vector4& vectorVal) const
	{
		return !IsDifferent(vectorVal);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	/******************************************************************************/
	/*!
	\brief
	inequality operator
	bool Vector4::operator== (const Vector4& vectorVal) const
	This method is used to overload the inequality operator so we can compare the values between vectors

	\param const Vector4& vectorVal - right hand side vector
	
	\exception None
	\return boolean: true if the vectors are different, otherwise, return false
	*/
	/******************************************************************************/
	bool Vector4::operator!= (const Vector4& vectorVal) const
	{
		return IsDifferent(vectorVal);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	bool Vector4::IsDifferent(const Vector4& vectorVal) const
	This method is used to validate if the values of the two vectors are different

	\param const Vector4& vectorVal - right hand side vector
	
	\exception None
	\return boolean: true if the vectors are different, otherwise, return false
	*/
	/******************************************************************************/
	bool Vector4::IsDifferent(const Vector4& vectorVal) const
	{
		bool boolVal = false;

		//get the difference between the vectors
		float xDiff = m_x - vectorVal.m_x;
		float yDiff = m_y - vectorVal.m_y;
		float zDiff = m_z - vectorVal.m_z;
		//float wDiff = m_w - vectorVal.m_w;

		//get the positive values of the difference
		if (xDiff < 0.0F)
		{
			xDiff *= -1.0F;
		}

		if (yDiff < 0.0F)
		{
			yDiff *= -1.0F;
		}

		if (zDiff < 0.0F)
		{
			zDiff *= -1.0F;
		}

		/*
		if (wDiff < 0.0F)
		{
			wDiff *= -1.0F;
		}
		*/

		//validate the difference against the EPSILON value that will allow a certain margin of difference
		if (xDiff > Math::EPSILON || yDiff > Math::EPSILON || zDiff > Math::EPSILON) //|| wDiff > Math::EPSILON)
		{
			boolVal = true;
		}

		return boolVal;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//settors
	/******************************************************************************/
	/*!
	\brief
	void Vector4::SetFloatX (float xVal)
	This method is used to set the vector value m_x

	\param float xVal
	
	\exception None
	\return void
	*/
	/******************************************************************************/
	void Vector4::SetFloatX (float xVal)
	{
		m_x = xVal;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Vector4::SetFloatY (float yVal)
	This method is used to set the vector value m_y

	\param float yVal
	
	\exception None
	\return void
	*/
	/******************************************************************************/
	void Vector4::SetFloatY (float yVal)
	{
		m_y = yVal;	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Vector4::SetFloatZ (float zVal)
	This method is used to set the vector value m_z

	\param float zVal
	
	\exception None
	\return void
	*/
	/******************************************************************************/
	void Vector4::SetFloatZ (float zVal)
	{
		m_z = zVal;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Vector4::SetFloatW (float wVal)
	This method is used to set the vector value m_w

	\param float wVal
	
	\exception None
	\return void
	*/
	/******************************************************************************/
	void Vector4::SetFloatW (float wVal)
	{
		m_w = wVal;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//gettors
	/******************************************************************************/
	/*!
	\brief
	float Vector4::GetFloatX (void) const
	This method is used to get the vector value m_x

	\param void
	
	\exception None
	\return float: value of vector m_x
	*/
	/******************************************************************************/
	float Vector4::GetFloatX (void) const
	{
		return m_x;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	float Vector4::GetFloatY (void) const
	This method is used to get the vector value m_y

	\param void
	
	\exception None
	\return float: value of vector m_y
	*/
	/******************************************************************************/
	float Vector4::GetFloatY (void) const
	{
		return m_y;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	float Vector4::GetFloatZ (void) const
	This method is used to get the vector value m_z

	\param void
	
	\exception None
	\return float: value of vector m_z
	*/
	/******************************************************************************/
	float Vector4::GetFloatZ (void) const
	{
		return m_z;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	/******************************************************************************/
	/*!
	\brief
	float Vector4::GetFloatW (void) const
	This method is used to get the vector value m_w

	\param void
	
	\exception None
	\return float: value of vector m_w
	*/
	/******************************************************************************/
	float Vector4::GetFloatW (void) const
	{
		return m_w;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	scalar multiplication
	AdvCert::Vector4 operator*( float scalar, const AdvCert::Vector4& rhs )
	This method is used to overload the multiplication operator so we can multiply the vector being passed by the factor

	\param float scalar - factor used to multiply the vector values
	\param const Vector4& vectorVal - right hand side vector
	
	\exception None
	\return Vector: the vector scaled by the factor
	*/
	/******************************************************************************/
	Math::Vector4 operator* ( float scalar, const Math::Vector4& rhs )
	{
		Math::Vector4 myVector (
			rhs.GetFloatX() * scalar, 
			rhs.GetFloatY() * scalar, 
			rhs.GetFloatZ() * scalar,
			rhs.GetFloatZ());
			//rhs.GetFloatW() * scalar);

		return myVector;
	}
	
}