/******************************************************************************/
/*!
\file LookAt.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1050
\par Project #03
\date 09/02/2012
\brief
This is the "look at" class that will be used to view the objects in the world from the view perspective

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


#include "LookAt.h"


namespace LookAt
{
	/******************************************************************************/
	/*! 
	\brief 
	The default constructor for the look at class

	\param
	\return
	*/
	/******************************************************************************/
	LookAt::LookAt( void )
		: m_lookAtPosition( 0.0F, 0.0F, 4.0F, 1.0F ), 
		m_lookAtTarget( 0.0F, 0.0F, 0.0F, 1.0F ), 
		m_worldUpVector( 0.0F, 1.0F, 0.0F, 0.0F ),
		m_lookAtViewDirectionVector( 0.0F, 0.0F, -1.0F, 0.0F ), 
		m_lookAtUpVector( 0.0F, 1.0F, 0.0F, 0.0F ), 
		m_lookAtSideVector( 1.0F, 0.0F, 0.0F, 0.0F ),
		m_xOrientation( 0.0F ),
		m_yOrientation( -90.0F )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	The constructor for the look at class that computes the view, side and up vectors

	\param lookAtPosition
	the position of the look at
	\param lookAtTarget
	the target of the look at
	\param worldUpVector
	the up vector of the world
	\return
	*/
	/******************************************************************************/
	LookAt::LookAt ( const Math::Vector4 & lookAtPosition, const Math::Vector4 & lookAtTarget, const Math::Vector4 & worldUpVector )
		: m_lookAtPosition( lookAtPosition ), 
		m_lookAtTarget( lookAtTarget ), 
		m_worldUpVector( worldUpVector ),
		m_lookAtViewDirectionVector( lookAtTarget - lookAtPosition ), 
		m_lookAtUpVector( 0.0F, 1.0F, 0.0F, 0.0F ), 
		m_lookAtSideVector( 1.0F, 0.0F, 0.0F, 0.0F )
	{
		this->m_lookAtViewDirectionVector.Normalize();

		//compute for the look at side vector by performing a cross product between the world up vector and the view direction vector
		this->m_lookAtSideVector = this->m_lookAtViewDirectionVector.Cross( worldUpVector );
		this->m_lookAtSideVector.Normalize();

		//compute for the look at up vector by performing the cross product between the look at side and view direction vectors
		this->m_lookAtUpVector = this->m_lookAtSideVector.Cross ( this->m_lookAtViewDirectionVector );
	}

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Sets the position of the look at

	\param lookAtPosition
	the position of the look at
	\return
	*/
	/******************************************************************************/
	void LookAt::SetLookAtPosition ( const Math::Vector4 & lookAtPosition )
	{
		this->m_lookAtPosition = lookAtPosition;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Sets the target of the look at

	\param target
	the target of the look at
	\return
	*/
	/******************************************************************************/
	void LookAt::SetLookAtTarget ( const Math::Vector4 & lookAtTarget )
	{
		this->m_lookAtTarget = lookAtTarget;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Sets the up vector of the world

	\param worldUpVector
	the up vector of the world
	\return
	*/
	/******************************************************************************/
	void LookAt::SetWorldUpVector ( const Math::Vector4 & worldUpVector )
	{
		this->m_worldUpVector = worldUpVector;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Gets the position of the look at

	\param
	\return
	Vector4 - the position of the look at
	*/
	/******************************************************************************/
	const Math::Vector4 & LookAt::GetLookAtPosition ( void ) const
	{
		return this->m_lookAtPosition;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Gets the target of the look at

	\param
	\return
	Vector4 - the target of the look at
	*/
	/******************************************************************************/
	const Math::Vector4 & LookAt::GetLookAtTarget ( void ) const
	{
		return this->m_lookAtTarget;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Gets the up vector of the world

	\param
	\return
	Vector4 - the up vector of the world
	*/
	/******************************************************************************/
	const Math::Vector4 & LookAt::GetWorldUpVector ( void ) const
	{
		return this->m_worldUpVector;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Sets the view vector of the look at

	\param lookAtViewDirectionVector
	the view vector of the look at
	\return
	*/
	/******************************************************************************/
	void LookAt::SetLookAtViewDirectionVector ( const Math::Vector4 & lookAtViewDirectionVector )
	{
		this->m_lookAtViewDirectionVector = lookAtViewDirectionVector;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Gets the view vector of the look at

	\param
	\return
	Vector4 - the view vector of the look at
	*/
	/******************************************************************************/
	const Math::Vector4 & LookAt::GetLookAtViewDirectionVector ( void ) const
	{
		return this->m_lookAtViewDirectionVector;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Gets the up vector of the look at

	\param
	\return
	Vector4 - the up vector of the look at
	*/
	/******************************************************************************/
	const Math::Vector4 & LookAt::GetLookAtUpVector ( void ) const
	{
		return this->m_lookAtUpVector;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Gets the up side of the look at

	\param
	\return
	Vector4 - the side vector of the look at
	*/
	/******************************************************************************/
	const Math::Vector4 & LookAt::GetLookAtSideVector ( void ) const
	{
		return this->m_lookAtSideVector;
	}
	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Generates the view transformation matrix

	\param
	\return
	Mtx44 - the view transformation matrix
	*/
	/******************************************************************************/
	Math::Mtx44 LookAt::GenerateViewTransformMtx ( void )
	{
		Math::Mtx44 viewTransformMtx;
		
		//compute the look at basis vectors
		Math::Vector4 fillerVector( 0.0F, 0.0F, 0.0F, 1.0F );

		//recompute the look at target based on the view direction and the look at position
		this->m_lookAtTarget = this->m_lookAtPosition + this->m_lookAtViewDirectionVector;
		this->m_lookAtViewDirectionVector.Normalize();

		//recompute the "up" vector if the view vector is parallel to the world up vector
		if ( this->m_lookAtViewDirectionVector.Cross( this->m_worldUpVector ).IsZero() )
		{
			this->m_worldUpVector.SetFloatX ( 1.0F );
			this->m_worldUpVector.SetFloatY ( 0.0F );
			this->m_worldUpVector.SetFloatZ ( 0.0F );
			this->m_worldUpVector.SetFloatW ( 0.0F );

			if ( this->m_lookAtViewDirectionVector.Cross( this->m_worldUpVector ).IsZero() )
			{
				this->m_worldUpVector.SetFloatX ( 0.0F );
				this->m_worldUpVector.SetFloatY ( 0.0F );
				this->m_worldUpVector.SetFloatZ ( 1.0F );
				this->m_worldUpVector.SetFloatW ( 0.0F );
			}
		}		

		//compute for the look at side vector by performing a cross product between the world up vector and the view direction vector
		this->m_lookAtSideVector = this->m_lookAtViewDirectionVector.Cross( this->m_worldUpVector );
		this->m_lookAtSideVector.Normalize();

		//compute for the look at up vector by performing the cross product between the look at side and view direction vectors
		this->m_lookAtUpVector = this->m_lookAtSideVector.Cross( this->m_lookAtViewDirectionVector );
		//this->m_worldUpVector.Normalize();

		//set up the rotational values view transformation matrix based on the computed look at basis vectors
		//we negate the lookAtViewDirectionVector to align with the world basis z vector
		//we also get the inverse of the model to view matrix (simply perform transpose since rotational matrix is orthographic)		
		viewTransformMtx.SetToIdentity();
		viewTransformMtx.SetRows( this->m_lookAtSideVector, this->m_lookAtUpVector, -(this->m_lookAtViewDirectionVector), fillerVector );

		//get the inverse of the translation
		//perform a dot product between the rows of the matrix and the look at position
		/*
		Math::Vector4 lookAtPositionInv = -( viewTransformMtx * lookAtPosition );
		lookAtPositionInv.SetFloatW( 1.0F );
		*/
		float xLookAtPositionInv = -( this->m_lookAtSideVector.Dot( this->m_lookAtPosition ) );
		float yLookatPositionInv = -( this->m_lookAtUpVector.Dot( this->m_lookAtPosition ) );
		float zLookAtPositionInv = this->m_lookAtViewDirectionVector.Dot( this->m_lookAtPosition );
		Math::Vector4 lookAtPositionInv( xLookAtPositionInv, yLookatPositionInv, zLookAtPositionInv, 1.0F );		

		//include the inverse transform in the view transformation matrix
		viewTransformMtx.SetColumn( 3, lookAtPositionInv );

		return viewTransformMtx;
	}

} //end namespace LookAt