/******************************************************************************/
/*!
\file Light.cpp
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

#include "Light.h"

namespace Light
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This is the constructor for the Light class
	\param
	\return
	*/
	/******************************************************************************/
	Light::Light( void )
		: m_lightColor( 1.0F, 1.0F, 1.0F, 1.0F ),
		m_globalAmbient( 0.75F, 0.75F, 0.75F, 1.0F ),
		//attenuation values
		m_constantCoeff( 1.0F ),
		m_linearCoeff( 0.022F ),
		m_quadraticCoeff( 0.0019F ),
		m_enableAttenuation( true )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This sets the color of the light
	\param lightColor
	the color of the light
	\return
	*/
	/******************************************************************************/
	void Light::SetLightColor( const Math::Vector4 lightColor )
	{
		this->m_lightColor = lightColor;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This sets the global ambient
	\param globalAmbient
	the global ambient intensity
	
	\return
	*/
	/******************************************************************************/
	void Light::SetGlobalAmbient( const Math::Vector4 globalAmbient )
	{
		this->m_globalAmbient = globalAmbient;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This sets the attenuation values
	\param constantCoeff
	the constant coefficient
	\param linearCoeff
	the linear coefficient
	\param quadraticCoeff
	the quadratic coefficient

	\return
	*/
	/******************************************************************************/
	void Light::SetAttenuationValues( const float constantCoeff, const float linearCoeff, const float quadraticCoeff )
	{
		this->m_constantCoeff = constantCoeff;
		this->m_linearCoeff = linearCoeff;
		this->m_quadraticCoeff = quadraticCoeff;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the light color
	\param

	\return Math::Vector4 &
	the light color values
	*/
	/******************************************************************************/
	const Math::Vector4 & Light::GetLightColor( void ) const
	{
		return this->m_lightColor;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the global ambient
	\param

	\return Math::Vector4 &
	the global ambient values
	*/
	/******************************************************************************/
	const Math::Vector4 & Light::GetGlobalAmbient( void ) const
	{
		return this->m_globalAmbient;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the constant coefficient attenuation value
	\param

	\return float
	the constant coefficient attenuation value
	*/
	/******************************************************************************/
	const float Light::GetConstantCoeff( void ) const
	{
		return this->m_constantCoeff;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the linear coefficient attenuation value
	\param

	\return float
	the constant linear attenuation value
	*/
	/******************************************************************************/
	const float Light::GetLinearCoeff( void ) const
	{
		return this->m_linearCoeff;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the quadratic coefficient attenuation value
	\param

	\return float
	the constant quadratic attenuation value
	*/
	/******************************************************************************/
	const float Light::GetQuadraticCoeff( void ) const
	{
		return this->m_quadraticCoeff;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This sets the the attenuation flag
	\param attenuationFlag
	the attenuation flag to indicate whether to turn on attenuation

	\return
	*/
	/******************************************************************************/
	void Light::SetAttenuationFlag( const bool attenuationFlag )
	{
		this->m_enableAttenuation = attenuationFlag;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the the attenuation flag
	\param 	

	\return bool
	the attenuation flag: if true, turn on attenuation else if false, turn it off
	*/
	/******************************************************************************/
	const bool Light::GetAttenuationFlag( void ) const
	{
		return this->m_enableAttenuation;
	}


}//end namespace Light