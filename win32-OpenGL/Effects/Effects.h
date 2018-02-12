/******************************************************************************/
/*!
\file Effects.h
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


////////////////////////////////////////////////////////////////////////////////
#ifndef EFFECTS_H
#define EFFECTS_H
////////////////////////////////////////////////////////////////////////////////

#include <unordered_map>
#include "../Game/GameObj.h"
#include "../Shaders/Shader.h"


namespace GraphicsFramework
{
	typedef std::unordered_map< const char *, Shader::Shader > ShaderEffectMap;
	

	class Effects
	{
	public:
		virtual void Init( const CGcontext cgContext ) = 0;
		virtual void Init( const CGcontext cgContext, const bool vtxComputationFlag );
		void Release( void );
	
		const ShaderEffectMap & GetShaderMap( void ) const;

	protected:
		ShaderEffectMap					m_shaderMap;
	};

} //end namespace GraphicsFramework

#endif
////////////////////////////////////////////////////////////////////////////////