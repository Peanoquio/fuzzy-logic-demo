/******************************************************************************/
/*!
\file Material.h
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

////////////////////////////////////////////////////////////////////////////////
#ifndef MATERIAL_H
#define MATERIAL_H
////////////////////////////////////////////////////////////////////////////////

#include "../Math/Vector4.h"


namespace Light
{
	class Material
	{
	public:
		Material( void );

		void SetMaterialProperties( const Math::Vector4 Ka, const Math::Vector4 Ke, const Math::Vector4 Kd, const Math::Vector4 Ks, const float shininess );

		const Math::Vector4 & GetAmbient( void ) const;
		const Math::Vector4 & GetEmissive( void ) const;
		const Math::Vector4 & GetDiffuse( void ) const;
		const Math::Vector4 & GetSpecular( void ) const;
		const float GetShininess( void ) const;

		void SetReflectiveProperties( const float reflectivity );
		const float GetReflectivity( void ) const;

		void SetRefractiveProperties( const float transmittance, const float etaRatio );
		const float GetTransmittance( void ) const;
		const float GetEtaRatio( void ) const;

		void SetChromaticDispersionEtaRatios( const float redLightEta, const float greenLightEta, const float blueLightEta );
		const float GetChromaticDispersionEtaRed( void ) const;
		const float GetChromaticDispersionEtaGreen( void ) const;
		const float GetChromaticDispersionEtaBlue( void ) const;

		void SetFresnelProperties( const float fresnelBias, const float fresnelScale, const float fresnelPower );
		const float GetFresnelBias( void ) const;
		const float GetFresnelScale( void ) const;
		const float GetFresnelPower( void ) const;

	private:
		//material properties
		Math::Vector4 m_Ka; //ambient
		Math::Vector4 m_Ke; //emissive
		Math::Vector4 m_Kd; //diffuse
		Math::Vector4 m_Ks; //specular
		float m_shininess;

		//reflective properties
		float m_reflectivity;

		//refractive properties
		float m_transmittance;
		float m_etaRatio;

		//Fresnel properties
		Math::Vector4 m_chromDispEtaRatio;
		float m_fresnelBias;
		float m_fresnelScale;
		float m_fresnelPower;
	};

}//end namespace Light

#endif
////////////////////////////////////////////////////////////////////////////////