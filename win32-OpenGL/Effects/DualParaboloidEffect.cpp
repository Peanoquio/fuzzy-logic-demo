/******************************************************************************/
/*!
\file DualParaboloidEffect.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1050
\par Project #03
\date 22/02/2012
\brief
This is the dual paraboloid effect

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "DualParaboloidEffect.h"

namespace GraphicsFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Initialize the dual paraboloid effect

	\param cgContext
	the CG context
	\return
	*/
	/******************************************************************************/
	void DualParaboloidEffect::Init( const CGcontext cgContext )
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//create vertex shader
		Shader::Shader vtxShader;
		vtxShader.Create( CG_GL_VERTEX, cgContext, "Shaders/dualParaboloidGenerationShader.v.cg", "main" );
		vtxShader.Init();
		this->m_shaderMap.insert( std::make_pair( "vtxShader", vtxShader ) );

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//create fragment shader
		Shader::Shader fragShader;
		fragShader.Create( CG_GL_FRAGMENT, cgContext, "Shaders/dualParaboloidLightingShader.f.cg", "main" );
		fragShader.Init();
		this->m_shaderMap.insert( std::make_pair( "fragShader", fragShader ) );
	}	

} //end namespace GraphicsFramework