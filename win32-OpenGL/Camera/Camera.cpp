/******************************************************************************/
/*!
\file Camera.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 12/12/2011
\brief
This is the camera that will be used to view the objects in the world from the camera view perspective

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


#include "Camera.h"


namespace Camera
{
	/******************************************************************************/
	/*! 
	\brief 
	The default constructor for the camera class

	\param
	\return
	*/
	/******************************************************************************/
	Camera::Camera (void)
		: m_cameraPosition(0.0F, 0.0F, 4.0F, 1.0F), 
		m_cameraTarget(0.0F, 0.0F, 0.0F, 1.0F), 
		m_upVector(0.0F, 1.0F, 0.0F, 0.0F),
		m_cameraViewDirectionVector(0.0F, 0.0F, -1.0F, 0.0F), 
		m_cameraUpVector(0.0F, 1.0F, 0.0F, 0.0F), 
		m_cameraSideVector(1.0F, 0.0F, 0.0F, 0.0F),
		m_xOrientation( 0.0F ),
		m_yOrientation( -90.0F )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	The constructor for the camera class that computes the camera view, side and up vectors

	\param cameraPosition
	the position of the camera
	\param target
	the target of the camera
	\param upVector
	the up vector of the world
	\return
	*/
	/******************************************************************************/
	Camera::Camera ( const Math::Vector4 & cameraPosition, const Math::Vector4 & target, const Math::Vector4 & upVector )
		: m_cameraPosition(cameraPosition), 
		m_cameraTarget(target), 
		m_upVector(upVector),
		m_cameraViewDirectionVector(target - cameraPosition), 
		m_cameraUpVector(0.0F, 1.0F, 0.0F, 0.0F), 
		m_cameraSideVector(1.0F, 0.0F, 0.0F, 0.0F)
	{
		this->m_cameraViewDirectionVector.Normalize();

		//compute for the camera side vector by performing a cross product between the world up vector and the view direction vector
		this->m_cameraSideVector = this->m_cameraViewDirectionVector.Cross( upVector );
		this->m_cameraSideVector.Normalize();

		//compute for the camera up vector by performing the cross product between the camera side and view direction vectors
		this->m_cameraUpVector = this->m_cameraSideVector.Cross ( this->m_cameraViewDirectionVector );
		this->m_cameraUpVector.Normalize();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	This recomputes the camera view direction vector based on the camera target and position

	\param
	\return
	*/
	/******************************************************************************/
	void Camera::RecomputeViewDirectionVector( void )
	{
		this->m_cameraViewDirectionVector = this->m_cameraTarget - this->m_cameraPosition;
		//this->m_cameraViewDirectionVector.Normalize();
	}

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Sets the position of the camera

	\param cameraPosition
	the position of the camera
	\return
	*/
	/******************************************************************************/
	void Camera::SetCameraPosition ( const Math::Vector4 & cameraPosition )
	{
		this->m_cameraPosition = cameraPosition;
		//this->RecomputeViewDirectionVector();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Sets the target of the camera

	\param target
	the target of the camera
	\return
	*/
	/******************************************************************************/
	void Camera::SetCameraTarget ( const Math::Vector4 & target )
	{
		this->m_cameraTarget = target;
		//this->RecomputeViewDirectionVector();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Sets the up vector of the world

	\param upVector
	the up vector of the world
	\return
	*/
	/******************************************************************************/
	void Camera::SetWorldUpVector ( const Math::Vector4 & upVector )
	{
		this->m_upVector = upVector;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Gets the position of the camera

	\param
	\return
	Vector4 - the position of the camera
	*/
	/******************************************************************************/
	const Math::Vector4 & Camera::GetCameraPosition ( void ) const
	{
		return this->m_cameraPosition;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Gets the target of the camera

	\param
	\return
	Vector4 - the target of the camera
	*/
	/******************************************************************************/
	const Math::Vector4 & Camera::GetCameraTarget ( void ) const
	{
		return this->m_cameraTarget;
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
	const Math::Vector4 & Camera::GetWorldUpVector ( void ) const
	{
		return this->m_upVector;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Sets the view vector of the camera

	\param cameraViewDirectionVector
	the view vector of the camera
	\return
	*/
	/******************************************************************************/
	void Camera::SetCameraViewDirectionVector ( const Math::Vector4 & cameraViewDirectionVector )
	{
		this->m_cameraViewDirectionVector = cameraViewDirectionVector;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Gets the view vector of the camera

	\param
	\return
	Vector4 - the view vector of the camera
	*/
	/******************************************************************************/
	const Math::Vector4 & Camera::GetCameraViewDirectionVector ( void ) const
	{
		return this->m_cameraViewDirectionVector;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Gets the up vector of the camera

	\param
	\return
	Vector4 - the up vector of the camera
	*/
	/******************************************************************************/
	const Math::Vector4 & Camera::GetCameraUpVector ( void ) const
	{
		return this->m_cameraUpVector;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Gets the up side of the camera

	\param
	\return
	Vector4 - the side vector of the camera
	*/
	/******************************************************************************/
	const Math::Vector4 & Camera::GetCameraSideVector ( void ) const
	{
		return this->m_cameraSideVector;
	}
	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Generates the camera view transformation matrix

	\param
	\return
	Mtx44 - the camera view transformation matrix
	*/
	/******************************************************************************/
	Math::Mtx44 Camera::GenerateViewTransformMtx ( void )
	{
		Math::Mtx44 viewTransformMtx;
		
		//compute the camera basis vectors
		Math::Vector4 fillerVector( 0.0F, 0.0F, 0.0F, 1.0F );

		//recompute the camera target based on the view direction and the camera position
		this->m_cameraTarget = this->m_cameraPosition + this->m_cameraViewDirectionVector;
		//this->RecomputeViewDirectionVector();
		this->m_cameraViewDirectionVector.Normalize();

		//recompute the "up" vector if the view vector is parallel to the world up vector
		if ( ( this->m_cameraViewDirectionVector.Cross( this->m_upVector ) ).IsZero() )
		{
			this->m_upVector.SetFloatX ( 1.0F );
			this->m_upVector.SetFloatY ( 0.0F );
			this->m_upVector.SetFloatZ ( 0.0F );
			this->m_upVector.SetFloatW ( 0.0F );

			if ( ( this->m_cameraViewDirectionVector.Cross( this->m_upVector ) ).IsZero() )
			{
				this->m_upVector.SetFloatX ( 0.0F );
				this->m_upVector.SetFloatY ( 0.0F );
				this->m_upVector.SetFloatZ ( 1.0F );
				this->m_upVector.SetFloatW ( 0.0F );
			}
		}		

		//compute for the camera side vector by performing a cross product between the world up vector and the view direction vector
		this->m_cameraSideVector = this->m_cameraViewDirectionVector.Cross( this->m_upVector );
		this->m_cameraSideVector.Normalize();

		//compute for the camera up vector by performing the cross product between the camera side and view direction vectors
		this->m_cameraUpVector = this->m_cameraSideVector.Cross ( this->m_cameraViewDirectionVector );
		this->m_cameraUpVector.Normalize();

		//set up the rotational values view transformation matrix based on the computed camera basis vectors
		//we negate the cameraViewDirectionVector to align with the world basis z vector
		//we also get the inverse of the model to view matrix (simply perform transpose transpose since rotational matrix is orthographic)		
		viewTransformMtx.SetToIdentity();
		viewTransformMtx.SetRows( this->m_cameraSideVector, this->m_cameraUpVector, -(this->m_cameraViewDirectionVector), fillerVector );

		//get the inverse of the translation
		//perform a dot product between the rows of the matrix and the camera position
		/*
		Math::Vector4 cameraPositionInv = -(viewTransformMtx * cameraPosition);
		cameraPositionInv.SetFloatW( 1.0F );
		*/
		float xCameraPositionInv = -(this->m_cameraSideVector.Dot( this->m_cameraPosition ));
		float yCameraPositionInv = -(this->m_cameraUpVector.Dot( this->m_cameraPosition ));
		float zCameraPositionInv = this->m_cameraViewDirectionVector.Dot( this->m_cameraPosition );
		Math::Vector4 cameraPositionInv( xCameraPositionInv, yCameraPositionInv, zCameraPositionInv, 1.0F );		

		//include the inverse transform in the view transformation matrix
		viewTransformMtx.SetColumn( 3, cameraPositionInv );

		return viewTransformMtx;
	}

} //end namespace Camera