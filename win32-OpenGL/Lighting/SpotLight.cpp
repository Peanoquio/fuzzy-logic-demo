/******************************************************************************/
/*!
\file SpotLight.cpp
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

#include "SpotLight.h"

namespace Light
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This is the constructor for the SpotLight class
	\param
	\return
	*/
	/******************************************************************************/
	SpotLight::SpotLight( void )
		: m_innerConeAngle( 0.0F ),
		m_outerConeAngle( 0.0F )
	{	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This sets the inner cone angle in degrees
	\param
	\return
	*/
	/******************************************************************************/
	void SpotLight::SetInnerConeAngleDegrees( const float innerConeAngle )
	{
		this->m_innerConeAngle = innerConeAngle;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This sets the outer cone angle in degrees
	\param
	\return
	*/
	/******************************************************************************/
	void SpotLight::SetOuterConeAngleDegrees( const float outerConeAngle )
	{
		this->m_outerConeAngle = outerConeAngle;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the inner cone angle in degrees
	\param
	\return
	*/
	/******************************************************************************/
	const float SpotLight::GetInnerConeAngleDegrees( void ) const
	{
		return this->m_innerConeAngle;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the outer cone angle in degrees
	\param
	\return
	*/
	/******************************************************************************/
	const float SpotLight::GetOuterConeAngleDegrees( void ) const
	{
		return this->m_outerConeAngle;
	}

}//end namespace Light