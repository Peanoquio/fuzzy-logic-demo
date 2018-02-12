/******************************************************************************/
/*!
\file Shader.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 25/01/2012
\brief
This is the shader manager that manages the creation of shader programs in the application

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


////////////////////////////////////////////////////////////////////////////////
#ifndef SHADER_H
#define SHADER_H
////////////////////////////////////////////////////////////////////////////////

#include <Cg/cg.h>
#include <Cg/cgGL.h>
#include <hash_map>

namespace Shader
{
	typedef std::hash_map< const std::string, CGparameter > CGparameterMap;
	typedef std::vector< CGprogram > CGprogramVector;
	typedef std::vector< CGprofile > CGprofileVector;

	class Shader
	{
	public:
		Shader( void );
		~Shader( void );

		void Create( const CGGLenum profileFlag, const CGcontext context, const char * shaderFileName, const char * shaderEntryPoint );
		void Init( void ) const;
		void Shutdown( void ) const;
		void UpdateProgramParams( void ) const;
		void EnableProfile( void ) const;
		void DisableProfile( void ) const;
		void BindProgram( void ) const;
		void UnbindProgram( void ) const;

		CGparameter GetParam( const char * paramName ) const;
		void SetMatrixParam ( const float * matrix, CGparameter param ) const;
		void SetTexSamplerParam ( const GLuint texId, CGparameter param ) const;
		void SetFloat3Param ( const GLfloat x, const GLfloat y, const GLfloat z, CGparameter param ) const;
		void SetFloatParam( const GLfloat x, CGparameter param ) const;
		void SetIntParam( const GLint x, CGparameter param ) const; 

	private:
		CGprofile		m_profile;
		CGprogram		m_program;

		const char * GetCgError( void ) const;
	};

}//end namespace Shader

#endif
////////////////////////////////////////////////////////////////////////////////