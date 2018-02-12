/******************************************************************************/
/*!
\file GraphicsObj.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 16/12/2011
\brief
This is the graphics object that will contain graphics related properties

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef GRAPHICSOBJ_H
#define GRAPHICSOBJ_H
////////////////////////////////////////////////////////////////////////////////

#include <GL/glew.h>
#include "../Lighting/Material.h"


namespace GraphicsFramework
{
	enum TextureIdEnum {
		TEXTURE1,
		TEXTURE2,
		TEXTURE3,
		NUMBER_OF_TEXTURES
	};


	class GraphicsObject
	{
	public:
		GraphicsObject( void );
		
		const GLuint GetNameOfVAO( void ) const; 
		const GLuint GetNameOfVBO( void ) const; 
		const GLuint GetNameOfIBO( void ) const; 

		void SetNameOfVAO( const GLuint vaoName ); 
		void SetNameOfVBO( const GLuint vboName );
		void SetNameOfIBO( const GLuint iboName );
		
		void SetTextureId( const GLuint textureId, const GLuint index );
		const GLuint GetTextureId( const GLuint index ) const;
		const GLuint GetTextureIdArrSize( void ) const;

		void SetEnvTextureId( const GLuint envTextureId );
		const GLuint GetEnvTextureId( void ) const;

		void SetFrontFaceEnvTextureId( const GLuint envTextureId );
		const GLuint GetFrontFaceEnvTextureId( void ) const;

		void SetBackFaceEnvTextureId( const GLuint envTextureId );
		const GLuint GetBackFaceEnvTextureId( void ) const;

		Light::Material & GetMaterial( void );

	private:
		GLuint				m_VAO; // Vertex Array Object
		GLuint				m_VBO; // Vertex Buffer Object
		GLuint				m_IBO; // Index Buffer Object

		GLuint				m_textIdArrSize;
		GLuint				m_textureIdArr[ NUMBER_OF_TEXTURES ]; //an array of texture ids

		GLuint				m_envTextureId; //for environment mapping

		GLuint				m_frontFaceTextureId; //for dual parabolic environment mapping
		GLuint				m_backFaceTextureId; //for dual parabolic environment mapping

		Light::Material		m_material; //for lighting
	};

} //end namespace GraphicsFramework

#endif
////////////////////////////////////////////////////////////////////////////////