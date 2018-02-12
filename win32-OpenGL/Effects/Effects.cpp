/******************************************************************************/
/*!
\file Effects.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1050
\par Project #03
\date 18/02/2012
\brief
This is the effects interface

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


#include "Effects.h"

namespace GraphicsFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Initialize the effect

	\param cgContext
	the CG context
	\param vtxComputationFlag
	if true, computation of the effect is done in the vertex shader, otherwise it's done in the fragment shader

	\return
	*/
	/******************************************************************************/
	void Effects::Init( const CGcontext /*cgContext*/, const bool /*vtxComputationFlag*/ )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Releases the effect

	\param
	\return
	*/
	/******************************************************************************/
	void Effects::Release( void )
	{
		//2. release the Cg resources
		//get the iterators of the map
		ShaderEffectMap::iterator shaderMapItor = this->m_shaderMap.begin();
		ShaderEffectMap::iterator shaderMapEnd = this->m_shaderMap.end();

		//loop through the iterator
		while ( shaderMapItor != shaderMapEnd )
		{
			//release the Cg resources
			shaderMapItor->second.Shutdown();
			++shaderMapItor;
		}//end while loop

		this->m_shaderMap.clear();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Gets the shader map

	\param
	\return
	*/
	/******************************************************************************/
	const ShaderEffectMap & Effects::GetShaderMap( void ) const
	{
		return this->m_shaderMap;
	}


} //end namespace GraphicsFramework