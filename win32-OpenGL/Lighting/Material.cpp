/******************************************************************************/
/*!
\file Material.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1050
\par Project #03
\date 14/02/2012
\brief
This is the material class that will contain functions and members needed for lighting

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "Material.h"

namespace Light
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This is the constructor for the Material class
	\param
	\return
	*/
	/******************************************************************************/
	Material::Material( void )		
		: 
		//pearl material properties
		m_Ka( 0.25F, 0.20725F, 0.20725F, 1.0F ),		
		m_Ke( 0.0F, 0.0F, 0.0F, 0.0F ),
		m_Kd( 1.0F, 0.829F, 0.829F, 1.0F ),
		m_Ks( 0.296648F, 0.296648F, 0.296648F, 1.0F ),
		m_shininess( 11.264F ),
		//reflective properties
		m_reflectivity( 0.9F ),
		//refractive properties
		m_transmittance( 0.8F ),
		m_etaRatio( 1.333F ),
		//Fresnel properrties
		m_chromDispEtaRatio( 1.333F, 1.222F, 1.111F, 0.0F ),
		m_fresnelBias( 0.1F ),
		m_fresnelScale( 1.0F ),
		m_fresnelPower( 4.0F )
	{	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This sets the material properties
	\param Ka
	the ambient value
	\param Ke
	the emissive value
	\param Kd
	the diffuse value
	\param Ks
	the specular value
	\param shininess
	the shininess intensity
	\return
	*/
	/******************************************************************************/
	void Material::SetMaterialProperties( const Math::Vector4 Ka, const Math::Vector4 Ke, const Math::Vector4 Kd, const Math::Vector4 Ks, const float shininess )
	{
		this->m_Ka = Ka;
		this->m_Ke = Ke;
		this->m_Kd = Kd;
		this->m_Ks = Ks;
		this->m_shininess = shininess;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the ambient value
	\param

	\return Math::Vector4 &
	the ambient values
	*/
	/******************************************************************************/
	const Math::Vector4 & Material::GetAmbient( void ) const
	{
		return this->m_Ka;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the emissive value
	\param

	\return Math::Vector4 &
	the emissive values
	*/
	/******************************************************************************/
	const Math::Vector4 & Material::GetEmissive( void ) const
	{
		return this->m_Ke;
	}

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the diffuse value
	\param

	\return Math::Vector4 &
	the diffuse values
	*/
	/******************************************************************************/
	const Math::Vector4 & Material::GetDiffuse( void ) const
	{
		return this->m_Kd;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the specular value
	\param

	\return Math::Vector4 &
	the specular values
	*/
	/******************************************************************************/
	const Math::Vector4 & Material::GetSpecular( void ) const
	{
		return this->m_Ks;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the shininess value
	\param

	\return float
	the shininess value
	*/
	/******************************************************************************/
	const float Material::GetShininess( void ) const
	{
		return this->m_shininess;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This sets the reflectivity value
	\param reflectivity
	the reflectivity value

	\return
	*/
	/******************************************************************************/
	void Material::SetReflectiveProperties( const float reflectivity )
	{
		this->m_reflectivity = reflectivity;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the reflectivity value
	\param

	\return float
	the reflectivity value
	*/
	/******************************************************************************/
	const float Material::GetReflectivity( void ) const
	{
		return this->m_reflectivity;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This sets the refractivity value
	\param transmittance
	the transmittance value
	\param etaRatio
	the index of refraction

	\return
	*/
	/******************************************************************************/
	void Material::SetRefractiveProperties( const float transmittance, const float etaRatio )
	{
		this->m_transmittance = transmittance;
		this->m_etaRatio = etaRatio;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the transmittance value
	\param

	\return float
	the transmittance value
	*/
	/******************************************************************************/
	const float Material::GetTransmittance( void ) const
	{
		return this->m_transmittance;
	}

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the index of refraction value
	\param

	\return float
	the index of refraction value
	*/
	/******************************************************************************/
	const float Material::GetEtaRatio( void ) const
	{
		return this->m_etaRatio;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This sets the chromatic dispersion index of refraction for the red, blue, green colors of the light spectrum
	\param redLightEta
	the eta ratio for the red light
	\param greenLightEta
	the eta ratio for the green light
	\param blueLightEta
	the eta ratio for the blue light

	\return
	*/
	/******************************************************************************/
	void Material::SetChromaticDispersionEtaRatios( const float redLightEta, const float greenLightEta, const float blueLightEta )
	{
		this->m_chromDispEtaRatio.SetFloatX( redLightEta );
		this->m_chromDispEtaRatio.SetFloatY( greenLightEta );
		this->m_chromDispEtaRatio.SetFloatZ( blueLightEta );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the chromatic dispersion index of refraction for the red light
	\param

	\return float
	the chromatic dispersion index of refraction for the red light
	*/
	/******************************************************************************/
	const float Material::GetChromaticDispersionEtaRed( void ) const
	{
		return this->m_chromDispEtaRatio.GetFloatX();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the chromatic dispersion index of refraction for the green light
	\param

	\return float
	the chromatic dispersion index of refraction for the green light
	*/
	/******************************************************************************/
	const float Material::GetChromaticDispersionEtaGreen( void ) const
	{
		return this->m_chromDispEtaRatio.GetFloatY();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the chromatic dispersion index of refraction for the blue light
	\param

	\return float
	the chromatic dispersion index of refraction for the blue light
	*/
	/******************************************************************************/
	const float Material::GetChromaticDispersionEtaBlue( void ) const
	{
		return this->m_chromDispEtaRatio.GetFloatZ();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This sets the Fresnel properties
	\param fresnelBias
	the Fresnel bias
	\param fresnelScale
	the Fresnel scale
	\param fresnelPower
	the Fresnel power

	\return
	*/
	/******************************************************************************/
	void Material::SetFresnelProperties( const float fresnelBias, const float fresnelScale, const float fresnelPower )
	{
		this->m_fresnelBias = fresnelBias;
		this->m_fresnelScale = fresnelScale;
		this->m_fresnelPower = fresnelPower;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the Fresnel bias
	\param

	\return float
	the Fresnel bias
	*/
	/******************************************************************************/
	const float Material::GetFresnelBias( void ) const
	{
		return this->m_fresnelBias;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the Fresnel scale
	\param

	\return float
	the Fresnel scale
	*/
	/******************************************************************************/
	const float Material::GetFresnelScale( void ) const
	{
		return this->m_fresnelScale;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This gets the Fresnel power
	\param

	\return float
	the Fresnel power
	*/
	/******************************************************************************/
	const float Material::GetFresnelPower( void ) const
	{
		return this->m_fresnelPower;
	}

}//namespace Light