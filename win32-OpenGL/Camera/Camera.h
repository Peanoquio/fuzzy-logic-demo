/******************************************************************************/
/*!
\file Camera.h
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

////////////////////////////////////////////////////////////////////////////////
#ifndef MYCAMERA_H
#define MYCAMERA_H
////////////////////////////////////////////////////////////////////////////////

#include "../Math/Mtx44.h"

namespace Camera
{
	class Camera
	{
	public:
		Camera (void);		
		Camera ( const Math::Vector4 & cameraPosition, const Math::Vector4 & target, const Math::Vector4 & upVector );

		Math::Mtx44 GenerateViewTransformMtx ( void );
		void RecomputeViewDirectionVector( void );

		void SetCameraPosition ( const Math::Vector4 & cameraPosition );
		void SetCameraTarget ( const Math::Vector4 & target );
		void SetWorldUpVector ( const Math::Vector4 & upVector );

		const Math::Vector4 & GetCameraPosition ( void ) const;
		const Math::Vector4 & GetCameraTarget ( void ) const;
		const Math::Vector4 & GetWorldUpVector ( void ) const;

		void SetCameraViewDirectionVector ( const Math::Vector4 & cameraViewDirectionVector );
		const Math::Vector4 & GetCameraViewDirectionVector ( void ) const;
		const Math::Vector4 & GetCameraUpVector ( void ) const;
		const Math::Vector4 & GetCameraSideVector ( void ) const;

		float m_xOrientation;
		float m_yOrientation;

	private:
		Math::Vector4 m_cameraPosition;
		Math::Vector4 m_cameraTarget;
		Math::Vector4 m_upVector;

		Math::Vector4 m_cameraViewDirectionVector;
		Math::Vector4 m_cameraUpVector;
		Math::Vector4 m_cameraSideVector;	
	};

} //end namespace Camera

#endif
////////////////////////////////////////////////////////////////////////////////