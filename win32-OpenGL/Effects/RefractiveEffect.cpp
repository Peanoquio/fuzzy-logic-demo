/******************************************************************************/
/*!
\file RefractiveEffect.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1050
\par Project #03
\date 18/02/2012
\brief
This is the refractive effect

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "RefractiveEffect.h"

namespace GraphicsFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Initialize the refractive effect

	\param cgContext
	the CG context
	\return
	*/
	/******************************************************************************/
	void RefractiveEffect::Init( const CGcontext cgContext )
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//create vertex shader
		Shader::Shader vtxShader;
		vtxShader.Create( CG_GL_VERTEX, cgContext, "Shaders/refractiveShaderR.v.cg", "main" );
		vtxShader.Init();
		this->m_shaderMap.insert( std::make_pair( "vtxShader", vtxShader ) );

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//create fragment shader
		Shader::Shader fragShader;
		fragShader.Create( CG_GL_FRAGMENT, cgContext, "Shaders/refractiveShader.f.cg", "main" );
		fragShader.Init();
		this->m_shaderMap.insert( std::make_pair( "fragShader", fragShader ) );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Initialize the refractive effect

	\param cgContext
	the CG context
	\param vtxComputationFlag
	if true, computation of the effect is done in the vertex shader, otherwise it's done in the fragment shader

	\return
	*/
	/******************************************************************************/
	void RefractiveEffect::Init( const CGcontext cgContext, const bool vtxComputationFlag )
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
			vtxShader.Create( CG_GL_VERTEX, cgContext, "Shaders/refractiveShader.v.cg", "main" );
			vtxShader.Init();
			this->m_shaderMap.insert( std::make_pair( "vtxShader", vtxShader ) );

			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			//create fragment shader
			Shader::Shader fragShader;
			fragShader.Create( CG_GL_FRAGMENT, cgContext, "Shaders/refractiveShaderR.f.cg", "main" );
			fragShader.Init();
			this->m_shaderMap.insert( std::make_pair( "fragShader", fragShader ) );
		}
	}

} //end namespace GraphicsFramework

