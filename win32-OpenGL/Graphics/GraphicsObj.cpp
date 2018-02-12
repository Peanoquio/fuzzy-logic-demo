/******************************************************************************/
/*!
\file GraphicsObject.cpp
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

#include "GraphicsObj.h"


namespace GraphicsFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The constructor for the GraphicsObject class
	\param
	\return
	*/
	/******************************************************************************/
	GraphicsObject::GraphicsObject( void )
		: m_VAO( 0 ),
		m_VBO( 0 ),
		m_IBO( 0 ),
		m_textIdArrSize( NUMBER_OF_TEXTURES ),
		m_envTextureId( 0 ),
		m_material()
	{
		//set the array element values to zero
		for ( unsigned index = 0; index < this->m_textIdArrSize; ++index )
		{
			this->m_textureIdArr[index] = 0;
		}//end for loop
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the name of the VAO (vertex array object)
	\param
	\return GLuint
	the name of the VAO (vertex array object)
	*/
	/******************************************************************************/
	const GLuint GraphicsObject::GetNameOfVAO( void ) const
	{
		return this->m_VAO;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the name of the VBO (vertex buffer object)
	\param
	\return GLuint
	the name of the VBO (vertex buffer object)
	*/
	/******************************************************************************/
	const GLuint GraphicsObject::GetNameOfVBO( void ) const
	{
		return this->m_VBO;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the name of the IBO (index buffer object)
	\param
	\return GLuint
	the name of the IBO (index buffer object)
	*/
	/******************************************************************************/
	const GLuint GraphicsObject::GetNameOfIBO( void ) const
	{
		return this->m_IBO;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the name of the VAO (vertex array object)
	\param GLuint
	the name of the VAO (vertex array object)
	\return
	*/
	/******************************************************************************/
	void GraphicsObject::SetNameOfVAO( const GLuint vaoName )
	{
		this->m_VAO = vaoName;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the name of the VBO (vertex buffer object)
	\param GLuint
	the name of the VBO (vertex buffer object)
	\return
	*/
	/******************************************************************************/
	void GraphicsObject::SetNameOfVBO( const GLuint vboName )
	{
		this->m_VBO = vboName;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the name of the IBO (index buffer object)
	\param GLuint
	the name of the IBO (index buffer object)
	\return
	*/
	/******************************************************************************/
	void GraphicsObject::SetNameOfIBO( const GLuint iboName )
	{
		this->m_IBO = iboName;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the texture id
	\param index
	the index of the texture id array
	\return GLuint
	the texture id
	*/
	/******************************************************************************/
	const GLuint GraphicsObject::GetTextureId( const GLuint index ) const
	{
		return this->m_textureIdArr[index];
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the texture id
	\param textureId
	the texture id
	\param index
	the index of the texture id array
	\return
	*/
	/******************************************************************************/
	void GraphicsObject::SetTextureId( const GLuint textureId, const GLuint index )
	{
		this->m_textureIdArr[index] = textureId;
	}
	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the texture id array size
	\param
	\return GLuint
	the size of the texure id array
	*/
	/******************************************************************************/
	const GLuint GraphicsObject::GetTextureIdArrSize( void ) const
	{
		return this->m_textIdArrSize;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the environment texture id
	\param envTextureId
	the environment texture id
	\return
	*/
	/******************************************************************************/
	void GraphicsObject::SetEnvTextureId( const GLuint envTextureId )
	{
		this->m_envTextureId = envTextureId;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the environment texture id
	\param
	\return GLuint
	the environment texture id
	*/
	/******************************************************************************/
	const GLuint GraphicsObject::GetEnvTextureId( void ) const
	{
		return this->m_envTextureId;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the front face environment texture id
	\param envTextureId
	the environment texture id
	\return
	*/
	/******************************************************************************/
	void GraphicsObject::SetFrontFaceEnvTextureId( const GLuint envTextureId )
	{
		this->m_frontFaceTextureId = envTextureId;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the front face environment texture id
	\param
	\return GLuint
	the environment texture id
	*/
	/******************************************************************************/
	const GLuint GraphicsObject::GetFrontFaceEnvTextureId( void ) const
	{
		return this->m_frontFaceTextureId;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the back face environment texture id
	\param envTextureId
	the environment texture id
	\return
	*/
	/******************************************************************************/
	void GraphicsObject::SetBackFaceEnvTextureId( const GLuint envTextureId )
	{
		this->m_backFaceTextureId = envTextureId;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the back face environment texture id
	\param
	\return GLuint
	the environment texture id
	*/
	/******************************************************************************/
	const GLuint GraphicsObject::GetBackFaceEnvTextureId( void ) const
	{
		return this->m_backFaceTextureId;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the material properties
	\param
	\return Material
	the material properties
	*/
	/******************************************************************************/
	Light::Material & GraphicsObject::GetMaterial( void )
	{
		return this->m_material;
	}


} //end namespace GraphicsFramework