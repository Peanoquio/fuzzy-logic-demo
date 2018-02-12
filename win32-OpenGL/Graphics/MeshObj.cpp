/******************************************************************************/
/*!
\file MeshObj.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 19/12/2011
\brief
This is the mesh object that will contain vertex and index arrays

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "MeshObj.h"


namespace GraphicsFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The constructor for the Normal struct
	\param
	\return
	*/
	/******************************************************************************/
	Normal::Normal( void )
		: m_x( 0.0F ), m_y( 0.0F ), m_z( 0.0F )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The constructor for the BiNormal struct
	\param
	\return
	*/
	/******************************************************************************/
	BiNormal::BiNormal( void )
		: m_x( 0.0F ), m_y( 0.0F ), m_z( 0.0F )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The constructor for the Tangent struct
	\param
	\return
	*/
	/******************************************************************************/
	Tangent::Tangent( void )
		: m_x( 0.0F ), m_y( 0.0F ), m_z( 0.0F )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The constructor for the TextCoord struct
	\param
	\return
	*/
	/******************************************************************************/
	TextureCoord::TextureCoord( void )
		: m_s( 0.0F ), m_t( 0.0F )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The constructor for the Color4 struct
	\param
	\return
	*/
	/******************************************************************************/
	Color4::Color4( void )
		: m_r( 0 ), m_g( 0 ), m_b( 0 ), m_a( 255 )
	{
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The constructor for the Point3 struct
	\param
	\return
	*/
	/******************************************************************************/
	Point3::Point3( void )
		: m_x( 0.0F ), m_y( 0.0F ), m_z( 0.0F )
	{
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The constructor for the Vertex struct
	\param
	\return
	*/
	/******************************************************************************/
	Vertex::Vertex( void )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the color values of the vertex
	\param
	\return
	Color4 - the struct containing the color values
	*/
	/******************************************************************************/
	Color4 Vertex::GetColor( void ) const
	{
		return this->m_color;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the point values of the vertex
	\param
	\return
	Point3 - the struct containing the point values
	*/
	/******************************************************************************/
	Point3 Vertex::GetPoint( void ) const
	{
		return this->m_point;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the s and t values of the texture coordinates
	\param
	\return
	TextureCoord - the struct containing the texture coordinates
	*/
	/******************************************************************************/
	TextureCoord Vertex::GetTextureCoord( void ) const
	{
		return this->m_textureCoord;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the values of the normal
	\param
	\return
	Normal - the struct containing the normal coordinates
	*/
	/******************************************************************************/
	Normal Vertex::GetNormal( void ) const
	{
		return this->m_normal;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the values of the bi-normal
	\param
	\return
	BiNormal - the struct containing the bi-normal coordinates
	*/
	/******************************************************************************/
	BiNormal Vertex::GetBiNormal( void ) const
	{
		return this->m_biNormal;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the values of the tangent
	\param
	\return
	Tangent - the struct containing the tangent coordinates
	*/
	/******************************************************************************/
	Tangent Vertex::GetTangent( void ) const
	{
		return this->m_tangent;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the color values of the vertex
	\param red
	the red color value
	\param green
	the green color value
	\param blue
	the blue color value
	\param alpha
	the alpha value
	\return
	*/
	/******************************************************************************/
	void Vertex::SetColor( const GLubyte red, const GLubyte green, const GLubyte blue, const GLubyte alpha )
	{
		this->m_color.m_r = red;
		this->m_color.m_g = green;
		this->m_color.m_b = blue;
		this->m_color.m_a = alpha;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the x point value of the vertex
	\param x
	the x point value
	\return
	*/
	/******************************************************************************/
	void Vertex::SetPointX( const GLfloat x )
	{
		this->m_point.m_x = x;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the y point value of the vertex
	\param y
	the y point value
	\return
	*/
	/******************************************************************************/
	void Vertex::SetPointY( const GLfloat y )
	{
		this->m_point.m_y = y;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the z point value of the vertex
	\param z
	the z point value
	\return
	*/
	/******************************************************************************/
	void Vertex::SetPointZ( const GLfloat z )
	{
		this->m_point.m_z = z;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the s and t texture coordinate values
	\param s
	the s texture coordinate value
	\param t
	the t texture coordinate value
	\return
	*/
	/******************************************************************************/
	void Vertex::SetTextureCoord( const GLfloat s, const GLfloat t )
	{
		this->m_textureCoord.m_s = s;
		this->m_textureCoord.m_t = t;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the normal values
	\param x
	the x normal coordinate value
	\param y
	the y normal coordinate value
	\param z
	the z normal coordinate value
	\return
	*/
	/******************************************************************************/
	void Vertex::SetNormal( const GLfloat x, const GLfloat y, const GLfloat z )
	{
		this->m_normal.m_x = x;
		this->m_normal.m_y = y;
		this->m_normal.m_z = z;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the bbi-normal values
	\param x
	the x normal coordinate value
	\param y
	the y normal coordinate value
	\param z
	the z normal coordinate value
	\return
	*/
	/******************************************************************************/
	void Vertex::SetBiNormal( const GLfloat x, const GLfloat y, const GLfloat z )
	{
		this->m_biNormal.m_x = x;
		this->m_biNormal.m_y = y;
		this->m_biNormal.m_z = z;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the tangent values
	\param x
	the x normal coordinate value
	\param y
	the y normal coordinate value
	\param z
	the z normal coordinate value
	\return
	*/
	/******************************************************************************/
	void Vertex::SetTangent( const GLfloat x, const GLfloat y, const GLfloat z )
	{
		this->m_tangent.m_x = x;
		this->m_tangent.m_y = y;
		this->m_tangent.m_z = z;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The constructor for the Mesh class
	\param
	\return
	*/
	/******************************************************************************/
	Mesh::Mesh( void )
		: m_VertexArray( 0 ), 
		m_IndexArray( 0 ),
		m_numberOfVertices( 0 ),
		m_numberOfIndices( 0 )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The destructor for the Mesh class
	\param
	\return
	*/
	/******************************************************************************/
	Mesh::~Mesh (void)
	{
		//this->DeleteVertexArray();
		//this->DeleteIndexArray();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Delete the vertex array of the mesh
	\param
	\return
	*/
	/******************************************************************************/
	void Mesh::DeleteVertexArray( void )
	{
		delete [] this->m_VertexArray;
		this->m_VertexArray = 0;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Delete the index array of the mesh
	\param
	\return
	*/
	/******************************************************************************/
	void Mesh::DeleteIndexArray( void )
	{
		delete [] this->m_IndexArray;
		this->m_IndexArray = 0;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Instantiate the vertex array of the mesh
	\param numberOfVertices
	the number of vertices
	\return
	*/
	/******************************************************************************/
	void Mesh::InstantiateVertexArray( const GLuint numberOfVertices )
	{
		this->m_VertexArray = new Vertex[ numberOfVertices ];	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Instantiate the index array of the mesh
	\param numberOfIndices
	the number of indices
	\return
	*/
	/******************************************************************************/
	void Mesh::InstantiateIndexArray( const GLuint numberOfIndices )
	{
		this->m_IndexArray = new GLushort[ numberOfIndices ];
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the vertex array of the object
	\param
	\return
	Vertex * - the vertex array of the object
	*/
	/******************************************************************************/
	Vertex * Mesh::GetVertexArray( void ) const
	{
		return this->m_VertexArray;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the index array of the object
	\param
	\return
	GLushort * - the index array of the object
	*/
	/******************************************************************************/
	GLushort * Mesh::GetIndexArray( void ) const
	{
		return this->m_IndexArray;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the number of vertices in the object
	\param
	\return
	GLuint - the number of vertices
	*/
	/******************************************************************************/
	const GLuint Mesh::GetNumberOfVertices( void ) const
	{
		return this->m_numberOfVertices;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the number of indices in the object
	\param
	\return
	GLuint - the number of indices
	*/
	/******************************************************************************/
	const GLuint Mesh::GetNumberOfIndices( void ) const
	{
		return this->m_numberOfIndices;
	}
			

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Set the number of vertices in the object
	\param numberOfVertices
	the number of vertices
	\return
	*/
	/******************************************************************************/
	void Mesh::SetNumberOfVertices( const GLuint numberOfVertices )
	{
		this->m_numberOfVertices = numberOfVertices;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Set the number of indices in the object
	\param numberOfIndices
	the number of indices
	\return
	*/
	/******************************************************************************/
	void Mesh::SetNumberOfIndices( const GLuint numberOfIndices )
	{
		this->m_numberOfIndices = numberOfIndices;
	}

} //end namespace GraphicsFramework