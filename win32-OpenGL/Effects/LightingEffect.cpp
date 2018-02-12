/******************************************************************************/
/*!
\file LightingEffect.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1050
\par Project #03
\date 18/02/2012
\brief
This is the lighting effect

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "LightingEffect.h"

namespace GraphicsFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Initialize the lighting effect

	\param cgContext
	the CG context
	\return
	*/
	/******************************************************************************/
	void LightingEffect::Init( const CGcontext cgContext )
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//create vertex shader
		Shader::Shader vtxShader;
		vtxShader.Create( CG_GL_VERTEX, cgContext, "Shaders/lightingShaderR.v.cg", "main" );
		vtxShader.Init();
		this->m_shaderMap.insert( std::make_pair( "vtxShader", vtxShader ) );

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//create fragment shader
		Shader::Shader fragShader;
		fragShader.Create( CG_GL_FRAGMENT, cgContext, "Shaders/lightingShader.f.cg", "main" );
		fragShader.Init();
		this->m_shaderMap.insert( std::make_pair( "fragShader", fragShader ) );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Initialize the lighting effect

	\param cgContext
	the CG context
	\param vtxComputationFlag
	if true, computation of the effect is done in the vertex shader, otherwise it's done in the fragment shader

	\return
	*/
	/******************************************************************************/
	void LightingEffect::Init( const CGcontext cgContext, const bool vtxComputationFlag )
	{
		if ( vtxComputationFlag == true )
		{
			this->Init( cgContext );
		}
		else if ( vtxComputationFlag == false )
		{
			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			//create vertex shader
			Shader::Shader vtxShader;
			vtxShader.Create( CG_GL_VERTEX, cgContext, "Shaders/lightingShader.v.cg", "main" );
			vtxShader.Init();
			this->m_shaderMap.insert( std::make_pair( "vtxShader", vtxShader ) );

			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			//create fragment shader
			Shader::Shader fragShader;
			fragShader.Create( CG_GL_FRAGMENT, cgContext, "Shaders/lightingShaderR.f.cg", "main" );
			fragShader.Init();
			this->m_shaderMap.insert( std::make_pair( "fragShader", fragShader ) );
		}
	}

} //end namespace GraphicsFramework

