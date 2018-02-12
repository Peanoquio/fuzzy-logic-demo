/******************************************************************************/
/*!
\file Shader.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1050
\par Project #02
\date 25/01/2012
\brief
This is the shader manager that manages the creation of shader programs in the application

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "Shader.h"
#include "../ErrorHandling/MessageBox.h"


namespace Shader
{
	/******************************************************************************/
	/*! 
	\brief 
	The constructor for the Shader class

	\param
	\return
	*/
	/******************************************************************************/
	Shader::Shader( void )
		: m_profile( ), 
		m_program( 0 )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	The destructor for the Shader class

	\param
	\return
	*/
	/******************************************************************************/
	Shader::~Shader( void )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Create the shader

	\param profileFlag
	the profile flag
	\param context
	the CG context
	\param shaderFileName
	the file name of the shader program
	\param shaderEntryPoint
	the main function name of the shader program
	\return
	*/
	/******************************************************************************/
	void Shader::Create( const CGGLenum profileFlag, const CGcontext context, const char * shaderFileName, const char * shaderEntryPoint )
	{
		// 4. get the best available profile for the current GPU
		// driver and cg GL library
		this->m_profile = cgGLGetLatestProfile( profileFlag );

		// 5. set the compiler optimization options for the specified profile
		cgGLSetOptimalOptions( this->m_profile );

		this->GetCgError();

		// 6. create vertex shader from file
		this->m_program = cgCreateProgramFromFile( 
			context, 
			CG_SOURCE, 
			shaderFileName, 
			this->m_profile, 
			shaderEntryPoint, 
			NULL
			);

		this->GetCgError();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Initializes the shader by loading the program into GPU and enable it for use

	\param
	\return
	*/
	/******************************************************************************/
	void Shader::Init( void ) const
	{
		// 8. load program into GPU and enable it for use
		cgGLLoadProgram( this->m_program );
		cgGLEnableProfile( this->m_profile );
		cgGLBindProgram( this->m_program );

		this->GetCgError();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Perform the cleanup of shader related stuff

	\param
	\return
	*/
	/******************************************************************************/
	void Shader::Shutdown( void ) const
	{
		// 2. cleanup shader related stuff
		cgGLUnbindProgram( this->m_profile );
		cgGLUnloadProgram( this->m_program );
		cgDestroyProgram( this->m_program );

		this->GetCgError();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Enables the profile

	\param
	\return
	*/
	/******************************************************************************/
	void Shader::EnableProfile( void ) const
	{
		cgGLEnableProfile( this->m_profile );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Disables the profile

	\param
	\return
	*/
	/******************************************************************************/
	void Shader::DisableProfile( void ) const
	{
		cgGLDisableProfile( this->m_profile );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Binds the program to the current state

	\param
	\return
	*/
	/******************************************************************************/
	void Shader::BindProgram( void ) const
	{
		cgGLBindProgram( this->m_program );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Unbinds the program bound in a profile

	\param
	\return
	*/
	/******************************************************************************/
	void Shader::UnbindProgram( void ) const
	{
		cgGLUnbindProgram( this->m_profile );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Update the uniform parameters in the shader

	\param
	\return
	*/
	/******************************************************************************/
	void Shader::UpdateProgramParams( void ) const
	{
		// 2. update the uniform parameters in the shader
		cgUpdateProgramParameters( this->m_program );

		this->GetCgError();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the handle to the uniform CG parameter

	\param paramName
	the parameter name in the CG program
	\return
	*/
	/******************************************************************************/
	CGparameter Shader::GetParam( const char * paramName ) const
	{
		// 7. get uniform handle
		return cgGetNamedParameter( this->m_program, paramName );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Set model-view-projection matrix

	\param matrix
	the values of the model-view-projection matrix
	\param param
	the handle to the CG parameter
	\return
	*/
	/******************************************************************************/
	void Shader::SetMatrixParam( const float * matrix, CGparameter param ) const
	{
		// 1. set model-view-projection matrix
		cgGLSetMatrixParameterfc( param, matrix );

		this->GetCgError();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Set texture sampler

	\param texId
	the texture Id
	\param param
	the handle to the CG parameter
	\return
	*/
	/******************************************************************************/
	void Shader::SetTexSamplerParam ( const GLuint texId, CGparameter param ) const
	{
		//set the texture sampler
		cgGLSetTextureParameter( param, texId );
		//enable the texture sampler
		cgGLEnableTextureParameter( param );

		this->GetCgError();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Set float 3 value

	\param x
	the float x value
	\param y
	the float y value
	\param z
	the float z value
	\param param
	the handle to the CG parameter
	\return
	*/
	/******************************************************************************/
	void Shader::SetFloat3Param ( const GLfloat x, const GLfloat y, const GLfloat z, CGparameter param ) const
	{
		//set the float 3
		cgGLSetParameter3f( param, x, y, z );

		this->GetCgError();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Set float value

	\param x
	the float x value
	the handle to the CG parameter
	\return
	*/
	/******************************************************************************/
	void Shader::SetFloatParam( const GLfloat x, CGparameter param ) const
	{
		//set the float
		cgGLSetParameter1f( param, x );

		this->GetCgError();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Set int value

	\param x
	the int x value
	the handle to the CG parameter
	\return
	*/
	/******************************************************************************/
	void Shader::SetIntParam( const GLint x, CGparameter param ) const
	{
		//set the int
		cgSetParameter1i( param, x );

		this->GetCgError();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the Cg error

	\param
	\return char *
	the error message
	*/
	/******************************************************************************/
	const char * Shader::GetCgError( void ) const
	{
		CGerror error;
		const char* errorString = cgGetLastErrorString( &error );		
		//errorString = cgGetErrorString( error );
		ASSERT ( error != NULL, errorString );

		return errorString;
	}

}//end namespace Shader