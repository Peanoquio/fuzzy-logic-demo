/******************************************************************************/
/*!
\file Light.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1050
\par Project #03
\date 11/02/2012
\brief
This is the light class that will contain functions and members needed for lighting

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef LIGHT_H
#define LIGHT_H
////////////////////////////////////////////////////////////////////////////////

#include "../LookAt/LookAt.h"

namespace Light
{
	enum LIGHT_EFFECT
	{
		NONE,
		DIRECTIONAL,
		POINT,
		SPOT
	};

	enum ATTENUATION_FLAG
	{
		ATTENUATION_OFF,
		ATTENUATION_ON		
	};


	class Light : public LookAt::LookAt
	{
	public:
		Light( void );

		void SetLightColor( const Math::Vector4 lightColor );
		void SetGlobalAmbient( const Math::Vector4 globalAmbient );
		void SetAttenuationValues( const float constantCoeff, const float linearCoeff, const float quadraticCoeff );

		const Math::Vector4 & GetLightColor( void ) const;
		const Math::Vector4 & GetGlobalAmbient( void ) const;

		const float GetConstantCoeff( void ) const;
		const float GetLinearCoeff( void ) const;
		const float GetQuadraticCoeff( void ) const;

		void SetAttenuationFlag( const bool attenuationFlag );
		const bool GetAttenuationFlag( void ) const;

	private:
		Math::Vector4 m_lightColor;
		Math::Vector4 m_globalAmbient;
		
		//attenuation value
		float m_constantCoeff;
		float m_linearCoeff;
		float m_quadraticCoeff;

		bool m_enableAttenuation;
	};

}//end namespace Light

#endif
////////////////////////////////////////////////////////////////////////////////