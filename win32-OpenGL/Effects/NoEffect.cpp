/******************************************************************************/
/*!
\file NoEffect.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1050
\par Project #03
\date 19/02/2012
\brief
This has no effect

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "NoEffect.h"

namespace GraphicsFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Initialize the no effect

	\param cgContext
	the CG context
	\return
	*/
	/******************************************************************************/
	void NoEffect::Init( const CGcontext cgContext )
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//create vertex shader
		Shader::Shader vtxShader;
		vtxShader.Create( CG_GL_VERTEX, cgContext, "Shaders/shader.v.cg", "main" );
		vtxShader.Init();
		this->m_shaderMap.insert( std::make_pair( "vtxShader", vtxShader ) );

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//create fragment shader
		Shader::Shader fragShader;
		fragShader.Create( CG_GL_FRAGMENT, cgContext, "Shaders/shader.f.cg", "main" );
		fragShader.Init();
		this->m_shaderMap.insert( std::make_pair( "fragShader", fragShader ) );
	}


} //end namespace GraphicsFramework

