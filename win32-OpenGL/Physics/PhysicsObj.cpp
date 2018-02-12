/******************************************************************************/
/*!
\file PhysicsObj.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 16/12/2011
\brief
This is the physics object that will contain physics related properties

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "PhysicsObj.h"


namespace PhysicsFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The constructor for the PhysicsObject class
	\param
	\return
	*/
	/******************************************************************************/
	PhysicsObject::PhysicsObject( void )
		: m_position( 0.0F, 0.0F, 0.0F, 1.0F ),
		m_velocity( 0.0F, 0.0F, 0.0F, 0.0F ),
		m_scale( 1.0F, 1.0F, 1.0F, 0.0F ),
		m_direction( 0.0F, 0.0F, 0.0F, 0.0F ),
		m_mass( 0.0F ),
		m_angleDegreesX( 0.0F ),
		m_angleDegreesY( 0.0F ),
		m_angleDegreesZ( 0.0F ),
		m_movementSpeed( 0.0F ),
		m_rotationalSpeed( 0.0F ),
		m_acceleration( 0.0F )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Resets all the physics related values
	\param
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::ResetValues( void )
	{
		Math::Vector4 zeroVector;
		zeroVector.Zero();

		this->SetPosition( Math::Vector4( 0.0F, 0.0F, 0.0F, 1.0F ) );
		this->SetScale( Math::Vector4( 1.0F, 1.0F, 1.0F, 1.0F ) );
		this->SetVelocity( zeroVector );
		this->SetDirection( zeroVector );
		this->SetRotationX( 0.0F );
		this->SetRotationY( 0.0F );
		this->SetRotationZ( 0.0F );

		m_mass = 0.0F;		
		m_angleDegreesX = 0.0F;
		m_angleDegreesY = 0.0F;
		m_angleDegreesZ = 0.0F;
		m_movementSpeed = 0.0F;
		m_rotationalSpeed = 0.0F;
		m_acceleration = 0.0F;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the position of the object
	\param Vector4
	the position of the object
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetPosition( const Math::Vector4 & position )
	{
		this->m_position = position;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the position of the object
	\param x
	the x position
	\param y
	the y position
	\param z
	the z position
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetPosition( const float x, const float y, const float z )
	{
		this->m_position.SetFloatX( x );
		this->m_position.SetFloatY( y );
		this->m_position.SetFloatZ( z );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the x position of the object
	\param x
	the x position
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetPositionX( const float x )
	{
		this->m_position.SetFloatX( x );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the y position of the object
	\param y
	the y position
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetPositionY( const float y )
	{
		this->m_position.SetFloatY( y );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the z position of the object
	\param z
	the z position
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetPositionZ( const float z )
	{
		this->m_position.SetFloatZ( z );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the velocity of the object
	\param Vector4
	the velocity of the object
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetVelocity( const Math::Vector4 & velocity )
	{
		this->m_velocity = velocity;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the x position of the object
	\param x
	the x position
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetVelocityX( const float x )
	{
		this->m_velocity.SetFloatX( x );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the y position of the object
	\param y
	the y position
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetVelocityY( const float y )
	{
		this->m_velocity.SetFloatY( y );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the z position of the object
	\param z
	the z position
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetVelocityZ( const float z )
	{
		this->m_velocity.SetFloatZ( z );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the mass of the object
	\param float
	the mass of the object
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetMass( const float mass )
	{
		this->m_mass = mass;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets scale mass of the object
	\param float
	the scale of the object
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetScale( const Math::Vector4 & scale )
	{
		this->m_scale = scale;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the object rotation along the x-axis
	\param x
	the rotation in degrees
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetRotationX( const float x )
	{
		this->m_rotation.SetFloatX( x );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the object rotation along the y-axis
	\param y
	the rotation in degrees
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetRotationY( const float y )
	{
		this->m_rotation.SetFloatY( y );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the object rotation along the z-axis
	\param z
	the rotation in degrees
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetRotationZ( const float z )
	{
		this->m_rotation.SetFloatZ( z );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the angle in degrees along the x-axis
	\param float
	the angle in degrees along the x-axis
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetAngleDegreesX( const float angleDegreesX )
	{
		this->m_angleDegreesX = angleDegreesX;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the angle in degrees along the y-axis
	\param float
	the angle in degrees along the y-axis
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetAngleDegreesY( const float angleDegreesY )
	{
		this->m_angleDegreesY = angleDegreesY;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the angle in degrees along the z-axis
	\param float
	the angle in degrees along the z-axis
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetAngleDegreesZ( const float angleDegreesZ )
	{
		this->m_angleDegreesZ = angleDegreesZ;
	}
	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the direction of the object
	\param float
	the direction of the object
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetDirection( const Math::Vector4 & direction )
	{
		this->m_direction = direction;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the direction of the object
	\param x
	the x direction
	\param y
	the y direction
	\param z
	the z direction
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetDirection( const float x, const float y, const float z )
	{
		this->m_direction.SetFloatX( x );
		this->m_direction.SetFloatY( y );
		this->m_direction.SetFloatZ( z );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the x direction of the object
	\param x
	the x direction
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetDirectionX( const float x )
	{
		this->m_direction.SetFloatX( x );
	}

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the y direction of the object
	\param y
	the y direction
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetDirectionY( const float y )
	{
		this->m_direction.SetFloatY( y );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the z direction of the object
	\param z
	the z direction
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetDirectionZ( const float z )
	{
		this->m_direction.SetFloatZ( z );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the movement speed of the object
	\param float
	the movement speed of the object
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetMovementSpeed( const float movementSpeed )
	{
		this->m_movementSpeed = movementSpeed;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the rotational speed of the object
	\param float
	the rotational speed of the object
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetRotationalSpeed( const float rotationalSpeed )
	{
		this->m_rotationalSpeed = rotationalSpeed;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the acceleration of the object
	\param float
	the acceleration of the object
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetAcceleration( const float acceleration )
	{
		this->m_acceleration = acceleration;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the position of the object
	\param
	\return Vector4
	the position of the object
	*/
	/******************************************************************************/
	const Math::Vector4 & PhysicsObject::GetPosition( void ) const
	{
		return this->m_position;
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the velocity of the object
	\param
	\return Vector4
	the velocity of the object
	*/
	/******************************************************************************/
	const Math::Vector4 & PhysicsObject::GetVelocity( void ) const
	{
		return this->m_velocity;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the mass of the object
	\param
	\return float
	the mass of the object
	*/
	/******************************************************************************/
	const float PhysicsObject::GetMass( void ) const
	{
		return this->m_mass;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the scale of the object
	\param
	\return float
	the scale of the object
	*/
	/******************************************************************************/
	const Math::Vector4 & PhysicsObject::GetScale( void ) const
	{
		return this->m_scale;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the rotation of the object
	\param
	\return float
	the rotation of the object
	*/
	/******************************************************************************/
	const Math::Vector4 & PhysicsObject::GetRotation( void ) const
	{
		return this->m_rotation;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the angle in degrees along the x-axis
	\param
	\return float
	the angle in degrees along the x-axis
	*/
	/******************************************************************************/
	const float PhysicsObject::GetAngleDegreesX( void ) const
	{
		return this->m_angleDegreesX;
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the angle in degrees along the y-axis
	\param
	\return float
	the angle in degrees along the y-axis
	*/
	/******************************************************************************/
	const float PhysicsObject::GetAngleDegreesY( void ) const
	{
		return this->m_angleDegreesY;
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the angle in degrees along the z-axis
	\param
	\return float
	the angle in degrees along the z-axis
	*/
	/******************************************************************************/
	const float PhysicsObject::GetAngleDegreesZ( void ) const
	{
		return this->m_angleDegreesZ;
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the direction of the object
	\param
	\return float
	the direction of the object
	*/
	/******************************************************************************/
	const Math::Vector4 & PhysicsObject::GetDirection( void ) const
	{
		return this->m_direction;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the movement speed of the object
	\param
	\return float
	the movement speed of the object
	*/
	/******************************************************************************/
	const float PhysicsObject::GetMovementSpeed( void ) const
	{
		return this->m_movementSpeed;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the rotational speed of the object
	\param
	\return float
	the rotational speed of the object
	*/
	/******************************************************************************/
	const float PhysicsObject::GetRotationalSpeed( void ) const
	{
		return this->m_rotationalSpeed;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the acceleration of the object
	\param
	\return float
	the acceleration of the object
	*/
	/******************************************************************************/
	const float PhysicsObject::GetAcceleration( void ) const
	{
		return this->m_acceleration;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Set the normal of the object
	\param
	\return normal
	the normal vector
	*/
	/******************************************************************************/
	void PhysicsObject::SetNormal( const Math::Vector4 normal )
	{
		this->m_normal = normal;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Compute for the normal of the object
	\param ptHead
	the end point of the vector
	\param ptTail
	the start point of the vector
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::ComputeNormal( const Math::Vector4 ptHead, const Math::Vector4 ptTail )
	{
		this->m_ptHead = ptHead;
		this->m_ptTail = ptTail;

		//compute for the normal
		Math::Vector4 myVec = ptHead - ptTail;
		Math::Vector4 normalVec( myVec.GetFloatY(), -myVec.GetFloatX(), myVec.GetFloatZ(), 0.0F );
		normalVec.Normalize();
		this->m_normal = normalVec;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the normal of the object
	\param
	\return Vector4 &
	the normal of the object
	*/
	/******************************************************************************/
	const Math::Vector4 & PhysicsObject::GetNormal( void ) const
	{
		return this->m_normal;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the vector end point of the object
	\param
	\return Vector4 &
	the vector end point of the object
	*/
	/******************************************************************************/
	const Math::Vector4 & PhysicsObject::GetHead( void ) const
	{
		return this->m_ptHead;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the vector start point of the object
	\param
	\return Vector4 &
	the vector start point of the object
	*/
	/******************************************************************************/
	const Math::Vector4 & PhysicsObject::GetTail( void ) const
	{
		return this->m_ptTail;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Set the center point of the object
	\param centerPt
	the center point of the object
	\return
	*/
	/******************************************************************************/
	void PhysicsObject::SetCenterPt( const Math::Vector4 centerPt )
	{
		this->m_ptCenter = centerPt;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the center point of the object
	\param 
	\return Vector4
	the center point of the object
	*/
	/******************************************************************************/
	const Math::Vector4 & PhysicsObject::GetCenterPt( void ) const
	{
		return this->m_ptCenter;
	}


} //end namespace PhysicsFramework