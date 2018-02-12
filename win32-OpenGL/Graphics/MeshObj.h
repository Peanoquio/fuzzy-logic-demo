/******************************************************************************/
/*!
\file MeshObj.h
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

////////////////////////////////////////////////////////////////////////////////
#ifndef MESHOBJ_H
#define MESHOBJ_H
////////////////////////////////////////////////////////////////////////////////

#include <GL/glew.h>


namespace GraphicsFramework
{
	struct Normal
	{
		GLfloat m_x, m_y, m_z;

		Normal( void );
	};


	struct BiNormal
	{
		GLfloat m_x, m_y, m_z;

		BiNormal( void );
	};


	struct Tangent
	{
		GLfloat m_x, m_y, m_z;

		Tangent( void );
	};


	struct TextureCoord
	{
		GLfloat m_s, m_t;

		TextureCoord( void );
	};


	struct Color4
	{
		GLubyte m_r, m_g, m_b, m_a;

		Color4( void );		
	};


	struct Point3
	{
		GLfloat m_x, m_y, m_z;

		Point3( void );		
	};


	struct Vertex
	{
		Vertex( void );

		Color4			m_color;
		Point3			m_point;
		TextureCoord	m_textureCoord;
		Normal			m_normal;
		BiNormal		m_biNormal;
		Tangent 		m_tangent;

		Color4 GetColor( void ) const;
		Point3 GetPoint( void ) const;
		TextureCoord GetTextureCoord( void ) const;
		Normal GetNormal( void ) const;
		BiNormal GetBiNormal( void ) const;
		Tangent GetTangent( void ) const;

		void SetColor( const GLubyte red, const GLubyte green, const GLubyte blue, const GLubyte alpha );
		void SetPointX( const GLfloat x );
		void SetPointY( const GLfloat y );
		void SetPointZ( const GLfloat z );
		void SetTextureCoord( const GLfloat s, const GLfloat t );
		void SetNormal( const GLfloat x, const GLfloat y, const GLfloat z );
		void SetBiNormal( const GLfloat x, const GLfloat y, const GLfloat z );
		void SetTangent( const GLfloat x, const GLfloat y, const GLfloat z );
	};


	struct MeshParameterContainer
	{
		GLuint		m_slices;
		GLuint		m_stacks;
		GLuint		m_xSubdivisions;
		GLuint		m_ySubdivisions;
		GLfloat		m_width;
		GLfloat		m_height;	
		GLfloat		m_radius;
		GLfloat		m_verticalPos;
		GLfloat		m_ctrPtVertPos;
		GLboolean	m_hasCenterPoint;
		GLboolean	m_invertPlaneNormal;

		GLfloat		m_xLimit;
		GLfloat		m_yLimit;
		GLfloat		m_zLimit;
		GLfloat		m_xOffset;
		GLfloat		m_yOffset;
		GLfloat		m_zOffset;	

		GLubyte		m_red;
		GLubyte		m_green;
		GLubyte		m_blue;
		GLubyte		m_alpha;
	};


	class Mesh
	{
	public:
		Mesh( void );
		~Mesh( void );

		Vertex * GetVertexArray( void ) const;			
		GLushort * GetIndexArray( void ) const;

		const GLuint GetNumberOfVertices( void ) const;	
		const GLuint GetNumberOfIndices( void ) const;
		void SetNumberOfVertices( const GLuint numberOfVertices );
		void SetNumberOfIndices( const GLuint numberOfIndices ); 

		void InstantiateVertexArray( const GLuint numberOfVertices );
		void InstantiateIndexArray( const GLuint numberOfIndices );
		void DeleteVertexArray( void );
		void DeleteIndexArray( void );

	private:
		//geometry vertices and indices
		Vertex *	m_VertexArray;
		GLushort *	m_IndexArray;
		GLuint		m_numberOfVertices;
		GLuint		m_numberOfIndices;
	};

} //end namespace GraphicsFramework

#endif
////////////////////////////////////////////////////////////////////////////////