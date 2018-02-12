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


#include "Mtx44.h"


namespace Math
{

	/******************************************************************************/
	/*!
	\brief
	Mtx44::Mtx44 (void)
	This is the default constructor

	\param void

	\exception None
	\return void
	*/
	/******************************************************************************/
	Mtx44::Mtx44 (void)
	{
		int index = 0;

		//loop through the one-dimensional 3D matrix
		for (unsigned j = 0; j < MAX_COL; ++j)		
		{
			for (unsigned i = 0; i < MAX_ROW; ++i)
			{
				index = (j * MAX_ROW) + i;
				this->m_matrixArr[index] = 0.0F;
			} //end for loop
		}//end for loop	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	Mtx44::Mtx44 (const float a, const float b, const float c, const float d, 
	const float e, const float f, const float g, const float h, 
	const float i, const float j, const float k, const float l,
	const float m, const float n, const float o, const float p)
	This is the constructor if the user passed values for the matrix

	\param const float a - value to populate the matrix element
	\param const float b
	\param const float c
	\param const float d
	\param const float e
	\param const float f
	\param const float g
	\param const float h
	\param const float i
	\param const float j
	\param const float k
	\param const float i
	\param const float m 
	\param const float n 
	\param const float o 
	\param const float p

	\exception None
	\return void
	*/
	/******************************************************************************/
	Mtx44::Mtx44 (const float a, const float b, const float c, const float d, 
		const float e, const float f, const float g, const float h, 
		const float i, const float j, const float k, const float l,
		const float m, const float n, const float o, const float p)
	{
		this->m_matrixArr[0] = a;
		this->m_matrixArr[1] = b;
		this->m_matrixArr[2] = c;
		this->m_matrixArr[3] = d;

		this->m_matrixArr[4] = e;
		this->m_matrixArr[5] = f;
		this->m_matrixArr[6] = g;
		this->m_matrixArr[7] = h;

		this->m_matrixArr[8] = i;
		this->m_matrixArr[9] = j;
		this->m_matrixArr[10] = k;
		this->m_matrixArr[11] = l;

		this->m_matrixArr[12] = m;
		this->m_matrixArr[13] = n;
		this->m_matrixArr[14] = o;
		this->m_matrixArr[15] = p;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//operator overload
	/******************************************************************************/
	/*!
	\brief
	Operator* for two Mtx44 classes.
	Mtx44 Mtx44::operator* (const Mtx44& rhsMatrix) const
	This method is used to overload the multiplication operator so we can multiply two matrices

	\param const Mtx44& rhsMatrix - right hand side matrix

	\exception None
	\return Mtx44: a copy of the matrix (result of multiplying two matrices)
	*/
	/******************************************************************************/
	Mtx44 Mtx44::operator* (const Mtx44& rhsMatrix) const
	{
		Mtx44 myMatrix;
		Vector4 vectorRow;
		Vector4 vectorCol;

		//loop through the one-dimensional 3D matrix by row progression
		for (unsigned i = 0; i < MAX_ROW; ++i)
		{
			vectorRow = this->GetRow(i);

			for (unsigned j = 0; j < MAX_COL; ++j)		
			{
				vectorCol = rhsMatrix.GetColumn(j);

				//get the dot product between the row and the column then assign it to the matrix element
				myMatrix.SetElement(i, j, vectorRow.Dot(vectorCol));

			}//end for loop		
		}//end for loop

		return myMatrix;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	Operator* for a Matrix and a vector.
	Vector4 Mtx44::operator* (const Vector4& vectorVal) const
	This method is used to overload the multiplication operator so we can multiply a matrix and a vector

	\param const Vector4& vectorVal - vector to be multiplied with the matrix

	\exception None
	\return Vector4: a copy of the vector (result of multiplying a matrix and a vector)
	*/
	/******************************************************************************/
	Vector4 Mtx44::operator* (const Vector4& vectorVal) const
	{
		Vector4 myVector;
		//get each row of the matrix 
		Vector4 vector1 = this->GetRow(0);
		Vector4 vector2 = this->GetRow(1);
		Vector4 vector3 = this->GetRow(2);
		Vector4 vector4 = this->GetRow(3);

		//set the values (after computing the dot product) of the vector to be returned
		myVector.SetFloatX(vector1.Dot(vectorVal));
		myVector.SetFloatY(vector2.Dot(vectorVal));
		myVector.SetFloatZ(vector3.Dot(vectorVal));
		myVector.SetFloatW(vector4.Dot(vectorVal));

		return myVector;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	Operator* for a scalar and a matrix.
	Mtx44 Mtx44::operator* (const float factor) const
	This method is used to overload the multiplication operator so we can multiply a matrix and a scalar factor

	\param const float factor - the scalar factor value to be multiplied

	\exception None
	\return Mtx44: a copy of the matrix (result of multiplying a matrix and a scalar)
	*/
	/******************************************************************************/
	Mtx44 Mtx44::operator* (const float factor) const
	{
		unsigned index = 0;
		Mtx44 myMatrix;

		//loop through the one-dimensional 3D matrix
		for (unsigned j = 0; j < MAX_COL; ++j)		
		{
			for (unsigned i = 0; i < MAX_ROW; ++i)
			{
				index = (j * MAX_ROW) + i;
				//multiply the element of the matrix by the factor
				myMatrix.m_matrixArr[index] = this->m_matrixArr[index] * factor;
			}//end for loop
		}//end for loop

		return myMatrix;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	Operator*= for two Mtx44 classes.	
	Mtx44& Mtx44::operator*= (const Mtx44 rhsMatrix)
	This method is used to overload the multiplication assignment operator so we can perform multiplication 
	between two matrices and assign the value back to the left-hand side matrix

	\param const Mtx44 rhsMatrix - right hand side matrix

	\exception None
	\return Mtx44: reference of the computed left-hand side matrix
	*/
	/******************************************************************************/
	Mtx44& Mtx44::operator*= (const Mtx44 rhsMatrix)
	{
		Mtx44 myMatrix;
		Vector4 vectorRow;
		Vector4 vectorCol;

		//loop through the one-dimensional 3D matrix by row progression		
		for (unsigned i = 0; i < MAX_ROW; ++i)
		{
			vectorRow = this->GetRow(i);

			for (unsigned j = 0; j < MAX_COL; ++j)
			{
				vectorCol = rhsMatrix.GetColumn(j);			

				//get the dot product between the row and the column then assign it to the matrix element
				myMatrix.SetElement(i, j, vectorRow.Dot(vectorCol));

			}//end for loop		
		}//end for loop

		//copy the values of the right-hand side matrix over to the left-hand side matrix
		*this = myMatrix;

		return *this;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	Operator= for the matrix class		
	Mtx44& Mtx44::operator= (const Mtx44 rhsMatrix)
	This method is used to overload the assignment operator so we can assign the value of 
	the right-hand side matrix to the left-hand side matrix

	\param const Mtx44 rhsMatrix - right hand side matrix

	\exception None
	\return Mtx44: reference of the left-hand side matrix
	*/
	/******************************************************************************/
	Mtx44& Mtx44::operator= (const Mtx44 rhsMatrix)
	{
		//check for self-assignment
		if (&rhsMatrix != this)
		{
			//copy the values of the source array into the destination array
			CopyArray(rhsMatrix.m_matrixArr, this->m_matrixArr, MAX_ROW*MAX_COL);
		}
		return *this;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	Operator!= for the matrix class
	bool Mtx44::operator!= (const Mtx44 rhsMatrix) const
	This method is used to overload the inequality operator so we can compare the values between matrices

	\param const Mtx44 rhsMatrix - right hand side matrix

	\exception None
	\return boolean: true if the matrices are the different, otherwise, return false
	*/
	/******************************************************************************/
	bool Mtx44::operator!= (const Mtx44 rhsMatrix) const
	{
		return this->IsMatrixDifferent(rhsMatrix);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	Operator== for the matrix class	
	bool Mtx44::operator== (const Mtx44 rhsMatrix) const
	This method is used to overload the equality operator so we can compare the values between matrices

	\param const Mtx44 rhsMatrix - right hand side matrix

	\exception None
	\return boolean: true if the matrices are the same, otherwise, return false
	*/
	/******************************************************************************/
	bool Mtx44::operator== (const Mtx44 rhsMatrix) const
	{
		return !this->IsMatrixDifferent(rhsMatrix);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Mtx44::SetColumns (const Vector4& v1, const Vector4& v2, const Vector4& v3, const Vector4& v4)
	A function called SetColumns that takes in three vectors that will be the columns of the matrix.

	\param const Vector4& v1 - vector containing the values to populate the matrix
	\param const Vector4& v2 - vector containing the values to populate the matrix
	\param const Vector4& v3 - vector containing the values to populate the matrix
	\param const Vector4& v4 - vector containing the values to populate the matrix

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::SetColumns (const Vector4& v1, const Vector4& v2, const Vector4& v3, const Vector4& v4)
	{
		this->m_matrixArr[0] = v1.GetFloatX();
		this->m_matrixArr[1] = v1.GetFloatY();
		this->m_matrixArr[2] = v1.GetFloatZ();
		this->m_matrixArr[3] = v1.GetFloatW();

		this->m_matrixArr[4] = v2.GetFloatX();
		this->m_matrixArr[5] = v2.GetFloatY();
		this->m_matrixArr[6] = v2.GetFloatZ();
		this->m_matrixArr[7] = v2.GetFloatW();

		this->m_matrixArr[8] = v3.GetFloatX();
		this->m_matrixArr[9] = v3.GetFloatY();
		this->m_matrixArr[10] = v3.GetFloatZ();
		this->m_matrixArr[11] = v3.GetFloatW();

		this->m_matrixArr[12] = v4.GetFloatX();
		this->m_matrixArr[13] = v4.GetFloatY();
		this->m_matrixArr[14] = v4.GetFloatZ();
		this->m_matrixArr[15] = v4.GetFloatW();		
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Mtx44::SetRows (const Vector4& v1, const Vector4& v2, const Vector4& v3, const Vector4& v4)
	A function called SetRows that takes three vectors that will be the rows of the matrix.

	\param const Vector4& v1 - vector containing the values to populate the matrix
	\param const Vector4& v2 - vector containing the values to populate the matrix
	\param const Vector4& v3 - vector containing the values to populate the matrix
	\param const Vector4& v4 - vector containing the values to populate the matrix

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::SetRows (const Vector4& v1, const Vector4& v2, const Vector4& v3, const Vector4& v4)
	{
		this->m_matrixArr[0] = v1.GetFloatX();
		this->m_matrixArr[4] = v1.GetFloatY();
		this->m_matrixArr[8] = v1.GetFloatZ();
		this->m_matrixArr[12] = v1.GetFloatW();

		this->m_matrixArr[1] = v2.GetFloatX();
		this->m_matrixArr[5] = v2.GetFloatY();
		this->m_matrixArr[9] = v2.GetFloatZ();
		this->m_matrixArr[13] = v2.GetFloatW();

		this->m_matrixArr[2] = v3.GetFloatX();
		this->m_matrixArr[6] = v3.GetFloatY();
		this->m_matrixArr[10] = v3.GetFloatZ();
		this->m_matrixArr[14] = v3.GetFloatW();

		this->m_matrixArr[3] = v4.GetFloatX();
		this->m_matrixArr[7] = v4.GetFloatY();
		this->m_matrixArr[11] = v4.GetFloatZ();
		this->m_matrixArr[15] = v4.GetFloatW();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	Vector4 Mtx44::GetRow (const int rowNum) const
	A function called GetRow that takes a row number and returns a vector.

	\param const int rowNum - row value of the matrix

	\exception None
	\return Vector4: vector populated with the values of specified row in the matrix
	*/
	/******************************************************************************/
	Vector4 Mtx44::GetRow (const int rowNum) const
	{
		return Vector4 (
			this->m_matrixArr[rowNum + (MAX_COL * 0)], 
			this->m_matrixArr[rowNum + (MAX_COL * 1)], 
			this->m_matrixArr[rowNum + (MAX_COL * 2)],
			this->m_matrixArr[rowNum + (MAX_COL * 3)]
		);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	Vector4 Mtx44::GetColumn (const int colNum) const
	A function called GetColumn that takes a column number and returns a vector.

	\param const int colNum - column value of the matrix

	\exception None
	\return Vector4: vector populated with the values of specified column in the matrix
	*/
	/******************************************************************************/
	Vector4 Mtx44::GetColumn (const int colNum) const
	{
		unsigned index = colNum * MAX_ROW;
		return Vector4 (
			this->m_matrixArr[index], 
			this->m_matrixArr[index+1], 
			this->m_matrixArr[index+2],
			this->m_matrixArr[index+3]
		);
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Mtx44::SetRow (const int rowNum, const Vector4& vectorVal)
	A function called SetRow, that takes a row number and a vector4 to set the values of the specified row in the matrix

	\param const int rowNum - row value of the matrix
	\param const Vector4& vectorVal - vector containing the values to populate the matrix

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::SetRow (const int rowNum, const Vector4& vectorVal)
	{
		this->m_matrixArr[rowNum + (MAX_COL * 0)] = vectorVal.GetFloatX();
		this->m_matrixArr[rowNum + (MAX_COL * 1)] = vectorVal.GetFloatY();
		this->m_matrixArr[rowNum + (MAX_COL * 2)] = vectorVal.GetFloatZ();
		this->m_matrixArr[rowNum + (MAX_COL * 3)] = vectorVal.GetFloatW();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Mtx44::SetColumn (const int colNum, const Vector4& vectorVal)
	A function called SetColumn, that takes a column number and a vector4 to set the values of the specified column in the matrix

	\param const int colNum - column value of the matrix
	\param const Vector4& vectorVal - vector containing the values to populate the matrix

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::SetColumn (const int colNum, const Vector4& vectorVal)
	{
		unsigned index = colNum * MAX_ROW;
		this->m_matrixArr[index] = vectorVal.GetFloatX();
		this->m_matrixArr[index+1] = vectorVal.GetFloatY();
		this->m_matrixArr[index+2] = vectorVal.GetFloatZ();		
		this->m_matrixArr[index+3] = vectorVal.GetFloatW();	
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Mtx44::SetToIdentity (void)
	A function called SetToIdentity that sets this matrix as an identity matrix.	
	sample matrix output:
	1 0 0 0
	0 1 0 0
	0 0 1 0
	0 0 0 1

	\param void

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::SetToIdentity (void)
	{
		unsigned index = 0;

		//loop through the one-dimensional 3D matrix
		for (unsigned j = 0; j < MAX_COL; ++j)		
		{
			for (unsigned i = 0; i < MAX_ROW; ++i)
			{
				index = (j * MAX_ROW) + i;

				//check if the diagonal element in the matrix
				if (i == j)
				{
					this->m_matrixArr[index] = 1.0F;
				}
				else
				{
					this->m_matrixArr[index] = 0.0F;
				}				

			} //end for loop
		}//end for loop	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Mtx44::SetToZero (void)
	A function called SetToZero that sets all of the values to zero	
	sample matrix output:
	0 0 0 0
	0 0 0 0
	0 0 0 0
	0 0 0 0

	\param void

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::SetToZero (void)
	{
		unsigned index = 0;

		//loop through the one-dimensional 3D matrix
		for (unsigned j = 0; j < MAX_COL; ++j)		
		{
			for (unsigned i = 0; i < MAX_ROW; ++i)
			{
				index = (j * MAX_ROW) + i;
				this->m_matrixArr[index] = 0.0F;
			} //end for loop
		}//end for loop	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Mtx44::Transpose (void)
	A function called Transpose that sets this matrix to its transpose.
	sample matrix output:
	0  1  2  3		0  4  8	 12
	4  5  6  7	-> 	1  5  9  13
	8  9  10 11		2  6  10 14
	12 13 14 15		3  7  11 15

	\param void

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::Transpose (void)
	{		
		//get the matrix values row by row
		Vector4 myVector1 = this->GetRow (0);
		Vector4 myVector2 = this->GetRow (1);
		Vector4 myVector3 = this->GetRow (2);
		Vector4 myVector4 = this->GetRow (3);

		//set the matrix values column by column
		this->SetColumn (0, myVector1);
		this->SetColumn (1, myVector2);
		this->SetColumn (2, myVector3);
		this->SetColumn (3, myVector4);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	Mtx44 Mtx44::GetTranspose (void) const
	A function called GetTranspose that Returns a matrix that is the transpose of this matrix.
	sample matrix output:
	0  1  2  3		0  4  8	 12
	4  5  6  7	-> 	1  5  9  13
	8  9  10 11		2  6  10 14
	12 13 14 15		3  7  11 15

	\param void

	\exception None
	\return Mtx44: a copy of the transposed matrix
	*/
	/******************************************************************************/
	Mtx44 Mtx44::GetTranspose (void) const
	{
		Mtx44 myMatrix;

		//get the matrix values row by row
		Vector4 myVector1 = this->GetRow (0);
		Vector4 myVector2 = this->GetRow (1);
		Vector4 myVector3 = this->GetRow (2);
		Vector4 myVector4 = this->GetRow (3);

		//set the matrix values column by column
		myMatrix.SetColumn (0, myVector1);
		myMatrix.SetColumn (1, myVector2);
		myMatrix.SetColumn (2, myVector3);
		myMatrix.SetColumn (3, myVector4);

		return myMatrix;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	float Mtx44::GetElement (unsigned rowVal, unsigned colVal) const
	A function called GetElement that takes a row and a column and returns the value.

	\param unsigned rowVal
	\param unsigned colVal

	\exception None
	\return float: the matrix element value
	*/
	/******************************************************************************/
	float Mtx44::GetElement (unsigned rowVal, unsigned colVal) const
	{
		unsigned index = (colVal * MAX_ROW) + rowVal;
		return this->m_matrixArr[index];
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Mtx44::SetElement (unsigned rowVal, unsigned colVal, float elementVal)
	A function called SetElement that takes a row a column and a value and sets that element to the value.

	\param unsigned rowVal
	\param unsigned colVal
	\param float elementVal

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::SetElement (unsigned rowVal, unsigned colVal, float elementVal)
	{
		unsigned index = (colVal * MAX_ROW) + rowVal;
		this->m_matrixArr[index] = elementVal;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Mtx44::SetToRotationX (const float radianValue)
	A function called SetToRotationX that takes an angle in radians and sets this matrix to the rotation matrix.
	sample matrix output:
	1 0   0    0
	0 cos -sin 0
	0 sin cos  0
	0 0   0    1

	\param const float radianValue

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::SetToRotationX (const float radianValue)
	{
		//set this matrix into an identity matrix
		this->SetToIdentity();
		//set the rotation values of the rotation matrix
		this->SetElement(1, 1, cos(radianValue));
		this->SetElement(1, 2, -sin(radianValue));
		this->SetElement(2, 1, sin(radianValue));
		this->SetElement(2, 2, cos(radianValue));
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Mtx44::SetToRotationDegreesX (const int degreeValue)
	A function called SetToRotationDegreesX that takes an angle in degrees and sets this matrix to the rotation matrix.
	sample matrix output:
	1  0   0    0
	0  cos -sin 0
	0  sin cos  0
	0  0   0    1

	\param const int degreeValue

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::SetToRotationDegreesX (const float degreeValue)
	{
		//convert the degree to radian value and then call the SetToRotation method
		this->SetToRotationX(Math::DegreeToRadian(static_cast<float>(degreeValue)));
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Mtx44::SetToRotationY (const float radianValue)
	A function called SetToRotationY that takes an angle in radians and sets this matrix to the rotation matrix.
	sample matrix output:
	cos  0  sin  0
	0    1  0    0
	-sin 0  cos  0
	0    0  0    1

	\param const float radianValue

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::SetToRotationY (const float radianValue)
	{
		//set this matrix into an identity matrix
		this->SetToIdentity();
		//set the rotation values of the rotation matrix
		this->SetElement(0, 0, cos(radianValue));
		this->SetElement(0, 2, sin(radianValue));
		this->SetElement(2, 0, -sin(radianValue));
		this->SetElement(2, 2, cos(radianValue));
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Mtx44::SetToRotationDegreesY (const int degreeValue)
	A function called SetToRotationDegreesY that takes an angle in degrees and sets this matrix to the rotation matrix.
	sample matrix output:
	cos  0  sin  0
	0    1  0    0
	-sin 0  cos  0
	0    0  0    1

	\param const int degreeValue

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::SetToRotationDegreesY (const float degreeValue)
	{
		//convert the degree to radian value and then call the SetToRotation method
		this->SetToRotationY(Math::DegreeToRadian(static_cast<float>(degreeValue)));
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Mtx44::SetToRotationZ (const float radianValue)
	A function called SetToRotationZ that takes an angle in radians and sets this matrix to the rotation matrix.
	sample matrix output:
	cos -sin 0  0
	sin cos  0  0
	0   0    1  0
	0   0    0  1

	\param const float radianValue

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::SetToRotationZ (const float radianValue)
	{
		//set this matrix into an identity matrix
		this->SetToIdentity();
		//set the rotation values of the rotation matrix
		this->SetElement(0, 0, cos(radianValue));
		this->SetElement(0, 1, -sin(radianValue));
		this->SetElement(1, 0, sin(radianValue));
		this->SetElement(1, 1, cos(radianValue));
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Mtx44::SetToRotationDegreesZ (const int degreeValue)
	A function called SetToRotationDegreesZ that takes an angle in degrees and sets this matrix to the rotation matrix.
	sample matrix output:
	cos -sin 0  0
	sin cos  0  0
	0   0    1  0
	0   0    0  1

	\param const int degreeValue

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::SetToRotationDegreesZ (const float degreeValue)
	{
		//convert the degree to radian value and then call the SetToRotation method
		this->SetToRotationZ(Math::DegreeToRadian(static_cast<float>(degreeValue)));
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Mtx44::SetToScale (const int xVal, const int yVal, const int zVal)
	A function called SetToScale that takes a scale value x, y and z and makes this matrix the scale matrix.
	sample matrix output:
	sx 0  0  0
	0  sy 0  0
	0  0  sz 0
	0  0  0  1

	\param const float xVal - x scale value
	\param const float yVal - y scale value
	\param const float zVal - z scale value

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::SetToScale (const float xVal, const float yVal, const float zVal)
	{
		//set this matrix into an identity matrix
		this->SetToIdentity();
		//set the scale values of the scale matrix
		this->SetElement(0, 0, static_cast<float>(xVal));
		this->SetElement(1, 1, static_cast<float>(yVal));
		this->SetElement(2, 2, static_cast<float>(zVal));
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Mtx44::SetToTranslation (const float xTransVal, const float yTransVal, const float zTransVal)
	A function called SetToTranslation that takes an x and y value and sets this matrix to the translation matrix.
	sample matrix output:
	1 0 0 tx
	0 1 0 ty
	0 0 1 tz
	0 0 0 1

	\param const int xTransVal - x translate value
	\param const int yTransVal - y translate value
	\param const int zTransVal - z translate value

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::SetToTranslation (const float xTransVal, const float yTransVal, const float zTransVal)
	{
		//set this matrix into an identity matrix
		this->SetToIdentity();
		//set the translation values of the translation matrix
		this->SetElement(0, 3, xTransVal);
		this->SetElement(1, 3, yTransVal);
		this->SetElement(2, 3, zTransVal);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//custom method
	/******************************************************************************/
	/*!
	\brief
	void Mtx44::CopyArray (const float* sourceArray, float* destinationArray, const unsigned arrSize) const
	A function called CopyArray that copies the contents of a source array into the destination array

	\param const float* sourceArray
	\param float* destinationArray
	\param const unsigned arrSize

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::CopyArray (const float* sourceArray, float* destinationArray, const unsigned arrSize) const
	{
		for (unsigned x = 0; x < arrSize; ++x)
		{
			destinationArray[x] = sourceArray[x];		
		}//end for loop
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	bool Mtx44::IsMatrixDifferent(const Mtx44& rhsMatrix) const
	This method is used to validate if the values of the two matrices are different

	\param const Mtx44& rhsMatrix - right hand side matrix

	\exception None
	\return boolean: true if the matrices are different, otherwise, return false
	*/
	/******************************************************************************/
	bool Mtx44::IsMatrixDifferent(const Mtx44& rhsMatrix) const
	{
		bool boolVal = false;
		float differenceVal = 0.0F;

		//loop through the one-dimensional 3D matrix
		for (unsigned j = 0; j < MAX_COL; ++j)		
		{
			if (boolVal == true)
			{
				break;
			}

			for (unsigned i = 0; i < MAX_ROW; ++i)
			{
				//get the difference between the matrix elements
				differenceVal = this->GetElement(i,j) - rhsMatrix.GetElement(i,j);

				//get the positive values of the difference
				if (differenceVal < 0.0F)
				{
					differenceVal *= -1;
				}

				//validate the difference against the Epsilon value that will allow a certain margin of difference
				if (differenceVal > Math::EPSILON)
				{
					boolVal = true;
					break;
				}

			}//end for loop
		}//end for loop

		return boolVal;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//non-class methods

	/******************************************************************************/
	/*!
	\brief
	Operator* for a scalar and a matrix.
	Mtx44 operator* (const float factor, Mtx44& rhsMatrix)
	This method is used to overload the multiplication operator so we can multiply a matrix and a scalar factor

	\param const float factor - the scalar factor value to be multiplied with the matrix
	\param Mtx44& rhsMatrix - the right-hand side matrix to be multiplied with the factor

	\exception None
	\return Mtx44: a copy of the matrix (result of multiplying a matrix and a scalar)
	*/
	/******************************************************************************/
	Mtx44 operator* (const float factor, Mtx44& rhsMatrix)
	{
		Mtx44 myMatrix;

		//loop through the one-dimensional 3D matrix
		for (unsigned j = 0; j < MAX_COL; ++j)		
		{
			for (unsigned i = 0; i < MAX_ROW; ++i)
			{
				//compute for the matrix element multiplied by the scalar factor and then assign the value back to the element
				myMatrix.SetElement(i, j, (rhsMatrix.GetElement(i, j) * factor));
			} //end for loop
		}//end for loop	

		return myMatrix;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	Operator* for a vector and a matrix.
	Vector4 operator* (const Vector4& vectorVal, const Mtx44& rhsMatrix)
	This method is used to overload the multiplication operator so we can multiply a vector and a matrix

	\param const Vector4& vectorVal - vector to be multiplied with the matrix
	\param const Mtx44& rhsMatrix - matrix to be multiplied with the vector

	\exception None
	\return Vector4: a copy of the vector (result of multiplying a matrix and a vector)
	*/
	/******************************************************************************/
	Vector4 operator* (const Vector4& vectorVal, const Mtx44& rhsMatrix)
	{
		Vector4 myVector;
		//get each row of the matrix 
		Vector4 vector1 = rhsMatrix.GetRow(0);
		Vector4 vector2 = rhsMatrix.GetRow(1);
		Vector4 vector3 = rhsMatrix.GetRow(2);
		Vector4 vector4 = rhsMatrix.GetRow(3);

		//set the values (after computing the dot product) of the vector to be returned
		myVector.SetFloatX(vector1.Dot(vectorVal));
		myVector.SetFloatY(vector2.Dot(vectorVal));
		myVector.SetFloatZ(vector3.Dot(vectorVal));
		myVector.SetFloatW(vector4.Dot(vectorVal));

		return myVector;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//projection transformations
	/******************************************************************************/
	/*!
	\brief
	void Mtx44::Ortho (const float left, const float right, const float bottom, const float top, const float nearVal, const float farVal)
	A function called Ortho that sets this matrix to the orthographic projection matrix.
	sample matrix output:
	2/r-l  0      0       -(r+l/r-l)
	0      2/t-b  0       -(t+b/t-b)
	0      0      -2/f-n  -(f+n/f-n)
	0      0      0       1

	\param const float left
	\param const float right
	\param const float bottom
	\param const float top
	\param const float nearVal
	\param const float farVal

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::Ortho (const float left, const float right, const float bottom, const float top, const float nearVal, const float farVal)
	{
		//set this matrix into an identity matrix
		this->SetToIdentity();

		//set the values of the matrix
		this->SetElement(0, 0, (2 / (right - left)));
		this->SetElement(1, 1, (2 / (top - bottom)));
		this->SetElement(2, 2, -(2 / (farVal - nearVal)));

		this->SetElement(0, 3, -((right + left) / (right - left)));
		this->SetElement(1, 3, -((top + bottom) / (top - bottom)));
		this->SetElement(2, 3, -((farVal + nearVal) / (farVal - nearVal)));
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
	/******************************************************************************/
	/*!
	\brief
	Mtx44 Mtx44::GetOrtho (const float left, const float right, const float bottom, const float top, const float nearVal, const float farVal) const
	A function called GetOrtho that returns an orthographic projection matrix
	sample matrix output:
	2/r-l  0      0       -(r+l/r-l)
	0      2/t-b  0       -(t+b/t-b)
	0      0      -2/f-n  -(f+n/f-n)
	0      0      0       1

	\param const float left
	\param const float right
	\param const float bottom
	\param const float top
	\param const float nearVal
	\param const float farVal

	\exception None
	\return Mtx44 orthographic projection matrix
	*/
	/******************************************************************************/
	Mtx44 Mtx44::GetOrtho (const float left, const float right, const float bottom, const float top, const float nearVal, const float farVal) const
	{
		Mtx44 myMatrix;

		//set this matrix into an identity matrix
		myMatrix.SetToIdentity();

		//set the values of the matrix
		myMatrix.SetElement(0, 0, (2 / (right - left)));
		myMatrix.SetElement(1, 1, (2 / (top - bottom)));
		myMatrix.SetElement(2, 2, -(2 / (farVal - nearVal)));

		myMatrix.SetElement(0, 3, -((right + left) / (right - left)));
		myMatrix.SetElement(1, 3, -((top + bottom) / (top - bottom)));
		myMatrix.SetElement(2, 3, -((farVal + nearVal) / (farVal - nearVal)));

		return myMatrix;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Mtx44::Frustum (const float left, const float right, const float bottom, const float top, const float nearVal, const float farVal)
	A function called Frustum that sets this matrix to the asymmetric frustum projection matrix.
	sample matrix output:
	2n/r-l  0       r+l/r-l     0
	0       2n/t-b  t+b/t-b     0
	0       0       n+f/n-f     2nf/n-f
	0       0       -1          0

	\param const float left
	\param const float right
	\param const float bottom
	\param const float top
	\param const float nearVal
	\param const float farVal

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::Frustum (const float left, const float right, const float bottom, const float top, const float nearVal, const float farVal)
	{
		//set this matrix into an identity matrix
		this->SetToIdentity();

		//set the values of the matrix
		this->SetElement(0, 0, ((2 * nearVal) / (right - left)));
		this->SetElement(1, 1, ((2 * nearVal) / (top - bottom)));
		this->SetElement(2, 3, ((2 * nearVal * farVal) / (nearVal - farVal)));		

		this->SetElement(0, 2, ((right + left) / (right - left)));
		this->SetElement(1, 2, ((top + bottom) / (top - bottom)));
		this->SetElement(2, 2, ((nearVal + farVal) / (nearVal - farVal)));

		this->SetElement(3, 2, -1.0F);
		this->SetElement(3, 3, 0.0F);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	Mtx44 Mtx44::GetFrustum (const float left, const float right, const float bottom, const float top, const float nearVal, const float farVal)
	A function called GetFrustum that returns an asymmetric frustum projection matrix
	sample matrix output:
	2n/r-l  0       r+l/r-l     0
	0       2n/t-b  t+b/t-b     0
	0       0       n+f/n-f     2nf/n-f
	0       0       -1          0

	\param const float left
	\param const float right
	\param const float bottom
	\param const float top
	\param const float nearVal
	\param const float farVal

	\exception None
	\return Mtx44 asymmetric frustum projection matrix
	*/
	/******************************************************************************/
	Mtx44 Mtx44::GetFrustum (const float left, const float right, const float bottom, const float top, const float nearVal, const float farVal) const
	{
		Mtx44 myMatrix;

		//set this matrix into an identity matrix
		myMatrix.SetToIdentity();

		//set the values of the matrix
		myMatrix.SetElement(0, 0, ((2 * nearVal) / (right - left)));
		myMatrix.SetElement(1, 1, ((2 * nearVal) / (top - bottom)));
		myMatrix.SetElement(2, 3, ((2 * nearVal * farVal) / (nearVal - farVal)));		

		myMatrix.SetElement(0, 2, ((right + left) / (right - left)));
		myMatrix.SetElement(1, 2, ((top + bottom) / (top - bottom)));
		myMatrix.SetElement(2, 2, ((nearVal + farVal) / (nearVal - farVal)));

		myMatrix.SetElement(3, 2, -1.0F);
		myMatrix.SetElement(3, 3, 0.0F);

		return myMatrix;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Mtx44::Perspective (const float fieldOfView, const float aspectRatio, const float nearVal, const float farVal)
	A function called Perspective that sets this matrix to the symmetric perspective projection matrix.
	sample matrix output:
	(cot(deg/2))/a  0           0           0
	0               cot(deg/2)  0           0
	0               0           -(f+n/f-n)  -(2nf/f-n)
	0               0           -1          0

	\param const float fieldOfView - Specifies the field of view angle, in degrees, in the y direction.
	\param const float aspectRatio - Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	\param const float nearVal - Specifies the distance from the viewer to the near clipping plane (always positive).
	\param const float farVal - Specifies the distance from the viewer to the far clipping plane (always positive).

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::Perspective (const float fieldOfView, const float aspectRatio, const float nearVal, const float farVal)
	{
		float computedFieldOfView = 1 / tan(Math::DegreeToRadian(fieldOfView / 2.0F));

		//set this matrix into an identity matrix
		this->SetToIdentity();		

		//set the values of the matrix
		this->SetElement(0, 0, (computedFieldOfView / aspectRatio));
		this->SetElement(1, 1, (computedFieldOfView));
		this->SetElement(2, 2, -((farVal + nearVal) / (farVal - nearVal)));
		this->SetElement(2, 3, -((2 * nearVal * farVal) / (farVal - nearVal)));	

		this->SetElement(3, 2, -1.0F);
		this->SetElement(3, 3, 0.0F);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	Mtx44 Mtx44::GetPerspective (const float fieldOfView, const float aspectRatio, const float nearVal, const float farVal) const
	A function called GetPerspective that returns an symmetric perspective projection matrix
	sample matrix output:
	(cot(deg/2))/a  0           0           0
	0               cot(deg/2)  0           0
	0               0           -(f+n/f-n)  -(2nf/f-n)
	0               0           -1          0

	\param const float fieldOfView - Specifies the field of view angle, in degrees, in the y direction.
	\param const float aspectRatio - Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	\param const float nearVal - Specifies the distance from the viewer to the near clipping plane (always positive).
	\param const float farVal - Specifies the distance from the viewer to the far clipping plane (always positive).

	\exception None
	\return Mtx44 symmetric frustum perspective matrix
	*/
	/******************************************************************************/
	Mtx44 Mtx44::GetPerspective (const float fieldOfView, const float aspectRatio, const float nearVal, const float farVal) const
	{
		Mtx44 myMatrix;

		float computedFieldOfView = 1 / tan(Math::DegreeToRadian(fieldOfView / 2.0F));

		//set this matrix into an identity matrix
		myMatrix.SetToIdentity();

		//set the values of the matrix
		myMatrix.SetElement(0, 0, (computedFieldOfView / aspectRatio));
		myMatrix.SetElement(1, 1, (computedFieldOfView));
		myMatrix.SetElement(2, 2, -((farVal + nearVal) / (farVal - nearVal)));
		myMatrix.SetElement(2, 3, -((2 * nearVal * farVal) / (farVal - nearVal)));	

		myMatrix.SetElement(3, 2, -1.0F);
		myMatrix.SetElement(3, 3, 0.0F);

		return myMatrix;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//rotation along general axis
	/******************************************************************************/
	/*!
	\brief
	void Mtx44::SetGeneralRotationAxis ( const float radianValue, const Vector4 & rotationAxis )
	A function called SetGeneralRotationAxis that sets a matrix for rotation along an arbitrary axis in radians
	sample matrix output:
	u^2 + (1 - u^2) cos     uv (1 - cos) - w sin      uw (1 - cos) + v sin     0
	uv (1 - cos) + w sin    v^2 + (1 - v^2) cos       vw (1 - cos) - u sin     0
	uw (1 - cos) - v sin    vw (1 - cos) + u sin      w^2 + (1 - w^2) cos      0        
	0                       0                         0                        1

	\param const float radianValue - specifies the rotation
	\param const Vector4 & rotationAxis - specifies the axis where to rotate along

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::SetGeneralRotationAxis ( const float radianValue, const Vector4 & rotationAxis )
	{
		float u = rotationAxis.GetFloatX();
		float v = rotationAxis.GetFloatY();
		float w = rotationAxis.GetFloatZ();

		//compute for the sin and cos
		float computedSin = sinf( radianValue );
		float computedCos = cosf( radianValue );

		//set this matrix into an identity matrix
		this->SetToIdentity();

		//set the values of the matrix

		//first row
		//u^2 + (1 - u^2) cos
		this->SetElement( 0, 0, ( u*u + (1 - u*u) * computedCos ) );
		//uv (1 - cos) - w sin
		this->SetElement( 0, 1, ( u*v * (1 - computedCos) - (w * computedSin) ) );
		//uw (1 - cos) + v sin
		this->SetElement( 0, 2, ( u*w * (1 - computedCos) + (v * computedSin) ) );

		//second row
		//uv (1 - cos) + w sin
		this->SetElement( 1, 0, ( u*v * (1 - computedCos) + (w * computedSin) ) );
		//v^2 + (1 - v^2) cos
		this->SetElement( 1, 1, ( v*v + (1 - v*v) * computedCos ) );
		//vw (1 - cos) - u sin
		this->SetElement( 1, 2, ( v*w * (1 - computedCos) - (u * computedSin) ) );

		//third row
		//uw (1 - cos) - v sin
		this->SetElement( 2, 0, ( u*w * (1 - computedCos) - (v * computedSin) ) );
		//vw (1 - cos) + u sin
		this->SetElement( 2, 1, ( v*w * (1 - computedCos) + (u * computedSin) ) );
		//w^2 + (1 - w^2) cos
		this->SetElement( 2, 2, ( w*w + (1 - w*w) * computedCos ) );
	}

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	void Mtx44::SetGeneralRotationAxisDegrees ( const float degreeValue, const Vector4 & rotationAxis )
	A function called SetGeneralRotationAxisDegrees that sets a matrix for rotation along an arbitrary axis in degrees
	sample matrix output:
	u^2 + (1 - u^2) cos     uv (1 - cos) - w sin      uw (1 - cos) + v sin     0
	uv (1 - cos) + w sin    v^2 + (1 - v^2) cos       vw (1 - cos) - u sin     0
	uw (1 - cos) - v sin    vw (1 - cos) + u sin      w^2 + (1 - w^2) cos      0        
	0                       0                         0                        1

	\param const float degreeValue - specifies the rotation
	\param const Vector4 & rotationAxis - specifies the axis where to rotate along

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::SetGeneralRotationAxisDegrees ( const float degreeValue, const Vector4 & rotationAxis )
	{
		//convert the degree to radian value and then call the SetGeneralRotationAxis method
		this->SetGeneralRotationAxis( Math::DegreeToRadian( degreeValue ), rotationAxis );
	}
	
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	Set the planar reflection matrix
	The reflection transformation can be decomposed for convenience into a translation to the origin, a rotation mapping the mirror into the plane, 
	a scale of -1 in , the inverse of the rotation previously used, and a translation back to the mirror location.
	Given one vertex  of the planar reflector and a vector  perpendicular to the plane, this sequence of transformations can be expressed as the single 4 by 4 matrix
	
	A function called SetPlanarReflection that sets the planar reflection matrix
	P: a vertex of the planar reflector
	V: the vector perpendicular to the plane
	sample matrix output:
	1 - 2 (Vx^2)    -2 (VxVy)      -2 (VxVz)		2 (P.V) Vx
	-2 (VxVy)		1 - 2 (Vy^2)   -2 (VyVz)		2 (P.V) Vy
	-2 (VxVz)		-2 (VyVz)      1 - 2 (Vz^2)     2 (P.V) Vz
	0               0              0                1

	\param reflectorVertex - a vertex of the planar reflector
	\param vectorPerpToPlane - the vector perpendicular to the plane

	\exception None
	\return void
	*/
	/******************************************************************************/
	void Mtx44::SetPlanarReflection ( const Vector4& reflectorVertex, const Vector4& vectorPerpToPlane )
	{
		//set this matrix into an identity matrix
		this->SetToIdentity();

		//set the values of the matrix
		float planeNormalX = vectorPerpToPlane.GetFloatX();
		float planeNormalY = vectorPerpToPlane.GetFloatY();
		float planeNormalZ = vectorPerpToPlane.GetFloatZ();
		float dotProductVal = reflectorVertex.Dot( vectorPerpToPlane );

		//first row
		// 1 - 2 (Vx^2)
		this->SetElement( 0, 0, ( 1.0f - 2.0F * ( planeNormalX * planeNormalX ) ) );
		// -2 (VxVy)
		this->SetElement( 0, 1, ( -2.0F * ( planeNormalX * planeNormalY ) ) );
		// -2 (VxVz)
		this->SetElement( 0, 2, ( -2.0F * ( planeNormalX * planeNormalZ ) ) );
		// 2 (P.V) Vx
		this->SetElement( 0, 3, ( 2.0F * ( dotProductVal ) * planeNormalX ) );

		//second row
		// -2 (VxVy)
		this->SetElement( 1, 0, ( -2.0F * ( planeNormalX * planeNormalY ) ) );
		// 1 - 2 (Vy^2)		
		this->SetElement( 1, 1, ( 1.0f - 2.0F * ( planeNormalY * planeNormalY ) ) );
		// -2 (VyVz)
		this->SetElement( 1, 2, ( -2.0F * ( planeNormalY * planeNormalZ ) ) );
		// 2 (P.V) Vy
		this->SetElement( 1, 3, ( 2.0F * ( dotProductVal ) * planeNormalY ) );

		//third row
		// -2 (VxVz)
		this->SetElement( 2, 0, ( -2.0F * ( planeNormalX * planeNormalZ ) ) );
		// -2 (VyVz)	
		this->SetElement( 2, 1, ( -2.0F * ( planeNormalY * planeNormalZ ) ) );
		// 1 - 2 (Vz^2)		
		this->SetElement( 2, 2, ( 1.0f - 2.0F * ( planeNormalZ * planeNormalZ ) ) );
		// 2 (P.V) Vz
		this->SetElement( 2, 3, ( 2.0F * ( dotProductVal ) * planeNormalZ ) );
	}



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief
	const float * Mtx44::GetMatrixArr (void) const
	A function called GetMatrixArr that returns the matrix array

	\param

	\exception None
	\return 
	float * - the matrix array
	*/
	/******************************************************************************/
	const float * Mtx44::GetMatrixArr (void) const
	{
		return this->m_matrixArr;
	}

}//end namespace Math