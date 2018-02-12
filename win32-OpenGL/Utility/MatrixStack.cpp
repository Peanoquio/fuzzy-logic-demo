/******************************************************************************/
/*!
\file MatrixStack.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 12/12/2011
\brief
The matrix stack that manages the matrix transformations

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "MatrixStack.h"

namespace Utility
{
	/******************************************************************************/
	/*!
	The constructor for the MatrixStack class
	\param
	\return
	*/
	/******************************************************************************/
	MatrixStack::MatrixStack (void)
		: m_currentMatrixMode( MODELVIEW )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the matrix mode of the matrix stack which simulates toggling between 
	GL_MODELVIEW and GL_PROJECTION OpenGL matrix modes
	\param matrixMode
	The matrix mode which should either be MY_GL_MODELVIEW or MY_GL_PROJECTION.
	If an invalid matrix mode as passed, the default matrix mode will be MY_GL_MODELVIEW
	\return
	*/
	/******************************************************************************/
	void MatrixStack::MatrixMode (const MatrixModeEnum matrixMode)
	{
		//set the matrix mode only if user passed the correct mode
		if (matrixMode == MODELVIEW || matrixMode == PROJECTION)
		{
			this->m_currentMatrixMode = matrixMode;	
		}	

		//validate if empty, load the identity matrix
		if ( this->IsEmpty() )
		{
			Math::Mtx44 myMatrix;
			myMatrix.SetToIdentity();
			//add the new matrix as the last element of the current matrix mode vector
			this->m_matrixStack[this->m_currentMatrixMode].push_back(myMatrix);
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Duplicates the current matrix on the stack and puts it on top of the stack
	\param
	\return
	*/
	/******************************************************************************/
	void MatrixStack::Push (void)
	{
		//to simulate duplicating the current matrix on the stack
		//get the matrix at the top of the stack
		Math::Mtx44 myMatrix = this->Top();
		//add the matrix as the last element of the current matrix mode vector
		this->m_matrixStack[this->m_currentMatrixMode].push_back(myMatrix);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Removes the current matrix from the top of the stack
	\param
	\return
	*/
	/******************************************************************************/
	void MatrixStack::Pop (void)
	{
		//remove the last element of the current matrix mode vector
		this->m_matrixStack[this->m_currentMatrixMode].pop_back();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Replaces the current matrix with the new matrix being passed
	\param matrix
	the new matrix to replace the current matrix
	\return
	*/
	/******************************************************************************/
	void MatrixStack::LoadMatrix (const Math::Mtx44 & matrix)
	{
		//to simulate replacing the current matrix on the stack
		if (this->IsEmpty())
		{
			//add the new matrix as the last element of the current matrix mode vector
			this->m_matrixStack[this->m_currentMatrixMode].push_back(matrix);
		}
		else
		{
			//overwrite the last element with the new matrix
			unsigned lastElementIndex = this->m_matrixStack[this->m_currentMatrixMode].size() - 1;
			this->m_matrixStack[this->m_currentMatrixMode].at(lastElementIndex) = matrix;
		}		
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Concatenates the current matrix with the new matrix being passed
	\param matrix
	the new matrix to be concatenated with the current matrix
	\return
	*/
	/******************************************************************************/
	void MatrixStack::MultMatrix (const Math::Mtx44 & matrix)
	{
		//get the matrix at the top of the stack
		Math::Mtx44 myMatrix = this->Top();
		//perform matrix multiplication
		myMatrix =  myMatrix * matrix;
		//load the concatenated matrix as the current matrix
		this->LoadMatrix(myMatrix);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Checks whether the matrix stack is empty
	\param
	\return
	boolean - true if empty, otherwise false
	*/
	/******************************************************************************/
	bool MatrixStack::IsEmpty (void) const
	{
		//check if the map is empty
		return this->m_matrixStack[this->m_currentMatrixMode].empty();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Retrieves the matrix on top of the stack
	\param
	\return
	Mtx44 - the matrix on top of the stack
	*/
	/******************************************************************************/
	const Math::Mtx44 & MatrixStack::Top (void) const
	{
		//return the last element of the current matrix mode vector
		return this->m_matrixStack[this->m_currentMatrixMode].back();
	}

} //end namespace Utility