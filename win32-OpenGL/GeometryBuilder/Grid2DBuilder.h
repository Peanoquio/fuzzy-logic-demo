/******************************************************************************/
/*!
\file Grid2DBuilder.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 29/12/2011
\brief
This is the grid builder that will generate the mesh for the grid.

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef GRID_2D_BUILDER_H
#define GRID_2D_BUILDER_H
////////////////////////////////////////////////////////////////////////////////

#include "BaseGeometryBuilder.h"
#include "../Math/Vector4.h"


namespace GraphicsFramework
{
	class Grid2DBuilder : public BaseGeometryBuilder
	{
	public:
		Grid2DBuilder( void );
		virtual ~Grid2DBuilder( void );

		virtual void DrawGeometry( const GLuint VAO ) const;
		virtual void DrawGeometry( const GLuint VAO, const GLuint textureId ) const;

		//option #1
		virtual void ComputeGeometryBoundaryAndOffset( const MeshParameterContainer & meshParameterContainer );
		virtual void LoadGeometryVertices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer );
		virtual void GenerateGeometryIndices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer );

		//option #2
		void ComputeGeometryBoundaryAndOffset( const GLfloat width = 1.0F, const GLfloat height = 1.0F, 
			const GLuint xSubdivisions = 1, const GLuint ySubdivisions = 1 );
		void LoadGeometryVertices( Mesh & mesh, 
			const GLfloat width = 1.0F, const GLfloat height = 1.0F, const GLuint xSubdivisions = 1, const GLuint ySubdivisions = 1,
			const GLubyte red = 0, const GLubyte green = 0, const GLubyte blue = 0, const GLubyte alpha = 255 );
		void GenerateGeometryIndices( Mesh & mesh, const GLuint xSubdivisions = 1, const GLuint ySubdivisions = 1 );

	private:
		GLuint		m_xSubdivisions;
		GLuint		m_ySubdivisions;
		GLfloat		m_width;
		GLfloat		m_height;
		GLfloat		m_xLimit;
		GLfloat		m_xOffset;	
		GLfloat		m_yLimit;
		GLfloat		m_yOffset;	
		GLfloat		m_sTextureOffset;
		GLfloat		m_tTextureOffset;
		GLfloat		m_normalX;
		GLfloat		m_normalY;
		GLfloat		m_normalZ;

		void ComputeGeometryBoundaryAndOffsetSubFunc( const GLfloat width = 1.0F, const GLfloat height = 1.0F, 
			const GLuint xSubdivisions = 1, const GLuint ySubdivisions = 1 );
		void LoadGeometryVerticesSubFunc( Mesh & mesh, 
			const GLuint xSubdivisions = 1, const GLuint ySubdivisions = 1,
			const GLubyte red = 0, const GLubyte green = 0, const GLubyte blue = 0, const GLubyte alpha = 255 );
		void GenerateGeometryIndicesSubFunc( Mesh & mesh, const GLuint xSubdivisions = 1, const GLuint ySubdivisions = 1 );

		const Math::Vector4 ComputePlaneNormal( void ) const;
	};

} // namespace GraphicsFramework


#endif
////////////////////////////////////////////////////////////////////////////////