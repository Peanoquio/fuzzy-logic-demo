/******************************************************************************/
/*!
\file Mtx44.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 12/12/2011
\brief
Implementation file for a 4 by 4 matrix that has the following functions:
Default Constructor
Copy Constructor
Constructor that takes 16 floats

A function called SetColumns that takes in three vectors that will be the columns of the matrix.
A function called SetRows that takes three vectors that will be the rows of the matrix.
A function called GetRow that takes a row number and returns a vector.
A function called GetColumn that takes a column number and returns a vector.
A function called SetRow, that takes a row number and a vector4.
A function called SetColumn that takes a column number and a vector4
A function called SetToIdentity that sets this matrix as an identity matrix.
A function called Transpose that sets this matrix to its transpose.
A function called SetToZero that sets all of the values to zero
A function called GetTranspose that Returns a matrix that is the transpose of this matrix.
A function called GetElement that takes a row and a column and returns the value.
A function called SetElement that takes a row a column and a value and sets that element to the value.

Operator* for two Mtx44 classes.
Operator*= for two Mtx44 classes.
Operator* for a Matrix and a vector.
Operator= for the matrix class
Operator* for a scalar and a matrix.

A function called SetToRotation that takes an angle in radians and sets this matrix to the rotation matrix.
A function called SetToRotationDegrees that takes an angle in degrees and sets this matrix to the rotation matrix.
A function called SetToScale that takes a scale value x, y and z and makes this matrix the scale matrix.
A function called SetToTranslation that takes an x, y and z value and sets this matrix to the translation matrix.

projection transformations
A function called Ortho that sets this matrix to the orthographic projection matrix.
A function called GetOrtho that returns an orthographic projection matrix
A function called Frustum that sets this matrix to the asymmetric frustum projection matrix.
A function called GetFrustum that returns an asymmetric frustum projection matrix
A function called Perspective that sets this matrix to the symmetric perspective projection matrix.
A function called GetPerspective that returns an symmetric perspective projection matrix

rotation along general axis
A function called SetGeneralRotationAxis that does a rotation along general axis in radians
A function called SetGeneralRotationAxisDegrees that does a rotation along general axis in degrees

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef MTX_44_H
#define MTX_44_H
////////////////////////////////////////////////////////////////////////////////

#include "Vector4.h"

static const int MAX_ROW = 4;
static const int MAX_COL = 4;

namespace Math
{
	class Mtx44
	{
	public:
		//default constructor
		Mtx44 (void);

		//constructor
		Mtx44 (const float a, const float b, const float c, const float d, 
			const float e, const float f, const float g, const float h, 
			const float i, const float j, const float k, const float l,
			const float m, const float n, const float o, const float p);


		//operator overload
		//Operator* for two Mtx44 classes.
		Mtx44 operator* (const Mtx44& rhsMatrix) const;
		//Operator* for a Matrix and a vector.
		Vector4 operator* (const Vector4& vectorVal) const;
		//Operator* for a scalar and a matrix.
		Mtx44 operator* (const float factor) const;		
		//Operator*= for two Mtx44 classes.	
		Mtx44& operator*= (const Mtx44 rhsMatrix);		
		//Operator= for the matrix class	
		Mtx44& operator= (const Mtx44 rhsMatrix);
		//Operator!= for the matrix class	
		bool operator!= (const Mtx44 rhsMatrix) const;
		//Operator== for the matrix class	
		bool operator== (const Mtx44 rhsMatrix) const;


		//methods
		//A function called SetColumns that takes in three vectors that will be the columns of the matrix.
		void SetColumns (const Vector4& v1, const Vector4& v2, const Vector4& v3, const Vector4& v4); 
		//A function called SetRows that takes three vectors that will be the rows of the matrix.
		void SetRows (const Vector4& v1, const Vector4& v2, const Vector4& v3, const Vector4& v4);
		//A function called GetRow that takes a row number and returns a vector.
		Vector4 GetRow (const int rowNum) const;
		//A function called GetColumn that takes a column number and returns a vector.
		Vector4 GetColumn (const int colNum) const;
		//A function called SetRow, that takes a row number and a vector4.
		void SetRow (const int rowNum, const Vector4& vectorVal);
		//A function called SetColumn that takes a column number and a vector4
		void SetColumn (const int colNum, const Vector4& vectorVal);


		//A function called SetToIdentity that sets this matrix as an identity matrix.
		void SetToIdentity (void);			
		//A function called SetToZero that sets all of the values to zero
		void SetToZero (void);
		//A function called Transpose that sets this matrix to its transpose.
		void Transpose (void);	
		//A function called Inverse that sets this matrix to its inverse.
		//void Inverse (void);		
		
		
		//A function called GetDeterminant that returns the determinant of this matrix.
		//float GetDeterminant (void) const;
		//A function called GetAdjugate that returns a matrix that is the adjugate of this matrix
		//Mtx44 GetAdjugate (void) const;
		//A function called GetInverse that returns a matrix that is the inverse of this matrix.
		//Mtx44 GetInverse (void) const;	
		//A function called GetTranspose that Returns a matrix that is the transpose of this matrix.
		Mtx44 GetTranspose (void) const;
		

		//A function called GetElement that takes a row and a column and returns the value.
		float GetElement (unsigned rowVal, unsigned colVal) const;
		//A function called SetElement that takes a row a column and a value and sets that element to the value.
		void SetElement (unsigned rowVal, unsigned colVal, float elementVal);

		
		//A function called SetToRotationX that takes an angle in radians and sets this matrix to the rotation matrix.
		void SetToRotationX (const float radianValue);
		//A function called SetToRotationDegreesX that takes an angle in degrees and sets this matrix to the rotation matrix.
		void SetToRotationDegreesX (const float degreeValue);
		//A function called SetToRotationY that takes an angle in radians and sets this matrix to the rotation matrix.
		void SetToRotationY (const float radianValue);
		//A function called SetToRotationDegreesY that takes an angle in degrees and sets this matrix to the rotation matrix.
		void SetToRotationDegreesY (const float degreeValue);
		//A function called SetToRotationZ that takes an angle in radians and sets this matrix to the rotation matrix.
		void SetToRotationZ (const float radianValue);
		//A function called SetToRotationDegreesZ that takes an angle in degrees and sets this matrix to the rotation matrix.
		void SetToRotationDegreesZ (const float degreeValue);

		//A function called SetToScale that takes a scale value x, y and z and makes this matrix the scale matrix.
		void SetToScale (const float xVal, const float yVal, const float zVal);
		//A function called SetToTranslation that takes an x, y and z value and sets this matrix to the translation matrix.
		void SetToTranslation (const float xTransVal, const float yTransVal, const float zTransVal);


		//custom method
		//A function called CopyArray that copies the contents of a source array into the destination array
		void CopyArray (const float* sourceArray, float* destinationArray, const unsigned arrSize) const;		
		//This method is used to validate if the values of the two matrices are different
		bool IsMatrixDifferent(const Mtx44& rhsMatrix) const;
		//A function called GetSubMatrix that populates an array only with the matrix values found in rows and columns that are not excluded 
		//void GetSubMatrix (const unsigned ignoreRowVal, const unsigned ignoreColVal, float* floatArr, const unsigned arrSize) const;

		//projection transformations
		//A function called Ortho that sets this matrix to the orthographic projection matrix.
		void Ortho (const float left, const float right, const float bottom, const float top, const float nearVal, const float farVal);	
		//A function called GetOrtho that returns an orthographic projection matrix
		Mtx44 GetOrtho (const float left, const float right, const float bottom, const float top, const float nearVal, const float farVal) const;	
		//A function called Frustum that sets this matrix to the asymmetric frustum projection matrix.
		void Frustum (const float left, const float right, const float bottom, const float top, const float nearVal, const float farVal);	
		//A function called GetFrustum that returns an asymmetric frustum projection matrix
		Mtx44 GetFrustum (const float left, const float right, const float bottom, const float top, const float nearVal, const float farVal) const;
		//A function called Perspective that sets this matrix to the symmetric perspective projection matrix.
		void Perspective (const float fieldOfView, const float aspectRatio, const float nearVal, const float farVal);	
		//A function called GetPerspective that returns an symmetric perspective projection matrix
		Mtx44 GetPerspective (const float fieldOfView, const float aspectRatio, const float nearVal, const float farVal) const;

		//rotation along general axis
		//A function called SetGeneralRotationAxis that does a rotation along general axis in radians
		void SetGeneralRotationAxis ( const float radianValue, const Vector4 & rotationAxis );
		//A function called SetGeneralRotationAxisDegrees that does a rotation along general axis in degrees
		void SetGeneralRotationAxisDegrees ( const float degreeValue, const Vector4 & rotationAxis );


		//set the planar reflection matrix
		void SetPlanarReflection ( const Vector4& reflectorVertex, const Vector4& vectorPerpToPlane );


		const float * GetMatrixArr (void) const;

	private:
		float m_matrixArr[MAX_ROW * MAX_COL];
	};

	//non-class methods

	//Operator* for a scalar and a matrix.
	Mtx44 operator* (const float factor, Mtx44& rhsMatrix);

	//Operator* for a vector and a matrix.
	Vector4 operator* (const Vector4& vectorVal, const Mtx44& rhsMatrix);
	

}//end namespace Math


#endif //MTX_44_H
////////////////////////////////////////////////////////////////////////////////