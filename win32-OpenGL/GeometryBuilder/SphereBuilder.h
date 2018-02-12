/******************************************************************************/
/*!
\file SphereBuilder.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 20/12/2011
\brief
This is the sphere builder that will generate the mesh for the sphere.

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef SPHERE_BUILDER_H
#define SPHERE_BUILDER_H
////////////////////////////////////////////////////////////////////////////////

#include "BaseGeometryBuilder.h"


namespace GraphicsFramework
{
	class SphereBuilder : public BaseGeometryBuilder
	{
	public:
		SphereBuilder( void );
		virtual ~SphereBuilder( void );

		virtual void DrawGeometry( const GLuint VAO ) const;
		virtual void DrawGeometry( const GLuint VAO, const GLuint textureId ) const;

		//option #1
		virtual void ComputeGeometryBoundaryAndOffset( const MeshParameterContainer & meshParameterContainer );
		virtual void LoadGeometryVertices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer );
		virtual void GenerateGeometryIndices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer );

		//option #2
		void ComputeGeometryBoundaryAndOffset( const GLuint slices = 3, const GLuint stacks = 2, 
			const GLfloat radius = 0.5F, const GLfloat height = 1.0F );
		void LoadGeometryVertices( Mesh & mesh, 
			const GLfloat radius = 0.5F, const GLuint slices = 3, const GLuint stacks = 2, const GLfloat verticalPos = 0.0F, 
			const GLubyte red = 0, const GLubyte green = 0, const GLubyte blue = 0, const GLubyte alpha = 255 );
		void GenerateGeometryIndices( Mesh & mesh, 
			const GLuint slices = 3, const GLuint stacks = 2 );

	private:
		GLfloat		m_radius;		
		GLuint		m_slices;
		GLuint		m_stacks;
		GLfloat		m_height;
		GLfloat		m_yLimit;
		GLfloat		m_yOffset;	
		GLfloat		m_radiusOffset;
		GLfloat		m_sTextureOffset;
		GLfloat		m_tTextureOffset;

		//private sub functions
		void ComputeGeometryBoundaryAndOffsetSubFunc( const GLuint stacks = 2, 
			const GLfloat radius = 0.5F, const GLfloat height = 1.0F );

		void LoadGeometryVerticesSubFunc( Mesh & mesh, 
			const GLfloat radius = 0.5F, const GLuint slices = 3, const GLuint stacks = 2, const GLfloat verticalPos = 0.0F, 
			const GLubyte red = 0, const GLubyte green = 0, const GLubyte blue = 0, const GLubyte alpha = 255 );
		void LoadGeometryVerticesSubFuncLessVtx( Mesh & mesh, 
			const GLfloat radius = 0.5F, const GLuint slices = 3, const GLuint stacks = 2, const GLfloat verticalPos = 0.0F, 
			const GLubyte red = 0, const GLubyte green = 0, const GLubyte blue = 0, const GLubyte alpha = 255 );

		void GenerateGeometryIndicesSubFunc( Mesh & mesh, 
			const GLuint slices = 3, const GLuint stacks = 2 );	
		void GenerateGeometryIndicesSubFuncLessIdx( Mesh & mesh, 
			const GLuint slices = 3, const GLuint stacks = 2 );	
	};

} //end namespace GraphicsFramework


#endif
////////////////////////////////////////////////////////////////////////////////