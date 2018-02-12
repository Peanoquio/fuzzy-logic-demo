/******************************************************************************/
/*!
\file LookAt.h
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

////////////////////////////////////////////////////////////////////////////////
#ifndef LOOK_AT_H
#define LOOK_AT_H
////////////////////////////////////////////////////////////////////////////////

#include "../Math/Mtx44.h"

namespace LookAt
{
	class LookAt
	{
	public:
		LookAt (void);		
		LookAt ( const Math::Vector4 & lookAtPosition, const Math::Vector4 & lookAtTarget, const Math::Vector4 & worldUpVector );

		Math::Mtx44 GenerateViewTransformMtx ( void );

		void SetLookAtPosition ( const Math::Vector4 & lookAtPosition );
		void SetLookAtTarget ( const Math::Vector4 & lookAtTarget );
		void SetWorldUpVector ( const Math::Vector4 & worldUpVector );

		const Math::Vector4 & GetLookAtPosition ( void ) const;
		const Math::Vector4 & GetLookAtTarget ( void ) const;
		const Math::Vector4 & GetWorldUpVector ( void ) const;

		void SetLookAtViewDirectionVector ( const Math::Vector4 & lookAtViewDirectionVector );
		const Math::Vector4 & GetLookAtViewDirectionVector ( void ) const;
		const Math::Vector4 & GetLookAtUpVector ( void ) const;
		const Math::Vector4 & GetLookAtSideVector ( void ) const;

		float m_xOrientation;
		float m_yOrientation;

	private:
		Math::Vector4 m_lookAtPosition;
		Math::Vector4 m_lookAtTarget;
		Math::Vector4 m_worldUpVector;

		Math::Vector4 m_lookAtViewDirectionVector;
		Math::Vector4 m_lookAtUpVector;
		Math::Vector4 m_lookAtSideVector;	
	};

} //end namespace LookAt

#endif
////////////////////////////////////////////////////////////////////////////////