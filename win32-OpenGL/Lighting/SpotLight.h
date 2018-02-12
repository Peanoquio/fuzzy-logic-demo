/******************************************************************************/
/*!
\file SpotLight.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1050
\par Project #03
\date 11/02/2012
\brief
This is the spot light

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H
////////////////////////////////////////////////////////////////////////////////

#include "Light.h"

namespace Light
{
	class SpotLight : public Light
	{
	public:
		SpotLight( void );

		void SetInnerConeAngleDegrees( const float innerConeAngle );
		void SetOuterConeAngleDegrees( const float outerConeAngle );

		const float GetInnerConeAngleDegrees( void ) const;
		const float GetOuterConeAngleDegrees( void ) const;

	private:
		float m_innerConeAngle;
		float m_outerConeAngle;
	};

}//end namespace Light

#endif
////////////////////////////////////////////////////////////////////////////////