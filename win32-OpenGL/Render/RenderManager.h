/******************************************************************************/
/*!
\file RenderManager.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1050
\par Project #03
\date 18/02/2012
\brief
This is the render manager responsible for rendering different effect

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


////////////////////////////////////////////////////////////////////////////////
#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H
////////////////////////////////////////////////////////////////////////////////

#include "../Game/GameObjectManager.h"
#include "../Effects/Effects.h"
#include "../Lighting/DirectionalLight.h"
#include "../Lighting/OmniLight.h"
#include "../Lighting/SpotLight.h"
#include "../Math/Mtx44.h"


namespace GraphicsFramework
{
	enum RENDER_EFFECT
	{
		NORMAL,
		LIGHT,
		LIGHT_FRAG,
		REFLECTIVE,
		REFLECTIVE_FRAG,
		REFRACTIVE,
		REFRACTIVE_FRAG,
		REFRACTIVE_CD,
		REFRACTIVE_CD_FRAG,
		FRESNEL,
		FRESNEL_FRAG,
		PROJECTED,
		DUAL_PARABOLOID_GENERATION,
		DUAL_PARABOLOID_REFLECTIVE
	};

	typedef std::vector< GameFramework::GameObject > GameObjVector;
	typedef std::unordered_map< RENDER_EFFECT, Effects * > EffectsMap;

	//forward declare
	class GraphicsInterface;


	class RenderManager
	{
	public:
		RenderManager( void );
		~RenderManager( void );

		void Init( GraphicsInterface * graphicsInterfacePtr, GameFramework::GameObjectManager * gameObjMgrPtr );
		void Shutdown( void );

		void InitEffect( const RENDER_EFFECT renderEffect, Effects * effectsPtr );
		void InitEffect( const RENDER_EFFECT renderEffect, Effects * effectsPtr, bool vtxEffectFlag );
		Effects * GetEffect( const RENDER_EFFECT renderEffect ) const;

		void GenerateCubeMap( const char * cubeMapTextureName, 
			const RENDER_EFFECT renderEffect, const Light::LIGHT_EFFECT lightEffect, 
			const char * projTexName,
			GameObjVector & currGameObjectVector );

		void GenerateCubeMap( const char * cubeMapTextureName, 
			const RENDER_EFFECT renderEffect, const Light::LIGHT_EFFECT lightEffect, 
			const char * projTexName,
			GameObjVector & currGameObjectVector, 
			const Math::Vector4 & sourcePosition );

		void GenerateDualParaboloidMap( const char * frontMapTextureName, const char * backMapTextureName,
			const RENDER_EFFECT renderEffect, const Light::LIGHT_EFFECT lightEffect, 
			const char * projTexName,
			GameObjVector & currGameObjectVector, 
			const Math::Vector4 & sourcePosition );

		void DrawObjects( float dt, const RENDER_EFFECT renderEffect, const Light::LIGHT_EFFECT lightEffect, 
			const char * projTexName,
			GameObjVector & currGameObjectVector, 
			const Math::Mtx44 & projMatrix, const Math::Mtx44 & viewMatrix );

		void DrawObjectsToDualParaboloid( float dt, const RENDER_EFFECT renderEffect, const Light::LIGHT_EFFECT lightEffect, 
			const char * projTexName,
			GameObjVector & currGameObjectVector, 
			const Math::Mtx44 & projMatrix, const Math::Mtx44 & viewMatrix, const int faceValue );

		void DrawObjects( float dt, const char * cubeMapTextureName, const RENDER_EFFECT sampleRenderEffect,
			const RENDER_EFFECT renderEffect, const Light::LIGHT_EFFECT lightEffect, 
			const char * projTexName,
			GameObjVector & currGameObjectVector, GameObjVector & sampleGameObjectVector,
			const Math::Mtx44 & projMatrix, const Math::Mtx44 & viewMatrix );

		void DrawObjects( float dt, const char * frontMapTextureName, const char * backMapTextureName, const RENDER_EFFECT sampleRenderEffect,
			const RENDER_EFFECT renderEffect, const Light::LIGHT_EFFECT lightEffect, 
			const char * projTexName,
			GameObjVector & currGameObjectVector, GameObjVector & sampleGameObjectVector,
			const Math::Mtx44 & projMatrix, const Math::Mtx44 & viewMatrix );

		Light::DirectionalLight & GetDirectionalLight( void );
		Light::OmniLight & GetOmniLight( void );
		Light::SpotLight & GetSpotLight( void );
		LookAt::LookAt & GetProjector( void );		

	private:
		CGcontext									m_cgContext;
		GraphicsInterface *							m_graphicsInterfacePtr;
		GameFramework::GameObjectManager *			m_gameObjMgrPtr;

		EffectsMap									m_effectsMap;

		LookAt::LookAt								m_projector;
		Light::DirectionalLight						m_directionalLight;
		Light::OmniLight							m_omniLight;
		Light::SpotLight							m_spotLight;


		void RenderObject( const Effects * effectsPtr, const RENDER_EFFECT renderEffect, const Light::LIGHT_EFFECT lightEffect,
			const char * projTexName,
			GameFramework::GameObject & gameObj, 
			const Math::Mtx44 & projMatrix, const Math::Mtx44 & viewMatrix );

		void RenderToDualParaboloid( const Effects * effectsPtr, const RENDER_EFFECT renderEffect, const Light::LIGHT_EFFECT lightEffect,
			const char * projTexName,
			GameFramework::GameObject & gameObj, 
			const Math::Mtx44 & projMatrix, const Math::Mtx44 & viewMatrix, 
			const int faceValue );

		const Math::Mtx44 GetObjectTransformation( GameFramework::GameObject & gameObj ) const;
		const Math::Mtx44 CreateTexGenMtx( const Math::Mtx44 & modelMtx, const Math::Mtx44 & viewMtx, const Math::Mtx44 & projMtx ) const;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		void InvokeDualParaboloidGenerationVertexShader( const Effects * effectsPtr, const char * vtxShaderName, 
			const char * vtxShaderParamName1, const float * modelViewMatrixVal,
			const char * vtxShaderParamName2, const float * modelViewITMatrixVal,
			const char * vtxShaderParamName3, const float * mvpMatrixVal, 
			const char * vtxShaderParamName4, const float * texGenMatrixVal,
			const char * vtxShaderParamName5, const float nearPlane,
			const char * vtxShaderParamName6, const float farPlane,
			const char * vtxShaderParamName7, const int faceValue ) const;

		void InvokeVertexShader( const Effects * effectsPtr, const char * vtxShaderName, 
			const char * vtxShaderParamName1, const float * mvpMatrixVal, 
			const char * vtxShaderParamName2, const float * texGenMatrixVal	) const;

		void InvokeLightVertexShader( const Effects * effectsPtr, const char * vtxShaderName, 
			const char * vtxShaderParamName1, const float * modelViewMatrixVal,
			const char * vtxShaderParamName2, const float * modelViewITMatrixVal,
			const char * vtxShaderParamName3, const float * mvpMatrixVal, 
			const char * vtxShaderParamName4, const float * texGenMatrixVal	) const;

		void InvokePerVtxLightVertexShader( const Effects * effectsPtr, const char * vtxShaderName, 
			const char * vtxShaderParamName1, const float * modelViewMatrixVal,
			const char * vtxShaderParamName2, const float * modelViewITMatrixVal,
			const char * vtxShaderParamName3, const float * mvpMatrixVal, 
			const char * vtxShaderParamName4, const float * texGenMatrixVal,
			const char * fragShaderParamName5, const Math::Vector4 globalAmbient, 
			const char * fragShaderParamName6, const Math::Vector4 lightColor, 
			const char * fragShaderParamName7, const Math::Vector4 lightDirection, 
			const char * fragShaderParamName8, const Math::Vector4 lightPosition, 
			const char * fragShaderParamName9, const Math::Vector4 eyePosition, 
			const char * fragShaderParamName10, const Math::Vector4 Ke, 
			const char * fragShaderParamName11, const Math::Vector4 Ka, 
			const char * fragShaderParamName12, const Math::Vector4 Kd, 
			const char * fragShaderParamName13, const Math::Vector4 Ks, 
			const char * fragShaderParamName14, const float shininess,
			const char * fragShaderParamName15, const float constantCoeff, 
			const char * fragShaderParamName16, const float linearCoeff, 
			const char * fragShaderParamName17, const float quadraticCoeff, 
			const char * fragShaderParamName18, const float spotLightInnerCone, 
			const char * fragShaderParamName19, const float spotLightOuterCone, 
			const char * fragShaderParamName20, const int lightType, 
			const char * fragShaderParamName21, const int lightAttenuationFlag ) const;

		void InvokeReflectiveVertexShader( const Effects * effectsPtr, const char * vtxShaderName, 
			const char * vtxShaderParamName1, const float * modelMatrixVal,
			const char * vtxShaderParamName2, const float * modelITMatrixVal,
			const char * vtxShaderParamName3, const float * modelViewMatrixVal,
			const char * vtxShaderParamName4, const float * modelViewITMatrixVal,
			const char * vtxShaderParamName5, const float * mvpMatrixVal, 
			const char * vtxShaderParamName6, const float * texGenMatrixVal, 
			const char * vtxShaderParamName7, const Math::Vector4 eyePosition ) const;

		void InvokeRefractiveVertexShader( const Effects * effectsPtr, const char * vtxShaderName, 
			const char * vtxShaderParamName1, const float * modelMatrixVal,
			const char * vtxShaderParamName2, const float * modelITMatrixVal,
			const char * vtxShaderParamName3, const float * modelViewMatrixVal,
			const char * vtxShaderParamName4, const float * modelViewITMatrixVal,
			const char * vtxShaderParamName5, const float * mvpMatrixVal, 
			const char * vtxShaderParamName6, const float * texGenMatrixVal, 
			const char * vtxShaderParamName7, const Math::Vector4 eyePosition,
			const char * vtxShaderParamName8, const float etaRatio ) const;

		void InvokeRefractiveChromDispVertexShader( const Effects * effectsPtr, const char * vtxShaderName, 
			const char * vtxShaderParamName1, const float * modelMatrixVal,
			const char * vtxShaderParamName2, const float * modelITMatrixVal,
			const char * vtxShaderParamName3, const float * modelViewMatrixVal,
			const char * vtxShaderParamName4, const float * modelViewITMatrixVal,
			const char * vtxShaderParamName5, const float * mvpMatrixVal, 
			const char * vtxShaderParamName6, const float * texGenMatrixVal, 
			const char * vtxShaderParamName7, const Math::Vector4 eyePosition,
			const char * vtxShaderParamName8, const Math::Vector4 etaRatio ) const;

		void InvokeFresnelVertexShader( const Effects * effectsPtr, const char * vtxShaderName, 
			const char * vtxShaderParamName1, const float * modelMatrixVal,
			const char * vtxShaderParamName2, const float * modelITMatrixVal,
			const char * vtxShaderParamName3, const float * modelViewMatrixVal,
			const char * vtxShaderParamName4, const float * modelViewITMatrixVal,
			const char * vtxShaderParamName5, const float * mvpMatrixVal, 
			const char * vtxShaderParamName6, const float * texGenMatrixVal, 
			const char * vtxShaderParamName7, const Math::Vector4 eyePosition,
			const char * vtxShaderParamName8, const Math::Vector4 etaRatio, 
			const char * vtxShaderParamName9, const float fresnelBias, 
			const char * vtxShaderParamName10, const float fresnelScale, 
			const char * vtxShaderParamName11, const float fresnelPower ) const;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		void InvokeFragmentShader( const Effects * effectsPtr, const char * fragShaderName, 
			const char * fragShaderParamName1, const unsigned textureId,
			const char * fragShaderParamName2, const unsigned projTextureId ) const;

		void InvokePerVtxLightFragmentShader( const Effects * effectsPtr, const char * fragShaderName, 
			const char * fragShaderParamName1, const char * fragShaderParamName2, const unsigned textureId,
			const char * fragShaderParamName3, const unsigned projTextureId );

		void InvokeLightFragmentShader( const Effects * effectsPtr, const char * fragShaderName, 
			const char * fragShaderParamName1, const char * fragShaderParamName2, const unsigned textureId,
			const char * fragShaderParamName3, const unsigned projTextureId,		
			const char * fragShaderParamName4, const Math::Vector4 globalAmbient, 
			const char * fragShaderParamName5, const Math::Vector4 lightColor, 
			const char * fragShaderParamName6, const Math::Vector4 lightDirection, 
			const char * fragShaderParamName7, const Math::Vector4 lightPosition, 
			const char * fragShaderParamName8, const Math::Vector4 eyePosition, 
			const char * fragShaderParamName9, const Math::Vector4 Ke, 
			const char * fragShaderParamName10, const Math::Vector4 Ka, 
			const char * fragShaderParamName11, const Math::Vector4 Kd, 
			const char * fragShaderParamName12, const Math::Vector4 Ks, 
			const char * fragShaderParamName13, const float shininess,
			const char * fragShaderParamName14, const float constantCoeff, 
			const char * fragShaderParamName15, const float linearCoeff, 
			const char * fragShaderParamName16, const float quadraticCoeff, 
			const char * fragShaderParamName17, const float spotLightInnerCone, 
			const char * fragShaderParamName18, const float spotLightOuterCone, 
			const char * fragShaderParamName19, const int lightType, 
			const char * fragShaderParamName20, const int lightAttenuationFlag ) const;

		void InvokeReflectiveFragmentShader( const Effects * effectsPtr, const char * fragShaderName, 
			const char * fragShaderParamName1, const char * fragShaderParamName2, const unsigned textureId,
			const char * fragShaderParamName3, const unsigned projTextureId,
			const char * fragShaderParamName4, const unsigned cubeMapTextureId,
			const char * fragShaderParamName5, const Math::Vector4 globalAmbient, 
			const char * fragShaderParamName6, const Math::Vector4 lightColor, 
			const char * fragShaderParamName7, const Math::Vector4 lightDirection, 
			const char * fragShaderParamName8, const Math::Vector4 lightPosition, 
			const char * fragShaderParamName9, const Math::Vector4 eyePosition, 
			const char * fragShaderParamName10, const Math::Vector4 Ke, 
			const char * fragShaderParamName11, const Math::Vector4 Ka, 
			const char * fragShaderParamName12, const Math::Vector4 Kd,
			const char * fragShaderParamName13, const Math::Vector4 Ks, 
			const char * fragShaderParamName14, const float shininess,
			const char * fragShaderParamName15, const float constantCoeff, 
			const char * fragShaderParamName16, const float linearCoeff, 
			const char * fragShaderParamName17, const float quadraticCoeff, 
			const char * fragShaderParamName18, const float spotLightInnerCone, 
			const char * fragShaderParamName19, const float spotLightOuterCone, 
			const char * fragShaderParamName20, const float reflectivity, 
			const char * fragShaderParamName21, const int lightType, 
			const char * fragShaderParamName22, const int lightAttenuationFlag ) const;

		void InvokeRefractiveFragmentShader( const Effects * effectsPtr, const char * fragShaderName, 
			const char * fragShaderParamName1, const char * fragShaderParamName2, const unsigned textureId,
			const char * fragShaderParamName3, const unsigned projTextureId,
			const char * fragShaderParamName4, const unsigned cubeMapTextureId,
			const char * fragShaderParamName5, const Math::Vector4 globalAmbient, 
			const char * fragShaderParamName6, const Math::Vector4 lightColor, 
			const char * fragShaderParamName7, const Math::Vector4 lightDirection, 
			const char * fragShaderParamName8, const Math::Vector4 lightPosition, 
			const char * fragShaderParamName9, const Math::Vector4 eyePosition, 
			const char * fragShaderParamName10, const Math::Vector4 Ke, 
			const char * fragShaderParamName11, const Math::Vector4 Ka, 
			const char * fragShaderParamName12, const Math::Vector4 Kd,
			const char * fragShaderParamName13, const Math::Vector4 Ks, 
			const char * fragShaderParamName14, const float shininess,
			const char * fragShaderParamName15, const float constantCoeff, 
			const char * fragShaderParamName16, const float linearCoeff, 
			const char * fragShaderParamName17, const float quadraticCoeff, 
			const char * fragShaderParamName18, const float spotLightInnerCone, 
			const char * fragShaderParamName19, const float spotLightOuterCone, 
			const char * fragShaderParamName20, const float transmittance,
			const char * fragShaderParamName21, const int lightType, 
			const char * fragShaderParamName22, const int lightAttenuationFlag ) const;

		void InvokeFresnelFragmentShader( const Effects * effectsPtr, const char * fragShaderName, 
			const char * fragShaderParamName1, const char * fragShaderParamName2, const unsigned textureId,
			const char * fragShaderParamName3, const unsigned projTextureId,
			const char * fragShaderParamName4, const unsigned cubeMapTextureId,
			const char * fragShaderParamName5, const Math::Vector4 globalAmbient, 
			const char * fragShaderParamName6, const Math::Vector4 lightColor, 
			const char * fragShaderParamName7, const Math::Vector4 lightDirection, 
			const char * fragShaderParamName8, const Math::Vector4 lightPosition, 
			const char * fragShaderParamName9, const Math::Vector4 eyePosition, 
			const char * fragShaderParamName10, const Math::Vector4 Ke, 
			const char * fragShaderParamName11, const Math::Vector4 Ka, 
			const char * fragShaderParamName12, const Math::Vector4 Kd,
			const char * fragShaderParamName13, const Math::Vector4 Ks, 
			const char * fragShaderParamName14, const float shininess,
			const char * fragShaderParamName15, const float constantCoeff, 
			const char * fragShaderParamName16, const float linearCoeff, 
			const char * fragShaderParamName17, const float quadraticCoeff, 
			const char * fragShaderParamName18, const float spotLightInnerCone, 
			const char * fragShaderParamName19, const float spotLightOuterCone, 			
			const char * fragShaderParamName20, const int lightType, 
			const char * fragShaderParamName21, const int lightAttenuationFlag ) const;

		void InvokeDualParaboloidReflectiveFragmentShader( const Effects * effectsPtr, const char * fragShaderName, 
			const char * fragShaderParamName1, const char * fragShaderParamName2, const unsigned textureId,
			const char * fragShaderParamName3, const unsigned projTextureId,
			const char * fragShaderParamName4, const unsigned frontMapTextureId,
			const char * fragShaderParamName5, const unsigned backMapTextureId,
			const char * fragShaderParamName6, const Math::Vector4 globalAmbient, 
			const char * fragShaderParamName7, const Math::Vector4 lightColor, 
			const char * fragShaderParamName8, const Math::Vector4 lightDirection, 
			const char * fragShaderParamName9, const Math::Vector4 lightPosition, 
			const char * fragShaderParamName10, const Math::Vector4 eyePosition, 
			const char * fragShaderParamName11, const Math::Vector4 Ke, 
			const char * fragShaderParamName12, const Math::Vector4 Ka, 
			const char * fragShaderParamName13, const Math::Vector4 Kd,
			const char * fragShaderParamName14, const Math::Vector4 Ks, 
			const char * fragShaderParamName15, const float shininess,
			const char * fragShaderParamName16, const float constantCoeff, 
			const char * fragShaderParamName17, const float linearCoeff, 
			const char * fragShaderParamName18, const float quadraticCoeff, 
			const char * fragShaderParamName19, const float spotLightInnerCone, 
			const char * fragShaderParamName20, const float spotLightOuterCone, 
			const char * fragShaderParamName21, const float reflectivity, 
			const char * fragShaderParamName22, const int lightType, 
			const char * fragShaderParamName23, const int lightAttenuationFlag ) const;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	};

} //end namespace GraphicsFramework

#endif
////////////////////////////////////////////////////////////////////////////////