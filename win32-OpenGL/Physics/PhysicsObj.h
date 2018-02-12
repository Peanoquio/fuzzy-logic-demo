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

////////////////////////////////////////////////////////////////////////////////
#ifndef PHYSICSOBJ_H
#define PHYSICSOBJ_H
////////////////////////////////////////////////////////////////////////////////

#include "../Math/Vector4.h"


namespace PhysicsFramework
{

	class PhysicsObject
	{
	public:
		PhysicsObject( void );

		void ResetValues( void );

		void SetPosition( const Math::Vector4 & position );
		void SetPosition( const float x, const float y, const float z );
		void SetPositionX( const float x );
		void SetPositionY( const float y );
		void SetPositionZ( const float z );

		void SetVelocity( const Math::Vector4 & velocity );
		void SetVelocityX( const float x );
		void SetVelocityY( const float y );
		void SetVelocityZ( const float z );

		void SetScale( const Math::Vector4 & scale );

		void SetRotationX( const float x );
		void SetRotationY( const float y );
		void SetRotationZ( const float z );

		void SetDirection( const Math::Vector4 & direction );
		void SetDirection( const float x, const float y, const float z );
		void SetDirectionX( const float x );
		void SetDirectionY( const float y );
		void SetDirectionZ( const float z );

		void SetAngleDegreesX( const float angleDegreesX );	
		void SetAngleDegreesY( const float angleDegreesY );	
		void SetAngleDegreesZ( const float angleDegreesZ );	

		void SetMass( const float mass );				
		void SetMovementSpeed( const float movementSpeed );
		void SetRotationalSpeed( const float rotationalSpeed );
		void SetAcceleration( const float acceleration );

		const Math::Vector4 & GetPosition( void ) const;
		const Math::Vector4 & GetVelocity( void ) const;
		const Math::Vector4 & GetScale( void ) const;
		const Math::Vector4 & GetRotation( void ) const;
		const Math::Vector4 & GetDirection( void ) const;
		const float GetMass( void ) const;		
		const float GetAngleDegreesX( void ) const;		
		const float GetAngleDegreesY( void ) const;	
		const float GetAngleDegreesZ( void ) const;	
		const float GetMovementSpeed( void ) const;
		const float GetRotationalSpeed( void ) const;
		const float GetAcceleration( void ) const;		

		void SetNormal( const Math::Vector4 normal );
		void ComputeNormal( const Math::Vector4 ptHead, const Math::Vector4 ptTail );
		const Math::Vector4 & GetNormal( void ) const;
		const Math::Vector4 & GetHead( void ) const;
		const Math::Vector4 & GetTail( void ) const;

		void SetCenterPt( const Math::Vector4 centerPt );
		const Math::Vector4 & GetCenterPt( void ) const;

	private:
		Math::Vector4	m_position;
		Math::Vector4	m_velocity;
		Math::Vector4	m_scale;
		Math::Vector4	m_rotation;
		Math::Vector4	m_direction;		
		float			m_mass;		
		float			m_angleDegreesX;
		float			m_angleDegreesY;
		float			m_angleDegreesZ;
		float			m_movementSpeed;
		float			m_rotationalSpeed;
		float			m_acceleration;
		Math::Vector4	m_ptHead;
		Math::Vector4	m_ptTail;
		Math::Vector4	m_normal;
		Math::Vector4	m_ptCenter;
	};

} //end namespace PhysicsFramework

#endif
////////////////////////////////////////////////////////////////////////////////